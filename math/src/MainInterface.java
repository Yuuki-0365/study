import java.awt.*;
import java.awt.event.*;
import java.util.regex.Pattern;
import javax.swing.*;

public class MainInterface implements ActionListener{
    private JFrame mainFrame;
    private JLabel headerLabel;
    private JPanel controlPanel;
    private JPanel inputPanel;
    private JTextField input = new JTextField();
    private JButton  sure = new JButton("ȷ��");
    private JButton reset = new JButton("����");

    private int n;

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == sure)
        {
            if (input.getText().equals("")) {
                JOptionPane.showMessageDialog(null, "δ֪����������Ϊ�գ�", "����", JOptionPane.ERROR_MESSAGE);
                input.setText("");
            }
            else {
                String pattern = "\\d+"; // �ж��Ƿ�Ϊ����
                if (Pattern.matches(pattern, input.getText()) == true){
                    n = Integer.parseInt(input.getText());
                    if (n == 0)
                    {
                        JOptionPane.showMessageDialog(null, "δ֪����������Ϊ0��", "����", JOptionPane.ERROR_MESSAGE);
                        input.setText("");
                    } else {
                        int x = JOptionPane.showConfirmDialog(null, "ȷ��δ֪������Ϊ"+n+"��", "ȷ�������Ƿ���ȷ", JOptionPane.YES_NO_OPTION);
                        if (x == JOptionPane.YES_OPTION) {
                            new SolveInterface(n);
                        } else if (x == JOptionPane.NO_OPTION) {
                                input.setText("");
                        }
                    }
                }
                else {
                    JOptionPane.showMessageDialog(null, "δ֪����������Ϊ��������", "����", JOptionPane.ERROR_MESSAGE);
                    input.setText("");
                }
            }
        }
        else if (e.getSource() == reset)
        {
            input.setText("");
        }
    }

    public static void main(String[] args) {
        new MainInterface();
    }

    public MainInterface() {
        mainFrame = new JFrame("����Ԫ��Ԫ��������Է�����");
        mainFrame.setSize(1500,1000);
        mainFrame.setLocation(210, 10);
        mainFrame.setLayout(new GridLayout(3, 1));
        mainFrame.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent windowEvent){
                System.exit(0);
            }
        });

        headerLabel = new JLabel("",JLabel.CENTER );
        headerLabel.setFont(new Font("Dialog", Font.PLAIN, 50));
        headerLabel.setText("������δ֪���ĸ���");

        controlPanel = new JPanel();
        controlPanel.setLayout(new FlowLayout());

        inputPanel = new JPanel();
        input.setPreferredSize(new Dimension(100, 50));
        input.setFont(new Font("Dialog", Font.PLAIN, 40));
        input.setHorizontalAlignment(JTextField.CENTER);
        input.addActionListener(this);
        inputPanel.add(input);


        JPanel panel = new JPanel();
        panel.setSize(200, 200);
        FlowLayout layout = new FlowLayout();
        layout.setHgap(10);
        layout.setVgap(10);
        panel.setLayout(layout);
        sure.setFont(new Font("Dialog", Font.PLAIN, 40));
        sure.addActionListener(this);
        reset.setFont(new Font("Dialog", Font.PLAIN, 40));
        reset.addActionListener(this);
        panel.add(sure);
        panel.add(reset);
        controlPanel.add(panel);

        mainFrame.add(headerLabel);
        mainFrame.add(inputPanel);
        mainFrame.add(controlPanel);
        mainFrame.setVisible(true);
    }

}

