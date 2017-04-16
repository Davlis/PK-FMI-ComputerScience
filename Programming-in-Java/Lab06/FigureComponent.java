package Lab06;

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
	private final int width, height;
	private ArrayList<Triangle> arr;
	private Point pressedPoint;
	private boolean isBeingDragged;

	public FigureComponent(int width, int height)
	{
		this.width = width;
		this.height = height;

		arr = new ArrayList<Triangle>();
		addMouseListener(new MouseHandler());
		addMouseMotionListener(new MouseMoutionHandler());
		pressedPoint = new Point(0, 0);
	}

	public void paintComponent(Graphics g)
	{
		for(Triangle t: arr)
			t.drawPolygon(g);
	}

	private void add(Point p1)
	{
		Point p2 = new Point(p1.getX()+20, p1.getY()-40);
		Point p3 = new Point(p1.getX()+40, p1.getY());
		arr.add(new Triangle(p1, p2, p3));
	}

	private void remove(Point p)
	{
		Triangle t = find(p);
		if(t==null)
			return;
		arr.remove(t);
	}

	private Triangle find(Point p)
	{
		if(arr.size()<=0)
			return null;

		for(Triangle t:arr){
			if(t.getPolygon().contains(p.getX(), p.getY()))
				return t;
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
					remove(new Point(e.getX(), e.getY()));
					repaint();
				}

				lastTimeClicked = currentTimeClicked;
			}
		}

		@Override
		public void mousePressed(MouseEvent e)
		{
			pressedPoint.set(e.getX(), e.getY());
			if(e.getButton() == MouseEvent.BUTTON1){
				Point p = new Point(e.getX(), e.getY());
				if(find(p) == null){
					add(p);
					repaint();
				}
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
		private Triangle t;

		public MouseMoutionHandler(){
			startPoint = new Point(0,0);
			endPoint = new Point(0,0);
		}

		@Override
		public void mouseDragged(MouseEvent e)
		{
			if(!isBeingDragged){
				startPoint.set(pressedPoint);
				t = find(startPoint);
				isBeingDragged = true;
			}

			if(e.getButton() == MouseEvent.BUTTON1){
				if(t!=null){
					endPoint.set(e.getX(), e.getY());
					t.move(startPoint, endPoint);
					startPoint.set(endPoint);
					repaint();
				}
			}
		}

		@Override
		public void mouseMoved(MouseEvent e) {
			if(find(new Point(e.getX(), e.getY()))!=null)
				setCursor(Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
			else
				setCursor(Cursor.getDefaultCursor());
		}
	}

}