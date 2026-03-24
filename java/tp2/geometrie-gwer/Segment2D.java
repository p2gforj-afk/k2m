public class Segment2D{
	private Point2D p;
	private Point2D d;
	
	Segment2D(Point2D p, Point2D d){
		this.p = p;
		this.d = d;
		if (p.equals(d)) {
			System.err.println("meme point");
		}
	}
	
	public void setP(Point2D p) {
		this.p = p;
	}
	
	public void setD(Point2D d) {
		this.d = d;
	}
	
	public Point2D getP() {
		return this.p;
	}
	
	public Point2D getD() {
		return this.d;
	}
	
	public String toString() {
		return "p : " + p.toString() + "\nd : " + d.toString();
	}
	
	public boolean equals(Segment2D s) {
		return ((this.p == s.getP() && this.d == s.getD()) ||
				(this.p == s.getD() && this.d == s.getP())
				);
	}
	
	public double norme() {
		return Math.sqrt(Math.pow(this.p.getX() - this.d.getX(),2))+(Math.pow(this.p.getY() - this.d.getY(),2)) ;
	}
}