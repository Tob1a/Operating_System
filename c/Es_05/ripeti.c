#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>

#define dim 80

static volatile sig_atomic_t numero_ricorrenze = 0;

void Gestore(int signo)
{
    printf("Il numero di ricorrenze e' %d. Termino\n", numero_ricorrenze);
    exit(0);
}

int main(int argc, char *argv[])
{
    int pid1, pid2, pid3, p1p2[2], p2p3[2], p3p0[2], status, n, fd, size;
    char spettacolo[dim], frase[dim], ris[dim];

    if (argc != 2)
    {
        fprintf(stderr, "Errore hai inserito troppi pochi argomenti\n");
        exit(1);
    }
    if (argv[1][0] != '/')
    {
        fprintf(stderr, "Non e' una directory assoluta\n");
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Errore apertura file\n");
        exit(2);
    }
    close(fd);
    signal(SIGINT, Gestore);

    while (1)
    {
        printf("Inserisci il nome dello spettacolo\n");
        scanf("%s", spettacolo);
        printf("Inserisci il numero di posti\n");
        scanf("%d", n);
        if (n == 0)
            break;

        // PiPe
        if (pipe(p1p2) < 0)
        {
            perror("p1p2");
            exit(3);
        }
        pid1 = fork();
        if (pid1 < 0)
        {
            perror("pid1");
            exit(4);
        }
        if (pid1 == 0)
        {
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            close(p1p2[0]);
            execlp("grep", "grep", spettacolo, argv[1], NULL);
            perror("grep");
            exit(5);
        }
        close(p1p2[1]);

        if (pipe(p2p3) > 0)
        {
            perror("p2p3");
            exit(3);
        }
        pid2 = fork();
        if (pid2 < 0)
        {
            perror("pid2");
            exit(4);
        }
        if (pid2 == 0)
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
            exit(5);
        }

        close(p1p2[0]);
        close(p2p3[1]);

        if (pipe(p3p0) < 0)
        {
            perror("p3p0");
            exit(3);
        }
        pid3 = fork();
        if (pid3 < 0)
        {
            perror("pid3");
            exit(4);
        }
        if (pid3 == 0)
        {
            close(0);
            dup(p2p3[0]);
            close(p2p3[0]);

            close(1);
            dup(p3p0[1]);
            close(p3p0[1]);

            close(p3p0[0]);

            sprintf(frase, "%d", n);
            execlp("head", "head", frase, NULL);
            perror("grep");
            exit(5);
        }
        close(p3p0[1]);
        close(p2p3[0]);

        wait(&status);
        wait(&status);
        wait(&status);

        size = read(p3p0[0], ris, sizeof(ris));
        if (size < 0)
        {
            perror("size");
            exit(8);
        }
        ris[size] = '\0';
        printf("%s", ris);
        close(p3p0[0]);

        numero_ricorrenze++;
    }
    printf("Il numero di interazioni e' %d", numero_ricorrenze);
    return 0;
}
