package repeat_2;

/**
 *
 * @author tobiasacchetto
 */
import java.io.PipedInputStream;
import java.io.PipedOutputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;

public class Repeat_2 {

    public static void main(String[] args) {
        PipedInputStream pis = null;
        PipedOutputStream pos = new PipedOutputStream();
        try{
            pis= new PipedInputStream(pos);
            
        }catch(IOException ioe){
            ioe.printStackTrace();
        }
        Repeat_class rc = new Repeat_class(pos);
        BufferedReader br = new BufferedReader(new InputStreamReader(pis));
        rc.start();
        int val;
        long tempo;
        long tempop=0;
        for(int i=0;i<8;i++){
            try{
                val=Integer.parseInt(br.readLine());
                if(val<20){
                    System.out.println("Basso "+val);
                }
                if(val>=20 && val<=75){
                    System.out.println("Medio "+val);
                }
                if(val>75){
                    System.out.println("Alto "+val);
                }
                tempo=Long.parseLong(br.readLine());
                if(tempo-tempop>15 && tempop!=0){
                    System.out.println("Attenzione");
                }
                tempop=tempo;
            }catch(IOException ioe){
                ioe.printStackTrace();
            }
            
        }
        System.out.println("Eseguo la join");
        rc.fermaRilevatoreAria();
        try{
            rc.join();
        }catch(InterruptedException ie){
            ie.printStackTrace();
        }
        
    }
    
}
