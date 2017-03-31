package Lab5;

import java.awt.*;
import java.util.Arrays;

abstract class Polygon implements Figure
{
	protected Point[] vertices;
	private int numberOfVertices;
	private Color figureColor;

	private int polygonNumber;
	private static int polygonCount;

	protected Polygon(Point[] p)
	{
		this.vertices = Arrays.copyOf(p, numberOfVertices=p.length);
		this.polygonCount++;
		this.polygonNumber = this.polygonCount;
	}

	public Point get(int i)
	{
		return vertices[i];
	}

	public int getPolygonNumber()
	{
		return this.polygonNumber;
	}

	public static int getPolygonCount()
	{
		return polygonCount;
	}

	public Polygon set(Point p, int i)
	{
		vertices[i] = p;
		return this;
	}

	public Polygon set(Point[] p)
	{
		this.vertices = Arrays.copyOf(p, numberOfVertices);
		return this;
	}

	public void setColor(Color col)
	{
		figureColor = col;
	}

	public void draw(Graphics g, int offsetX, int offsetY)
	{
		java.awt.Polygon p = new java.awt.Polygon();

		for(int i=0; i<numberOfVertices; i++){
			p.addPoint((int) vertices[i].getX() + offsetX, (int) vertices[i].getY() * -1 + offsetY);
		}

		g.setColor(figureColor);
		g.drawPolygon(p);
		g.fillPolygon(p);
	}

	public double countPerimeter()
	{
		double out=0;
		for(int i=0; i<numberOfVertices; i++)
			out+=vertices[i].distance(vertices[(i+1)%numberOfVertices]);
		return out;
	}
	
	public double countArea()
	{
		double out=0;
		for(int i=0; i<numberOfVertices; i++)
			out += vertices[i].getX() * (vertices[(i+1)%numberOfVertices].getY() - vertices[(i+numberOfVertices-1)%numberOfVertices].getY());
		return Math.abs(out) / 2;
	}
	
	public static void sortByArea(Polygon[] arr)
	{
		Arrays.sort(arr, (a, b) -> a.countArea() > b.countArea() ? 1 : -1);
	}

	public String toString()
	{
		return "Number: " + this.polygonNumber + "\t\tArea: " + this.countArea() + "\t\tPerimeter: " + this.countPerimeter();
	}


	
	/*private void checkPoints(){
		ArrayList<Integer> dat = new ArrayList<Integer>();
		for(int i = 0; i < numberOfVertices; i++)
			data.add(i);
		
		int[] data;
		dat.toArray();
		
		VectorListener<Integer> listener = new VectorListener<Integer>(){
		    @Override
		    public void action(Integer[] vector) {
		    	Quadrangle Q = new Quadrangle(p[vector[0]], p[vector[1]], p[vector[2]], p[vector[3]]);
		        System.out.println(Q.area());
		    }
		};
		        
		        
		PermutationGenerator perm = new PermutationGenerator(data, listener);
		perm.generate(new AntylexStrategy());
	}*/
}