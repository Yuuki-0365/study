import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Hint extends JFrame implements ActionListener {
    //�����
    private JPanel jpl = new JPanel();
    private JLabel jlb = new JLabel();
    private JButton jbt = new JButton("ȷ��");

    public void actionPerformed(ActionEvent e)
    {
        this.dispose();
    }

    public void setInformation(String information)
    {
        //������ʾ��Ϣ
        jlb.setText(information);
    }

    public Hint()
    {
        super("�����");
        this.add(jpl);
        jpl.setLayout(null);
        // ���ò���Ϊ��

        jpl.add(jlb);
        jlb.setSize(800, 450);
        jlb.setLocation(0, 0);
        jlb.setFont(new Font("Dialog", Font.PLAIN, 25));
        jlb.setHorizontalAlignment(SwingConstants.CENTER);// ���־���

        jpl.add(jbt);
        jbt.setSize(100, 50);
        jbt.setLocation(350, 450);
        jbt.setFont(new Font("Dialog", Font.PLAIN, 18));
        jbt.addActionListener(this);

        this.setSize(800, 600);
        this.setLocation(1000, 550);
        this.setVisible(true);
    }
}