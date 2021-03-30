// Gray codes
int g (int n) {
	return n ^ (n >> 1);
}

int rev_g(int g) {
	int n = 0;
	for (; g; g>>=1)
		n ^= g;
	return n;
} 


// All masks and their submasks
for (int m=0; m<(1<<n); ++m)
	for (int s=m; s; s=(s-1)&m)


// Euler function O(sqrt(n))
int phi (int n) {
	int result = n;
	for (int i=2; i*i<=n; ++i)
		if (n % i == 0) {
			while (n % i == 0)
				n /= i;
			result -= result / i;
		}
	if (n > 1)
		result -= result / n;
	return result;
}


// Euclid - ax+by=gcd(a,b)
int gcd (int a, int b, int & x, int & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int d = gcd (b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}
