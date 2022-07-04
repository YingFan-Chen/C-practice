#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sqlite3.h>
using namespace std;
#define server_port 8080
#define max_client 1000

sqlite3* setup_environment();
int setup_master_socket(struct sockaddr*);

int main(){
    struct sockaddr_in address;
    sqlite3 *db;
    int master_sock;

    db = setup_environment();

    address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(server_port);

    master_sock = setup_master_socket((struct sockaddr *) &address);

    
}

sqlite3* setup_environment(){
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

int setup_master_socket(struct sockaddr *address){
    int master_sock;
    int opt = 1;
    struct sockaddr_in address;

    if(master_sock = socket(AF_INET , SOCK_STREAM , 0)) == 0){
        perror("Fail to socket");
    }else{
        fprintf(stderr, "Socket successfully....\n");
    }

    if(setsockopt(master_sock, SOL_SOCKET, SO_REUSEADDR | SOREUSEPORT, &opt, sizeof(opt))){
        perror("Fail to setsockopt");
    }else{
        fprintf(stderr, "Setsockopt successfully....\n");
    }

    if(bind(master_sock, address, sizeof(*address)) < 0){  
        perror("Fail to bind");
    }else{
        fprintf(stderr, "Bind successfully....\n");
    }

    if(listen(master_sock, max_client) < 0){
        perror("Fail to listen");
    }else{
        fprintf(stderr, "Listen successfully....\n");
    }
}