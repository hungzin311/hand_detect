import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SeatGUI extends JFrame {

    public SeatGUI() {
        setTitle("Sơ đồ chỗ ngồi");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 5, 5, 5));

        for (int i = 1; i <= 25; i++) {
            JButton button = new JButton("Ghế " + i);

            final int seatNumber = i;
            button.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    showSeatInfo(seatNumber);
                }
            });
            add(button);
        }

        pack();
        setLocationRelativeTo(null);
    }

    private void showSeatInfo(int seatNumber){
        // Giả lập thông tin ghế (trong thực tế, bạn sẽ lấy thông tin từ cơ sở dữ liệu)
        String seatInfo = "Thông tin Ghế " + seatNumber + ":\n\n";
        seatInfo += "Trạng thái: " + (seatNumber % 2 == 0 ? "Đã đặt" : "Trống") + "\n";
        seatInfo += "Giá: " + (50000 + seatNumber * 1000) + " VND\n";
        seatInfo += "Loại ghế: " + (seatNumber % 5 == 0 ? "VIP" : "Thường");

        JOptionPane.showMessageDialog(this, seatInfo, "Thông tin Ghế " + seatNumber, JOptionPane.INFORMATION_MESSAGE);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new SeatGUI().setVisible(true);
            }
        });
    }
}