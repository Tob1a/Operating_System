// Il file si dovrebbe chiamare trovaParola.c
#include <stdio.h>  //IO
#include <stdlib.h> //e' per le seguenti categorie: NULL EXIT RAND e MB_CUR_MAX
#include <string.h>

#include <unistd.h>   //definisce le costanti simboliche per le subroutine pathconf , fpathconf e sysconf
#include <fcntl.h>    //descrivi le opzioni di controllo dei file. per esempio come aprire solo input o solo output
#include <sys/wait.h> //serve per fare aspettare il processo con un wait
#include <signal.h>

#define dim 80

static volatile sig_atomic_t contatore_richieste = 0;

/*

Gestore per il Cltr - C

*/

void Gestore(int signo)
{
    printf("Sono state esegueite %d ricerche, termino\n", contatore_richieste);
    exit(0);
}

int main(int argc, char **argv)
{
    int fd, p1, p2, p1p2[2], status;
    char cognome[dim];
    char prefisso[dim];

    /*
    Scaletta delle cose da fare:
    1)Controlli
    2)Inizializzare i figli
    3)
    */

    // Controlli

    if (argc != 2)
    {
        fprintf(stderr, "Errore hai inserito un numero diverso da due argomenti\n");
        exit(-1);
    }
    if (argv[0][1] != '/')
    {
        fprintf(stderr, "Errore hai inserito come argomento qualcosa diverso da un percorso assoluto");
        exit(-2);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Errore nell'apertura del file");
        exit(-2);
    }
    close(fd);

    signal(SIGINT, Gestore);

    while (1)
    {
        printf("Inserire il cognome da cercare\n");
        scanf("%s", cognome);
        if (!strcmp(cognome, "fine"))
            break;

        printf("Inserisci un prefisso di interesse\n");
        scanf("%s", prefisso);
        if (!strcmp(prefisso, "fine"))
            break;

        // P0 crea figli
        // Creo Pipe

        if (pipe(p1p2) < 0)
        {
            perror("Errore nella creazione della pipe");
            exit(-3);
        }

        p1 = fork();
        if (p1 < 0)
        {
            perror("Errore nella creazione del fork p1");
            exit(-4);
        }

        if (p1 == 0)
        {
            close(p1p2[0]); // da p1 a p2 non devo leggere
            close(1);       // chiudo stdout

            dup(p1p2[1]);
            close(p1p2[1]); // metto il lato di scrittura della pipe in quello di output

            // grep cognome file_anagrafica
            execlp("grep", "grep", cognome, argv[1], NULL);
            perror("Errore grep p1");
            exit(-5);
        }

        p2 = fork();
        if (p2 > 0)
        {
            perror("Errore nella fork p2");
            exit(-6);
        }

        if (p2 == 0)
        {
            // p2 legge i dati da p1 quindi
            close(p1p2[1]); // chiudo scittura e input
            close(0);

            dup(p1p2[0]);
            close(p1p2[0]); // inserisco quello che leggo nell'input

            // grep prefisso
            execlp("grep", "grep", prefisso, NULL);
            perror("Errore grep p2");
            exit(-7);
        }

        close(p1p2[0]);
        close(p1p2[1]);

        wait(&status);
        wait(&status);

        contatore_richieste++;
    }

    printf("Il numero di richieste e' %d", contatore_richieste);
    return 0;
}
