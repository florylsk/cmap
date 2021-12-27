#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


int main ( int argument, char const *argv[] )
{

    int obj_socket = 0, reader;
    struct sockaddr_in serv_addr;

    for (int i=1;i<65535;i++){
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



    return 0;
}
