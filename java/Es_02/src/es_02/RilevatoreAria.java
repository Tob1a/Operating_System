/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package es_02;

/**
 *
 * @author tobiasacchetto
 */
import java.io.IOException;
import java.io.PipedOutputStream;
import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.util.concurrent.atomic.AtomicBoolean;

public class RilevatoreAria extends Thread{
    PipedOutputStream pos = null;
    final private AtomicBoolean isRunning = new AtomicBoolean(false);
    public RilevatoreAria(PipedOutputStream pos){
        this.pos=pos;
    }
    public void run(){
        isRunning.set(true);
        final BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(pos));
        while(isRunning.get()){
            try{
                String line = ((int)(110*Math.random()-10)+"");
                bw.write(line);
                bw.newLine();
                line = ((System.currentTimeMillis()/1000)+"");
                bw.write(line);
                bw.newLine();
                bw.flush();
            }catch(IOException ioe){
                ioe.printStackTrace();
            }
            try{
                Thread.currentThread().sleep(12*1000);
                System.out.println("Sto aspettando 12 secondi per il processo");
                
            }catch(InterruptedException ie)
            {
                ie.printStackTrace();
            }
        }
    }
    public void FermaRilevatoreAria(){
            isRunning.set(false);
        }
}
