package lab05;

import java.awt.*;

public class Triangle extends Polygon
{	
	public Triangle(Point a, Point b, Point c)
	{
		super(new Point[]{a, b, c});
		setColor(Color.BLUE);
	}

	public Triangle(double[] c)
	{
		this(new Point(c[0], c[1]), new Point(c[2], c[3]), new Point(c[4], c[5]));
	}

	public Triangle(Triangle t)
	{
		this(t.get(0), t.get(1), t.get(2));
	}

	public Triangle set(Point a, Point b, Point c)
	{
		return (Triangle) set(new Point[]{a, b, c});
	}

	public double height(int crn)
	{
		return 2*(this.countArea()/(vertices[(crn+1)%3].distance(vertices[(crn+2)%3])));
	}

	public double countArea()
	{
		return area();
	}

	public double countPerimeter()
	{
		return perimeter();
	}

	public void draw(Graphics g, int offsetX, int offsetY)
	{
		drawFigure(g, offsetX, offsetY);
	}
}