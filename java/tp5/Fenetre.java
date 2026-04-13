
import java.awt.GridLayout;

import javax.swing.*;
import java.awt.BorderLayout;
import java.awt.event.*;

public class Fenetre extends JFrame {
    public Fenetre() {
        JFrame maFramme = new JFrame();
        maFramme.setBounds(100, 100, 500, 1000);
        maFramme.setTitle("j'ai des livres mais j'ai pas d'livres");

        String[] tableauDevises = {
            "Euro",
            "Livre sterling",
            "Dollar americain",
            "Dollar canadien",
            "Franc suisse",
            "Yen japonais",
            "Yuan chinois",
            "Dollar australien",
            "Dollar neo-zelandais",
            "Rouble russe",
            "Roupie indienne",
            "Real bresilien",
            "Peso mexicain",
            "Rand sud-africain",
            "Won sud-coreen",
            "Dirham des Emirats",
            "Riyal saoudien",
            "Livre turque",
            "Couronne suedoise",
            "Couronne norvegienne",
            "Couronne danoise",
            "Zloty polonais",
            "Forint hongrois",
            "Couronne tcheque",
            "Shekel israelien",
            "Peso argentin",
            "Baht thailandais",
            "Ringgit malaisien",
            "Peso philippin",
            "Dong vietnamien"
        };

        JList origine = new JList<>(tableauDevises);
        JList cible = new JList<>(tableauDevises);
        JLabel euro = new JLabel("Euro");
        JLabel yen = new JLabel("Yen");

        JTextField eurotxt = new JTextField("");
        JTextField yentxt = new JTextField("");

        Double[] tauxConversion = {
            1.0,    // Euro
            0.86,   // GBP
            1.08,   // USD
            1.47,   // CAD
            0.96,   // CHF
            162.0,  // JPY
            7.80,   // CNY
            1.65,   // AUD
            1.80,   // NZD
            100.0,  // RUB
            90.0,   // INR
            5.40,   // BRL
            18.5,   // MXN
            20.0,   // ZAR
            1450.0, // KRW
            3.95,   // AED
            4.05,   // SAR
            35.0,   // TRY
            11.5,   // SEK
            11.7,   // NOK
            7.45,   // DKK
            4.30,   // PLN
            390.0,  // HUF
            25.0,   // CZK
            4.00,   // ILS
            950.0,  // ARS
            39.0,   // THB
            5.10,   // MYR
            60.0,   // PHP
            27000.0 // VND
        };
        JButton convertir = new JButton("convertir");
        JButton reset = new JButton("reset");
        convertir.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e){
                if (!eurotxt.getText().equals("")){
                    double euro2 = Double.parseDouble(eurotxt.getText());

                    euro2 = (euro2 / tauxConversion[origine.getSelectedIndex()]) * tauxConversion[cible.getSelectedIndex()];

                    yentxt.setText(Double.toString(euro2));
                }
                else{
                    if (!yentxt.getText().equals("")){
                        double euro2 = Double.parseDouble(yentxt.getText());

                        euro2 = (euro2 / tauxConversion[cible.getSelectedIndex()]) * tauxConversion[origine.getSelectedIndex()];

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
        jpanel.add(origine);
        jpanel.add(eurotxt);
        jpanel.add(cible);
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