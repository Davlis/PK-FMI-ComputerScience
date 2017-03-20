import java.awt.*;
import java.util.Arrays;

abstract class Figure
{
	protected Point[] vertices;
	private int numberOfVertices;
	private Color figureColor;
	
	protected Figure()
	{
		this.vertices = new Point[0];
	}

	protected Figure(Point[] p)
	{
		this.vertices = Arrays.copyOf(p, numberOfVertices=p.length);
	}
	
	public Point get(int i)
	{
		return vertices[i];
	}
	
	public Figure set(Point p, int i)
	{
		vertices[i] = p;
		return this;
	}
	
	public Figure set(Point[] p)
	{
		this.vertices = Arrays.copyOf(p, numberOfVertices);
		return this;
	}
	
	public double perimeter()
	{
		double out=0;
		for(int i=0; i<numberOfVertices; i++)
			out+=vertices[i].distance(vertices[(i+1)%numberOfVertices]);
		return out;
	}
	
	public double area()
	{
		double out=0;
		for(int i=0; i<numberOfVertices; i++)
			out += vertices[i].getX() * (vertices[(i+1)%numberOfVertices].getY() - vertices[(i+numberOfVertices-1)%numberOfVertices].getY());
		return Math.abs(out) / 2;
	}
	
	public static void sortByArea(Figure[] arr)
	{
		Arrays.sort(arr, (a, b) -> a.area() > b.area() ? 1 : -1);
	}
	
	protected void setColor(Color col)
	{
		figureColor = col;
	}
	
	public void drawFigure(Graphics g, int offsetX, int offsetY)
	{
		Polygon p = new Polygon();
		
		for(int i=0; i<numberOfVertices; i++){
			p.addPoint((int) vertices[i].getX() + offsetX, (int) vertices[i].getY() * -1 + offsetY);
		}
		
		g.setColor(figureColor);
		g.drawPolygon(p);
		g.fillPolygon(p);
	}
}