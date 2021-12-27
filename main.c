#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <omp.h>

#define NUM_THREADS 20
#define NSEC_PER_SEC 1000000000UL

struct arg_struct {
    int startLoop;
    int endLoop;
};

//global variables
pthread_mutex_t lock;


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

void *testPort(void* arguments){

    struct arg_struct *args = arguments;

    int obj_socket = 0, reader;
    struct sockaddr_in serv_addr;
    int start_loop=args -> startLoop;
    int end_loop=args -> endLoop;

    for (int i=start_loop;i<end_loop;i++){
        //pthread_mutex_lock(&lock);
        obj_socket = socket (AF_INET, SOCK_STREAM, 0 );
        //pthread_mutex_unlock(&lock);
        inet_pton ( AF_INET, "45.33.32.156", &serv_addr.sin_addr);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(i);

        if ( connect( obj_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr )) < 0){
            //printf("[-] Port %d closed\n",i);
        }
        else{
            printf ( "[+]Port %d open\n",i);

        }
        close(obj_socket);
    }
}


int main ( int argument, char const *argv[] )
{
    struct timespec startTime;
    clock_gettime(CLOCK_REALTIME, &startTime);


    int obj_socket = 0, reader;
    struct sockaddr_in serv_addr;
    omp_set_num_threads(20);
    #pragma omp parallel for
    for (int i=0;i<10000;i++){
        //pthread_mutex_lock(&lock);
        obj_socket = socket (AF_INET, SOCK_STREAM, 0 );
        //pthread_mutex_unlock(&lock);
        inet_pton ( AF_INET, "45.33.32.156", &serv_addr.sin_addr);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(i);

        if ( connect( obj_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr )) < 0){
            //printf("[-] Port %d closed\n",i);
        }
        else{
            printf ( "[+]Port %d open\n",i);

        }
        close(obj_socket);
    }

    struct timespec endTime;
    struct timespec _diffTime;
    clock_gettime(CLOCK_REALTIME, &endTime);
    diffTime(endTime,startTime,&_diffTime);
    printf("Time taken: %d seconds",_diffTime.tv_sec);

    return 0;
}
