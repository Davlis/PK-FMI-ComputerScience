public class Calculations
{
	public static void main(String[] args)
	{
		Vector vecA = new Vector(new double[] { 1, 1, 1, 1, 1, 1 });
		Vector vecB = new Vector(new double[] { 2, 2, 2, 2, 2, 2 });
		Vector vecC = new Vector(new double[] { 4, 4, 4 });
		Matrix matrixA = new Matrix(new double[][] {{ 6, 6, 6 }, { 6, 6, 6 }, { 6, 6, 6 }});
		Matrix matrixB = new Matrix(new double[][] {{ 0, 0, 0 }, { 1, 2, 3 }, { 2, 4, 6 }});
		double scalar = 20.0;

		System.out.println("Vector1: " + vecA + "\nVector2: " + vecB + "\nVector3: " + vecC);
		System.out.println("Vector1 + Vector2:\t" + vecA.add(vecB));
		System.out.println("Vector2 after inserted 10 to position number [3]:\t" + vecB.setValue(3, 10));
		System.out.println("Element located at the position 3 of Vector2: " + vecB.getValue(3));
		System.out.println("Dot product of Vector1 and Vecotor2: " + vecA.dotProduct(vecB));
		System.out.println("Scalar: " + scalar);
		System.out.println("Matrix1:\n" + matrixA + "\nMatrix2:\n" + matrixB);
		System.out.println("Matrix1 + Matrix2:\n" + matrixA.add(matrixB));
		System.out.println("Matrix1 after inserted 7 to position [2,1]:\n" + matrixA.setValue(2, 1, 7));
		System.out.println("Element located at the position [2,1] of Matrix1: " + matrixA.getValue(2, 1));
		System.out.println("Vector after multiplied Vector3 by Matrix2:\n" + matrixB.multiply(vecC));
	}
}