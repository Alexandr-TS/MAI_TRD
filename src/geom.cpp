struct Pt {
  ld x, y;
};

struct Ln {
  ld a, b, c;
};

Ln line_from_2_points(Pt p1, Pt p2) {
  ld a = p1.y - p2.y;
  ld b = p2.x - p1.x;
  return Ln{a, b, -a * p1.x - b * p1.y};
}


// 2 lines intersection
double det (double a, double b, double c, double d) {
	return a * d - b * c;
}

bool intersect (line m, line n, pt & res) {
	double zn = det (m.a, m.b, n.a, n.b);
	if (abs (zn) < EPS)
		return false;
	res.x = - det (m.c, m.b, n.c, n.b) / zn;
	res.y = - det (m.a, m.c, n.a, n.c) / zn;
	return true;
}

bool parallel (line m, line n) {
	return abs (det (m.a, m.b, n.a, n.b)) < EPS;
}

bool equivalent (line m, line n) {
	return abs (det (m.a, m.b, n.a, n.b)) < EPS
		&& abs (det (m.a, m.c, n.a, n.c)) < EPS
		&& abs (det (m.b, m.c, n.b, n.c)) < EPS;
}


// Line and circle intersection
// p(x, y), l(a, b, c), rad
// 1) c += a*x + b*y
// 2) assume that p = (0, 0)
// 3) find intersections
// 4) add (x,y) to them
  double r, a, b, c; // входные данные
  double x0 = -a*c/(a*a+b*b),  y0 = -b*c/(a*a+b*b);
  if (c*c > r*r*(a*a+b*b)+EPS)
    puts ("no points");
  else if (abs (c*c - r*r*(a*a+b*b)) < EPS) {
    puts ("1 point");
    cout << x0 << ' ' << y0 << '\n';
  }
  else {
    double d = r*r - c*c/(a*a+b*b);
    double mult = sqrt (d / (a*a+b*b));
    double ax,ay,bx,by;
    ax = x0 + b * mult;
    bx = x0 - b * mult;
    ay = y0 - a * mult;
    by = y0 + a * mult;
    puts ("2 points");
    cout << ax << ' ' << ay << '\n' << bx << ' ' << by << '\n';
  }


Pt vector_rotate(Pt vec, ld alpha) {
  return Pt{
    vec.x * cos(alpha) - vec.y * sin(alpha),
    vec.x * sin(alpha) + vec.y * cos(alpha)
  }
}



// Check that 2 segments intersect
inline int area (Pt a, Pt b, Pt c) {
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


// Common tangents of 2 circles
void tangents (pt c, double r1, double r2, vector<line> & ans) {
	double r = r2 - r1;
	double z = sqr(c.x) + sqr(c.y);
	double d = z - sqr(r);
	if (d < -EPS)  return;
	d = sqrt (abs (d));
	line l;
	l.a = (c.x * r + c.y * d) / z;
	l.b = (c.y * r - c.x * d) / z;
	l.c = r1;
	ans.push_back (l);
}

vector<line> tangents (circle a, circle b) {
	vector<line> ans;
	for (int i=-1; i<=1; i+=2)
		for (int j=-1; j<=1; j+=2)
			tangents (b-a, a.r*i, b.r*j, ans);
	for (size_t i=0; i<ans.size(); ++i)
		ans[i].c -= ans[i].a * a.x + ans[i].b * a.y;
	return ans;
}
