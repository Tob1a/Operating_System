#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

#define dim 80

static volatile sig_atomic_t numero_ric = 0;

void Gestore(int signo)
{
    printf("\nHo eseguito %d iterazioni. Mi fermo\n", numero_ric);
    exit(0);
}

int main(int argc, char *argv[])
{
    int fd, p1, p2, p3, status, n, p1p2[2], p2p3[2];
    char frase[dim], percorso[dim];

    // controlli
    sprintf(percorso, "/var/local/ticket/%s.txt", argv[1]);
    fd = open(percorso, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "errore");
        exit(4);
    }
    close(fd);

    signal(SIGINT, Gestore);

    while (1)
    {
        printf("Inserisci  la data di partenza (in formato DDMMYYYY\n");
        scanf("%d", n);
        if (n == -1)
            break;
        sprintf(frase, "%d", n);

        if (pipe(p1p2) < 0)
        {
            perror("p1p2");
            exit(5);
        }
        p1 = fork();
        if (p1 < 0)
        {
            perror("p1p2");
            exit(5);
        }
        if (p1 == 0)
        {
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            close(p1p2[0]);
            execlp("grep", "grep", frase, percorso, NULL);
            perror("Grep");
            exit(5);
        }
        close(p1p2[1]);

        if (pipe(p2p3) > 0)
        {
            perror("p2p3");
            exit(5);
        }

        p2 = fork();
        if (p2 < 0)
        {
            perror("p2");
            exit(5);
        }
        if (p2 == 0)
        {
            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);

            close(1);
            dup(p2p3[1]);
            close(p2p3[1]);

            close(p2p3[0]);
            execlp("sort", "sort", "-n", "-r", NULL);
            perror("sort");
            exit(6);
        }
        close(p1p2[0]);
        close(p2p3[1]);

        p3 = fork();
        if (p3 < 0)
        {
            perror("p3");
            exit(5);
        }
        if (p3 == 0)
        {
            close(0);
            dup(p2p3[0]);
            close(p2p3[0]);

            execlp("head", "head", "-n", argv[2], NULL);
            perror("head");
            exit(5);
        }
        close(p2p3[0]);

        wait(&status);
        wait(&status);
        wait(&status);

        numero_ric++;
    }

    printf("\nHo eseguito %d iterazioni. Mi fermo\n", numero_ric);

    return 0;
}