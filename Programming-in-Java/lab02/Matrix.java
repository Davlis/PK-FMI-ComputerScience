package lab02;

import java.util.Arrays;

public class Matrix
{
	private double[][] matrix;
	
	public Matrix()
	{
		this(0);
	}
	
	public Matrix(int a)
	{
		matrix = new double[a][a];
	}
	
	public Matrix(double[][] arr)
	{
		matrix = new double[arr.length][arr.length];
		for(int i=0; i<matrix.length; i++)
			matrix[i] = Arrays.copyOf(arr[i], arr.length);
	}
	
	public Matrix(Matrix copy)
	{
		this(copy.matrix);
	}
	
	public Matrix setValue(int a, int b)
	{
		return this.setValue(a, b, 0);
	}
	
	public Matrix setValue(int a, int b, double val)
	{
		matrix[a][b]=val;
		return this;
	}
	
	public double getValue(int a, int b)
	{
		return matrix[a][b];
	}
	
	public Matrix add(Matrix a)
	{
		Matrix out = new Matrix(this);
		
		for(int i=0; i<out.matrix.length; i++)
			for(int j=0; j<out.matrix.length; j++)
				out.matrix[i][j]+=a.getValue(i, j);
		
		return out;
	}
	
	public Vector multiply(Vector vector)
	{
		if(vector.getSize()!=matrix.length){
			System.out.println("Wrong matrix size");
			return null;
		}
		
		Vector out = new Vector(vector.getSize());
		
		for(int i=0; i<matrix.length; i++)
		{
			for(int j=0; j<matrix.length; j++)
				out.setValue(i, out.getValue(i) + matrix[i][j] * vector.getValue(i));
		}

		return out;
	}
	
	public String toString()
	{
		String out = "";

		for(int i=0; i<matrix.length; i++)
		{
			for(int j=0; j<matrix.length; j++)
				out+="["+i+","+j+"]"+matrix[i][j]+"\t";
			out+="\n";
		}

		return out;
	}
}