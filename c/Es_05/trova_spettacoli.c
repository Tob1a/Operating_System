#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

#define dim 180

static volatile sig_atomic_t numero_ricorrenze = 0;

void Gestore(int signo)
{
    printf("Il numero di ricorsioni e' %d. Termino\n", numero_ricorrenze);
    exit(0);
}

int main(int argc, char *argv[])
{
    int fd, p1, p2, p3, status, p1p2[2], N, p2p3[2], p3p0[2], pipe_read;
    char percorso[dim], Nspettacolo[dim], char_n[4], ris[dim];
    // argc = 2;
    if (argc != 2)
    {
        fprintf(stderr, "Errore hai inserito pochi elementi");
        exit(1);
    }

    strcpy(percorso, "/Users/tobiasacchetto/Documents/GitHub/Operating_System/c/Es_05/test/TeatroComunale.txt");

    fd = open(percorso, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Errore apertura file");
        exit(2);
    }
    close(fd);

    signal(SIGINT, Gestore);
    while (1)
    {
        printf("Inserisci il nome dello spettacolo\n");
        scanf("%s", Nspettacolo);
        printf("Inserisci il numero di posti\n");
        scanf("%d", &N);
        if (N == 0)
            break;

        if (pipe(p1p2) < 0)
        {
            perror("Errore Pipe");
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
            execlp("grep", "grep", Nspettacolo, percorso, NULL);
            perror("Errore grep");
            exit(5);
        }
        close(p1p2[1]);

        if (pipe(p2p3) < 0)
        {
            perror("Errore p2p3");
            exit(3);
        }

        p2 = fork();
        if (p2 < 0)
        {
            perror("Errore p2");
            exit(4);
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
            perror("Errore p2");
            exit(6);
        }
        close(p1p2[0]);
        close(p2p3[1]);

        if (pipe(p3p0) < 0)
        {
            perror("Errore pipe0");
            exit(4);
        }

        p3 = fork();
        if (p3 < 0)
        {
            perror("Errore p3");
            exit(4);
        }
        if (p3 == 0)
        {
            close(0);
            dup(p2p3[0]);
            close(p2p3[0]);

            close(1);
            dup(p3p0[1]);
            close(p3p0[1]);
            close(p3p0[0]);

            // seleziono i primi n risultati
            sprintf(char_n, "%d", N);
            execlp("head", "head", "-n", char_n, NULL);
            perror("Errore p3");
            exit(8);
        }
        close(p2p3[0]);
        close(p3p0[1]);

        // Eseguo P0
        pipe_read = read(p3p0[0], ris, sizeof(ris) - 1);
        if (pipe_read < 0)
        {
            perror("Errore Read");
            exit(10);
        }
        close(p2p3[0]);

        // stampa a video
        ris[pipe_read] = '\0';
        printf("%s", ris);

        numero_ricorrenze++;
        wait(&status);
        wait(&status);
        wait(&status);
    }

    return 0;
}