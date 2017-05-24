package lab09;

import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class Square extends Thread
{
	private int x;
	private int y;
	public final static int height = 10;
	public final static int width = 10;

	private final int xBorder;
	private final int yBorder;
	private final Color squareColor = this.generateColor();
	private final int pixelsPerFrame = new Random().nextInt(10) + 1;

	public Square(int xBorder, int yBorder){
        this.xBorder = xBorder;
        this.yBorder = yBorder;
        this.set(new Random().nextInt(this.xBorder), -Square.height);
    }

	private void moveSquare(int x, int y) {
		this.x += x;
		this.y += y;
    }

	private void set(int x, int y){
        this.x = x;
        this.y = y;
	}

    private Color generateColor(){
        Random r = new Random();
        int red = r.nextInt(256);
        int green = r.nextInt(256);
        int blue = r.nextInt(256);
        return new Color(red, green, blue);
    }

    public java.awt.Polygon getPolygon()
    {
        java.awt.Polygon p = new java.awt.Polygon();
        p.addPoint(this.x, this.y);
        p.addPoint(this.x + Square.width, this.y);
        p.addPoint(this.x + Square.width, this.y + Square.height);
        p.addPoint(this.x, this.y + Square.height);
        return p;
    }

    public void drawPolygon(Graphics g) {
        java.awt.Polygon p = this.getPolygon();
        g.setColor(this.squareColor);
        g.drawPolygon(p);
        g.fillPolygon(p);
    }


    public void run() {
        while(true){
            Square.this.moveSquare(0, Square.this.pixelsPerFrame);
            try{
                this.wait(0, (int) 1000/60);
            } catch (InterruptedException ex){

            }

            if(Square.this.y >= Square.this.yBorder)
                Square.this.set(new Random().nextInt(xBorder), -Square.height);

            //SquareComponent.repaintAll();
        }
    }

}