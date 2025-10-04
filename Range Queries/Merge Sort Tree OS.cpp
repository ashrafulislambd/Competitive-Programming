struct MergeSortTree {
    MergeSortTree *l=0, *r=0;
    int lo, hi;

    ordered_multiset* os;

    ordered_multiset* merge(ordered_multiset* x, ordered_multiset* y) {
        ordered_multiset* new_os = new ordered_multiset();
        for(int i=0; i<y->size(); i++) {
            new_os->insert(*y->find_by_order(i));
        }
        for(int i=0; i<x->size(); i++) {
            new_os->insert(*x->find_by_order(i));
        }
        return new_os;
    }

    MergeSortTree(vector<int>& v, int lo, int hi):lo(lo),hi(hi) {
        if(lo+1<hi) {
            int mid=lo+(hi-lo)/2;
            l = new MergeSortTree(v, lo, mid);
            r = new MergeSortTree(v, mid, hi);
            os = merge(l->os, r->os);
        } else {
            os = new ordered_multiset();
            os->insert(v[lo]);
        }
    }

    int query(int L, int R, int k) {
        if(R<=lo || hi<=L) return 0;
        if(L<=lo && hi<=R) return os->order_of_key(k);
        return l->query(L, R, k) + r->query(L, R, k);
    }
};