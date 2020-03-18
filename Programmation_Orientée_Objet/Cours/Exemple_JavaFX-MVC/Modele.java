/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mvc;

import java.util.Observable;
import mvc.libInterpreteurExpr.Node;

/**
 *
 * @author fred
 */
public class Modele extends Observable {

    double lastValue;
    boolean err = false;

    
    
    public void calc(String expr) {
        StringBuffer input;
        StringBuffer output;
        Node toto;

        input = new StringBuffer(expr);
        output = new StringBuffer(255);

        toto = Node.Construct_Tree(input, input.length(), 0);
        if (toto != null) {
            toto.Write_Tree(output);
            lastValue = toto.Compute_Tree(0, 0, 0);
            err = false;
        } else {
            err = true;
        }
        
        // notification de la vue, suite à la mise à jour du champ lastValue
        setChanged();
        notifyObservers();
    }
    
    public boolean getErr() {
        return err;
    }
    
    public double getValue() {
        return lastValue;
    }

}