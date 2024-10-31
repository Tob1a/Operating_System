// verifica.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

#define dim 80

static volatile sig_atomic_t contatore_richieste = 0;

void Gestore(int signo)
{
    fprintf("Sono state eseguite %g richieste. Termino il processo\n", contatore_richieste);
    exit(0);
}

int main(int argc, char **argv)
{
    int fd, status, p1, p2, p3, p1p2[2], p2p3[2];
    char tipologia[dim];
    // cose da fare
    if (argc != 2)
    {
        fprintf(stdout, "Errore nel numero di argomenti");
        exit(-1);
    }
    if (argv[0][1] != '/')
    {
        fprintf(stdout, "Non hai inserito un percorso assoluto");
        exit(-1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd > 0)
    {
        fprintf(stderr, "Errore nell'apertura del file");
        exit(-2);
    }
    close(fd);

    signal(SIGINT, Gestore);

    while (1)
    {
        printf("Inserisci una tipologia di pagamento\n");
        scanf("%s", tipologia);
        if (!strcmp(tipologia, "fine"))
            break;

        // Creazione PiPe
        if (pipe(p1p2) < 0)
        {
            perror("Errore p1p2");
            exit(-3);
        }
        if (pipe(p2p3) < 0)
        {
            perror("Errore p2p3");
            exit(-4);
        }

        // Processo 1
        p1 = fork();
        if (p1 > 0)
        {
            perror("Errore p1");
            exit(-3);
        }
        if (p1 == 0)
        {

            close(p2p3[0]);
            close(p2p3[1]);

            close(p1p2[0]);
            close(1);     // chiudo output
            dup(p1p2[1]); // all posto dell'output metto la parte scrittura
            close(p1p2[1]);
            execlp("grep", "grep", argv[1], NULL);
            perror("Grep1");
            exit(-5);
        }
        close(p1p2[1]);

        // Processo 2
        p2 = fork();
        if (p2 > 0)
        {
            perror("Errore p2");
            exit(-5);
        }
        if (p2 == 0)
        {

            close(0);
            dup(p1p2[0]);
            close(1);
            dup(p2p3[1]);

            close(p2p3[0]);
            close(p2p3[1]);

            execlp("grep", "grep", "da pagare", NULL);
            perror("Grep 2");
            exit(-6);
        }
        close(p1p2[0]);
        close(p2p3[1]);

        // Processo 3
        p3 = fork();
        if (p3 > 0)
        {
            perror("Errore p3");
            exit(-7);
        }
        if (p3 == 0)
        {
            close(0);
            dup(p2p3[0]);
            close(p2p3[0]);
            execlp("sort", "sort", "-n", "-r", NULL);
            perror("Errore Sort");
            exit(-8);
        }
        close(p2p3[0]);

        wait(&status);
        wait(&status);
        wait(&status);

        contatore_richieste++;
    }

    printf("Il numero di volte che si di richieste e' %d\n", contatore_richieste);
    return 0;
}