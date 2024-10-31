#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#define dim 80

static volatile sig_atomic_t num_ric = 0;

void Gestore(int signo)
{
    printf("Ho eseguito %d ricorsioni. Termino", num_ric);
    exit(0);
}

int main(int argc, char *argv[])
{
    int fd, p1, p2, status, p1p2[2], num_ris;
    char frase[dim], ris[dim], frase1[dim];

    sprintf(frase1, "%s%s.txt", argv[1], frase);
    fd = open(argv[1], O_DIRECTORY);
    if (fd < 0)
    {
        fprintf(stderr, "Errore apertura cartella");
        exit(1);
    }
    close(fd);

    signal(SIGINT, Gestore);
    while (1)
    {
        printf("Inserisci il nome del file");
        scanf("%s", frase);
        sprintf(frase1, "%s%s.txt", argv[1], frase);
        fd = open(frase1, O_RDONLY);
        if (fd < 0)
        {
            fprintf(stderr, "Errore apertura file");
            exit(1);
        }
        close(fd);
    }

    return 0;
}