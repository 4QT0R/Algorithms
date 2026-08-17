#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <const unsigned int alphabet_size, const char first_letter>
struct Suffix_automaton
{
	struct node
	{
		array<node *, alphabet_size> links;
		node *suf_link;
		ll paths;
		int cnt;
		int len;

		node(int Len) : links(array<node *, alphabet_size>{}), suf_link(nullptr),
						paths(0), cnt(0), len(Len) {}
	};

	node *head;

	Suffix_automaton()
	{
		node *guardian = create_node(-1);
		head = create_node(0);
		for (unsigned int i = 0; i < alphabet_size; i++)
			guardian->links[i] = head;

		head->suf_link = guardian;
	}

	Suffix_automaton(string s) : Suffix_automaton()
	{
		build(s);
	}

	void add_char(node *last, int c)
	{
		node *cur = create_node(last->len + 1);
		cur->cnt = 1;

		while (last->links[c] == nullptr)
		{
			last->links[c] = cur;
			last = last->suf_link;
		}

		node *nxt = last->links[c];
		if ((last->len + 1) == nxt->len)
		{
			cur->suf_link = nxt;
			return;
		}

		node *clone = create_node(last->len + 1);
		clone->links = nxt->links;
		clone->suf_link = nxt->suf_link;

		cur->suf_link = clone;
		nxt->suf_link = clone;

		while (last->links[c] == nxt)
		{
			last->links[c] = clone;
			last = last->suf_link;
		}
	}

	void build(string s)
	{
		node *last = head;
		for (char &c : s)
		{
			add_char(last, (int)(c - first_letter));
			last = last->links[c - first_letter];
		}
	}

	~Suffix_automaton()
	{
		while (nodes.size())
		{
			delete nodes.back();
			nodes.pop_back();
		}
	}

	ll different_substrings()
	{
		count_paths(head);
		return head->paths - 1;
	}

	void count_paths(node *cur)
	{
		if (cur->paths)
			return;

		cur->paths = 1;
		for (unsigned int i = 0; i < alphabet_size; i++)
		{
			if (cur->links[i] == nullptr)
				continue;
			count_paths(cur->links[i]);
			cur->paths += cur->links[i]->paths;
		}
	}

	string kth_substring(ll k)
	{
		count_paths(head);

		k++;
		string ans;
		node *cur = head;
		while (k)
		{
			k--;
			if (!k)
				return ans;
			for (unsigned int i = 0; i < alphabet_size; i++)
			{
				if (cur->links[i] == nullptr)
					continue;
				if (k <= cur->links[i]->paths)
				{
					ans.push_back(first_letter + i);
					cur = cur->links[i];
					break;
				}
				k -= cur->links[i]->paths;
			}
		}
		return ans;
	}

	void count_occurences()
	{
		unordered_map<node *, vector<node *>> graph;
		for (unsigned int i = 2; i < nodes.size(); i++)
		{
			graph[nodes[i]->suf_link].push_back(nodes[i]);
		}
		auto dfs = [&](auto &self, node *v) -> void
		{
			for (auto u : graph[v])
			{
				self(self, u);
				v->cnt += u->cnt;
			}
		};
		dfs(dfs, head);
	}

	unsigned int count_occurences(string s)
	{
		if (!head->cnt)
			count_occurences();
		node* cur = head;
		for (unsigned int i = 0; i < s.size(); i++){
			if (cur->links[s[i]-first_letter] == nullptr)return 0;
			cur = cur->links[s[i]-first_letter];
		}
		return cur->cnt;
	}

protected:
	vector<node *> nodes;

	node *create_node(int len)
	{
		node *new_node = new node(len);
		nodes.push_back(new_node);
		return new_node;
	}
};

// int main()
// {
// 	ios_base::sync_with_stdio(0);
// 	cin.tie(0);

// 	string s, pattern;
// 	cin >> s >> pattern;

// 	Suffix_automaton<26, 'a'> suf_automaton(s);
// 	cout << suf_automaton.count_occurences(pattern) << '\n';
// }