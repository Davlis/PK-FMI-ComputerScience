package lab08;

import java.util.Arrays;

public class Vector
{
	private double[] vect;
	
	public Vector()
	{
		this(0);
	}
	
	public Vector(int size)
	{
		vect = new double[size];
	}
	
	public Vector(double[] arr)
	{
		vect = Arrays.copyOf(arr, arr.length);
	}
	
	public Vector(Vector copy)
	{
		vect = Arrays.copyOf(copy.vect, copy.vect.length);
	}
	
	public Vector setValue(int a)
	{
		return this.setValue(a, 0);
	}
	
	public Vector setValue(int a, double val)
	{
		vect[a]=val;
		return this;
	}
	
	public double getValue(int a)
	{
		return vect[a];
	}
	
	public int getSize()
	{
		return vect.length;
	}
	
	public Vector add(Vector a){
		Vector out = new Vector(this);
		for(int tmp=0; tmp<out.vect.length&&tmp<a.vect.length; tmp++)
			out.vect[tmp]+=a.vect[tmp];
		return out;
	}
	
	public Vector multiply(double scalar)
	{
		Vector out = new Vector(this);
		for(int i=0; i<out.vect.length; i++)
			out.vect[i]*=scalar;
		return out;
	}

	public Vector simple_multiplication(Vector v){
		if(this.vect.length != v.vect.length)
			return null;

		Vector out = new Vector(this.vect.length);
		for(int i = 0; i < this.vect.length; i++){
			out.setValue(i, (this.getValue(i)*v.getValue(i)));
		}
		return out;
	}

	public double dotProduct(Vector vector)
	{
		double out=0.0;

		for(int i=0; i<vect.length; i++)
			out+=vect[i]*vector.getValue(i);

		return out;
	}
	
	public String toString()
	{
		String out = "";

		for(int i=0; i<vect.length; i++)
			out+="["+i+"]"+vect[i]+"\t";

		return out;
	}
}