

public class Triangle2D{
	private Point2D p;
	private Point2D d;
	private Point2D g;
	
	Triangle2D(Point2D p, Point2D d, Point2D g){
		this.p = p;
		this.d = d;
		this.g = g;
		if (p.equals(d) || p.equals(g) || g.equals(d)) {
			System.err.println("not a triangle");
		}
	}
	
	public void setP(Point2D p) {
		this.p = p;
	}
	
	public void setD(Point2D d) {
		this.d = d;
	}
	
	public void setG(Point2D g) {
		this.g = g;
	}
	public Point2D getP() {
		return this.p;
	}
	
	public Point2D getD() {
		return this.d;
	}
	
	public Point2D getG() {
		return this.g;
	}
	
	public String toString() {
		return "p : " + p.toString() + "\nd : " + d.toString() + "\ng : " + g.toString() ;
	}
	
	/* public boolean equals(Triangle2D t) { 
		return ((this.p == s.getP() && this.d == s.getD()) ||
				(this.p == s.getD() && this.d == s.getP())
				);
	}
	*/

	public boolean estIsocele() {
		Segment2D s1 = new Segment2D(p, d);
		Segment2D s2 = new Segment2D(d, g);
		Segment2D s3 = new Segment2D(g, p);
		return (s1.norme() == s2.norme() || s1.norme() == s3.norme() || s2.norme() == s3.norme());
	}
	
	public boolean estEquilateral() {
		Segment2D s1 = new Segment2D(p, d);
		Segment2D s2 = new Segment2D(d, g);
		Segment2D s3 = new Segment2D(g, p);
		return (s1.norme() == s2.norme() && s1.norme() == s3.norme());
	}
	
	public boolean estRectangle() {
		Segment2D s1 = new Segment2D(p, d);
		Segment2D s2 = new Segment2D(d, g);
		Segment2D s3 = new Segment2D(g, p);
		return (Math.pow(s1.norme(), 2)) == Math.pow(s2.norme(), 2) + Math.pow(s3.norme(), 2) ||
				Math.pow(s2.norme(), 2) == Math.pow(s1.norme(), 2) + Math.pow(s3.norme(), 2) ||
				Math.pow(s3.norme(), 2) == Math.pow(s2.norme(), 2) + Math.pow(s1.norme(), 2);
	}
	
	public double aire() {
		Segment2D s1 = new Segment2D(p, d);
		Segment2D s2 = new Segment2D(d, g);
		Segment2D s3 = new Segment2D(g, p);
		return Math.sqrt(Math.pow(Math.pow(s1.norme(), 2) + Math.pow(s2.norme(), 2) + Math.pow(s3.norme(), 2) , 2)
						- 2 * (Math.pow(s1.norme(), 4) + Math.pow(s2.norme(), 4) + Math.pow(s3.norme(), 4))) / 4 ;
	}
}