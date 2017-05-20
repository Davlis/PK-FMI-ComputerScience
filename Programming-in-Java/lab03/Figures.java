package lab03;

public class Figures
{
	public static void main(String[] args)
	{
		Point P1 = new Point(1, 2);
		Point P2 = new Point(2, -3);
		Triangle T1 = new Triangle(new Point(0,0), new Point(4,0), new Point(4,3));
		Triangle T2 = new Triangle(new Point(0,0), new Point(4,3), new Point(3,11));
		Triangle T3 = new Triangle(new Point(-1,2), new Point(4,1), new Point(6, 5));
		Triangle T4 = new Triangle(new Point(1,0), new Point(4,0), new Point(4,3));
		Triangle[] arrayT = new Triangle[]{T1, T2, T3, T4};
		Quadrangle Q1 = new Quadrangle(new double[]{0, 0, 4, 0, 4, 3, 0, 5});
		Quadrangle Q2 = new Quadrangle(new double[]{1, 0, 4, 0, 4, 3, 1, 5});
		Quadrangle Q3 = new Quadrangle(new double[]{2, 0, 4, -1, 4, 3, -2, 5});
		Quadrangle Q4 = new Quadrangle(new double[]{3, 0, 4, -2, 4, 3, -1, 5});
		Quadrangle[] arrayQ = new Quadrangle[]{Q1, Q2, Q3, Q4};
		
		System.out.println("P1=" + P1 + "\tP2=" + P2);
		System.out.println("Coordinate y of the point P1: " + P1.getY());
		System.out.println("The distance between P1 and P2: " + P1.distance(P2));
		System.out.println("P1 after update to P2: " + P1.set(P2));
		System.out.println("Triangle: " + T1);
		System.out.println("Perimeter: " + T1.perimeter() + "  Area: "+ T1.area() + "  Height from coordinate A: " + T1.height(0));
		System.out.println("Coordinate0" + T1.get(0) + "  Coordinate1" + T1.get(1) + "  Coordinate2" + T1.get(2));
		System.out.println("Triangle after update coordinate A:" + T1.set(P2, 0));
		System.out.println("Quadrangle: " + Q1);
		System.out.println("Perimeter: " + Q1.perimeter() + "  Diagonal from coordinate A to C: " + Q1.diagonal(0));
		System.out.println("Area: " + Q1.area());
		System.out.println("Coordinate0" + Q1.get(0) + "  Coordinate1" + Q1.get(1) + "  Coordinate2" + Q1.get(2) + "  Coordinate3" + Q1.get(3));
		System.out.println("Quadrangle after update coordinate A:" + Q1.set(P2, 0));
		System.out.println("An array of triangles:\n" + arrayT[0].area() + "\n" + arrayT[1].area() + "\n" + arrayT[2].area() + "\n" + arrayT[3].area());
		Figure.sortByArea(arrayT);
		System.out.println("An array after sorting triangles according to area:\n" + arrayT[0].area() + "\n" + arrayT[1].area() + "\n" + arrayT[2].area() + "\n" + arrayT[3].area());
		System.out.println("An array of quadrangles:\n" + arrayQ[0].area() + "\n" + arrayQ[1].area() + "\n" + arrayQ[2].area() + "\n" + arrayQ[3].area());
		Figure.sortByArea(arrayQ);
		System.out.println("An array after sorting quadrangles according to area:\n" + arrayQ[0].area() + "\n" + arrayQ[1].area() + "\n" + arrayQ[2].area() + "\n" + arrayQ[3].area());
	}
}