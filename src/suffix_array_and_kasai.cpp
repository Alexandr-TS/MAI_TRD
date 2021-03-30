#include <bits/stdc++.h>
#define fr(i, n) for (int i = 0; i < n; i++)
#define frab(i, a, b) for (int i = a; i < b; i++)
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

const int N = 6e5 + 1;
const int INF = 2e9 + 1;

struct tn {
    int x;
    int num;
};

int p1[N], group1[N], p[N], group[N];
int tq[N], pows[N], lcp[N];
string ans[N];
tn ar[N];
vector <int> pos;

bool cmp(tn a, tn b) {
    return a.x < b.x;
}

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

//    int cnt;
//    cin >> cnt;
//
    string s1, s;
//
//    pos.reserve(N);
//
//    fr(i, cnt) {
//        cin >> s1;
//        s += (s1 + char(2));
//        fr(j, s1.size())
//            pos.pb(i);
//        pos.pb(INF);
//    }
    cin >> s;
    s += char(1);
    //s += char(1);
    //pos.pb(INF);
    int n = s.size();

    pows[0] = 1;
    for (int i = 1; i < 31; i++)
        pows[i] = pows[i - 1] * 2;

    for (int i = 0; i < n; i++)
        tq[(int)s[i]]++;
    for (int i = 0; i <= 300; i++)
        tq[i] += tq[i - 1];
    for (int i = 0; i < n; i++) {
        tq[(int)s[i]]--;
        p1[tq[(int)s[i]]] = i;
    }

    int quacl = 1;
    group1[p1[0]] = 0;

    for (int i = 1; i < n; i++) {
        if (s[p1[i - 1]] != s[p1[i]])
            quacl++;
        group1[p1[i]] = quacl - 1;
    }

    for (int h = 0; pows[h] < n; h++) {
        for (int i = 0; i < n; i++)
            tq[i] = 0;

        for (int i = 0; i < n; i++) {
            if (p1[i] < pows[h])
                p[i] = p1[i] - pows[h] + n;
            else
                p[i] = p1[i] - pows[h];
        }

        for (int i = 0; i < n; i++)
            tq[group1[p[i]]]++;
        for (int i = 1; i < quacl; i++)
            tq[i] += tq[i - 1];
        for (int i = n - 1; i >= 0; i--) {
            tq[group1[p[i]]]--;
            p1[tq[group1[p[i]]]] = p[i];
        }
        quacl = 1;
        group[p1[0]] = 0;
        for (int i = 1; i < n; i++) {
            int t1 = (p1[i - 1] + n + pows[h]) % n;
            int t2 = (p1[i] + n + pows[h]) % n;
            if ((group1[t1] != group1[t2]) ||
                (group1[p1[i]] != group1[p1[i - 1]]))
                quacl++;
            group[p1[i]] = quacl - 1;
        }

        for (int i = 0; i < n; i++)
            group1[i] = group[i];
    }

    for (int i = 0; i < n; i++) {
        ar[i].x = group[i];
        ar[i].num = i;
    }
    sort(ar, ar + n, cmp);

    for (int i = 0; i < n; i++)
        cout << ar[i].num + 1 << " "; cout << endl;
    //void solve(const std::string& text, const std::vector<int>& pos, std::vector<int>& lcp)
	vector <int> rnk(n);
	for (int i = 0; i < n; ++i) rnk[ar[i].num] = i;
	for (int i = 0, k = 0; i < n; ++i)
	{
		if (k > 0) k--;
		if (rnk[i] == n - 1)
                {
                    lcp[n - 1] = -1, k = 0;
                    continue;
                }
		int j = ar[rnk[i] + 1].num;
		while (max(i + k, j + k) < (int)s.size() && s[i + k] == s[j + k]) k++;
		lcp[rnk[i]] = k;
	}
	fr(i, n - 1)
        cout << lcp[i] << " ";
}

