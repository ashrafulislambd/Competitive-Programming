struct MergeSortTree {
    MergeSortTree *l=0, *r=0;
    int lo, hi;
 
    vector<int> os;
 
    MergeSortTree(vector<int>& v, int lo, int hi):lo(lo),hi(hi) {
        if(lo+1<hi) {
            int mid=lo+(hi-lo)/2;
            l = new MergeSortTree(v, lo, mid);
            r = new MergeSortTree(v, mid, hi);
            os = vector<int>(l->os.size()+r->os.size());
            merge(all(l->os),all(r->os), os.begin());
        } else {
            os.push_back(v[lo]);
        }
    }
 
    int query(int L, int R, int k) {
        if(R<=lo || hi<=L) return 0;
        if(L<=lo && hi<=R) return lower_bound(all(os), k) - os.begin();
        return l->query(L, R, k) + r->query(L, R, k);
    }
};
