package Lab06;

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
	
	public void setX(double x)
	{
		this.x = x;
	}

	public void setY(double y)
	{
		this.y = y;
	}

	public void set(double x, double y)
	{
		setX(x);
		setY(y);
	}
	
	public void set(Point p)
	{
		set(p.x, p.y);
	}

	public Point distanceVector(Point p)
	{
		return new Point(this.x-p.x, this.y-p.y);
	}

	public String toString()
	{
		return "("+x+","+y+")";
	}
}