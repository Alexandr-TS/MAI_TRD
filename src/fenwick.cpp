void add(int pos, int val, int n) {
	for (int i = x; i < n; i = (i | (i + 1)))
		tree[i] += val;
}

int pref_sum(int x) {
	int ans = 0;
	for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
		ans += tree[i];
	return ans;
}

int sum(int l, int r) {
    return pref_sum(r) - pref_sum(l - 1);
}
