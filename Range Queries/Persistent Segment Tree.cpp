/**
 * Generic persistent segment tree that supports range add, range multiply, range query of sum, max and min altogether
 * Inspired from Benq's template and modification was done to it.
 * The original snippet credit goes to Benq
 * 
 * Just like the original segment tree, this call the `persistentClone` 
 * method to create a persistent clone of the entire segment tree. each clone
 * takes extra logN space
 * 
 * CSES Accepted Solution: https://cses.fi/problemset/result/14709167/
 */ 

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
            mn = min(l->val, r->val);
            mx = max(l->val, r->val);
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

    Node& persistentClone(int L, int R, int b, int c) {
        if (R <= lo || hi <= L) return *this;
        if (L <= lo && hi <= R) {
            Node* newNode = new Node(lo, hi);
            newNode->val = val;
            newNode->mx = mx;
            newNode->mn = mn;
            newNode->mup = mup;

            if(newNode->mup==make_pair(inf, inf))
                newNode->mup = {b, c};
            else {
                newNode->mup = {b*newNode->mup.first, b*newNode->mup.second+c};
            }
            if(b > 0) {
                newNode->mn = b*mn + c;
                newNode->mx = b*mx + c;
            } else {
                newNode->mn = b*mx + c;
                newNode->mx = b*mn + c;
            }
            newNode->val = b*val + (hi-lo)*c;
            newNode->l = l;
            newNode->r = r;
            return *newNode;
        }
        else {
            push();
            Node* newL = &l->persistentClone(L, R, b, c);
            Node* newR = &r->persistentClone(L, R, b, c);
            Node* newNode = new Node(lo, hi);
            newNode->val = val;
            newNode->mx = mx;
            newNode->mn = mn;
            newNode->mup = mup;
            newNode->l = newL;
            newNode->r = newR;

            newNode->val = newL->val + newR->val;
            newNode->mn = min(newL->mn, newR->mn);
            newNode->mx = max(newL->mx, newR->mx);
            return *newNode;
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