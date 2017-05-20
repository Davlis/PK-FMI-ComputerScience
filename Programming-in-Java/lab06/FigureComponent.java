package lab06;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.util.ArrayList;
import java.time.*;
import java.awt.Cursor;

public class FigureComponent extends JPanel
{
	private ArrayList<Polygon> arr;
	private Point pressedPoint, currentPoint;
	private boolean isBeingDragged;

	public FigureComponent()
	{
		arr = new ArrayList<>();
		addMouseListener(new MouseHandler());
		addMouseMotionListener(new MouseMoutionHandler());
		pressedPoint = new Point();
		currentPoint = new Point();
	}

	@Override
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		for(Polygon pl: arr)
			pl.drawPolygon(g);
	}

	private void add(Point p1, int numberOfVertices)
	{
		if(numberOfVertices==3){
			Point p2 = new Point(p1.getX()+20, p1.getY()-40);
			Point p3 = new Point(p1.getX()+40, p1.getY());
			arr.add(new Triangle(p1, p2, p3));
		}
		else if(numberOfVertices==4){
			Point p2 = new Point(p1.getX()+20, p1.getY()-20);
			Point p3 = new Point(p1.getX()+40, p1.getY());
			Point p4 = new Point(p1.getX()+20, p1.getY()+20);
			arr.add(new Quadrangle(p1, p2, p3, p4));
		}

	}

	private void remove(Point p)
	{
		arr.remove(find(p));
	}

	private Polygon find(MouseEvent e){
		return find(new Point(e.getX(), e.getY()));
	}

	private Polygon find(Point p)
	//searches every Polygon if it contains the point passed to it, null if no match, else returns the objects
	{
		for(Polygon pl: arr){
			if(pl.contains(p))
				return pl;
		}
		return null;
	}

	private class MouseHandler extends MouseAdapter
	{
		private Instant lastTimeClicked, currentTimeClicked;

		public MouseHandler()
		{
			lastTimeClicked = Instant.now();
		}

		@Override
		public void mouseClicked(MouseEvent e)
		{
			if(e.getButton() == MouseEvent.BUTTON1){
				currentTimeClicked = Instant.now();

				if (currentTimeClicked.toEpochMilli() - lastTimeClicked.toEpochMilli() <= 500){
					remove(new Point(e));
					repaint();
				}

				lastTimeClicked = currentTimeClicked;
			}
		}

		@Override
		public void mousePressed(MouseEvent e)
		{
			pressedPoint.set(e);
			Point p = new Point(e);
			if(find(e) == null){
				if(e.getButton() == MouseEvent.BUTTON1) add(p, 3);
				else if(e.getButton() == MouseEvent.BUTTON3) add(p, 4);
				repaint();
			}
		}

		@Override
		public void mouseReleased(MouseEvent e)
		{
			isBeingDragged = false;
		}
	}

	private class MouseMoutionHandler implements MouseMotionListener
	{
		private Point startPoint, endPoint;
		private Polygon pl;

		public MouseMoutionHandler(){
			startPoint = new Point(0,0);
			endPoint = new Point(0,0);
		}

		@Override
		public void mouseDragged(MouseEvent e)
		{
			if(!isBeingDragged){
				startPoint.set(pressedPoint);
				pl = find(startPoint);
				//arr.remove(pl);
				//arr.add(pl);
				isBeingDragged = true;
			}

			if(e.getButton() == MouseEvent.BUTTON1 && pl != null){
				endPoint.set(e);
				pl.move(startPoint, endPoint);
				startPoint.set(endPoint);
				repaint();
			}
		}

		@Override
		public void mouseMoved(MouseEvent e) {
			if(find(e)!=null)
				setCursor(Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
			else
				setCursor(Cursor.getDefaultCursor());
		}
	}
}