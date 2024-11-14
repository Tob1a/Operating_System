package repeat;

/**
 *
 * @author tobiasacchetto
 */
import java.io.BufferedReader;
import java.io.PipedInputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.concurrent.atomic.AtomicBoolean;

public class RepeatInput implements Runnable{
    private PipedInputStream pis = null;
    final private AtomicBoolean isRunning = new AtomicBoolean(false);
    
    public RepeatInput(PipedInputStream pis){
        this.pis=pis;
    }
    public void run(){
        isRunning.set(true);
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        while(isRunning.get()){
            try{
                String line = br.readLine();
                System.out.println("L'utente ha inviato"+line);
                if(line.equals("1234") || line.equals("abcd")){
                    System.out.print("Pericolo");
                }else
                {
                    System.out.println("ok");
                }
            }catch(IOException ioe){
                ioe.printStackTrace();
            }
        }
    }
    public void stop(){
        isRunning.set(false);
    }
}
