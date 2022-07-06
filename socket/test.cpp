#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sqlite3.h>
#include <netinet/in.h>
#include<unistd.h>

using namespace std;
#define server_port 8080
#define max_clients 1000

class client{
    public:
        int sock;
        bool login;
        client(int _sock) : sock(_sock){
            login = false;
        }
        inline bool operator== (const client &i) const{
            return sock == i.sock;
        }
};

sqlite3* set_environment();
void set_address(struct sockaddr_in &);
int set_master_socket(struct sockaddr*);
void poll(vector<client> &, int, struct sockaddr*);
void client_operation(client &, struct sockaddr*, vector<client> &);


int main(){
    struct sockaddr_in address;
    sqlite3 *db;
    int master_sock;
    vector<client> clients;

    db = set_environment();

    set_address(address);

    master_sock = set_master_socket((struct sockaddr *) &address);

    while(true){
        poll(clients, master_sock, (struct sockaddr *) &address);
    }

    
}

sqlite3* set_environment(){
    sqlite3 *db;
    char *err;
    int rc;

    mkdir("./server_dir/", 0755);

    rc = sqlite3_open("./server_dir/client_database.db", &db);
    if(rc){
        fprintf(stderr, "Fail to open the database : %s\n", sqlite3_errmsg(db));
    }else{
        fprintf(stderr, "Open database successfully....\n");
    }

    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS accounts(account varchar(128), password varchar(128));", NULL, NULL, &err);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Fail to create account table : %s\n", err);
    }else{
        fprintf(stderr, "Create account table successfully....\n");
    }

    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS relations(client varchar(128), friends varchar(128), chatroom varchar(1024));", NULL, NULL, &err);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Fail to create relation table : %s\n", err);
    }else{
        fprintf(stderr, "Create relation table successfully....\n");
    }

    return db;
}

void set_address(struct sockaddr_in &address){
    address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(server_port);
}

int set_master_socket(struct sockaddr *address){
    int master_sock;
    int opt = 1;

    if((master_sock = socket(AF_INET , SOCK_STREAM , 0)) == 0){
        perror("Fail to socket ");
    }else{
        fprintf(stderr, "Socket successfully....\n");
    }

    if(setsockopt(master_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("Fail to setsockopt ");
    }else{
        fprintf(stderr, "Setsockopt successfully....\n");
    }

    if(bind(master_sock, address, sizeof(*address)) < 0){  
        perror("Fail to bind ");
    }else{
        fprintf(stderr, "Bind successfully....\n");
    }

    if(listen(master_sock, max_clients) < 0){
        perror("Fail to listen ");
    }else{
        fprintf(stderr, "Listen successfully....\n");
    }

    return master_sock;
}

void poll(vector<client> &clients, int master_sock, struct sockaddr *address){
    int max_fd, new_sock;
    int addr_len = sizeof(*address);
    fd_set readfds;

    FD_ZERO(&readfds);

    FD_SET(master_sock, &readfds);
    max_fd = master_sock;

    for(auto &i : clients){
        FD_SET(i.sock, &readfds);
        max_fd = max(max_fd, i.sock);
    }

    if(select(max_fd + 1, &readfds, NULL, NULL, NULL) < 0 and errno != EINTR){
        perror("Fail to select ");
    }else{
        fprintf(stderr, "Select successfully....\n");
    }

    if(FD_ISSET(master_sock, &readfds)){
        if((new_sock = accept(master_sock, address, (socklen_t*) &addr_len)) < 0){
            perror("Fail to accept.... ");
        }else{
            clients.push_back(client{new_sock});
            fprintf(stderr, "Accept successfully....\n");
        }
    }

    for(auto &i : clients){
        if(FD_ISSET(i.sock, &readfds)){
            /**************************************************/
            client_operation(i, address, clients);
        }
    }
}

void client_operation(client &client_obj, struct sockaddr *address, vector<client> &clients){
    int valread;
    int addr_len = sizeof(*address), sock = client_obj.sock;
    char read_buffer[4096];

    memset(read_buffer, 0, 4096);
    valread = recv(sock, read_buffer, 4096, 0);

    //This means someone disconnected
    if(valread == 0){
        getpeername(sock , (struct sockaddr*)&address , (socklen_t*) &addr_len); 
        close(sock);
        auto iter= find(clients.begin(), clients.end(), client_obj);
        clients.erase(iter);
    }
    else if(client_obj.login == false){
        fprintf(stderr, "%s\n", read_buffer);
        
    }
}