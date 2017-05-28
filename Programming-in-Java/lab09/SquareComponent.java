package lab09;

import java.awt.*;
import java.util.*;
import javax.swing.*;

public class SquareComponent extends JPanel
{
	private static int initAmountOfSquares = new Random().nextInt(50)+1;
	private boolean isFalling;
	private HashSet<Square> squares;
	private DisplayPanel display;
	private Sound loop;

	public SquareComponent(Dimension size)
	{
		setSize(size);
		setBackground(new Color(0x333333));
		isFalling = true;
		squares = new HashSet<Square>();

		setLayout(new GridBagLayout());

		GridBagConstraints con = new GridBagConstraints();
		con.gridx = 0;
		con.weightx = 100;
		con.fill = GridBagConstraints.BOTH;
		
		con.gridy = 0;
		con.weighty = 97;
		con.anchor = GridBagConstraints.PAGE_START;
		con.insets = new Insets(5, 5, 0, 5);
		display = new DisplayPanel(size);
		add(display, con);

		con.gridy = 1;
		con.weighty = 3;
		con.insets = new Insets(5, 3, 5, 3);
		con.anchor = GridBagConstraints.PAGE_END;
		add(new ButtonPanel(), con);

		for(int i = 0; i < initAmountOfSquares; i++)
			addSquare();

		loop = new Sound("loop.wav");
		loop.loop();
	}

	public void addSquare()
	{
		Square sqr = new Square(display);
		if(isFalling)
			sqr.start();
		
		squares.add(sqr);
	}

	public void startFalling()
	{
		if(isFalling)
			return;

		loop.loop();
		isFalling = true;
		squares.forEach(Square::start);
	}

	public void stopFalling()
	{
		if(!isFalling)
			return;

		loop.stop();
		isFalling = false;
		squares.forEach(Square::stop);
	}

	private class DisplayPanel extends JPanel
	{
		public DisplayPanel(Dimension size)
		{
			setSize(size);
			setLayout(null);
			setBackground(new Color(0x072255));
		}
	}

	private class ButtonPanel extends JPanel
	{
		public ButtonPanel()
		{
			setBackground(new Color(0x333333));
			setLayout(new GridLayout(1, 3)); //FlowLayout(FlowLayout.CENTER, 200, 0));

			JButton button;
			button = new JButton("Stop");
			button.addActionListener(ev -> {
				SquareComponent.this.stopFalling();
			});
			add(button);

			button = new JButton("Another Box");
			button.addActionListener(ev -> {
				SquareComponent.this.addSquare();
			});
			add(button);

			button = new JButton("Start");
			button.addActionListener(ev -> {
				SquareComponent.this.startFalling();
			});
			add(button);
		}
	}
}
