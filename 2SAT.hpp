#include <bits/stdc++.h>
#include "SCC.hpp"
using namespace std;

struct SAT_solver
{
	const int size;

	const static int TRUTH = 0; // vertice 0 corresponds to global variable of truth

	vector<vector<int>> g;

	SAT_solver(int n) : size(n + 1)
	{
		g.resize(2 * size);
		IMPLIES(NOT(TRUTH), TRUTH);
	};

	void TRUE(int x)
	{
		IMPLIES(TRUTH, x);
		IMPLIES(NOT(x), NOT(TRUTH));
	}

	void FALSE(int x)
	{
		IMPLIES(TRUTH, NOT(x));
		IMPLIES(x, NOT(TRUTH));
	}

	int NOT(int x)
	{
		return x < size ? x + size : x - size;
	}

	void IMPLIES(int a, int b)
	{
		g[a].push_back(b);
	}

	void OR(int a, int b)
	{
		IMPLIES(NOT(a), b);
		IMPLIES(NOT(b), a);
	}

	vector<bool> solve()
	{
		SCC scc(2 * size);
		vector<int> comp = scc.find_components(g);
		for (int i = 0; i < size; i++)
		{
			if (comp[i] == comp[NOT(i)])
				return {};
		}

		vector<bool> result(size);
		for (int i = 0; i < size; i++)
		{
			result[i] = comp[i] > comp[NOT(i)];
		}
		return result;
	}

	void clear()
	{
		g.clear();
		g.resize(2 * size);
	}
};