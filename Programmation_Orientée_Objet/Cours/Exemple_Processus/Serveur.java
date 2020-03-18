/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package patisserie;

import java.util.LinkedList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author freder
 */
public class Serveur implements Runnable {

    private LinkedList<Client> file = new LinkedList<Client>();

    public synchronized void entrerEnFile(Client c) {
        file.add(c);
        notify();
    }

    public void servir(Client c) {
        System.out.println("Service du client : " + c);
        try {
            Thread.sleep(500);
        } catch (InterruptedException ex) {
            Logger.getLogger(Serveur.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @Override
    public void run() {

        while (true) {
            synchronized (this) {
                if (file.isEmpty()) {
                    try {
                        wait();
                    } catch (InterruptedException ex) {
                        Logger.getLogger(Serveur.class.getName()).log(Level.SEVERE, null, ex);
                    }

                }
            }
            Client c = file.remove();
            servir(c);
            synchronized (c) {
                c.notify();
            }

        }

    }
}
