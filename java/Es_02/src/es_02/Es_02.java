package es_02;

/**
 *
 * @author tobiasacchetto
 */
import java.io.PipedInputStream;
import java.io.PipedOutputStream;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Es_02 {

    public static void main(String[] args) {
        PipedInputStream pis = null;
        PipedOutputStream pos = null;
        try{
            /*metodo corretto
            Lo utilizzi quando hai già un oggetto PipedOutputStream e 
            vuoi creare un PipedInputStream che legge da quel flusso. 
            Questo è comune in scenari in cui un thread scrive dati e 
            un altro thread li legge.
            */
            pos= new PipedOutputStream();
            pis = new PipedInputStream(pos);
        }catch(IOException ioe){
            System.out.println("Errore sulla Pipe");
        }
        //anche questo funziona correttamente cosí
        BufferedReader br = new BufferedReader(new InputStreamReader(pis));
        
        RilevatoreAria ra = new RilevatoreAria(pos);
        ra.start();
        
        long oldTime =0;
        
        for(int i=0; i<8; i++){
            try{
            int val = Integer.parseInt(br.readLine());
            long newTime = Long.parseLong(br.readLine());
            if(val < 20){
                System.out.println("Basso "+ val);
            }
            else if(val >= 20 && val <= 75){
                System.out.println("Medio " + val);
            }
            else{
                System.out.println("Alto "+val);
            }
            if(newTime-oldTime > 15*1000 ){
                System.out.println("Attenzione");
            }
            oldTime=newTime;
            }
            catch(IOException ioe){
                ioe.printStackTrace();
            }
        }
        
        ra.FermaRilevatoreAria();
        try{
            ra.join();
            System.out.println("Termino dopo 8 misurazioni. Ho eseguito la join");
        }catch(InterruptedException ie){
            ie.printStackTrace();
        }
        
        
        
        
        
    }
    
}
