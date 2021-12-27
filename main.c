#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <omp.h>
#include <stdlib.h>

#define NSEC_PER_SEC 1000000000UL


void diffTime(struct timespec end,
              struct timespec start,
              struct timespec *diff)
{
    if (end.tv_nsec < start.tv_nsec) {
        diff->tv_nsec = NSEC_PER_SEC - start.tv_nsec + end.tv_nsec;
        diff->tv_sec = end.tv_sec - (start.tv_sec+1);
    } else {
        diff->tv_nsec = end.tv_nsec - start.tv_nsec;
        diff->tv_sec = end.tv_sec - start.tv_sec;
    }
}




int main ( int argc, char const *argv[] )
{
    struct timespec startTime;
    clock_gettime(CLOCK_REALTIME, &startTime);
    if (argc!=4){
        printf("Format: cmap {IP} {PortStart} {PortEnd}\n");
        return 0;
    }
    //IP to ping
    char* inputIP = argv[1];
    //port to start scanning at
    int startPort=atoi(argv[2]);
    //port to stop scanning at
    int endPort=atoi(argv[3]);
    int obj_socket = 0, reader;
    struct sockaddr_in serv_addr;

    omp_set_num_threads(40);
    #pragma omp parallel for
    for (int i=startPort;i<endPort;i++){
        //open socket for connection
        obj_socket = socket (AF_INET, SOCK_STREAM, 0 );
        inet_pton ( AF_INET, inputIP, &serv_addr.sin_addr);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(i);
        //try to connect and see if it's open
        if ( connect( obj_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr )) < 0){}
        else{
            switch(i){
                case 21:
                    printf ( "[+]Port %d open | FTP\n",i);
                    break;
                case 22:
                    printf ( "[+]Port %d open | SSH\n",i);
                    break;
                case 23:
                    printf ( "[+]Port %d open | Telnet\n",i);
                    break;
                case 25:
                    printf ( "[+]Port %d open | SMTP\n",i);
                    break;
                case 53:
                    printf ( "[+]Port %d open | DNS\n",i);
                    break;
                case 80:
                    printf ( "[+]Port %d open | HTTP\n",i);
                    break;
                case 88:
                    printf ( "[+]Port %d open | Kerberos\n",i);
                    break;
                case 110:
                    printf ( "[+]Port %d open | POP3\n",i);
                    break;
                case 139:
                    printf ( "[+]Port %d open | Netbios-ssn\n",i);
                    break;
                case 389:
                    printf ( "[+]Port %d open | LDAP\n",i);
                    break;
                case 443:
                    printf ( "[+]Port %d open | HTTPS\n",i);
                    break;
                case 445:
                    printf ( "[+]Port %d open | SAMBA\n",i);
                    break;
                case 636:
                    printf ( "[+]Port %d open | LDAPS\n",i);
                    break;
                case 992:
                    printf ( "[+]Port %d open | Telnets\n",i);
                    break;
                case 3306:
                    printf ( "[+]Port %d open | MySQL\n",i);
                    break;
                default:
                    printf ( "[+]Port %d open\n",i);
                    break;
            }
            close(obj_socket);

        }

    }

    struct timespec endTime;
    struct timespec _diffTime;
    clock_gettime(CLOCK_REALTIME, &endTime);
    diffTime(endTime,startTime,&_diffTime);
    printf("Time taken: %d seconds",_diffTime.tv_sec);

    return 0;
}
