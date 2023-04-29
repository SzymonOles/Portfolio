import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.Line2D;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.List;
import javax.swing.*;

public class Start {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new MyFrame();
            }
        });

    }
}

class MyFrame extends JFrame implements ActionListener {

    Drawing panel;
    JButton button;
    File file;
    List<List<Integer>> points = new LinkedList<>();
    List<List<Integer>> lines = new LinkedList<>();
    int maxX;
    int maxY;

    MyFrame() {
        panel = new Drawing();
        button = new JButton("Load");
        button.addActionListener(this);

        this.setSize(800, 800);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLayout(new BorderLayout());

        add(button, BorderLayout.NORTH);
        add(panel);

        this.setVisible(true);
    }

    public void ReadFile() {
        try {
            points.clear();
            lines.clear();
            int number;
            Scanner myReader = new Scanner(file);

            number = Integer.parseInt(myReader.nextLine());

            for (int i = 0; i < number; i++) {
                List<String> strlist;
                String str = myReader.nextLine();
                strlist = Arrays.asList(str.split("\\s+"));

                List<Integer> intlist = new LinkedList<>();
                intlist.add(Integer.parseInt(strlist.get(0)));
                intlist.add(Integer.parseInt(strlist.get(1)) * (-1));
                points.add(intlist);
            }

            number = Integer.parseInt(myReader.nextLine());

            for (int i = 0; i < number; i++) {
                List<String> strlist;
                String str = myReader.nextLine();
                strlist = Arrays.asList(str.split("\\s+"));

                List<Integer> intlist = new LinkedList<>();
                for (String s :
                        strlist) {
                    intlist.add(Integer.parseInt(s));
                }
                lines.add(intlist);
            }

            myReader.close();

            Recalculate();
        } catch (FileNotFoundException ignored) {
            System.out.println("couldn't open file");
        }
    }

    public void Recalculate() {
        int min1 = 0;
        boolean min1in = false;
        int min2 = 0;
        boolean min2in = false;

        for (List<Integer> l :
                points) {
            if (!min1in) {
                min1 = l.get(0);
                min1in = true;
            }
            if (!min2in) {
                min2 = l.get(1);
                min2in = true;
            }
            if (l.get(0) < min1) {
                min1 = l.get(0);
            }
            if (l.get(1) < min2) {
                min2 = l.get(1);
            }
        }

        for (List<Integer> l :
                points) {
            l.set(0, l.get(0) - min1);
            l.set(1, l.get(1) - min2);
        }

        int max1 = 0;
        boolean max1in = false;
        int max2 = 0;
        boolean max2in = false;
        for (List<Integer> l :
                points) {
            if (!max1in) {
                max1 = l.get(0);
                max1in = true;
            }
            if (!max2in) {
                max2 = l.get(1);
                max2in = true;
            }
            if (l.get(0) > max1) {
                max1 = l.get(0);
            }
            if (l.get(1) > max2) {
                max2 = l.get(1);
            }
        }
        maxX = max1;
        maxY = max2;

        int min3 = 0;
        boolean min3in = false;
        for (List<Integer> l :
                lines) {
            if (!min3in) {
                min3 = l.get(2);
                min3in = true;
            }
            if (l.get(2) < min3) {
                min3 = l.get(2);
            }
        }
        if (min3 != 0) {
            for (List<Integer> l :
                    lines) {
                l.set(2, l.get(2) / min3);
            }
        }

        panel.repaint();
    }

    class Drawing extends JPanel {

        int margin = 20;
        int marginx = margin;
        int marginy = margin;
        int height;
        int width;

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2 = (Graphics2D) g;
            g.setColor(Color.BLACK);
            marginx = panel.getWidth() / margin;
            marginy = panel.getHeight() / margin;
            int maxXY = Math.max(maxX, maxY);
            int minmargin = Math.min(marginy, marginx);
            int minsize = Math.min(panel.getWidth() - (2 * minmargin), panel.getHeight() - (2 * minmargin));
            minmargin = minsize / margin;
            int x = 0, x2 = 0;
            int y = 0, y2 = 0;

            for (List<Integer> l :
                    lines) {
                x = points.get(l.get(0) - 1).get(0) * ((minsize- 2*minmargin) / maxX) + minmargin;
                x2 = points.get(l.get(1) - 1).get(0) * ((minsize- 2*minmargin) / maxX) + minmargin;
                y = points.get(l.get(0) - 1).get(1) * ((minsize- 2*minmargin) / maxY) + minmargin;
                y2 = points.get(l.get(1) - 1).get(1) * ((minsize- 2*minmargin) / maxY) + minmargin;

                g2.setStroke(new BasicStroke(l.get(2) * ((float) minmargin / 10)));
                g2.draw(new Line2D.Float(x, y, x2, y2));
            }
            for (List<Integer> l :
                    points) {
                x = l.get(0) * ((minsize- 2*minmargin) / maxX) + minmargin;
                y = l.get(1) * ((minsize- 2*minmargin) / maxY) + minmargin;

                g2.setStroke(new BasicStroke(1 + ((float) minmargin / 10)));
                g2.drawOval(x - minmargin / 2, y - minmargin / 2, minmargin, minmargin);
            }
        }

    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == button) {

            JFileChooser fileChooser = new JFileChooser();
            fileChooser.setCurrentDirectory(new File("."));
            int response = fileChooser.showOpenDialog(null);

            if (response == JFileChooser.APPROVE_OPTION) {
                file = new File(fileChooser.getSelectedFile().getAbsolutePath());
                ReadFile();
            }
        }
        panel.repaint();
    }
}