package lab09;

import java.awt.*;
import java.util.*;
import javax.swing.*;

public class SquareComponent extends JPanel
{
	private static int initAmountOfSquares = 1;
	private boolean isFalling;
	private HashSet<Square> squares;
	private DisplayPanel display;

	public SquareComponent(Dimension size)
	{
		setSize(size);
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
		display = new DisplayPanel(size);
		add(display, con);

		con.gridy = 1;
		con.weighty = 3;
		con.insets = new Insets(10, 0, 10, 0);
		con.anchor = GridBagConstraints.PAGE_END;
		add(new ButtonPanel(), con);

		for(int i = 0; i < initAmountOfSquares; i++)
			addSquare();
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

		isFalling = true;
		squares.forEach(Square::start);
	}

	public void stopFalling()
	{
		if(!isFalling)
			return;

		isFalling = false;
		squares.forEach(Square::stop);
	}

	private class DisplayPanel extends JPanel
	{
		public DisplayPanel(Dimension size)
		{
			setSize(size);
			setLayout(null);
			setBackground(new Color(255, 200, 0));
		}
	}

	private class ButtonPanel extends JPanel
	{
		public ButtonPanel()
		{
			setLayout(new FlowLayout(FlowLayout.CENTER, 200, 0)); // or GridLayout(1, 3)

			JButton button;
			button = new JButton("ITS TIME TO STOP");
			button.addActionListener(ev -> SquareComponent.this.stopFalling());
			add(button);

			button = new JButton("ANOTHER ONE");
			button.addActionListener(ev -> SquareComponent.this.addSquare());
			add(button);

			button = new JButton("Start");
			button.addActionListener(ev -> SquareComponent.this.startFalling());
			add(button);
		}
	}
}