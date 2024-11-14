#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#define dim 80

static volatile sig_atomic_t num_ric = 0;

void Gestore(int signo)
{
    printf("\nHo eseguito %d ricorsioni. Termino.\n", num_ric);
    exit(0);
}

int main(int argc, char *argv[])
{
    int fd, p1p2[2], p1, p2, status;
    char frase[dim], frase2[dim], tipologia[dim];
    if (argc != 1)
    {
        fprintf(stderr, "Hai inserito meno argomenti");
        exit(1);
    }
    if (argv[1][0] == '/')
    {
        fprintf(stderr, "Hai inserito una directory assoluta");
        exit(1);
    }
    fd = open(argv[1], O_DIRECTORY);
    if (fd < 0)
    {
        fprintf(stderr, "Errore apertura directory");
        exit(1);
    }
    close(fd);
    signal(SIGINT, Gestore);
    while (1)
    {
        printf("Inserisci la tipologia del video\n");
        scanf("%s", tipologia);
        printf("Inserisci la data formato YYYYMM\n");
        scanf("%s", frase);
        sprintf(frase2, "%s%s.txt", argv[1], frase);
        fd = open(frase2, O_RDONLY);
        if (fd < 0)
        {
            fprintf(stderr, "Errore apertura file");
            exit(1);
        }
        close(fd);
        if (pipe(p1p2) < 0)
        {
            perror("p1p2");
            exit(2);
        }
        p1 = fork();
        if (p1 < 0)
        {
            perror("errore fork p1");
            exit(2);
        }
        if (p1 == 0)
        {
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            close(p1p2[0]);
            execlp("grep", "grep", tipologia, frase2, NULL);
            perror("grep");
            exit(2);
        }
        close(p1p2[1]);

        p2 = fork();
        if (p2 < 0)
        {
            perror("p2");
            exit(3);
        }
        if (p2 == 0)
            ;
        {
            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);

            execlp("sort", "sort", "-n", "-r", NULL);
            perror("sort");
            exit(3);
        }
        close(p1p2[0]);

        wait(&status);
        wait(&status);

        num_ric++;
        }
    return 0;
}