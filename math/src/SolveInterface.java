import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.regex.Pattern;

public class SolveInterface implements ActionListener {
    private JFrame mainFrame;
    private java.util.List<JTextField> list = new ArrayList<>();// 增广矩阵的输入
    private JPanel controlPanel = new JPanel();
    private JPanel inputPanel = new JPanel();
    private JLabel headerLabel;
    private JButton sure = new JButton("求解");
    private JButton reset = new JButton("重置");
    private int n;
    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == reset) {
            for (int i = 0; i < list.size(); i++) {
                list.get(i).setText("");
            }
        } else if (e.getSource() == sure) {
            // 正则匹配
            int x = JOptionPane.showConfirmDialog(null, "确认输入正确吗？", "检查输入是否正确", JOptionPane.YES_NO_OPTION);
            if (x == JOptionPane.YES_OPTION) {
                String pattern = "[+-]?\\d+(\\.\\d+)?";
                double[][] a = new double[n + 1][n + 1];
                double[] b = new double[n + 1];
                for (int i = 0; i < n * (n + 1); i++)
                {
                    if (Pattern.matches(pattern, list.get(i).getText()))
                    {
                        if (i % (n + 1) == n)
                        {
                            //最后一列
                            b[i / (n + 1) + 1] = Double.parseDouble(list.get(i).getText());
                        }
                        else
                        {
                            a[i / (n + 1) + 1][i % (n + 1) + 1] = Double.parseDouble(list.get(i).getText());
                        }
                    }
                    else
                    {
                        JOptionPane.showMessageDialog(null, "增广矩阵必须全为数！", "错误", JOptionPane.ERROR_MESSAGE);
                        return;
                    }
                }
                //列主元消元法求解线性方程组
                solve(a, b);
            }
        }
    }

    public void solve(double[][] a, double[] b) {//列主元消元法求解线性方程组
        for (int k = 1; k <= n - 1; k++)
        {
            if (select(a, b, k) == false)//选择主元素
            {
                Hint ht = new Hint();
                ht.setInformation("该方程组不存在唯一解");
                return;
            }
            for (int i = k + 1; i <= n; i++)
            {//消元计算
                double m = a[i][k] / a[k][k];
                for (int j = k + 1; j <= n; j++)
                {
                    a[i][j] -= m * a[k][j];
                }
                b[i] -= m * b[k];
            }
        }
        //已转换为上三角阵，回代求解
        if (Math.abs(a[n][n]) < 1e-20)
        {
            if (Math.abs(b[n]) < 1e-20)
            {
                Hint ht = new Hint();
                ht.setInformation("该方程组存在无穷多组解");
                return;
            }
            else
            {
                Hint ht = new Hint();
                ht.setInformation("该方程组无解");
                return;
            }
        }
        //存在唯一解
        double[] answer = new double[n + 1];//解
        for (int i = n; i >= 1; i--)
        {
            answer[i] = b[i];
            for (int j = i + 1; j <= n; j++)
            {
                answer[i] -= a[i][j] * answer[j];
            }
            answer[i] /= a[i][i];
        }
        String str = new String();
        str = "<html><body>该方程组存在唯一解<br>解如下：";
        for (int i = 1; i <= n; i++)
        {
//            str += "<br>x" + i + " = " + new BigDecimal(answer[i]).setScale(6, BigDecimal.ROUND_HALF_UP).doubleValue();
            str += "<br>x" + i + " = " + answer[i];
        }
        str += "</html></body>";
        Hint ht = new Hint();
        ht.setInformation(str);
    }

    public boolean select(double[][] a, double[] b, int k) {//按列选择主元素
        double max = Math.abs(a[k][k]);
        int maxi = k;
        for (int i = k + 1; i <= n; i++)
        {
            if(Math.abs(a[i][k]) > max)
            {
                max = Math.abs(a[i][k]);
                maxi = i;
            }
        }
        if(max < 1e-14)
        {//主元素极小
            return false;
        }
        else if (maxi != k)
        {//交换
            double num;
            for (int j = k; j <= n; j++)
            {
                num = a[k][j];
                a[k][j] = a[maxi][j];
                a[maxi][j] = num;
            }
            num = b[k];
            b[k] = b[maxi];
            b[maxi] = num;
        }
        return true;
    }

    public SolveInterface(int x) {
        n = x;
        mainFrame = new JFrame("请输入增广矩阵");
        mainFrame.setSize(1500,1000);
        mainFrame.setLocation(210, 10);
        mainFrame.setLayout(new BorderLayout());
        mainFrame.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent windowEvent){
                System.exit(0);
            }
        });

        headerLabel = new JLabel("",JLabel.CENTER );
        headerLabel.setFont(new Font("Dialog", Font.PLAIN, 50));
        headerLabel.setText("请输入增广矩阵");

        JPanel jPanel = new JPanel();
        jPanel.setLayout(new FlowLayout());
        inputPanel.removeAll();
        inputPanel.repaint();
        list.clear();
        inputPanel.setPreferredSize(new Dimension(n * 200, n * 100));
        inputPanel.setLayout(new GridLayout(n, n + 1, 30, 30));
        for (int i = 0; i < n * (n + 1); i++)
        {
            list.add(new JTextField());
            list.get(i).setHorizontalAlignment(JTextField.CENTER);
            list.get(i).setFont(new Font("Dialog", Font.PLAIN, 40));
            inputPanel.add(list.get(i));
        }
        inputPanel.revalidate();
        jPanel.add(inputPanel);

        JPanel panel = new JPanel();
        panel.setSize(200, 200);
        FlowLayout layout = new FlowLayout();
        layout.setHgap(10);
        layout.setVgap(10);
        panel.setLayout(layout);
        sure.setFont(new Font("Dialog", Font.PLAIN, 30));
        sure.addActionListener(this);
        reset.setFont(new Font("Dialog", Font.PLAIN, 30));
        reset.addActionListener(this);
        panel.add(sure);
        panel.add(reset);
        controlPanel.add(panel);


        mainFrame.add(headerLabel, BorderLayout.NORTH);
        mainFrame.add(jPanel, BorderLayout.CENTER);
        mainFrame.add(controlPanel, BorderLayout.SOUTH);
        mainFrame.setVisible(true);
    }
}
