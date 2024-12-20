package es_01;

/**
 *
 * @author tobiasacchetto
 */
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PipedOutputStream;
import java.util.concurrent.atomic.AtomicBoolean;

public class InputUtente implements Runnable {
    private PipedOutputStream pos = null;
    final private AtomicBoolean isRunning = new AtomicBoolean(false);
    
    public InputUtente(PipedOutputStream pos)
    {
        this.pos=pos;
    }
    
    public void run()
    {
        isRunning.set(true);
        
        //Creo un BufferedWriter per inviare le stringhe al thread scansiona input
        final BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(pos));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while(isRunning.get())
        {
            try{
            String line = br.readLine();
            bw.write(line);
            bw.newLine();
            bw.flush();
            }catch(IOException e)
            {
                e.printStackTrace();
            }
        }
    }
    public void stop()
    {
        isRunning.set(false);
    }
}
