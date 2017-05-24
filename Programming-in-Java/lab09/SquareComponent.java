package lab09;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.time.Instant;
import java.util.ArrayList;

public class SquareComponent extends JPanel
{
	private GridBagLayout layout;
	private static int amountOfBoxes = 0;//2;
	private DisplayPanel displayPanel;
	private ButtonPanel buttonPanel;

	public SquareComponent(int width, int height)
	{
		this.setSize(width, height);

		layout = new GridBagLayout();
		this.setLayout(layout);
		this.setBackground(Color.BLACK);

		GridBagConstraints con = new GridBagConstraints();

		displayPanel = new DisplayPanel(width, (int) height * 4 / 5);
		con.fill = GridBagConstraints.REMAINDER;
		con.gridheight = 9;
		con.gridwidth = 9;
		con.anchor = GridBagConstraints.CENTER;
		layout.setConstraints(displayPanel, con);
		this.add(displayPanel);

		buttonPanel = new ButtonPanel();
		con.gridheight = 1;
		layout.setConstraints(buttonPanel, con);
		this.add(buttonPanel);
	}

	public void repaintAll(){
		displayPanel.repaint();
	}




	private class DisplayPanel extends JPanel
	{
		private ArrayList<Square> squares;

		public DisplayPanel(int width, int height) {
			this.setSize(width, height);
			this.setLayout(new GridLayout(1, 1));
			this.setBackground(Color.YELLOW);
			this.squares = new ArrayList<>();

			for(int i = 0; i < SquareComponent.amountOfBoxes; i++){
				this.addThread();
			}
		}

		@Override
		public void paintComponent(Graphics g)
		{
			for(Square s: this.squares){
				s.drawPolygon(g);
			}
		}

		public void addThread(){
			int xBorder = (int) this.getWidth() - Square.width + 1;
			int yBorder = (int) this.getHeight();
			Square s = new Square(xBorder, yBorder);
			squares.add(s);
			s.start();
		}

		private void start(){
			for(Square t: squares)
				t.notify();
		}

		private void stop(){
			for(Square t: squares) {
				try{
					t.wait();
				}
				catch (InterruptedException ex){
				}
			}
		}
	}

	private class ButtonPanel extends JPanel
	{
		private ArrayList<JButton> buttons;

		public ButtonPanel() {
			this.setLayout(new GridLayout(1, 3, this.getWidth()/11, this.getHeight()/3));

			buttons = new ArrayList<>();
			buttons.add(new JButton("ITS TIME TO STOP"));
			buttons.get(0).addActionListener(event -> SquareComponent.this.displayPanel.stop());
			buttons.add(new JButton("ANOTHER ONE"));
			buttons.get(1).addActionListener(event -> {SquareComponent.amountOfBoxes++; SquareComponent.this.displayPanel.addThread();});
			buttons.add(new JButton("start"));
			buttons.get(2).addActionListener(event -> SquareComponent.this.displayPanel.start());
			for(JButton b: buttons)
				this.add(b);
		}
	}
}