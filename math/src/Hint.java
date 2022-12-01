import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Hint extends JFrame implements ActionListener {
    //求解结果
    private JPanel jpl = new JPanel();
    private JLabel jlb = new JLabel();
    private JButton jbt = new JButton("确认");

    public void actionPerformed(ActionEvent e)
    {
        this.dispose();
    }

    public void setInformation(String information)
    {
        //设置提示信息
        jlb.setText(information);
    }

    public Hint()
    {
        super("求解结果");
        this.add(jpl);
        jpl.setLayout(null);
        // 设置布局为空

        jpl.add(jlb);
        jlb.setSize(800, 450);
        jlb.setLocation(0, 0);
        jlb.setFont(new Font("Dialog", Font.PLAIN, 25));
        jlb.setHorizontalAlignment(SwingConstants.CENTER);// 文字居中

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