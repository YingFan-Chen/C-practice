#include <stdio.h>
#include <sys/stat.h>  //mkdir()
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>   //fd_set
#include <unistd.h>
#include <string.h>
#include <map>
#include <arpa/inet.h>
#include <dirent.h>
#include <sqlite3.h>
#include <stdlib.h>

#define server_port 8080
#define max_clients 30

static int callback1(void *data, int argc, char **argv, char **azColName){
    for(int i = 0; i<argc; i++){
        strcat((char*) data, argv[i]);
    }
    return 0;
}

static int callback2(void *data, int argc, char **argv, char **azColName){
    for(int i = 0; i<argc; i++){
        strcat((char*) data, argv[i]);
        strcat((char*) data, " ");
    }
    return 0;
}

static int callback3(void *data, int argc, char **argv, char **azColName){
    if(argc != 0){
        strncat((char*)data, argv[0], 16);
        strcat((char*)data, " : ");
        strncat((char*)data, argv[1], 4097);
    }    
    return 0;
}


int main(){
    int i, flag;
    int master_socket, max_sd, sd, activity, new_socket, valread, addrlen, rc, max_line, file_size;
    char* err;
    char read_buffer[4097], write_buffer[4097], account[17], password[17], /*data1[17], data2[17],*/ dest[100], data[4097], sql[4097];
    char filename[100]; 
    std::string str;
    struct sockaddr_in address;
    fd_set readfds;
    DIR* dir;
    FILE* fp0;
    struct dirent *diread;
    sqlite3* db;
    struct client_info{
        int sock = 0;
        int login = 0;
        int sending = 0;
        int read_line = 1;
        char name[17] = "";
        char friend_name[17] = "";
        char chatroom_name[50] = "";
        FILE* fp1 = nullptr;
    }   clients[max_clients];

    //make dir for server
	mkdir("./server_dir", 0777);

    //sqlite
    rc = sqlite3_open("./server_dir/client_database.db", &db);
    if(rc){
        perror("fail to open database");
        exit(EXIT_FAILURE);
    }
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS accounts(account varchar(16), password varchar(16));", NULL, NULL, &err);
    if(rc != SQLITE_OK){
        perror("fail to creat accounts");
         exit(EXIT_FAILURE);
    }
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS relations(client varchar(16), friends varchar(16), chatroom varchar(50));", NULL, NULL, &err);
    if(rc != SQLITE_OK){
        perror("fail to creat relations");
         exit(EXIT_FAILURE);
    }

    //set master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
	{
		perror("fail to set master socket");
		exit(EXIT_FAILURE);
	}

    //set address 
    address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(server_port);

    //bind master socket
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
        perror("fail to bind master socket");  
        exit(EXIT_FAILURE);  
    }

    //listen master socket
    if (listen(master_socket, max_clients) < 0)
	{
		perror("fail to listen master socket");
		exit(EXIT_FAILURE);
	}
    addrlen = sizeof(address);  

    //body	
	while(1)
	{
		//clear the socket set
		FD_ZERO(&readfds);
	
		//add master socket to set
		FD_SET(master_socket, &readfds);
		max_sd = master_socket;
			
		//add child sockets to set
		for ( i = 0 ; i < max_clients ; i++)
		{
			//socket descriptor
			sd = clients[i].sock;
				
			//if valid socket descriptor then add to read list
			if(sd > 0)
				FD_SET( sd , &readfds);
				
			//highest file descriptor number, need it for the select function
			if(sd > max_sd)
				max_sd = sd;
		}
	
		//wait for an activity on one of the sockets , timeout is NULL 
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
		if ((activity < 0) && (errno!=EINTR))
		{
			perror("fail to select");
			exit(EXIT_FAILURE);
		}
			
		//If something happened on the master socket , then its an incoming connection
		if (FD_ISSET(master_socket, &readfds))
		{
			if ((new_socket = accept(master_socket, (struct sockaddr *) &address, (socklen_t*) &addrlen))<0)
			{
				perror("fail to accept a new socket");
				exit(EXIT_FAILURE);
			}		
				
			//add new socket to array of sockets
			for (i = 0; i < max_clients; i++)
			{
				//if position is empty
				if( clients[i].sock == 0 )
				{
					clients[i].sock = new_socket;
					break;
				}
			}
		}
			
		//else its some IO operation on some other socket
		for (i = 0; i < max_clients; i++)
		{
			sd = clients[i].sock;
				
			if (FD_ISSET( sd , &readfds))
			{
                memset(read_buffer, 0, 4097);
				valread = recv(sd, read_buffer, 4096, 0);   //指令  	

				if (valread == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*) &addrlen);    
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    clients[i].sock = 0;
                    clients[i].fp1 = nullptr;
                    clients[i].login = 0;
                    clients[i].read_line = 0;
                    clients[i].sending = 0;
                    memset(clients[i].name, 0, 17);
                    memset(clients[i].friend_name, 0, 17);
                    memset(clients[i].chatroom_name, 0, 50);
                }

				//login part
				else if( clients[i].login == 0 ){
                    send(sd, "ACK", strlen("ACK"), 0);
                    memset(account, 0 ,17);
                    strncpy(account, read_buffer, 16);
                    memset(read_buffer, 0, 4097);
                    recv(sd, read_buffer, 4096 ,0);
                    memset(password, 0 ,17);
                    strncpy(password, read_buffer, 16);

                    memset(sql, 0,4097);
                    strcat(sql, "SELECT password FROM accounts WHERE account='");
                    strncat(sql, account, 16);
                    strcat(sql, "';");
                    memset(data, 0, 4097); 
                    rc = sqlite3_exec(db, sql, callback1, (void*) data, &err);
                    if(rc != SQLITE_OK){
                        perror("fail to select");
                        exit(EXIT_FAILURE);
                    }
                    
                    if(strlen(data) != 0){
                        if(!strcmp(data, password)){
                            clients[i].login = 1;
                            strncpy(clients[i].name, account, 16);
                            send(sd, "LoginSuccesss", strlen("LoginSuccess"), 0);
                        }else{
                            send(sd, "PasswordWrong", strlen("PasswordWrong"), 0);
                        }
                    }else{
                        memset(sql, 0,4097);
                        strcat(sql, "INSERT INTO accounts (account, password) VALUES('");
                        strncat(sql, account, 16);
                        strcat(sql, "', '");
                        strncat(sql, password, 16);
                        strcat(sql, "');");
                        rc = sqlite3_exec(db, sql, NULL, NULL, &err);
                        if(rc != SQLITE_OK){
                            perror("fail to insert");
                            exit(EXIT_FAILURE);
                        }
                        clients[i].login = 1;
                        strncpy(clients[i].name, account, 16);
                        send(sd, "NewAccountRegister", strlen("NewAccountRegister"), 0);
                    }

                    //Old Version
                    /*fp0 = fopen("./server_dir/account.txt", "a+");
                    flag = 0;
                    while(1){
                        memset(read_buffer, 0, 4097);
                        fgets(read_buffer, 4096, fp0);
                        if(strlen(read_buffer) == 0){
                            flag = 1;
                            break;
                        }
                        memset(data1, 0, 17);
                        memset(data2, 0, 17);
                        strncpy(data1, strtok(read_buffer, " "), 16);
                        strncpy(data2, strtok(NULL, " "), 16);
                        if (!strcmp(data1, account)){
                            if(!strcmp(data2, password)){
                                clients[i].login = 1;
                                strncpy(clients[i].name, account, 16);
                                send(sd, "LoginSuccesss", strlen("LoginSuccess"), 0);
                                break;
                            }else{
                                send(sd, "PasswordWrong", strlen("PasswordWrong"), 0);
                                break;
                            }
                        }
                    }
                    if(flag == 1){
                        memset(write_buffer, 0, 4097);
                        strncat(write_buffer, account, 16);
                        strcat(write_buffer, " ");
                        strncat(write_buffer, password, 16);
                        fwrite(write_buffer, sizeof(char), strlen(write_buffer), fp0);
                        clients[i].login = 1;
                        strncpy(clients[i].name, account, 16);
                        send(sd, "NewAccountRegister", strlen("NewAccountRegister"), 0);
                    }
                    fclose(fp0);*/
                }


                //operation part
                else{
                    
                    if(!strcmp(read_buffer, "(1)")){
                        memset(sql, 0,4097);
                        strcat(sql, "SELECT friends FROM relations WHERE client='");
                        strncat(sql, clients[i].name, 16);
                        strcat(sql, "';");
                        memset(data, 0, 4097); 
                        rc = sqlite3_exec(db, sql, callback2, (void*) data, &err);
                        if(rc != SQLITE_OK){
                            perror("fail to select");
                            exit(EXIT_FAILURE);
                        }
                        strcat(data, "\n");
                        send(sd, data, strlen(data), 0);
                    }
                    else if(!strcmp(read_buffer, "(2)")){
                        send(sd, "ACK", strlen("ACK"), 0);
                        memset(read_buffer, 0, 4097);
                        recv(sd, read_buffer, 4096, 0);

                        memset(sql, 0,4097);
                        strcat(sql, "SELECT account FROM accounts WHERE account='");
                        strncat(sql, read_buffer, 4096);
                        strcat(sql, "';");
                        memset(data, 0, 4097); 
                        rc = sqlite3_exec(db, sql, callback1, (void*) data, &err);
                        if(rc != SQLITE_OK){
                            perror("fail to select");
                            exit(EXIT_FAILURE);
                        }
                        if(strlen(data) != 0){
                            memset(sql, 0, 4097);
                            strcat(sql, "INSERT INTO relations (client, friends, chatroom) VALUES('");
                            strncat(sql, clients[i].name, 16);
                            strcat(sql, "', '");
                            strncat(sql, read_buffer, 16);
                            strcat(sql, "', '");
                            strncat(sql, clients[i].name, 16);
                            strcat(sql, "_");
                            strncat(sql, read_buffer, 16);
                            strcat(sql, "');");
                            rc = sqlite3_exec(db, sql, NULL, NULL, &err);
                            if(rc != SQLITE_OK){
                                perror("fail to insert");
                                exit(EXIT_FAILURE);
                            }

                            memset(sql, 0, 4097);
                            strcat(sql, "INSERT INTO relations (client, friends, chatroom) VALUES('");
                            strncat(sql, read_buffer, 16);
                            strcat(sql, "', '");
                            strncat(sql, clients[i].name, 16);
                            strcat(sql, "', '");
                            strncat(sql, clients[i].name, 16);
                            strcat(sql, "_");
                            strncat(sql, read_buffer, 16);
                            strcat(sql, "');");
                            rc = sqlite3_exec(db, sql, NULL, NULL, &err);
                            if(rc != SQLITE_OK){
                                perror("fail to insert");
                                exit(EXIT_FAILURE);
                            }

                            memset(sql, 0, 4097);
                            strcat(sql, "CREATE TABLE IF NOT EXISTS ");
                            strncat(sql, clients[i].name, 16);
                            strcat(sql, "_");
                            strncat(sql, read_buffer, 16);
                            strcat(sql, " (line INT, sender varchar(255), content varchar(255));");
                            rc = sqlite3_exec(db, sql, NULL, NULL, &err);
                            if(rc != SQLITE_OK){
                                perror("fail to creat chatroom");
                                exit(EXIT_FAILURE);
                            }

                            memset(sql, 0, 4097);
                            strcat(sql, "INSERT INTO ");
                            strncat(sql, clients[i].name, 16);
                            strcat(sql, "_");
                            strncat(sql, read_buffer, 16);
                            strcat(sql, " (line, sender, content) VALUES(0, 'system', 'test\n');");
                            rc = sqlite3_exec(db, sql, NULL, NULL, &err);
                            if(rc != SQLITE_OK){
                                perror("fail to creat chatroom");
                                exit(EXIT_FAILURE);
                            }

                            send(sd, "AddSuccess", strlen("AddSuccess"), 0);
                        }else{
                            send(sd, "AccountNotFound", strlen("AccountNotFound"), 0);
                        }
                    }else if(!strcmp(read_buffer, "(3)")){
                        send(sd, "ACK", strlen("ACK"), 0);
                        memset(read_buffer, 0, 4097);
                        recv(sd, read_buffer, 4096, 0);

                        memset(sql, 0,4097);
                        strcat(sql, "SELECT chatroom FROM relations WHERE client='");
                        strncat(sql, clients[i].name, 16);
                        strcat(sql, "' AND friends='");
                        strncat(sql, read_buffer, 16);
                        strcat(sql, "';");
                        memset(data, 0, 4097);
                        rc = sqlite3_exec(db, sql, callback1, (void*) data, &err);
                        if(rc != SQLITE_OK){
                            perror("fail to select");
                            exit(EXIT_FAILURE);
                        }
                        if(strlen(data) != 0){
                            memset(sql, 0, 4097);
                            strcat(sql, "DELETE FROM relations WHERE chatroom='");
                            strncat(sql, data, 50);
                            strcat(sql, "';");
                            sqlite3_exec(db, sql, NULL, NULL, &err);
                            
                            memset(sql, 0, 4097);
                            strcat(sql, "Drop Table ");
                            strncat(sql, data, 50);
                            strcat(sql, ";");
                            rc = sqlite3_exec(db, sql, NULL, NULL, &err);
                            if(rc != SQLITE_OK){
                                perror("fail to drop");
                                exit(EXIT_FAILURE);
                            }
                            send(sd, "DeleteSuccess", strlen("DeleteSuccess"), 0);
                        }else{
                            send(sd, "AccountNotFound", strlen("AccountNotFound"), 0);
                        }
                    }else if(!strcmp(read_buffer, "(4)")){
                        send(sd, "ACK", strlen("ACK"), 0);
                        memset(read_buffer, 0, 4097);
                        recv(sd, read_buffer, 4097, 0);
                        memset(clients[i].friend_name, 0, 17);
                        strncpy(clients[i].friend_name, read_buffer, 16);

                        memset(sql, 0,4097);
                        strcat(sql, "SELECT chatroom FROM relations WHERE client='");
                        strncat(sql, clients[i].name, 16);
                        strcat(sql, "' AND friends='");
                        strncat(sql, read_buffer, 16);
                        strcat(sql, "';");
                        memset(data, 0, 4097);
                        rc = sqlite3_exec(db, sql, callback1, (void*) data, &err);
                        if(rc != SQLITE_OK){
                            perror("fail to select");
                            exit(EXIT_FAILURE);
                        }
                        if(strlen(data) != 0){                            
                            send(sd, "ChatroomConnect", strlen("ChatroomConnect"), 0);
                            recv(sd, read_buffer, 4096, 0);
                            memset(clients[i].chatroom_name, 0, 50);
                            strncpy(clients[i].chatroom_name, data, 50);

                            memset(sql, 0, 4097);
                            strcat(sql, "SELECT MAX(line) FROM ");
                            strncat(sql, clients[i].chatroom_name, 50);
                            strcat(sql, ";");
                            memset(data, 0 ,4097);
                            rc = sqlite3_exec(db, sql, callback1, (void*) &data, &err);
                            if(rc != SQLITE_OK){
                                perror("fail to select MAX");
                                exit(EXIT_FAILURE);
                            }

                            if(!strcmp(data, "0")){
                                clients[i].read_line = 1;
                                send(sd, "End", strlen("End"), 0);
                            }else{
                                max_line = atoi(data);
                                for(clients[i].read_line = 1; clients[i].read_line <= max_line; clients[i].read_line++){
                                    memset(sql, 0, 4097);
                                    strcat(sql, "SELECT sender,content FROM ");
                                    strncat(sql, clients[i].chatroom_name, 50);
                                    strcat(sql, " WHERE line=");
                                    str = std::to_string(clients[i].read_line);
                                    strncat(sql, str.c_str(), 50);
                                    strcat(sql, ";");
                                    memset(data, 0, 4097);
                                    rc = sqlite3_exec(db, sql, callback3, (void*) &data, &err);
                                    if(rc != SQLITE_OK){
                                        perror("fail to select-1");
                                        exit(EXIT_FAILURE);
                                    }
                                    send(sd, data, strlen(data), 0);
                                    memset(read_buffer, 0, 4097);
                                    recv(sd, read_buffer, 4096, 0);
                                    if(strcmp(read_buffer, "ACK")){
                                        perror("fail to ACK");
                                        exit(EXIT_FAILURE);
                                    }
                                }
                                send(sd, "End",strlen("End"), 0);
                            }

                            //Old Version
                            /*while(1){
                                memset(write_buffer, 0, 4097);
                                fgets(write_buffer, 4096, clients[i].fp1);
                                if(strlen(write_buffer) == 0) break;
                                else{
                                    send(sd, write_buffer, strlen(write_buffer), 0);
                                    memset(read_buffer, 0, 4097);
                                    recv(sd, read_buffer, 4097, 0);
                                    if(strcmp(read_buffer, "ACK")){
                                        perror("error to ACK");
                                        exit(EXIT_FAILURE);
                                    }
                                }
                            }*/
                        }else{
                            send(sd, "NoSuchChatroom", strlen("NoSuchChatroom"), 0);
                        }
                    }else if(!strcmp(read_buffer, "(5)")){
                        send(sd, "ACK", strlen("ACK"), 0);
                        memset(read_buffer, 0, 4097);
                        recv(sd, read_buffer, 4096, 0);
                        memset(filename, 0, 100);
                        strncpy(filename, read_buffer, 100);
                        send(sd, "ACK", strlen("ACK"), 0);
                        memset(read_buffer, 0, 4097);
                        valread = recv(sd, read_buffer, 4096, 0);
                        
                        if(!strcmp(read_buffer, "End"))
                        {
                            memset(sql, 0, 4097);
                            strcat(sql, "SELECT MAX(line) FROM ");
                            strncat(sql, clients[i].chatroom_name, 50);
                            strcat(sql, ";");
                            memset(data, 0 ,4097);
                            rc = sqlite3_exec(db, sql, callback1, (void*) &data, &err);
                            if(rc != SQLITE_OK){
                                perror("fail to select MAX");
                                exit(EXIT_FAILURE);
                            }
                            max_line = atoi(data);

                            memset(sql, 0, 4097);
                            strcat(sql, "INSERT INTO ");
                            strncat(sql, clients[i].chatroom_name, 50);
                            strcat(sql, " (line, sender, content) VALUES(");
                            str = std::to_string(max_line+1);
                            strncat(sql, str.c_str(), 50);
                            strcat(sql, ", '");
                            strncat(sql, clients[i].name, 16);
                            strcat(sql, "', 'send ");
                            strncat(sql, filename, strlen(filename));
                            strcat(sql, "\n');");
                            rc = sqlite3_exec(db, sql, NULL, NULL, &err);
                            if(rc != SQLITE_OK){
                                perror("fail to select");
                                exit(EXIT_FAILURE);
                            }
                        }
                        else
                        {
                            memset(dest, 0, 100);
                            strcat(dest, "./server_dir/");
                            strncat(dest, filename, strlen(filename));
                            clients[i].fp1 = fopen(dest, "a+");
                            fwrite(read_buffer, sizeof(char), valread, clients[i].fp1);
                            send(sd, "ACK", strlen("ACK"), 0);
                            fclose(clients[i].fp1);
                        }
                    }else if(!strcmp(read_buffer, "(6)")){
                        if(clients[i].sending == 0){
                            send(sd, "ACK", strlen("ACK"), 0);
                            memset(read_buffer, 0, 4097);
                            recv(sd, read_buffer, 4096, 0);     //read_buffer = filename

                            /*memset(sql, 0, 4097);
                            strcat(sql, "SELECT MAX(line) FROM ");
                            strncat(sql, clients[i].chatroom_name, 50);
                            strcat(sql, ";");
                            memset(data, 0 ,4097);
                            rc = sqlite3_exec(db, sql, callback1, (void*) &data, &err);
                            if(rc != SQLITE_OK){
                                perror("fail to select MAX");
                                exit(EXIT_FAILURE);
                            }
                            max_line = atoi(data);

                            memset(sql, 0, 4097);
                            strcat(sql, "INSERT INTO ");
                            strncat(sql, clients[i].chatroom_name, 50);
                            strcat(sql, " (line, sender, content) VALUES(");
                            str = std::to_string(max_line+1);
                            strncat(sql, str.c_str(), 50);
                            strcat(sql, ", '");
                            strncat(sql, clients[i].name, 16);
                            strcat(sql, "', 'recv ");
                            strncat(sql, read_buffer, strlen(read_buffer));
                            strcat(sql, "\n');");
                            rc = sqlite3_exec(db, sql, NULL, NULL, &err);
                            if(rc != SQLITE_OK){
                                perror("fail to select");
                                exit(EXIT_FAILURE);
                            }*/

                            memset(dest, 0, 100);
                            strcat(dest, "./server_dir/");
                            strncat(dest, read_buffer, strlen(read_buffer));
                            clients[i].fp1 = fopen(dest, "r");
                            if(clients[i].fp1 == nullptr){
                                send(sd, "FileNotFound", strlen("FileNotFound"), 0);
                            }else{
                                clients[i].sending = 1;
                                valread = 0;

                                fseek(clients[i].fp1, 0, SEEK_END);
                                file_size = ftell(clients[i].fp1);
                                fseek(clients[i].fp1, 0, SEEK_SET);
                                memset(write_buffer, 0, 4097);
                                sprintf(write_buffer, "%d", file_size);
                                send(sd, write_buffer, strlen(write_buffer), 0);
                                recv(sd, read_buffer, 4096, 0);    //ACK

                                memset(write_buffer, 0, 4097);
                                valread = fread(write_buffer, sizeof(char), 4096, clients[i].fp1);
                                if(valread == 0){
                                    send(sd, "End", strlen("End"), 0);
                                    fclose(clients[i].fp1);
                                    clients[i].sending = 0;
                                }else{
                                    send(sd, write_buffer, valread, 0);
                                }
                            }
                        }else{
                            memset(write_buffer, 0, 4097);
                            valread = fread(write_buffer, sizeof(char), 4096, clients[i].fp1);
                            if(valread == 0){
                                send(sd, "End", strlen("End"), 0);
                                fclose(clients[i].fp1);
                                clients[i].sending = 0;
                            }else{
                                send(sd, write_buffer, valread, 0);
                            }
                        }
                    }else if(!strcmp(read_buffer, "(7)")){
                        clients[i].read_line = 1;
                        memset(clients[i].friend_name, 0, 17);
                        memset(clients[i].chatroom_name, 0, 50);
                    }else if(!strcmp(read_buffer, "(8)")){
                        send(sd , "ACK", strlen("ACK"), 0);
                        memset(read_buffer, 0, 4097);
                        recv(sd, read_buffer, 4096, 0);
                        send(sd , "ACK", strlen("ACK"), 0);
                        memset(sql, 0, 4097);
                        strcat(sql, "SELECT MAX(line) FROM ");
                        strncat(sql, clients[i].chatroom_name, 50);
                        strcat(sql, ";");
                        memset(data, 0 ,4097);
                        rc = sqlite3_exec(db, sql, callback1, (void*) &data, &err);
                        if(rc != SQLITE_OK){
                            perror("fail to select MAX");
                            exit(EXIT_FAILURE);
                        }
                        max_line = atoi(data);

                        memset(sql, 0, 4097);
                        strcat(sql, "INSERT INTO ");
                        strncat(sql, clients[i].chatroom_name, 50);
                        strcat(sql, " (line, sender, content) VALUES(");
                        str = std::to_string(max_line+1);
                        strncat(sql, str.c_str(), 50);
                        strcat(sql, ", '");
                        strncat(sql, clients[i].name, 16);
                        strcat(sql, "', '");
                        strcat(sql, read_buffer);
                        strcat(sql, "');");
                        rc = sqlite3_exec(db, sql, NULL, NULL, &err);
                        if(rc != SQLITE_OK){
                            perror("fail to insert");
                            exit(EXIT_FAILURE);
                        }
                    }else if(!strcmp(read_buffer, "(9)")){
                        memset(sql, 0, 4097);
                        strcat(sql, "SELECT MAX(line) FROM ");
                        strncat(sql, clients[i].chatroom_name, 50);
                        strcat(sql, ";");
                        memset(data, 0 ,4097);
                        rc = sqlite3_exec(db, sql, callback1, (void*) &data, &err);
                        if(rc != SQLITE_OK){
                            perror("fail to select MAX");
                            exit(EXIT_FAILURE);
                        }

                        if(strcmp(data, "0")){
                            max_line = atoi(data);
                            while(clients[i].read_line <= max_line){
                                memset(sql, 0, 4097);
                                strcat(sql, "SELECT sender,content FROM ");
                                strncat(sql, clients[i].chatroom_name, 50);
                                strcat(sql, " WHERE line=");
                                str = std::to_string(clients[i].read_line);
                                strncat(sql, str.c_str(), 50);
                                strcat(sql, " AND sender='");
                                strncat(sql, clients[i].friend_name, 16);
                                strcat(sql, "';");
                                memset(data, 0, 4097);
                                rc = sqlite3_exec(db, sql, callback3, (void*) &data, &err);
                                if(rc != SQLITE_OK){
                                    perror("fail to select");
                                    exit(EXIT_FAILURE);
                                }
                                if(strlen(data) != 0){
                                    send(sd, data, strlen(data), 0);
                                    memset(read_buffer, 0, 4097);
                                    recv(sd, read_buffer, 4097, 0);
                                    if(strcmp(read_buffer, "ACK")){
                                        perror("fail to ACK");
                                        exit(EXIT_FAILURE);
                                    }
                                }
                                
                                clients[i].read_line++;
                            }
                        }
                        send(sd, "End", strlen("End"), 0);
                    }
                }	
			}
		}
	}
    sqlite3_close(db);
}
