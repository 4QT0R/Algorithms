#include <bits/stdc++.h>
using namespace std;

const int maxN = 400003;
int trie[maxN][26];
int link[maxN];
int prev_word[maxN];
int wolne = 1;
string wej[maxN];
vector<int> slowa[maxN];
vector<int> odp[maxN];

void build(string s, int ind)
{
	int v = 1;
	for (int i = 0; i < s.size(); i++){
		if (!trie[v][s[i] - 'a'])
			trie[v][s[i] - 'a'] = ++wolne;
		v = trie[v][s[i] - 'a'];
	}
	slowa[v].push_back(ind);
}

void go(int &v, int c)
{
	while (!trie[v][c])
		v = link[v];
	v = trie[v][c];
}

void bfs()
{
	for (int i = 0; i < 26; i++)
		trie[0][i] = 1;
	queue<int> q;
	q.push(1);
	while (!q.empty())
	{
		int now = q.front();
		q.pop();
		for (int i = 0; i < 26; i++)
		{
			int son = trie[now][i];
			if (son)
			{
				link[son] = link[now];
				go(link[son], i);
				if (slowa[link[son]].size())
					prev_word[son] = link[son];
				else
					prev_word[son] = prev_word[link[son]];
				q.push(son);
			}
		}
	}
}

void init(int &n)
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> wej[i];
		build(wej[i], i);
	}
	bfs();
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	init(n);
	string s;
	cin >> s;
	int vert = 1;
	for (int i = 0; i < s.size(); i++)
	{
		go(vert, s[i] - 'a');
		int travel = vert;
		while (travel > 1)
		{
			for (auto u : slowa[travel])
				odp[u].push_back(i + 2 - wej[u].size());
			travel = prev_word[travel];
		}
	}
	for (int i = 1; i <= n; i++)
	{
		cout << odp[i].size();
		for (auto u : odp[i])
			cout << ' ' << u;
		cout << '\n';
	}
}