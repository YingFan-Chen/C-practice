#include <stdio.h>
#include <sys/stat.h>  //mkdir()
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>

#define server_port 8080

void history(int sock){
    char buffer[4097];
    send(sock, "(9)", strlen("(9)"), 0);
    while(1)
    {
        memset(buffer, 0, 4097);
        recv(sock, buffer, 4096, 0);
        if(!strcmp(buffer, "End")) break;
        else{
            printf("%s", buffer);
            send(sock, "ACK", strlen("ACK"), 0);
        }
    }
}


int main(int argc, char *argv[]){
    int sock, valread;
    char account[17], password[17], read_buffer[4097], write_buffer[4097], tmp[4097], inst[100], filename[100], path[100];
    struct sockaddr_in addr;
    FILE* fp;
    fd_set readfds;
    struct timeval tv;
    //==========================================//
    int client_port = atoi(argv[argc-1]);
    int master_socket, new_socket, service = 0, file_size = 0, i;
    struct sockaddr_in new_address;
    int addrlen = sizeof(new_address);
    char request[10241] , response[10241], deletelist[10241], chatlist[10241], tmp1[4097], firstpart[50], secondpart[50], tmp2[50];
    char firstline[4096], lastline[4096], header[1024];
    char method[1024], object[1024], name[1024], value[1024];
    char *tmp_buffer;

    //make dir for client
	mkdir("client_dir", 0777);
	
	//set the client socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to set socket");
		exit(EXIT_FAILURE);
	}

    //set the address
	addr.sin_family = AF_INET;
	addr.sin_port = htons(server_port);
	if(inet_pton(AF_INET, (const char*) "127.0.0.1", &addr.sin_addr)<=0)
	{
		perror("fail to set address");
		exit(EXIT_FAILURE);
	}

    //connect the socket
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("fail to connect to server");
		exit(EXIT_FAILURE);
	}

    //Login
    while(1){
        memset(account,0,17);
        memset(password,0,17);

        printf("Please enter your account:\n");
        fgets(account, 16, stdin);
        printf("Please enter your password:\n");
        fgets(password, 16, stdin); 

        send(sock, account, strlen(account)-1, 0);    
        memset(read_buffer, 0, 4097);
        recv(sock, read_buffer, 4096, 0);   
        if(strcmp(read_buffer, "ACK")){
            perror("error to ACK");
            exit(EXIT_FAILURE);
        }

        send(sock, password, strlen(password)-1, 0);
        memset(read_buffer, 0, 4097);
        recv(sock, read_buffer, 4096, 0);
        if(!strcmp(read_buffer, "LoginSuccess")){
            printf("Login Successfully!\n\n");
            break;
        }if(!strcmp(read_buffer, "NewAccountRegister")){
            printf("New Account Register Successfully!\n\n");
            break;
        }else if(!strcmp(read_buffer, "PasswordWrong")){
            printf("Password Wrong. Please try again!\n\n");
        }else{
            perror("error to login");
            exit(EXIT_FAILURE);
        }
    }

    printf("Choose the mode:\n");
    printf("(1) Command Line\n");
    printf("(2) Browser\n");
    memset(read_buffer, 0, 4097);
    fgets(read_buffer, 4096, stdin);
    printf("\n");
    if(!strcmp(read_buffer, "1\n"))
    {
        while(1){
            printf("Home\n");
            printf("(1) List all friends\n");
            printf("(2) Add friend\n");
            printf("(3) Delete friend\n");
            printf("(4) Choose a chat room\n");
            memset(read_buffer, 0, 4097);
            fgets(read_buffer, 4096, stdin);   
            if(!strcmp(read_buffer, "1\n")){
                send(sock, "(1)", strlen("(1)"), 0);
                memset(read_buffer, 0, 4097);
                recv(sock, read_buffer, 4096, 0);
                printf("%s\n", read_buffer);
            }
            else if(!strcmp(read_buffer, "2\n")){
                printf("Please enter the friend's account to be added:\n");
                memset(write_buffer, 0, 4097);
                fgets(write_buffer, 4097, stdin);

                send(sock, "(2)", strlen("(2)"), 0);
                memset(read_buffer, 0, 4097);
                recv(sock, read_buffer, 4096, 0);
                if(strcmp(read_buffer, "ACK")){
                    perror("error to ACK");
                    exit(EXIT_FAILURE);
                }
                send(sock, write_buffer, strlen(write_buffer)-1, 0);
                memset(read_buffer, 0, 4097);
                recv(sock, read_buffer, 4096, 0);
                if(!strcmp(read_buffer, "AddSuccess")){
                    printf("Add Successfully!\n\n");
                }else if(!strcmp(read_buffer, "AccountNotFound")){
                    printf("No Such Account.\n\n");
                }else{
                    perror("fail to add friend");
                    exit(EXIT_FAILURE);
                }
            }
            else if(!strcmp(read_buffer, "3\n")){
                printf("Please enter the friend's account to be deleted:\n");
                memset(write_buffer, 0, 4097);
                fgets(write_buffer, 4097, stdin);

                send(sock, "(3)", strlen("(3)"), 0);
                memset(read_buffer, 0, 4097);
                recv(sock, read_buffer, 4096, 0);
                if(strcmp(read_buffer, "ACK")){
                    perror("error to ACK");
                    exit(EXIT_FAILURE);
                }
                send(sock, write_buffer, strlen(write_buffer)-1, 0);
                memset(read_buffer, 0, 4097);
                recv(sock, read_buffer, 4096, 0);
                if(!strcmp(read_buffer, "DeleteSuccess")){
                    printf("Delete Successfully!\n\n");
                }else if(!strcmp(read_buffer, "AccountNotFound")){
                    printf("No Such Friend.\n\n");
                }else{
                    perror("fail to delete friend");
                    exit(EXIT_FAILURE);
                }
            }else if(!strcmp(read_buffer, "4\n")){
                printf("Choose a chatroom:\n");
                memset(write_buffer, 0, 4097);
                fgets(write_buffer, 4097, stdin);
                send(sock, "(4)", strlen("(4)"), 0);
                memset(read_buffer, 0, 4097);
                recv(sock, read_buffer, 4096, 0);
                if(strcmp(read_buffer, "ACK")){
                    perror("error to ACK");
                    exit(EXIT_FAILURE);
                }

                send(sock, write_buffer, strlen(write_buffer)-1, 0);
                memset(read_buffer, 0, 4097);
                recv(sock, read_buffer, 4096, 0);
                send(sock, "ACK", strlen("ACK"), 0);
                if(!strcmp(read_buffer, "ChatroomConnect")){
                    printf("\n");
                    printf("===========================================================\n");
                    while(1){
                        memset(read_buffer, 0, 4097);
                        recv(sock, read_buffer, 4097, 0);
                        if(!strcmp(read_buffer, "End")) break;
                        else{
                            printf("%s", read_buffer);
                            send(sock, "ACK", strlen("ACK"), 0);
                        }
                    }
                    printf("===========================================================\n");
                    printf("Chatroom Instructions:\n");
                    printf("Enter 'send filename' to send a file.\n");
                    printf("Enter 'recv filename' to receive a file.\n");
                    printf("Enter 'exit' to exit the chatroom.\n");
                    printf("Otherwise, message will send.\n");
                    printf("===========================================================\n");

                    while(1)
                    {
                        tv.tv_sec = 2;
                        tv.tv_sec = 0;
                        FD_ZERO(&readfds);
                        FD_SET(STDIN_FILENO, &readfds);
                        select(STDIN_FILENO+1, &readfds, NULL, NULL, &tv);
                        if(FD_ISSET(STDIN_FILENO, &readfds))
                        {
                            
                            memset(write_buffer, 0, 4097);
                            fgets(write_buffer, 4097, stdin);
                            
                            memset(tmp, 0, 4097);
                            strncpy(tmp, write_buffer, strlen(write_buffer)-1);
                            memset(inst, 0, 100);
                            
                            strncpy(inst, strtok(tmp, " "), 100);
                            if(!strcmp(inst, "send")){

                                memset(filename, 0, 100);
                                strncpy(filename, strtok(NULL, " "), 100);
                                memset(path, 0, 100);
                                strcpy(path, "./client_dir/");
                                strncat(path, filename, 100);
                                fp = fopen(path, "r");
                                if(fp == nullptr)
			                    {
				                    printf("System : No Such File.\n");
			                    }else{
                                    valread = 0;
                                    while(1)
                                    {
                                        memset(write_buffer, 0, 4097);
                                        valread = fread(write_buffer, sizeof(char), 4096, fp);
                                
                                        if(valread == 0){
                                            send(sock, "(5)", strlen("(5)"), 0);
                                            memset(read_buffer, 0, 4097);
                                            recv(sock, read_buffer, 4096, 0);
                                            if(strcmp(read_buffer, "ACK")){
                                                perror("error to ACK");
                                                exit(EXIT_FAILURE);
                                            }

                                            send(sock, filename, strlen(filename), 0);
                                            memset(read_buffer, 0, 4097);
                                            recv(sock, read_buffer, 4096, 0);
                                            if(strcmp(read_buffer, "ACK")){
                                                perror("error to ACK");
                                                exit(EXIT_FAILURE);
                                            }

                                            send(sock, "End", strlen("End"), 0);
                                            break;
                                        } 
                                        else{
                                            send(sock, "(5)", strlen("(5)"), 0);
                                            memset(read_buffer, 0, 4097);
                                            recv(sock, read_buffer, 4096, 0);
                                            if(strcmp(read_buffer, "ACK")){
                                                perror("error to ACK");
                                                exit(EXIT_FAILURE);
                                            }

                                            send(sock, filename, strlen(filename), 0);
                                            memset(read_buffer, 0, 4097);
                                            recv(sock, read_buffer, 4096, 0);
                                            if(strcmp(read_buffer, "ACK")){
                                                perror("error to ACK");
                                                exit(EXIT_FAILURE);
                                            }
                                    
                                            send(sock, write_buffer, valread, 0);
                                            memset(read_buffer, 0, 4097);
                                            recv(sock, read_buffer, 4096, 0);
                                            if(strcmp(read_buffer, "ACK")){
                                                perror("error to ACK");
                                                exit(EXIT_FAILURE);
                                            }
                                        }
                                    }
                                    fclose(fp);
                                    printf("System : Send Successfully.\n");
                                }

                            }else if(!strcmp(inst, "recv")){
                                memset(filename, 0, 100);
                                strncpy(filename, strtok(NULL, " "), 100);

                                send(sock, "(6)", strlen("(6)"), 0);
                                memset(read_buffer, 0, 4097);
                                recv(sock, read_buffer, 4096, 0);
                                if(strcmp(read_buffer, "ACK")){
                                    perror("error to ACK");
                                    exit(EXIT_FAILURE);
                                }

                                send(sock, filename, strlen(filename), 0);

                                memset(read_buffer, 0, 4097);
                                recv(sock, read_buffer, 4096, 0);
                                if(!strcmp(read_buffer, "FileNotFound")){
                                    printf("File Not Found.\n");
                                }else{
                                    file_size = atoi(read_buffer);
                                    send(sock, "ACK", strlen("ACK"), 0);
                                    memset(read_buffer, 0, 4097);
                                    valread = recv(sock, read_buffer, 4096, 0);

                                    memset(path, 0, 100);
                                    strcat(path, "./client_dir/");
                                    strncat(path, filename, strlen(filename));
                                    fp = fopen(path, "a+");
                                    if(!strcmp(read_buffer, " End")){
                                        fclose(fp);
                                        printf("System : Receive Successfully.\n");
                                    }else{
                                        fwrite(read_buffer, sizeof(char), valread, fp);
                                    }                            
                                    while(1){
                                        send(sock, "(6)", strlen("(6)"), 0);
                                        memset(read_buffer, 0, 4097);
                                        valread = recv(sock, read_buffer, 4096, 0);
                                        if(!strcmp(read_buffer, "End")){
                                            fclose(fp);
                                            printf("System : Receive Successfully.\n");
                                            break;
                                        }else{
                                            fwrite(read_buffer, sizeof(char), valread, fp);
                                        } 
                                    }
                                }

                            }else if(!strcmp(inst, "exit")){
                                send(sock, "(7)", strlen("(7)"), 0);
                                printf("\n");
                                break;
                            }else{
                                send(sock, "(8)", strlen("(8)"), 0);
                                memset(read_buffer, 0, 4097);
                                recv(sock, read_buffer, 4096, 0);
                                if(strcmp(read_buffer, "ACK")){
                                    perror("error to ACK");
                                    exit(EXIT_FAILURE);
                                }
                                send(sock, write_buffer, strlen(write_buffer), 0);
                                memset(read_buffer, 0, 4097);
                                recv(sock, read_buffer, 4096, 0);
                                if(strcmp(read_buffer, "ACK")){
                                    perror("error to ACK");
                                    exit(EXIT_FAILURE);
                                }
                            }
                        }else{
                            history(sock);
                        }
                    }
                }else if(!strcmp(read_buffer, "NoSuchChatroom")){
                    printf("No Such Chatroom.\n\n");
                }else{
                    perror("fail to connect to chatroom");
                    exit(EXIT_FAILURE);
                }
            }
        } 
    }else if(!strcmp(read_buffer, "2\n")){
        if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
	    {
		    perror("fail to set master socket");
		    exit(EXIT_FAILURE);
	    }

        new_address.sin_family = AF_INET;
	    new_address.sin_addr.s_addr = INADDR_ANY;
	    new_address.sin_port = htons(client_port);

        if (bind(master_socket, (struct sockaddr *) &new_address, sizeof(new_address))<0)  
        {  
            perror("fail to bind master socket");  
            exit(EXIT_FAILURE);  
        }

        if (listen(master_socket, 15) < 0)
	    {
		    perror("fail to listen master socket");
		    exit(EXIT_FAILURE);
	    }

        if ((new_socket = accept(master_socket, (struct sockaddr *)&new_address, (socklen_t*) &addrlen))<0)
	    {
		    perror("fail to accept a new socket");
		    exit(EXIT_FAILURE);
	    }

        //===========================//

        while(1){
            memset(request, 0, 10241);
            recv(new_socket, request, 10240, 0);
            puts(request);
            

            send(sock, "(1)", strlen("(1)"), 0);
            memset(read_buffer, 0, 4096);
            recv(sock, read_buffer, 4096, 0);
            read_buffer[strlen(read_buffer)-1] = '\0';

            memset(deletelist, 0, 10241);
            memset(chatlist, 0, 10241);
            tmp_buffer = strtok(read_buffer, " ");
            while(tmp_buffer != nullptr){
                memset(tmp, 0, 4097);
                sprintf(tmp, "<input type='radio' name='deletefriend' value='%s'> %s<br>", tmp_buffer, tmp_buffer);
                strncat(deletelist, tmp, strlen(tmp));
            
                memset(tmp, 0, 4097);
                sprintf(tmp, "<input type='radio' name='chatfriend' value='%s'> %s<br>", tmp_buffer, tmp_buffer);
                strncat(chatlist, tmp, strlen(tmp));

                tmp_buffer = strtok(NULL, " ");
            }

            memset(firstline, 0, 4096);
            tmp_buffer = strtok(request, "\r\n");
            strcpy(firstline, tmp_buffer);
            while(tmp_buffer != nullptr){
                memset(lastline, 0, 4096);
                strcpy(lastline, tmp_buffer);
                tmp_buffer = strtok(NULL, "\r\n");
            }
            memset(method, 0, 1024);
            strcpy(method, strtok(firstline, " "));
            memset(object, 0, 1024);
            strcpy(object, strtok(NULL, " "));
        
            if(!strcmp(method, "GET")){
                if(!strcmp(object, "/favicon.ico")){
                    memset(response, 0, 10241);
                    fp = fopen("./icon.jpg", "r");
                    fseek(fp, 0, SEEK_END);
                    file_size = ftell(fp);
                    fseek(fp, 0, SEEK_SET);
                    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: image/jpg\r\nContent-Length: %d\r\n\r\n", file_size);
                    send(new_socket, response, strlen(response), 0);
                    memset(response, 0, 10241);
                    while(valread = fread(response, sizeof(char), 10240, fp)){
                        send(new_socket, response, valread, 0);
                        memset(response, 0, 10241);
                    }
                    fclose(fp);
                }else if(!strcmp(object, "/home")){
                    memset(response, 0, 10241);
                    fp = fopen("./home.html", "r");
                    fseek(fp, 0, SEEK_END);
                    file_size = ftell(fp);
                    fseek(fp, 0, SEEK_SET);
                    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: %d\r\n\r\n", file_size);
                    send(new_socket, response, strlen(response), 0);
                    memset(response, 0, 10241);
                    while(valread = fread(response, sizeof(char), 10240, fp)){
                        send(new_socket, response, valread, 0);
                        memset(response, 0, 10241);
                    }
                    fclose(fp);

                }else if(!strcmp(object, "/deletelist")){
                    memset(header, 0, 1024);
                    sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: %ld\r\n\r\n", strlen(deletelist));
                    send(new_socket, header, strlen(header), 0);
                    send(new_socket, deletelist, strlen(deletelist), 0);

                }else if(!strcmp(object, "/chatlist")){
                    memset(header, 0, 1024);
                    sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: %ld\r\n\r\n", strlen(chatlist));
                    send(new_socket, header, strlen(header), 0);
                    send(new_socket, chatlist, strlen(chatlist), 0);

                }else{
                    memset(tmp, 0, 4097);
                    for(i = 1; i < strlen(object); i++){
                        tmp[i-1] = object[i];
                    }
                    send(sock, "(6)", strlen("(6)"), 0);
                    recv(sock, read_buffer, 4096, 0);   //ACK
                    send(sock, tmp, strlen(tmp), 0);
                    memset(read_buffer, 0, 4097);
                    recv(sock, read_buffer, 4096, 0);
                    file_size = atoi(read_buffer);
                    send(sock, "ACK", strlen("ACK"), 0);

                    memset(header, 0, 1024);
                    sprintf(header, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n", file_size);
                    send(new_socket, header, strlen(header), 0);

                    memset(read_buffer, 0, 4097);
                    valread = recv(sock, read_buffer, 4096, 0);
                    while(strcmp(read_buffer, "End")){
                        send(new_socket, read_buffer, valread, 0);
                        send(sock, "(6)", strlen("(6)"), 0);
                        memset(read_buffer, 0, 4097);
                        valread = recv(sock, read_buffer, 4096, 0);
                    }

                }
            }else if(!strcmp(method, "POST")){
                memset(name, 0, 1024);
                strcpy(name, strtok(lastline, "="));
                memset(value, 0, 1024);
                strcpy(value, strtok(NULL, "="));

                if(!strcmp(object, "/add")){
                    memset(response, 0, 10241);
                    fp = fopen("./add.html", "r");
                    fseek(fp, 0, SEEK_END);
                    file_size = ftell(fp);
                    fseek(fp, 0, SEEK_SET);
                    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: %d\r\n\r\n", file_size);
                    send(new_socket, response, strlen(response), 0);
                    memset(response, 0, 10241);
                    while(valread = fread(response, sizeof(char), 10240, fp)){
                        send(new_socket, response, valread, 0);
                        memset(response, 0, 10241);
                    }
                    fclose(fp);

                }else if(!strcmp(object, "/delete")){
                    memset(response, 0, 10241);
                    fp = fopen("./delete.html", "r");
                    fseek(fp, 0, SEEK_END);
                    file_size = ftell(fp);
                    fseek(fp, 0, SEEK_SET);
                    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: %d\r\n\r\n", file_size);
                    send(new_socket, response, strlen(response), 0);
                    memset(response, 0, 10241);
                    while(valread = fread(response, sizeof(char), 10240, fp)){
                        send(new_socket, response, valread, 0);
                        memset(response, 0, 10241);
                    }
                    fclose(fp);

                }else if(!strcmp(object, "/chat")){
                    memset(response, 0, 10241);
                    fp = fopen("./chat.html", "r");
                    fseek(fp, 0, SEEK_END);
                    file_size = ftell(fp);
                    fseek(fp, 0, SEEK_SET);
                    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: %d\r\n\r\n", file_size);
                    send(new_socket, response, strlen(response), 0);
                    memset(response, 0, 10241);
                    while(valread = fread(response, sizeof(char), 10240, fp)){
                        send(new_socket, response, valread, 0);
                        memset(response, 0, 10241);
                    }
                    fclose(fp);

                }else if(!strcmp(object, "/home")){
                    memset(response, 0, 10241);
                    fp = fopen("./home.html", "r");
                    fseek(fp, 0, SEEK_END);
                    file_size = ftell(fp);
                    fseek(fp, 0, SEEK_SET);
                    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: %d\r\n\r\n", file_size);
                    send(new_socket, response, strlen(response), 0);
                    memset(response, 0, 10241);
                    while(valread = fread(response, sizeof(char), 10240, fp)){
                        send(new_socket, response, valread, 0);
                        memset(response, 0, 10241);
                    }
                    fclose(fp);

                    if(!strcmp(name, "addfriend")){
                        send(sock, "(2)", strlen("(2)"), 0);
                        recv(sock, read_buffer, 4096, 0);
                        send(sock, value, strlen(value), 0);
                        recv(sock, read_buffer, 4096, 0);                        
                    }else if(!strcmp(name, "deletefriend")){
                        send(sock, "(3)", strlen("(3)"), 0);
                        recv(sock, read_buffer, 4096, 0);
                        send(sock, value, strlen(value), 0);
                        recv(sock, read_buffer, 4096, 0);    
                    }else if(!strcmp(name, "chatmessage")){
                        for(i = 0 ; i < strlen(value); i++){
                            if(value[i] == '+') value[i] = ' ';
                        }
                        strcat(value, "\n");
                        send(sock, "(8)", strlen("(8)"), 0);
                        recv(sock, read_buffer, 4096, 0);   //ACK
                        send(sock, value, strlen(value), 0);
                        recv(sock, read_buffer, 4096, 0);   //ACK
                    }

                }else if(!strcmp(object, "/chatroom")){
                    memset(response, 0, 10241);
                    fp = fopen("./chatroom.html", "r");
                    fseek(fp, 0, SEEK_END);
                    file_size = ftell(fp);
                    fseek(fp, 0, SEEK_SET);
                    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: %d\r\n\r\n", file_size);
                    send(new_socket, response, strlen(response), 0);
                    memset(response, 0, 10241);
                    while(valread = fread(response, sizeof(char), 10240, fp)){
                        send(new_socket, response, valread, 0);
                        memset(response, 0, 10241);
                    }
                    fclose(fp);

                    memset(request, 0, 10241);
                    recv(new_socket, request, 10240, 0);
                    puts(request);

                    send(sock, "(4)", strlen("(4)"), 0);
                    recv(sock, read_buffer, 4096, 0);  //ACK
                    send(sock, value, strlen(value), 0);  //name
                    recv(sock, read_buffer, 4096, 0);   //chatroomconnect
                    send(sock, "ACK", strlen("ACK"), 0);
                    memset(read_buffer, 0, 4096);
                    recv(sock, read_buffer, 4096, 0);
                    
                    if(!strcmp(read_buffer, "End")){
                        memset(response, 0, 10241);
                        strcpy(response, "<br>");
                        memset(header, 0, 1024);
                        sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: %ld\r\n\r\n", strlen(response));\
                        send(new_socket, header, strlen(header), 0);
                        send(new_socket, response, strlen(response), 0);
                    }else{
                        memset(response, 0, 10241);
                        while(strcmp(read_buffer, "End")){
                            send(sock, "ACK", strlen("ACK"), 0);
                            read_buffer[strlen(read_buffer)-1] = '\0';
                            memset(tmp, 0, 4097);

                            memset(tmp1, 0, 4097);
                            strncpy(tmp1, read_buffer, 4096);
                            
                            strtok(tmp1, " ");
                            strtok(NULL, " ");
                            memset(tmp2, 0, 50);
                            strncpy(tmp2, strtok(NULL, " "), 50);
                            if(!strcmp(tmp2, "send")){
                                memset(firstpart, 0, 50);
                                memset(secondpart, 0, 50);
                                strncpy(firstpart, strtok(NULL, "."), 50);
                                strncpy(secondpart, strtok(NULL, "."), 50);

                                if((!strcmp(secondpart, "jpg")) || (!strcmp(secondpart, "png"))){
                                    sprintf(tmp, "<p>%s</p><img src='%s.%s' alt='%s.%s'><br>", read_buffer, firstpart, secondpart, firstpart, secondpart);
                                    strncat(response, tmp, strlen(tmp));
                                }else{
                                    sprintf(tmp, "<p>%s</p><a href = '%s.%s' download='%s.%s'>%s.%s<a>", read_buffer, firstpart, secondpart, firstpart, secondpart, firstpart, secondpart);
                                    strncat(response, tmp, strlen(tmp));
                                }
                            }else if(!strcmp(tmp2, "recv")){

                            }else{
                                sprintf(tmp, "<p>%s</p>", read_buffer);
                                strncat(response, tmp, strlen(tmp));
                            }
                            memset(read_buffer, 0, 4096);
                            recv(sock, read_buffer, 4096, 0);
                            printf("%s", read_buffer);
                        }
                        memset(header, 0, 1024);
                        sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: %ld\r\n\r\n", strlen(response));\
                        send(new_socket, header, strlen(header), 0);
                        send(new_socket, response, strlen(response), 0);
                    }
                }
            }
        }
    }
}