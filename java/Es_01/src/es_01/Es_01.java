package es_01;

/**
 *
 * @author tobiasacchetto
 */
import java.io.IOException;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;
public class Es_01 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // Creo canale di comunicazione Tra le due macchine
        PipedInputStream pis = null;
        PipedOutputStream pos = null;
        
        try
        {
            pis = new PipedInputStream();
            pos = new PipedOutputStream(pis);
        }
        catch(IOException ioe)
        {
            System.err.println("Impossibile creare una PipedOutputStream o PipedInputStream");
            System.exit(1);
        }
        
        InputUtente iU = new InputUtente(pos); //InputUtente lo definiamo in un'altra classe
        Thread tiU = new Thread(iU);
        tiU.start();
        
        ScansionaInput sI = new ScansionaInput(pis); //Anche qui lo dobbiamo definire
        Thread tsI = new Thread(sI);
        tsI.start();
        
        //eseguo un wait di 30 secondi
        try
        {
            Thread.currentThread().sleep(30*1000);
            System.out.println("Il sistema sta per terminare");
            tiU.stop();
            tsI.stop();
        }
        catch(InterruptedException e)
        {
            e.printStackTrace();
        }
        
        //effettuo la join al padre dei figli
        try
        {
            tsI.join();
            tiU.join();
        }
        catch(InterruptedException e)
        {
            System.err.println("Errore nel join");
            e.printStackTrace();
        }
    }
    
    
    
}
