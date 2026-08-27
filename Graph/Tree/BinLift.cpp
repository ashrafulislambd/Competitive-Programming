/*
Binary Lifting Template

Initialize with: binlift(Graph, Source) constructor
call getkth(node, k) to get kth ancestor. If kth ancestor doesn't exist 0 is returend 
 */

class binlift {
public:
	vector<vector<int>> kth;
	vector<int> par;

	binlift(vector<vector<int>>& G, int s) {
		function<void(int,int)> dfs = [&] (int u, int p=-1) {
			for(auto v : G[u]) {
				if(v!=p) {
					par[v] = u;
					dfs(v, u);
				}
			}
		};


		int n = G.size();
		par = vector<int>(n+1);

		dfs(s,-1);
		kth = vector<vector<int>>(n+1, vector<int>(33));

		for(int i=0; i<32; i++) {
			for(int j=1; j<=n; j++) {

				if(!i) {
					kth[j][i] = par[j];
				} else {
					kth[j][i] = kth[kth[j][i-1]][i-1];
				}
			}
		}
	}

	int getkth(int u, int k) {
		for(int i=0; i<32; i++) {
			if((k>>i)&1) {
				u = kth[u][i];
			}
		}
		return u;
	}
};