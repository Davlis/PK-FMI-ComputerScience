package lab09;

import java.awt.*;
import java.util.*;
import java.util.concurrent.atomic.*;

import javax.swing.*;

public class Square extends JPanel
{
    public static final int DEFAULT_SIZE = 10;
    private final JPanel parent;
    private final Position position;
    private final double speed;
    private final int border;
    private final AtomicBoolean flag;
    private Thread falling;

    public Square(final JPanel parent)
    {
        this(parent, DEFAULT_SIZE);
    }

    public Square(final JPanel parent, int size)
    {
        this.parent = parent;
        flag = new AtomicBoolean();
        border = parent.getHeight();
        speed = new Random().nextDouble() * 8 + 0.5;
        position = new Position(new Random().nextInt(parent.getWidth()), 0);

        setSize(new Dimension(size, size));
        setLocation(position.toPoint());
        setBackground(randomColor());

        parent.add(this);
        parent.repaint();
    }

    public void start()
    {
        flag.set(true);
        falling = new Thread(() -> {
            while(flag.get())
            {
                position.translate(0, speed);
                if(position.getY() > border)
                    position.setY(0);
                    
                setLocation(position.toPoint());
                parent.repaint();

                try {
                    Thread.sleep(16);
                } catch (InterruptedException ex) {
                    break;
                }
            }
        });
        falling.start();
    }

    public void stop()
    {
        flag.set(false);
        falling.interrupt();
    }

    private Color randomColor()
    {
        Random rnd = new Random();
        return new Color(rnd.nextInt(256), rnd.nextInt(256), rnd.nextInt(256));
    }

    private class Position
    {
        private double x;
        private double y;

        public Position(double x, double y)
        {
            this.x = x;
            this.y = y;
        }

        public void setX(double x)
        {
            this.x = x;
        }

        public double getX()
        {
            return x;
        }

        public void setY(double y)
        {
            this.y = y;
        }

        public double getY()
        {
            return y;
        }

        public void translate(double dx, double dy)
        {
            x += dx;
            y += dy;
        }

        public Point toPoint()
        {
            return new Point((int) x, (int) y);
        }

        public String toString()
        {
            return "[ " + x + " , " + y + " ]";
        }
    }
}