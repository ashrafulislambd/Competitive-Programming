int dd;

int fartheaste(vector<vector<pair<int,int>>>& G, int s, vector<int>& d, vector<bool>& vis) {
	//int n = G.size()+1;
	//d.assign(n+1, n);
	d[s] = 0;
	//vector<bool> vis(n+1);
	queue<int> q, q2;
	q.push(s);
	q2.push(s);
	vis[s] = true;
	d[s] = 0;
	int last = s;

	while(!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = true;
		for(auto& v : G[u]) {
			if(!vis[v.first]) {
				q.push(v.first);
				q2.push(v.first);
				d[v.first] = d[u] + v.second;
				if(d[v.first] > d[last]) last = v.first;
			}
		}
	}

	dd = d[last];

	while(!q2.empty()) {
		int u = q2.front();
		vis[u] = false;
		q2.pop();
	}

	return last;
}