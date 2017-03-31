package Lab5;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class FirstJFrame
{	
	public static void main(String[] args)
	{
		Runnable eventHandler = new Runnable()
		{
			public void run(){
				JFrame frame = new JFrame();
				Toolkit kit = Toolkit.getDefaultToolkit();
				Dimension screenSize = kit.getScreenSize();
				FigureComponent comp = new FigureComponent(screenSize.width/2, screenSize.height/2);
		
				frame.setBounds(screenSize.width/4, screenSize.height/4, screenSize.width/2, screenSize.height/2);
				frame.setResizable(false);
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.add(comp);
				frame.setVisible(true);

				System.out.println("Amount of polygons: " + Polygon.getPolygonCount());
				comp.displayPolygonList();
				comp.displayFigureArray();
			}	
		};

		SwingUtilities.invokeLater(eventHandler);
	}
}