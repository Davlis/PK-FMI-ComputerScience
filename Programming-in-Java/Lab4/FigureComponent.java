import java.awt.*;

import javax.swing.*;

public class FigureComponent extends JPanel
{
	int width, height;
	
	public FigureComponent(int width, int height){
		this.width = width;
		this.height = height;
	}
	
	public void paintComponent(Graphics g)
	{
		Triangle T1 = new Triangle(new Point(12,38), new Point(40, 12), new Point(78,30));
		Triangle T2 = new Triangle(new Point(-150,-125), new Point(125,-175), new Point(-50,-68));
		Triangle[] arrayT = new Triangle[]{T1, T2};
		Quadrangle Q1 = new Quadrangle(new double[]{-120, 10, -110, 150, -50, 90, -30, 50});
		Quadrangle Q2 = new Quadrangle(new double[]{100, -150, 110, 120, 140, -10, 135, -50});
		Quadrangle[] arrayQ = new Quadrangle[]{Q1, Q2};
		
		for(int i=0; i<2; i++){
			arrayT[i].drawFigure(g, width, height);
			arrayQ[i].drawFigure(g, width, height);
		}
	}
}