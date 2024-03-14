#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int generarNumeroPar() {
    return rand() % 26 + 97;
}

typedef struct {
    long mtype;
    char mdata;
} Msg;

int main(void) {
    key_t key = ftok(".", 'a');
    int msgid = msgget(key, 0666 | IPC_CREAT);

    Msg message;
    message.mtype = 3;
    
    printf("Caracteres random\n");

    int count = 0;
    while (count < 10) {
        int num = generarNumeroPar();
        char character = (char)num;
        
        message.mdata = character;
        msgsnd(msgid, &message, sizeof(message), 0);
        printf("%c\n", character);
        count++;
    }

    return 0;
}
