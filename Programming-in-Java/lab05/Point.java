package lab05;

public class Point
{
	private double x;
	private double y;
	
	public Point() {
		this(0, 0);
	}

	public Point(double x, double y)
	{
		this.x=x;
		this.y=y;
	}

	public double getX()
	{
		return x;
	}

	public double getY()
	{
		return y;
	}
	
	public Point setX(double x)
	{
		this.x = x;
		return this;
	}

	public Point setY(double y)
	{
		this.y = y;
		return this;
	}

	public Point set(double x, double y)
	{
		setX(x);
		return setY(y);
	}
	
	public Point set(Point pnt)
	{
		return this.set(pnt.x, pnt.y);
	}

	public double distance(Point pnt)
	{
		return Math.sqrt(Math.pow(x-pnt.x, 2) + Math.pow(y-pnt.y, 2));
	}

	public String toString()
	{
		return "("+x+","+y+")";
	}
}