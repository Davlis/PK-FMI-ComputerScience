package lab09;

import javax.swing.*;
import java.awt.*;

public class FallFrame
{
	public static void main(String[] args)
	{
		Runnable eventHandler = new Runnable()
		{
			public void run(){
				JFrame frame = new JFrame();
				Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
				SquareComponent comp = new SquareComponent(screenSize.width/2, screenSize.height/2);

				frame.setBounds(screenSize.width/4, screenSize.height/4, screenSize.width/2, screenSize.height/2);
				frame.setResizable(false);
				frame.setTitle("Lab09 Kamil Kosiński");
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.add(comp);
				frame.setVisible(true);
			}	
		};

		SwingUtilities.invokeLater(eventHandler);
	}
}