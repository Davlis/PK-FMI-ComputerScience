package Lab5;

import java.awt.*;

public interface Figure
{
    void setColor(Color col);
    double countPerimeter();
    double countArea();
    void draw(Graphics g, int offsetX, int offsetY);
}
