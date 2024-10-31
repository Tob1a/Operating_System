// trova_video.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

#define dim 80

static volatile sig_atomic_t numero_riccorenze = 0;

void Gestore(int signo)
{
    printf("Il numero di volte che e' stato richiamato e' %d", numero_riccorenze);
    exit(0);
}

int main(int argc, char *argv[])
{
    int fd, p1, p2, p1p2[2], status;
    char data[9], tipo[dim];

    // controllo sugli argomenti
    if (argc != 2)
    {
        fprintf(stderr, "Errore nel numero di argomenti");
        exit(1);
    }
    if (argv[1][0] != '/')
    {
        fprintf(stderr, "Errore nella directory assoluta");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd > 0)
    {
        fprintf(stderr, "Errore nell'apertura della cartella");
        exit(2);
    }
    close(fd);

    signal(SIGINT, Gestore);

    while (1)
    {
        printf("Inserisci la tipologia del video\n");
        scanf("%s", tipo);

        printf("Inserisci la data\n");
        scanf("%s", data);
        sprintf(data, "%s%s.txt", argv[1], data); // serve per aggiungere alla data.txt

        // devo aprire il file anche qui
        fd = open(data, O_RDONLY);
        if (fd < 0)
        {
            fprintf(stderr, "Errore nell'apertura file");
            exit(2);
        }
        close(fd);

        // Creazione PiPe

        if (pipe(p1p2) < 0)
        {
            perror("Errore p1p2");
            exit(6);
        }
        p1 = fork();
        if (p1 > 0)
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
            execlp("grep", "grep", tipo, data, NULL);
            perror("grep");
            exit(5);
        }
        close(p1p2[1]);

        p2 = fork();
        if (p2 > 0)
        {
            perror("Errore p2");
            exit(7);
        }
        if (p2 == 0)
        {
            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);

            execlp("sort", "sort", "-r", "-n", NULL);
            perror("Errore sort");
            exit(8);
        }
        close(p1p2[0]);

        wait(&status);
        wait(&status);

        numero_riccorenze++;
    }

    return 0;
}