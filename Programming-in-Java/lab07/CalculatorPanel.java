package lab07;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import javax.swing.ImageIcon;

public class CalculatorPanel extends JPanel
{
	private final int width, height;
	private TextPanel text;
	private ButtonPanel button;

	public CalculatorPanel(int width, int height)
	{
		this.width = width;
		this.height = height;
		this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
		text = new TextPanel();
		button = new ButtonPanel();
		this.add(text);
		this.add(button);
	}

	private class TextPanel extends JPanel
	{
		private JTextField textField;
		private StringBuilder expression;
		private Boolean isToBeErased;

		TextPanel()
		{
			textField = new JTextField();
			textField.setEditable(false);
			textField.setFont(new Font("Helvetica", Font.PLAIN,16));
			this.setLayout(new GridLayout());
			this.add(textField);
			isToBeErased = false;
			expression = new StringBuilder();
		}

		void add(String c)
		{
			expression.append(c);
			textField.setText(expression.toString());
		}

		void clear()
		{
			expression.delete(0, expression.length());
			textField.setText(expression.toString());
		}

		void backspace()
		{
			if(isToBeErased){
				this.clear();
				isToBeErased = false;
			}

			if(!textField.getText().isEmpty()){
				expression.deleteCharAt(expression.length()-1);
				textField.setText(expression.toString());
			}
		}

		void equals()
		{
			ReversPolishNotation rpn = new ReversPolishNotation(expression.toString());
			expression = new StringBuilder(rpn.solve());
			textField.setText(this.expression.toString());
			isToBeErased = true;
		}
	}

	private class ButtonPanel extends JPanel
	{
		private GridLayout layout;
		private ArrayList<JButton> buttons;

		public ButtonPanel()
		{
			layout = new GridLayout(5, 4, this.getWidth()/15, this.getHeight()/19);
			this.setLayout(layout);

			String[] str = {"CE", "<-", "(", ")", "7", "8", "9", "/", "4", "5", "6", "*", "1", "2", "3", "-", ".", "0", "=", "+"};
			buttons = new ArrayList<>();

			for(String s: str)
				buttons.add(new JButton(s));

			for(JButton b: buttons){
				switch(b.getLabel()){
					case "CE": b.addActionListener(event -> text.clear()); break;
					case "<-": b.addActionListener(event -> text.backspace()); break;
					case "=": b.addActionListener(event -> text.equals()); break;
					default: b.addActionListener(event -> text.add(b.getLabel()));
				}
				this.add(b);
			}
		}
	}
}