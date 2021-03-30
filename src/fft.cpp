const ld PI = acos(-1);

struct Compl {
    ld x, y;
    Compl(ld x1, ld y1) {
        x = x1;
        y = y1;
    }
    Compl() {}

    Compl operator * (const ld &k) const {
        return {x * k, y * k};
    }
    Compl operator + (const Compl &a) const {
        return {x + a.x, y + a.y};
    }
    Compl operator - (const Compl &a) const {
        return {x - a.x, y - a.y};
    }
    int toInt() {
        return round(x);
    }
    Compl operator * (const Compl &a) const {
        return {x * a.x - y * a.y, x * a.y + y * a.x};
    }
};

inline void dft(vector<Compl> &a, bool inv) {
    int n = a.size();
	int i, j, k, h;
	for (i = k = 0; i < n; i++) {
		if (i > k)
            swap(a[i], a[k]);
		for (j = n >> 1; (k ^= j) < j; j >>= 1);
	}
	Compl t;
	for (h = 2; h <= n; h <<= 1) {
		Compl wn(cos(2 * PI * (inv ? -1 : 1) / h), sin(2 * PI * (inv ? -1 : 1) / h));
		for (i = 0; i < n; i += h) {
			Compl w(1.0, 0.0);
			for (j = i; j < i + h / 2; j++) {
        t = w * a[j + h / 2];
        a[j + h / 2] = a[j] - t;
        a[j] = a[j] + t;
        w = w * wn;
			}
		}
	}
}

vector<int> mult(vector<int> &a, vector<int> &b) {
    vector<Compl> a1, b1;
    int n = 1, pw = 0;
    while (n < max(a.size(), b.size()) * 2)
        n *= 2, pw++;
    for (int i = 0; i < a.size(); i++) a1.push_back({a[i], 0});
    for (int i = 0; i < b.size(); i++) b1.push_back({b[i], 0});
    while (a1.size() < n) a1.push_back({0, 0});
    while (b1.size() < n) b1.push_back({0, 0});
    dft(a1, false);
    dft(b1, false);
    for (int i = 0; i < a1.size(); i++)
        a1[i] = a1[i] * b1[i];
    dft(a1, true);
    for (int i = 0; i < a1.size(); i++)
        a1[i] = a1[i] * (1. / (ld)a1.size());
    vector<int> ans;
    for (int i = 0; i < a1.size(); i++)
        ans.push_back(a1[i].toInt());
    return ans;
}
