public class Solution
{
	private int count;
	private double[] solutions;
	private boolean minimum;
	private double extremumX;
	private double extremumY;

	public Solution()
	{
		this.count = 0;
		this.solutions = new double[3];
		this.minimum = false;
		this.extremumX = 0;
		this.extremumY = 0;
	}

	public int getCount()
	{
		return count;
	}

	public double getSolution(int i)
	{
		return solutions[i];
	}

	public void addSolution(double solution)
	{
		this.solutions[count++] = solution;
	}

	public boolean isMinimum()
	{
		return minimum;
	}

	public void isMinimum(boolean val)
	{
		this.minimum = val;
	}

	public String getExtremum()
	{
		return extremumX + ";" + extremumY;
	}

	public void setExtremum(double x, double y)
	{
		this.extremumX = x;
		this.extremumY = y;
	}
}