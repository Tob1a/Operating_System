package repeat_2;

/**
 *
 * @author tobiasacchetto
 */
import java.io.PipedOutputStream;
import java.util.concurrent.atomic.AtomicBoolean;
import java.io.OutputStreamWriter;
import java.io.BufferedWriter;
import java.io.IOException;

public class Repeat_class extends Thread{
    private PipedOutputStream pos = null;
    final AtomicBoolean isRunning = new AtomicBoolean(false);
    public Repeat_class(PipedOutputStream pos){
        this.pos=pos;
    }
    public void run(){
        isRunning.set(true);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(pos));
        while(isRunning.get()){
            try{
                String line = (int)(Math.random()*110)+"";
                bw.write(line);
                bw.newLine();
                bw.write((long)(System.currentTimeMillis()/1000)+"");
                bw.newLine();
                bw.flush();
            }catch(IOException ie){
                ie.printStackTrace();
            }
            try{
                Thread.sleep(12*1000);
            }catch(InterruptedException ie){
                ie.printStackTrace();
            }
        }
    }
    public void fermaRilevatoreAria(){
        isRunning.set(false);
    }
    
}
