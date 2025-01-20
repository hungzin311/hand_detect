import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public  class Seat extends JFrame{
    public Seat(){
        setTitle("So do cho ngoi");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5,5));

        for(int i = 1; i<= 25; i++) {
            JButton button = new JButton("Ghe" +  i);
            final int seatNumber = i;
            button.addActionListener(new ActionListener(){
                @Override
                public void actionPerformed(ActionEvent e){showInfoSeat(seatNumber);}
            });
            add(button);
        }
        pack();
        setLocationRelativeTo(null);
    }

    public void showInfoSeat(int seatNumber){
        String seatInfo = "Thong tin ghe " + seatNumber + ":\n";
        JOptionPane.showMessageDialog(this, seatInfo);
    }

    public static  void main(String [] args){
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new Seat().setVisible(true);
            }
        });
    }
}