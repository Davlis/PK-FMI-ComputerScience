package Lab5;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Line2D;
import java.util.ArrayList;

@SuppressWarnings("serial")
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
		arr2 = new Figure[]{new Triangle(new double[]{-13, 61, 21, 105, 45, 27}), new Quadrangle(new double[]{-145, 150, -135, 150, -120, 130, -150, 120})};
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
		Graphics2D g2d = (Graphics2D) g;
		Line2D x = new Line2D.Double(0, height/2, width, height/2);
		Line2D y = new Line2D.Double(width/2, 0, width/2, height);
		g2d.setColor(Color.BLACK);
		g2d.draw(x);
		g2d.draw(y);
	}
	
	public void paintComponent(Graphics g)
	{
		drawAxis(g);
		
		for(Polygon p: arr)
			p.draw(g, width/2, height/2);
		for(Figure p: arr2)
			p.draw(g, width/2, height/2);
	}
}