package es_04;

/**
 *
 * @author tobiasacchetto
 */
import java.util.concurrent.atomic.AtomicBoolean;
public class RecuperaDati extends Thread{
    DatiAzionari da = null;
    private AtomicBoolean isRunning = new AtomicBoolean(false);
    public RecuperaDati(DatiAzionari da){
        this.da=da;
    }
    public void run(){
        isRunning.set(true);
        int valn=0;
        int valp=0;
        while(isRunning.get()){
            valn=(int)((Math.random()*81)+20);
            if(valn==valp){
                System.out.println("Warning i valori sono uguali");
            }
            da.setValore(valn);
            try{
            Thread.currentThread().sleep(5*1000);}catch(InterruptedException ie){
                ie.printStackTrace();
            }
            valp=valn;
        }
    }
    public void terminaThread(){
        isRunning.set(false);
    }
}
