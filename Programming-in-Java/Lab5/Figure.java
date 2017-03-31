package Lab5;

import java.awt.*;

public interface Figure
{
    public void setColor(Color col);
    public double countPerimeter();
    public double countArea();
    public void draw(Graphics g, int offsetX, int offsetY);
}
