package es_04;

/**
 *
 * @author tobiasacchetto
 */
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class Es_04 {

    public static void main(String[] args) {
        DatiAzionari da = new DatiAzionari();
        RecuperaDati rd = new RecuperaDati(da);
        String nome=null;
        int val=0,ind=0;
        System.out.println("Inserisci l'indice da vedere");
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        try{
            ind=Integer.parseInt(br.readLine());
        }catch(IOException ioe){
            ioe.printStackTrace();
        }
        da.setIndice(ind);
        rd.start();
        while(true){
            try{
                Thread.currentThread().sleep(7*1000);
            }catch(InterruptedException ie){
                ie.printStackTrace();
            }
            val=da.getValore();
            System.out.println("Valore = "+val);
            if(val > 70 || val < 30){
                System.out.println("Valore superiore a 70 o inferiore a 30. Termino");
                rd.terminaThread();
                break;
            }
            
        }
        
        //eseguo la join
        try{
            rd.join();
        }catch(InterruptedException ie){
            ie.printStackTrace();
        }
    }
    
}
