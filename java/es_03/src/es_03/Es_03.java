package es_03;

/**
 *
 * @author tobiasacchetto
 */

public class Es_03 {
    public static void main(String[] args) {
        consumi c = new consumi();
        SimulaConsumi sc = new SimulaConsumi(c);
        Thread tsc = new Thread(sc);
        tsc.start();
        float valI=0.0F;
        float valF=0.0F;
        int count=0;
        while(true){
            try{
            Thread.currentThread().sleep(900);
            }catch(InterruptedException ie){
                ie.printStackTrace();
            }
            valI=c.getConsumi();
            if(valI > (valF*30/100)+valF){
                System.out.println("Warning valore superato del 30%");
            }
            if(valI>20){
                count++;
                if(count >= 3){
                    System.out.println("Superato il valore di 3. Termino");
                    sc.terminaSimulazioneConsumi();
                    break;
                }
            }
        }
        try{
            tsc.join();
        }catch(InterruptedException ie){
            ie.printStackTrace();
        }
    }
       
    
}
