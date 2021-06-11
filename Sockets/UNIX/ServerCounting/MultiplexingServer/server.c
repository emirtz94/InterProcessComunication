#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "/tmp/DemoSocket"
#define BUFFER_SIZE 128

#define MAX_CLIENT_SUPPORTED    32

int monitored_fd_set[MAX_CLIENT_SUPPORTED];

int client_result[MAX_CLIENT_SUPPORTED] = {0};

static void intitiaze_monitor_fd_set(){

    int i = 0;
    for(; i < MAX_CLIENT_SUPPORTED; i++)
        monitored_fd_set[i] = -1;
}

static void add_to_monitored_fd_set(int skt_fd){

    int i = 0;
    for(; i < MAX_CLIENT_SUPPORTED; i++){

        if(monitored_fd_set[i] != -1)
            continue;
        monitored_fd_set[i] = skt_fd;
        break;
    }
}

static void remove_from_monitored_fd_set(int skt_fd){

    int i = 0;
    for(; i < MAX_CLIENT_SUPPORTED; i++){

        if(monitored_fd_set[i] != skt_fd)
            continue;

        monitored_fd_set[i] = -1;
        break;
    }
}

static void refresh_fd_set(fd_set *fd_set_ptr){

    FD_ZERO(fd_set_ptr);
    int i = 0;
    for(; i < MAX_CLIENT_SUPPORTED; i++){
        if(monitored_fd_set[i] != -1){
            FD_SET(monitored_fd_set[i], fd_set_ptr);
        }
    }
}


static int get_max_fd(){
    int i = 0;
    int max = -1;

    for(; i < MAX_CLIENT_SUPPORTED; i++){
        if(monitored_fd_set[i] > max)
            max = monitored_fd_set[i];
    }

    return max;
}



int
main(int argc, char *argv[])
{
    struct sockaddr_un name;

#if 0  
    struct sockaddr_un {
        sa_family_t sun_family;               /* AF_UNIX */
        char        sun_path[108];            /* pathname */
    };
#endif

    int ret;
    int connection_socket;
    int data_socket;
    int result;
    int data;
    char buffer[BUFFER_SIZE];
    fd_set readfds;
    int comm_socket_fd, i;
    intitiaze_monitor_fd_set();
    add_to_monitored_fd_set(0);

    unlink(SOCKET_NAME);

    connection_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    if (connection_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    printf("Master socket created\n");

    memset(&name, 0, sizeof(struct sockaddr_un));

    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);
    
    ret = bind(connection_socket, (const struct sockaddr *) &name,
            sizeof(struct sockaddr_un));

    if (ret == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    printf("bind() call succeed\n");

    ret = listen(connection_socket, 20);
    if (ret == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    add_to_monitored_fd_set(connection_socket);
    for (;;) {
        refresh_fd_set(&readfds);
        printf("Waiting on select() sys call\n");

        select(get_max_fd() + 1, &readfds, NULL, NULL, NULL);

        if(FD_ISSET(connection_socket, &readfds)){
            printf("New connection recieved recvd, accept the connection\n");

            data_socket = accept(connection_socket, NULL, NULL);

            if (data_socket == -1) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            printf("Connection accepted from client\n");

            add_to_monitored_fd_set(data_socket);
        }
        else if(FD_ISSET(0, &readfds)){
            memset(buffer, 0, BUFFER_SIZE);
            ret = read(0, buffer, BUFFER_SIZE);
            printf("Input read from console : %s\n", buffer);
        }
        else 
        {
            i = 0, comm_socket_fd = -1;
            for(; i < MAX_CLIENT_SUPPORTED; i++){

                if(FD_ISSET(monitored_fd_set[i], &readfds)){
                    comm_socket_fd = monitored_fd_set[i];

                    memset(buffer, 0, BUFFER_SIZE);

                    printf("Waiting for data from the client\n");
                    ret = read(comm_socket_fd, buffer, BUFFER_SIZE);

                    if (ret == -1) {
                        perror("read");
                        exit(EXIT_FAILURE);
                    }
                    memcpy(&data, buffer, sizeof(int));
                    if(data == 0) {
                        memset(buffer, 0, BUFFER_SIZE);
                        sprintf(buffer, "Result = %d", client_result[i]);

                        printf("sending final result back to client\n");
                        ret = write(comm_socket_fd, buffer, BUFFER_SIZE);
                        if (ret == -1) {
                            perror("write");
                            exit(EXIT_FAILURE);
                        }

                        close(comm_socket_fd);
                        client_result[i] = 0; 
                        remove_from_monitored_fd_set(comm_socket_fd);
                        continue;
                    }
                    client_result[i] += data;
                }
            }
        }
    }

    close(connection_socket);
    remove_from_monitored_fd_set(connection_socket);
    printf("connection closed..\n");

    unlink(SOCKET_NAME);
    exit(EXIT_SUCCESS);
}

