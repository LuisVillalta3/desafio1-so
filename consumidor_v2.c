#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct {
    long mtype;
    char mdata;
} MsgChar;

typedef struct {
    long mtype;
    int mdata;
} MsgInt;

int main() {
    key_t key = ftok(".", 'a');
    int msgid = msgget(key, 0666 | IPC_CREAT);

    MsgInt messageInt;
    MsgChar messageChar;

    printf("Recibiendo mensajes\n");

    int primos[10], pares[10];
    char chars[10];
    int indexPrimos = 0, indexPares = 0, indexChars = 0;

    while (1)
    {
        if (msgrcv(msgid, &messageInt, sizeof(messageInt), 1, IPC_NOWAIT) > 0) {
            primos[indexPrimos++] = messageInt.mdata;
        } else if (msgrcv(msgid, &messageInt, sizeof(messageInt), 2, IPC_NOWAIT) > 0) {
            pares[indexPares++] = messageInt.mdata;
        } else if (msgrcv(msgid, &messageChar, sizeof(messageInt), 3, IPC_NOWAIT) > 0) {
            chars[indexChars++] = messageChar.mdata;
        } else {
            break;
        }
    }

    printf("Números pares recibidos: \n");
    for (int i = 0; i < indexPares; i++) {
        printf("%d\n", pares[i]);
    }
    
    printf("\n");

    printf("Caracteres recibidos: \n");
    for (int i = 0; i < indexChars; i++) {
        printf("%c\n", chars[i]);
    }
    
    printf("\n");

    printf("Números primos recibidos: \n");
    for (int i = 0; i < indexPrimos; i++) {
        printf("%d\n", primos[i]);
    }
    
    printf("\n");

    return 0;
}

