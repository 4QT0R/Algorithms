#include <bits/stdc++.h> 
using namespace std;
#define ll long long

const ll oo = 1e18 + 1000;

struct Edge {
	int from, to;
	ll capac, flow;

	int oth (int u) {
		return u ^ from ^ to;
	}
	ll capacity (int u) {
		if (u == from) {
			return capac - flow;
		} else {
			return flow;
		}
	}

	bool exists (int u) {
		return capacity(u) != 0;
	}

	void add_flow (int u, ll df) {
		if (u == from) {
			flow += df;
		} else {
			flow -= df;
		}
	}
};

class MaxFlow {
	int n;
	int source, sink;

	vector<vector<Edge*>> adj;

	vector<Edge*> edges;

	vector<int> lvl;
 
	void dinitz_bfs () {
		lvl = vector<int> (n, n + 10); 		
		queue<int> Q;
		Q.push(source);
		lvl[source] = 0;
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			for (auto e : adj[u]) {
				if (!e->exists(u)) {
					continue;
				}
				int v = e->oth(u);
				if (lvl[v] > n) {
					lvl[v] = lvl[u] + 1;
					Q.push(v);
				}
			}
		}
	}
 
	bool in_current_dag (int u, int v) {
		return lvl[v] == lvl[u] + 1;
	}

	ll dinitz_dfs (int u, ll F, vector<int> &blocked){
		if (u == sink) {
			return F;
		}
		ll flow_pushed = 0;
		bool all_blocked = true;
		for (auto e : adj[u]) {
			int v = e->oth(u);
			if (!in_current_dag(u, v)) {
				continue;
			}
			if (e->exists(u) && !blocked[v]) {
				ll dF = dinitz_dfs(v, min(F, e->capacity(u)), blocked);
				flow_pushed += dF;
				F -= dF;
				e->add_flow(u, dF);
			}
		}
		if (!flow_pushed){
			blocked[u] = true;
		}
		return flow_pushed;
	}

	void dinitz_dfs () {
		vector<int> blocked (n, false);
		dinitz_dfs(source, oo, blocked);
	}

public:
	MaxFlow (int _source, int _sink, const vector<tuple<int, int, ll>> &_edges)
		: source(_source), sink(_sink) {
		n = max(1 + source, 1 + sink);
		for (auto e : _edges) {
			n = max(n, max(1 + get<0>(e), 1 + get<1>(e)));
		}

		adj = vector<vector<Edge*>> (n, vector<Edge*> (0));
		for (auto e : _edges) {
			auto ee = new Edge();
			ee->from = get<0>(e);
			ee->to = get<1>(e);
			ee->flow = 0;
			ee->capac = get<2>(e);

			edges.push_back(ee);
			if (ee->from != ee->to) {
				adj[ee->from].push_back(ee);
				adj[ee->to].push_back(ee);
			}
		}
	}

	ll calc_max_flow () {
		while (true) {
			dinitz_bfs();
			if (lvl[sink] > n){
				break;
			}
			dinitz_dfs();
		}
		ll ans = 0;
		for (auto e : adj[source]) {
			if (e->from == source) {
				ans += e->flow;
			} else {
				ans -= e->flow;
			}
		}
		return ans;
	}
	ll flow_on_edge (int idx) {
		return edges[idx]->flow;
	}
};

class GraphBuilder {
	int source, sink;
	vector<tuple<int, int, ll>> edges;

public:
	GraphBuilder (int _source, int _sink) : source(_source), sink(_sink), edges(0) {}

	void add_edge (int u, int v, ll capacity) {
		edges.push_back(make_tuple(u, v, capacity));
	}

	MaxFlow build () {
		return MaxFlow(source, sink, edges);
	}
};
 
// int main () {
// 	ios::sync_with_stdio(false);
// 	cin.tie(0);

// 	int n, m;
// 	cin >> n >> m;

// 	GraphBuilder gb (1, n);
// 	for (int i = 0; i < m; i++) {
// 		int u, v;
// 		ll capac;
// 		cin >> u >> v >> capac;

// 		gb.add_edge(u, v, capac);
// 	}

// 	auto mf = gb.build();
// 	ll ans = mf.calc_max_flow();
// 	cout << ans << '\n';
// }