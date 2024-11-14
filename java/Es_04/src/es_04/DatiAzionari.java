package es_04;

/**
 *
 * @author tobiasacchetto
 */

public class DatiAzionari {
    private int Indice=0, Val=0;
    public synchronized int getIndice(){
        return Indice;
    }
    public synchronized void setIndice(int Indice){
        this.Indice=Indice;
    }
    public synchronized int getValore(){
        return Val;
    }
    public synchronized void setValore(int Val){
        this.Val=Val;
    }
}
