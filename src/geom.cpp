Ln line_from_2_points(Pt p1, Pt p2);
Pt lines_intersection(Ln l1, Ln l2);
vector<Pt> lines_circle_intersection(Ln l, Pt o, ld rad);
vector<Pt> circles_intersection(Pt o1, ld rad1, Pt o2, ld rad2);
Pt vector_rotate(Pt vec, ld alpha);



// Check that 2 segments intersect
inline int area (pt a, pt b, pt c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
 
inline bool intersect_1 (int a, int b, int c, int d) {
	if (a > b)  swap (a, b);
	if (c > d)  swap (c, d);
	return max(a,c) <= min(b,d);
}
 
bool intersect (pt a, pt b, pt c, pt d) {
	return intersect_1 (a.x, b.x, c.x, d.x)
		&& intersect_1 (a.y, b.y, c.y, d.y)
		&& area(a,b,c) * area(a,b,d) <= 0
		&& area(c,d,a) * area(c,d,b) <= 0;
}
