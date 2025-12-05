/**
 * Generic segment tree that supports range add, range multiply, range query of sum, max and min altogether
 * Inspired from Benq's template and modification was done to it.
 * The original snippet credit goes to Benq
 * 
 * Interval is [l, r) =  l to r-1
 * querySum(l, r), queryMin(l, r), queryMax() for query
 * set(l, r, {0, x}) for setting the range to x
 * set(l, r, {1, x}) for adding to the range x
 * set(l, r, {x, 0}) for multiplying the range by x
 * set(l, r, {x, y}) for applying affine operation x*a[i] + y on the range
 * 
 * Everything can be used together on the single segment tree
 */ 

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi

const int inf = 1e9;
struct Node {
    Node *l = 0, *r = 0;
    int lo, hi, val=0, mn=0, mx=0;
    pii mup = {inf, inf};
    Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of =inf
    Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
        if (lo + 1 < hi) {
            int mid = lo + (hi - lo)/2;
            l = new Node(v, lo, mid); r = new Node(v, mid, hi);
            val = l->val + r->val;
            mn = min(l->val, r->mn);
            mx = max(l->val, r->mx);
        }
        else {
            val = v[lo];
            mn = v[lo];
            mx = v[lo];
        };
    }

    int querySum(int L, int R) {
        if (R <= lo || hi <= L) return 0;
        if (L <= lo && hi <= R) return val;
        push();
        return l->querySum(L, R) + r->querySum(L, R);
    }

    int queryMin(int L, int R) {
        if (R <= lo || hi <= L) return inf;
        if (L <= lo && hi <= R) return mn;
        push();
        return min(l->queryMin(L, R), r->queryMin(L, R));
    }

    int queryMax(int L, int R) {
        if (R <= lo || hi <= L) return -inf;
        if (L <= lo && hi <= R) return mx;
        push();
        return max(l->queryMax(L, R), r->queryMax(L, R));
    }

    void set(int L, int R, int b, int c) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) {
            if(mup==make_pair(inf, inf))
                mup = {b, c};
            else {
                mup = {b*mup.first, b*mup.second+c};
            }
            if(b > 0) {
                mn = b*mn + c;
                mx = b*mx + c;
            } else {
                mn = b*mx + c;
                mx = b*mn + c;
            }
            val = b*val + (hi-lo)*c;
        }
        else {
            push(), l->set(L, R, b, c), r->set(L, R, b, c);
            val = l->val + r->val;
            mn = min(l->mn, r->mn);
            mx = max(l->mx, r->mx);
        }
    }

    void push() {
        if (!l) {
            int mid = lo + (hi - lo)/2;
            l = new Node(lo, mid); r = new Node(mid, hi);
        }
        if (mup != make_pair(inf, inf)) {
            l->set(lo,hi,mup.first, mup.second), r->set(lo,hi,mup.first, mup.second), 
            mup = {inf, inf};
        }
    }
};