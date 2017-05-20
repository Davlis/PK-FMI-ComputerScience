public class Polynomial
{
	private double a;
	private double b;
	private double c;
	private Solution solution;
	

	public Polynomial()
	{
		this(0, 0, 0);
	}

	public Polynomial(double b, double c)
	{
		this(0, b, c);
	}

	public Polynomial(double a, double b, double c)
	{
		this.a = a;
		this.b = b;
		this.c = c;
		this.solution = new Solution();

		if(a == 0){
			if(b != 0)
				solution.addSolution(-1 * c / b);
		}else{
			double delta = b * b - 4 * a * c;
			double sqrtDelta = Math.sqrt(Math.abs(delta));

			if(delta > 0){
				solution.addSolution((-1 * b + sqrtDelta) / (2 * a));
				solution.addSolution((-1 * b - sqrtDelta) / (2 * a));
			}else if(delta == 0){
				solution.addSolution((-1 * b) / (2 * a));
			}else if(delta < 0){
				solution.addSolution((-1 * b) / (2 * a));
				solution.addSolution(sqrtDelta / (2 * a));
				solution.addSolution((-1 * sqrtDelta) / (2 * a));
			}
			
			solution.isMinimum(a > 0);
			solution.setExtremum((-1 * b) / (2 * a), (-1 * delta) / (4 * a));
		}
	}

	public String toString()
	{
		String str = "";

		if(a != 0) str += (a < 0 ? "" : "+") + a + "x^2";
		if(b != 0) str += (b < 0 ? "" : "+") + b + "x";
		str += (c < 0 ? "" : "+") + c;

		if(str.charAt(0) == '+') str = str.substring(1);

		if(!str.equals("")) str += "\nRównanie ";
		switch(solution.getCount()){
			case 0 :
				str += (c == 0 ? "ma nieskończenie wiele pierwiastków." : "nie ma pierwiastków.");
				break;
			case 1 :
				str += "ma jeden pierwiastek" + (a != 0 ? " podwójny" : "") + ": x1 = " + solution.getSolution(0);
				break;
			case 2 :
				str += "ma dwa pierwiastki: x1 = " + solution.getSolution(0) + ", x2 = " + solution.getSolution(1);
				break;
			case 3:
				str += "ma dwa pierwiastki zespolone: x1 = " + solution.getSolution(0) + "+" + solution.getSolution(1) + "i, x2 = " + solution.getSolution(0) + solution.getSolution(2) + "i";
				break;
		}

		if(!str.equals("") && a != 0)
			str += "\nFunkcja ma " + (solution.isMinimum() ? "minimum" : "maksimum") + " w punkcie (" + solution.getExtremum() + ")";
			
		return str + "\n";
	}
}