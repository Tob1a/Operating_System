#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <signal.h>

#define dim 80

static volatile sig_atomic_t numero_ric = 0;

void Gestore(int signo)
{
    printf("Il numero di ricorsioni che eseguo e' %d. Termino\n", numero_ric);
    exit(0);
}

int main(int argc, char *argv[])
{
    int fd, p1, p2, p3, p1p2[2], p2p3[2], status;
    char frase[dim];
    signal(SIGINT, Gestore);
    if (argc != 2)
    {
        fprintf(stderr, "Errore hai inserito meno di 2\n");
        exit(1);
    }
    if (argv[1][0] != '/')
    {
        fprintf(stderr, "Errore non hai inserito una direcotory assoluta\n");
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);

    if (fd < 0)
    {
        fprintf(stderr, "Errore apertura file");
        exit(1);
    }
    close(fd);

    while (1)
    {
        printf("Inserisci la tipologia\n");
        scanf("%s", frase);
        if (!strcmp(frase, "fine"))
            break;
        if (pipe(p1p2) < 0)
        {
            perror("p1p2");
            exit(2);
        }
        p1 = fork();
        if (p1 < 0)
        {
            perror("p1");
            exit(2);
        }
        if (p1 == 0)
        {
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            close(p1p2[0]);
            execlp("grep", "grep", frase, argv[1], NULL);
            perror("grep");
            exit(2);
        }

        close(p1p2[1]);

        if (pipe(p2p3) < 0)
        {
            perror("p2p3");
            exit(2);
        }
        p2 = fork();
        if (p2 < 0)
        {
            perror("p2");
            exit(2);
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
            execlp("grep", "grep", "da pagare", NULL);
            perror("grep2");
            exit(2);
        }
        close(p1p2[0]);
        close(p2p3[1]);

        p3 = fork();
        if (p3 < 0)
        {
            perror("p3");
            exit(2);
        }
        if (p3 == 0)
        {
            close(0);
            dup(p2p3[0]);
            close(p2p3[0]);

            execlp("sort", "sort", "-n", "-r", NULL);
            perror("sort");
            exit(2);
        }
        close(p2p3[0]);

        wait(&status);
        wait(&status);
        wait(&status);

        numero_ric++;
    }

    printf("Termino. Ho eseguito %d cicli\n", numero_ric);

    return 0;
}