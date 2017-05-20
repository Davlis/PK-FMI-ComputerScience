package lab05;

import java.awt.*;

public class Quadrangle extends Polygon
{
	public Quadrangle(Point a, Point b, Point c, Point d)
	{
		super(new Point[]{a, b, c, d});
		setColor(Color.GREEN);
	}
	
	public Quadrangle(double[] c)
	{
		this(new Point(c[0], c[1]), new Point(c[2], c[3]), new Point(c[4], c[5]), new Point(c[6], c[7]));
	}
	
	public Quadrangle(Quadrangle q)
	{
		this(q.get(0), q.get(1), q.get(2), q.get(3));
	}
	
	public Quadrangle set(Point a, Point b, Point c, Point d)
	{
		return (Quadrangle) set(new Point[]{a, b, c, d});
	}
	
	public double diagonal(int i)
	{
		return vertices[i].distance(vertices[(i+2)%4]);
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