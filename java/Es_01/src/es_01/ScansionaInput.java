package es_01;

/**
 *
 * @author tobiasacchetto
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PipedInputStream;
import java.util.concurrent.atomic.AtomicBoolean;

public class ScansionaInput implements Runnable {
    final private AtomicBoolean isRunning = new AtomicBoolean(false);
    private PipedInputStream pis = null;
    
    public ScansionaInput(PipedInputStream psi)
    {
        this.pis=pis;
    }
    
    public void run()
    {
        isRunning.set(true);
        BufferedReader br = new BufferedReader(new InputStreamReader(pis));
        
        
        while(isRunning.get())
        {
            try{
            String line = br.readLine();
            System.out.println("L'utente ha inviato "+ line);
            
            if(line.equals("1234") || line.equals("abcd"))
            {
                System.out.println("Pericolo");
            }
            else
            {
                System.out.println("ok");
            }
            }
            catch(IOException e)
            {
                e.printStackTrace();
            }            
            
        }
    }
}
