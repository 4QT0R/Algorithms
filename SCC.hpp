#include <bits/stdc++.h>
using namespace std;

struct SCC
{
	const int size;

	vector<vector<int>> g;

	SCC(int n) : size(n) { g.resize(size); };

	template <typename Pre, typename Post>
	void dfs(int v, const vector<vector<int>> &g, vector<bool> &vis, Pre pre, Post post)
	{
		vis[v] = true;
		pre(v);
		for (int u : g[v])
		{
			if (!vis[u])
			{
				dfs(u, g, vis, pre, in, post);
			}
		}
		post(v);
	}

	void EDGE(int a, int b)
	{
		g[a].push_back(b);
	}

	vector<int> find_components()
	{
		vector<vector<int>> gr(size);
		for (int v = 0; v < size; v++)
			for (auto u : g[v])
				gr[u].push_back(v);

		stack<int> st;
		vector<int> comp(size);
		{
			vector<bool> vis(size);
			for (int v = 0; v < size; v++)
			{
				if (!vis[v])
					dfs(v, g, vis, [](int v) {}, [&st](int v)
						{ st.push(v); });
			}
		}
		int cnt = 0;
		{
			vector<bool> vis(size);
			while (st.size())
			{
				auto v = st.top();
				st.pop();

				if (!vis[v])
				{
					++cnt;
					dfs(v, g, vis, [&comp, cnt](int v)
						{ comp[v] = cnt; }, [](int v) {});
				}
			}
		}
		return comp;
	}
};