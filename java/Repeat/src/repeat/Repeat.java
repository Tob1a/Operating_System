package repeat;

/**
 *
 * @author tobiasacchetto
 */
import java.io.PipedInputStream;
import java.io.PipedOutputStream;
import java.io.IOException;

public class Repeat {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        PipedOutputStream pos = null;
        PipedInputStream pis= null;
        try{
             pis= new PipedInputStream();
             pos = new PipedOutputStream(pis);
        }catch(IOException ioe){
            System.out.println("Errore nella pipe");
            System.exit(1);
               }
        InputUtente iu = new InputUtente(pos);
        ScansionaInput si = new ScansionaInput(pis);
        Thread tiu = new Thread(iu);
        Thread tsi = new Thread(si);
        tiu.start();
        tsi.start();
       try{
           Thread.currentThread().sleep(30*1000);
           System.out.println("Sto terminando il processo");
           tiu.stop();
           tsi.stop();
       }catch(InterruptedException ie){
           ie.printStackTrace();
       }
       try{
           tsi.join();
           tiu.join();
       }catch(InterruptedException ie){
           System.err.println("Errore della join");
           ie.printStackTrace();
       }
    }
    
}
