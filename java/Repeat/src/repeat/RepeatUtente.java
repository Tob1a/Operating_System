package repeat;

/**
 *
 * @author tobiasacchetto
 */
import java.io.PipedOutputStream;
import java.io.BufferedWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.IOException;
import java.util.concurrent.atomic.AtomicBoolean;
public class RepeatUtente implements Runnable{
    PipedOutputStream pos = null;
    final static AtomicBoolean isRunning = new AtomicBoolean(true);
    public RepeatUtente(PipedOutputStream pos){
        this.pos=pos;
    }
    public void run(){
        isRunning.set(true);
        final BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(pos));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while(isRunning.get()){
            try{
            String line = br.readLine();
            bw.write(line);
            bw.newLine();
            bw.flush();}catch(IOException ioe){
                ioe.printStackTrace();
            }
        }
    }
    public void stop(){
        isRunning.set(false);
    }
}
