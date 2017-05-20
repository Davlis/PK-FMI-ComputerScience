package lab06;

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

	public void set(Point a, Point b, Point c, Point d)
	{
		set(new Point[]{a, b, c, d});
	}
}