package Lab06;

import java.awt.*;
import java.util.Arrays;

abstract class Polygon
{
	protected Point[] vertices;
	private int numberOfVertices;
	private Color figureColor;

	protected Polygon(Point[] p)
	{
		this.vertices = Arrays.copyOf(p, numberOfVertices=p.length);
	}

	public void setColor(Color col)
	{
		figureColor = col;
	}

	public Point get(int i)
	{
		return vertices[i];
	}

	public void set(Point p, int i)
	{
		vertices[i] = p;
	}

	public void set(Point[] p)
	{
		this.vertices = Arrays.copyOf(p, numberOfVertices);
	}

	public void move(Point start, Point end)
	{
		Point vector = end.distanceVector(start);

		for(Point px: vertices)
			px.set(px.getX()+vector.getX(), px.getY()+vector.getY());
	}

	public java.awt.Polygon getPolygon()
	{
		java.awt.Polygon p = new java.awt.Polygon();
		for(int i=0; i<numberOfVertices; i++){
			p.addPoint((int) vertices[i].getX(), (int) vertices[i].getY());
		}
		return p;
	}

	public void drawPolygon(Graphics g)
	{
		java.awt.Polygon p = this.getPolygon();
		g.setColor(figureColor);
		g.drawPolygon(p);
		g.fillPolygon(p);
	}
}

