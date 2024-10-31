#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

#define dim 80

static volatile sig_atomic_t numero_ricorrenze = 0;

void Gestore(int signo)
{
    printf("Ho eseguito %d ricorrenze. Termino\n", numero_ricorrenze);
    exit(0);
}

int main(int argc, char *argv[])
{
    int fd, status, p1p2[2], p1, p2;
    char tipologia[dim], tipologia2[dim];
    if (argc != 2)
    {
        fprintf(stderr, "Errore hai messo troppi pochi argomenti\n");
        exit(1);
    }
    if (argv[1][0] != '/')
    {
        fprintf(stderr, "Hai inserito un percorso relativo\n");
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Errore nell'apertura del file");
        exit(2);
    }
    close(fd);

    signal(SIGINT, Gestore);
    while (1)
    {
        printf("Inserisci la tipologia\n");
        scanf("%s", tipologia);
        if (!strcmp(tipologia, "fine"))
            break;

        // inizio Pipe
        if (pipe(p1p2))
        {
            perror("Errore pipe");
            exit(3);
        }
        p1 = fork();
        if (p1 < 0)
        {
            perror("Errore p1");
            exit(4);
        }

        if (p1 == 0)
        {
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            close(p1p2[0]);
            sprintf(tipologia2, "%s.*da pagare", tipologia);
            execlp("grep", "grep", tipologia2, argv[1], NULL);
            perror("Errore grep");
            exit(5);
        }

        close(p1p2[1]);
        p2 = fork();
        if (p2 < 0)
        {
            perror("Errore p2");
            exit(6);
        }

        if (p2 == 0)
        {
            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);

            execlp("sort", "sort", "-n", "-r", NULL);
            perror("Errore p2");
            exit(6);
        }
        close(p1p2[0]);
        wait(&status);
        wait(&status);
        numero_ricorrenze++;
    }
    printf("Hai eseguito  %d ricorsioni", numero_ricorrenze);
    return 0;
}