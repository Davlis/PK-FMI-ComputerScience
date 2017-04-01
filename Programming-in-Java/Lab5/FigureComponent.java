package Lab5;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Line2D;
import java.util.ArrayList;

public class FigureComponent extends JPanel
{
	private int width, height;
	private ArrayList<Polygon> arr;
	private Figure[] arr2;
	
	public FigureComponent(int width, int height)
	{
		this.width = width;
		this.height = height;

		arr = new ArrayList<Polygon>();
		arr.add(new Triangle(new Point(12,38), new Point(40, 12), new Point(78,30)));
		arr.add(new Triangle(new Point(-150,-125), new Point(125,-175), new Point(-50,-68)));
		arr.add(new Quadrangle(new double[]{-120, 10, -110, 150, -50, 90, -30, 50}));
		arr.add(new Quadrangle(new double[]{100, -150, 110, 120, 140, -10, 135, -50}));
		arr2 = new Figure[]{new Triangle(new double[]{-153, 61, -119, 105, -65, 77}), new Quadrangle(new double[]{-75, -120, -35, -120, -20, -100, -50, -90})};
	}

	public void displayPolygonList()
	{
		System.out.println("List of polygons:");
		for(Polygon p: arr)
			System.out.println(p);
	}

	public void displayFigureArray()
	{
		System.out.println("Array of figures:");
		for(Figure p: arr2)
			System.out.println(p);
	}

	private void drawAxis(Graphics g){
		g.setColor(Color.BLACK);
		g.drawLine(0, height/2, width, height/2);
		g.drawLine(width/2, 0, width/2, height);
	}
	
	public void paintComponent(Graphics g)
	{
		//drawAxis(g);
		
		for(Polygon p: arr)
			p.draw(g, width/2, height/2);
		for(Figure p: arr2)
			p.draw(g, width/2, height/2);
	}
}