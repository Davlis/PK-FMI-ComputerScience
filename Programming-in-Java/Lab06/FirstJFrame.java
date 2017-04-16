package Lab06;

import javax.swing.*;
import java.awt.*;

public class FirstJFrame
{	
	public static void main(String[] args)
	{
		Runnable eventHandler = new Runnable()
		{
			public void run(){
				JFrame frame = new JFrame();
				Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
				FigureComponent comp = new FigureComponent();

				frame.setBounds(screenSize.width/4, screenSize.height/4, screenSize.width/2, screenSize.height/2);
				frame.setResizable(true);
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.add(comp);
				frame.setVisible(true);
			}	
		};

		SwingUtilities.invokeLater(eventHandler);
	}
}