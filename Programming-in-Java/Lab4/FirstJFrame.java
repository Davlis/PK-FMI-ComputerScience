import java.awt.*;
import javax.swing.*;


public class FirstJFrame
{	
	public static void main(String[] args)
	{
		EventQueue.invokeLater(() ->
		{
			JFrame frame = new JFrame();
			Toolkit kit = Toolkit.getDefaultToolkit();
			Dimension screenSize = kit.getScreenSize();
			Component comp = new FigureComponent(screenSize.width/4, screenSize.height/4);
			//Container contentPane = getContentPane();
	
			frame.setBounds(screenSize.width/4, screenSize.height/4, screenSize.width/2, screenSize.height/2);
			frame.setResizable(false);
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.add(comp);
			frame.setVisible(true);
		});
	}
}