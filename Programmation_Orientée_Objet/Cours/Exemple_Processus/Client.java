/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package patisserie;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author freder
 */
public class Client implements Runnable {
    private Serveur s;
    private String nomClient;
    
    public Client(String _nomClient, Serveur _s) {
        s = _s;
        nomClient = _nomClient;
    }
    
    @Override
    public void run() {
    
        System.out.println("arrivée du client : " + this);
        s.entrerEnFile(this);
       
        try {
            synchronized(this) {
                wait();
            }
        } catch (InterruptedException ex) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        System.out.println("départ du client : " + this);
        
    }
    
    public String toString() {
        return nomClient;
    }
    
}
