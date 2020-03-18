/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package blokus;

import javax.swing.SwingUtilities;

/**
 *
 * @author frederic
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable(){
			public void run(){
				//On crée une nouvelle instance de notre JDialog
				Vue fenetre = new Vue();
				fenetre.setVisible(true);//On la rend visible
			}
		});

    }

}
