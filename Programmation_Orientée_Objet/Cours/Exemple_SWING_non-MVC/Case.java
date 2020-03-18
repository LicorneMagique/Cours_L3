/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package blokus;

import java.awt.Color;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JPanel;

/**
 *
 * @author frederic
 */
public class Case extends JPanel {

    public Case() {
        super();
        
        setBackground(Color.white);
        
        addMouseListener(new MouseAdapter() {
        
            @Override
            public void mouseEntered(MouseEvent arg0) {
                super.mouseClicked(arg0);
                setBackground(Color.BLACK);
            }

            @Override
            public void mouseExited(MouseEvent arg0) {
                super.mouseExited(arg0);
                setBackground(Color.red);
            }
            
            
            
        });
        
    }
    
}
