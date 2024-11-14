package es_03;


/**
 *
 * @author tobiasacchetto
 */

public class consumi {
    
   private float consumo =0.0F;
   public synchronized void setConsumi(float consumo){
       this.consumo=consumo;
   }
   public synchronized float getConsumi(){
       return consumo;
   }
}
