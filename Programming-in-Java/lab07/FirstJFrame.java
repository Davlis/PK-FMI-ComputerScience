package lab07;

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
				int calcWidth = screenSize.width/6;
				int calcHeight = screenSize.height/2;

				frame.setBounds(calcWidth/2, calcHeight/2, calcWidth, calcHeight);
				frame.setResizable(true);
				frame.setTitle("Lab07 Kamil Kosiński");
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.add(new CalculatorPanel(calcWidth, calcHeight));
				frame.setVisible(true);
			}	
		};

		SwingUtilities.invokeLater(eventHandler);
	}
}