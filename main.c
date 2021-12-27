#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>


int main ( int argument, char const *argv[] )
{
    clock_t begin = clock();
    int obj_socket = 0, reader;
    struct sockaddr_in serv_addr;

    for (int i=1;i<50000;i++){
        if (( obj_socket = socket (AF_INET, SOCK_STREAM, 0 )) < 0)
        {
            printf ( "Socket creation error !" );
            return -1;
        }
        if(inet_pton ( AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
        {
            printf ( "\nInvalid address ! This IP Address is not supported !\n" );
            return -1;
        }
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(i);

        if ( connect( obj_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr )) < 0){}
        else{
            printf ( "[+]Port %d open\n",i);

        }
        close(obj_socket);
    }


    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time taken: %f",time_spent);

    return 0;
}
