#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <bitset>
#include <sstream>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <random>
#include <functional>
#include <climits>
#include <cstdio>
#include <ctype.h>
#include <time.h>
using namespace std;

#define PI acos(-1.0)
#define EPS 1e-8
#define MOD 1000000007
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define fi first
#define se second
#define go(i, a, b) for(int i = a; i <= b; ++i)
#define gorev(i, a, b) for(int i = a; i >= b; --i)

typedef long double ld;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

template <class L, class R> ostream &operator <<(ostream &os, pair<L, R> P){
    return os << "(" << P.fi << "," << P.se << ")";
}
template <class T> ostream &operator <<(ostream &os, vector<T> V){
    os << "["; for (auto vv: V) os << vv << ","; return os << "]";
}
template <class L, class R> ostream &operator <<(ostream &os, map<L, R> M){
    os << "["; for (auto pr: M) os << pr.fi << "->" << pr.se << ","; return os << "]";
}
template <class L, class R> ostream &operator <<(ostream &os, unordered_map<L, R> M){
    os << "["; for (auto pr: M) os << pr.fi << "->" << pr.se << ","; return os << "]";
}

mt19937_64 mt(time(0));

struct Matrix {
    vvi data;
    int r, c;
    Matrix(int row, int col, bool identity = false) : r(row), c(col) {
        data.assign(row, vector<int>(col, 0));
        if (identity) {
            for (int i = 0; i < r; ++i) {
                data[i][i] = 1;
            }
        }
    }
    Matrix operator * (Matrix& other) {
        int m = r, n = c, p = other.c;
        Matrix res(m, p);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < p; ++j) {
                for (int k = 0; k < n; ++k) {
                    res.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return res;
    }
};

vector<int> extendGcd(int a, int b) {
    if (b == 0) {
        return {1, 0, a};
    } else {
        vector<int> tmp = extendGcd(b, a % b);
        return {tmp[1], tmp[0] - (a / b) * tmp[1], tmp[2]};
    }
}

Matrix matrix_power(Matrix base, ll exp) {
    int n = base.r;
    Matrix res(n, n, true);
    while (exp) {
        if (exp & 1) {
            res = res * base;
        }
        base = base * base;
        exp >>= 1;
    }
    return res;
}

inline char get(void) {
    static char buf[100000], *S = buf, *T = buf;
    if (S == T) {
        T = (S = buf) + fread(buf, 1, 100000, stdin);
        if (S == T) return EOF;
    }
    return *S++;
}

template<class T> inline void read(T &x) {
    static char c; x = 0; int sgn = 0;
    for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
    for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
    if (sgn) x = -x;
}

/*************************
 ******* template ********
 ************************/
int n, m;
pii a[12], b[12];
// sure : number, not sure : 0
set<int> oka[12], okb[12];

int count(int i, int j) {
    if (a[i].fi == b[j].fi) {
        if (a[i].se == b[j].se) {
            return 0;
        } else {
            return a[i].fi;
        }
    } else if (a[i].fi < b[j].fi) {
        if (a[i].se == b[j].fi || a[i].se == b[j].se) {
            return a[i].se;
        } else {
            return 0;
        }
    } else {
        if (a[i].fi == b[j].se || a[i].se == b[j].se) {
            return b[j].se;
        } else {
            return 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout.precision(10);
    cout << fixed;
#ifdef ZYC_LOCAL
    freopen("input.txt", "rt", stdin);
#endif
    cin >> n >> m;
    go(i, 0, n - 1) {
        cin >> a[i].fi >> a[i].se;
        if (a[i].fi > a[i].se) {
            swap(a[i].fi, a[i].se);
        }
    }
    go(i, 0, m - 1) {
        cin >> b[i].fi >> b[i].se;
        if (b[i].fi > b[i].se) {
            swap(b[i].fi, b[i].se);
        }
    }

    go(i, 0, n - 1) {
        set<int> ss;
        go(j, 0, m - 1) {
            int tmp = count(i, j);
            if (tmp) {
                ss.insert(tmp);
            }
        }
        for (int k : ss) {
            oka[i].insert(k);
        }
    }

    go(j, 0, m - 1) {
        set<int> ss;
        go(i, 0, n - 1) {
            int tmp = count(i, j);
            if (tmp) {
                ss.insert(tmp);
            }
        }
        for (int k : ss) {
            okb[j].insert(k);
        }
    }

    set<int> sa, sb;
    go(i, 0, n - 1) {
        if (oka[i].size() > 1) {
            cout << -1;
            return 0;
        } else if (!oka[i].empty()){
            sa.insert(*oka[i].begin());
        }
    }
    go(i, 0, m - 1) {
        if (okb[i].size() > 1) {
            cout << -1;
            return 0;
        } else if (!okb[i].empty()) {
            sb.insert(*okb[i].begin());
        }
    }

    for (int i : sa) if (sb.find(i) == sb.end()) {
        cout << -1;
        return 0;
    }

    for (int i : sb) if (sa.find(i) == sa.end()) {
        cout << -1;
        return 0;
    }

    if (sa.size() > 1) {
        cout << 0;
    } else if (sa.size() == 1) {
        cout << *sa.begin();
    } else {
        cout << -1;
    }

#ifdef ZYC_LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
