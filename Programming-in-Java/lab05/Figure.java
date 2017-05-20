package lab05;

import java.awt.*;

public interface Figure
{
    void setColor(Color col);
    abstract double countPerimeter();
    abstract double countArea();
    abstract void draw(Graphics g, int offsetX, int offsetY);
}
