import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class TimeUDPClient {
    private static boolean isPaused = false;
    private static DatagramSocket clientSocket;
    private static InetAddress serverAddress;
    private static int serverPort = 9876;

    public static void main(String[] args) {
        JFrame frame = new JFrame("Time UDP Client");
        JLabel timeLabel = new JLabel("Waiting for time...", SwingConstants.CENTER);
        JButton pauseButton = new JButton("Pause");
        JButton resumeButton = new JButton("Resume");

        frame.setLayout(new BoxLayout(frame.getContentPane(), BoxLayout.Y_AXIS));
        frame.add(timeLabel);
        frame.add(pauseButton);
        frame.add(resumeButton);

        frame.setSize(300, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);

        try {
            clientSocket = new DatagramSocket();
            serverAddress = InetAddress.getByName("localhost");

            pauseButton.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    sendMessage("pause");
                }
            });

            resumeButton.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    sendMessage("resume");
                }
            });

            new Thread(() -> {
                while (true) {
                    try {
                        byte[] receiveData = new byte[1024];
                        DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                        clientSocket.receive(receivePacket);

                        String receivedTime = new String(receivePacket.getData(), 0, receivePacket.getLength());
                        timeLabel.setText("Current Time: " + receivedTime);
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }
                }
            }).start();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void sendMessage(String message) {
        try {
            byte[] sendData = message.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, serverAddress, serverPort);
            clientSocket.send(sendPacket);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
