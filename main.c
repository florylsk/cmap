#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define NUM_THREADS 20

struct arg_struct {
    int startLoop;
    int endLoop;
};

//global variables
pthread_mutex_t lock;

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
        inet_pton ( AF_INET, "127.0.0.1", &serv_addr.sin_addr);
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
    int num_ports=40000;
    clock_t begin = clock();

    pthread_t tid;
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    int iter_per_thread=num_ports/NUM_THREADS;
    for (int i=0; i<num_ports;i+=iter_per_thread+1){
        struct arg_struct args;
        args.startLoop=i;
        args.endLoop=i+iter_per_thread;
        if (pthread_create(&tid, NULL, &testPort, (void *)&args)) {
            printf("Uh-oh!\n");
            return -1;
        }

    }

    for (int i=0; i<NUM_THREADS;i++){
        pthread_join(tid, NULL); /* Wait until thread is finished */
    }
    pthread_mutex_destroy(&lock);


    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time taken: %f",time_spent);

    return 0;
}
