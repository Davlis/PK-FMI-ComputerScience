package lab09;

import java.awt.*;
import javax.swing.*;

public class FallFrame extends JFrame
{
	public FallFrame()
	{
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();

		add(new SquareComponent(new Dimension(screenSize.width / 2, screenSize.height / 2)));

		setBounds(screenSize.width / 4, screenSize.height / 4, screenSize.width / 2, screenSize.height / 2);
		setTitle("Lab09 Kamil Kosiński");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setResizable(true);
		setVisible(true);
	}

	public static void main(String[] args)
	{
		SwingUtilities.invokeLater(FallFrame::new);
	}
}