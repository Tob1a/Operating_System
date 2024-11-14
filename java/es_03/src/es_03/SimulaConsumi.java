package es_03;

/**
 *
 * @author tobiasacchetto
 */


import java.util.concurrent.atomic.AtomicBoolean;

public class SimulaConsumi implements Runnable{
    final private AtomicBoolean isRunning = new AtomicBoolean(false);
    private consumi c = null;
    public SimulaConsumi(consumi c){
        this.c=c;
    }
    public void run(){
        isRunning.set(true);
        float val;
        while(isRunning.get()){
            val = (float)(Math.random() * 30);
            c.setConsumi(val);
            try{
                Thread.currentThread().sleep(1000);
            }catch(InterruptedException ie){
                ie.printStackTrace();
            }
        }
    }
    public void terminaSimulazioneConsumi(){
        isRunning.set(false);
    }
}
