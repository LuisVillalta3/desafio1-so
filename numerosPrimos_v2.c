#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/msg.h>

bool is_prime(int n) {
    if (n <= 1) {
	    return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
	        return false;
	    }
    }
    return true;
}

typedef struct {
    long mtype;
    int mdata;
} Msg;

int main(void) {
    key_t key = ftok(".", 'a');
    int msgid = msgget(key, 0666 | IPC_CREAT);

    Msg message;
    message.mtype = 1;

    int primes[10];
    int count = 0;

    printf("Números primos\n");

    while (count < 10) {
        int num = rand() % 201;;

        if (is_prime(num)) {
            message.mdata = num;
            msgsnd(msgid, &message, sizeof(message), 0);
            printf("%d\n", num);
            count++;
        }
    }

    return 0;
}
