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

/******************************** template ********************************/
#define N 300010
#define LEN 30
int n;
int a[N], p[N];

struct TrieNode {
    int cnt;
    TrieNode* ch[2];
    TrieNode() {
        cnt = 0;
        ch[0] = ch[1] = nullptr;
    }
};

struct Trie {
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }

    void insert(int x) {
        TrieNode* cur = root;
        ++(cur->cnt);
        for (int i = LEN - 1; i >= 0; --i) {
            int bit = (x >> i) & 1;
            if (cur->ch[bit] == nullptr) {
                cur->ch[bit] = new TrieNode();
            }
            cur = cur->ch[bit];
            ++(cur->cnt);
        }
    }

    int findAndDelete(int x) {
        TrieNode *cur = root, *pa;
        --(cur->cnt);
        int res = 0;
        for (int i = LEN - 1; i >= 0; --i) {
            pa = cur;
            int bit = (x >> i) & 1;
            if (cur->ch[bit]) {
                cur = cur->ch[bit];
                if (cur->cnt == 1) {
                    pa->ch[bit] = nullptr;
                }
                res <<= 1;
            } else {
                cur = cur->ch[bit ^ 1];
                if (cur->cnt == 1) {
                    pa->ch[bit ^ 1] = nullptr;
                }
                res = (res << 1) | 1;
            }
            --(cur->cnt);
        }

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout.precision(10);
    cout << fixed;
#ifdef ZYC_LOCAL
    freopen("input.txt", "rt", stdin);
#endif
    cin >> n;
    Trie t;
    go(i, 1, n) cin >> a[i];
    go(i, 1, n) {
        cin >> p[i];
        t.insert(p[i]);
    }

    go(i, 1, n) {
        cout << t.findAndDelete(a[i]) << " \n"[i == n];
    }

#ifdef ZYC_LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}