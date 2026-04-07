
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import javax.swing.*;
import java.awt.BorderLayout;
import java.awt.event.*;

public class Fenetre extends JFrame {
    public Fenetre() {
        JFrame maFramme = new JFrame();
        maFramme.setBounds(100, 100, 200, 300);
        maFramme.setTitle("j'ai des livres mais j'ai pas d'livres");

        JLabel euro = new JLabel("Euro");
        JLabel yen = new JLabel("Yen");

        JTextField eurotxt = new JTextField("");
        JTextField yentxt = new JTextField("");

        JButton convertir = new JButton("convertir");
        JButton reset = new JButton("reset");
        convertir.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e){
                if (!eurotxt.getText().equals("")){
                    double euro2 = Double.parseDouble(eurotxt.getText());
                    euro2 = 184.75 * euro2;
                    yentxt.setText(Double.toString(euro2));
                }
                else{
                    if (!yentxt.getText().equals("")){
                        double euro2 = Double.parseDouble(yentxt.getText());
                        euro2 = euro2 / 185.75;
                        eurotxt.setText(Double.toString(euro2));
                }
            }
        }
        });

        reset.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e){
                eurotxt.setText("");
                yentxt.setText("");
            }
        });
        JPanel jpanel = new JPanel();

        jpanel.setLayout(new GridLayout(3, 2));
        jpanel.add(euro);
        jpanel.add(eurotxt);
        jpanel.add(yen);
        jpanel.add(yentxt);
        jpanel.add(convertir);
        jpanel.add(reset);

        maFramme.getContentPane().add(jpanel);
        maFramme.setVisible(true);
        maFramme.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    }

    public static void main(String args[]) {
        Fenetre convTest = new Fenetre();
    }
}