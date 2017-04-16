package Lab06;

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

	public void set(Point a, Point b, Point c)
	{
		set(new Point[]{a, b, c});
	}
}