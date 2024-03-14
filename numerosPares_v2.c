#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int generarNumeroPar() {
    int num = rand() % 201;
    return num % 2 == 0 ? num : num + 1;
}

typedef struct {
    long mtype;
    int mdata;
} Msg;

int main(void) {
    key_t key = ftok(".", 'a');
    int msgid = msgget(key, 0666 | IPC_CREAT);

    Msg message;
    message.mtype = 2;

    printf("Números pares\n");
    
    int count = 0;
    while (count < 10) {
        int num = generarNumeroPar();
        
        message.mdata = num;
        msgsnd(msgid, &message, sizeof(message), 0);
        printf("%d\n", num);
        count++;
    }

    return 0;
}

