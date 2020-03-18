/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package blokus;

import java.awt.Color;
import java.awt.GridLayout;

import java.awt.event.ItemListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.BorderFactory;

import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JMenu;

import javax.swing.border.Border;
import javax.swing.plaf.basic.BasicComboBoxUI.ItemHandler;

/**
 *
 * @author frederic
 */
public class Vue extends JFrame {

    public Vue() {
        super();
        
        build();
        
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent arg0) {
                super.windowClosing(arg0);
                System.exit(0);
            }
        });
        
        
    }
    
    public void build() {
        

        //JMenu jm = new JMenu();
        JMenuBar jm = new JMenuBar();
        
        JMenu m = new JMenu("Jeu");
        
        JMenuItem mi = new JMenuItem("Partie");
        
        //ItemListener i = new Item
        
        m.add(mi);
        
        jm.add(m);
        
       
        
        setJMenuBar(jm);
        
        
        setTitle("Ma première fenêtre");
        setSize(400, 400);
        JComponent pan = new JPanel (new GridLayout(10,10));
        Border blackline = BorderFactory.createLineBorder(Color.black,1);

        for(int i = 0; i<100;i++){
            JComponent ptest = new Case();
            ptest.setBorder(blackline);
            pan.add(ptest);
        }
        pan.setBorder(blackline);
        add(pan);
        //setContentPane(pan);

        
        
        
    }

    
}
