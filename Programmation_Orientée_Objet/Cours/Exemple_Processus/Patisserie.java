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
public class Patisserie {

    private final static int NB_CLIENT = 5;
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Serveur s = new Serveur();
        
        new Thread(s).start();
        
        Client[] tab = new Client[NB_CLIENT];
        
        
        for (int i = 0; i < NB_CLIENT; i++) {
            tab[i] = new Client("Client " + i, s);
        }
        
        for (Client c : tab) {
            new Thread(c).start();
            try {
                Thread.sleep(100);
            } catch (InterruptedException ex) {
                Logger.getLogger(Patisserie.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
        
        
    }
    
}
