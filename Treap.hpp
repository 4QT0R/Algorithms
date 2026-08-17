#include <bits/stdc++.h>
using namespace std;

mt19937 x(chrono::high_resolution_clock::now().time_since_epoch().count());

const int mod = 1e9+7;

struct treap{
	struct node{
		node* l;
		node* p;
		int ran;
		int val;
		int mx;

		node(int value){
			l = nullptr;
			p = nullptr;
			ran = x()%mod;
			val = value;
			mx = value;
		}
	}* head;

	treap(){
		head = nullptr;
	}

	node* merge(node* a, node* b){
		if (!a || !b)return a?a:b;
		if (a->ran < b->ran)swap(a,b);
		if (a->val < b->val)a->p = merge(a->p,b);
		else a->l = merge(a->l,b);
		if (a->p)a->mx=max(a->val,a->p->mx);
		return a;
	}
	void insert(int t){
		node* tmp = new node(t);
		head = merge(head,tmp);
	}
	pair<node*,node*> split(node* v, int t){
		if (!v)return {nullptr,nullptr};
		if (v->val > t){
			auto wyn = split(v->l, t);
			v->l = wyn.second;
			return {wyn.first,v};
		}
		else{
			auto wyn = split(v->p, t);
			v->p = wyn.first;
			if (v->p)v->mx=max(v->val,v->p->mx);
			return {v,wyn.second};
		}
	}
	void print(node* v){
		cout << "Current: " << v->val << '\n';
		if (v->l){
			cout << "Left subtree:\n";
			print(v->l);
		}
		if (v->p){
			cout << "Right subtree:\n";
			print(v->p);
		}
	}
	void clear(node* v){
		if (v->l)clear(v->l);
		if (v->p)clear(v->p);
		delete v;
	}
	void erase(pair<int,int> inter){
		auto treaps = split(head, inter.first);
		auto treaps2 = split(treaps.second, inter.second+1);
		if (treaps2.first)clear(treaps2.first);
		head = merge(treaps.first,treaps2.second);
	}
	int loverbound(int x){
		node* tmp = head; 
		while(true){
			if (tmp->val <= x){
				if (tmp->p)tmp = tmp->p;
				else return -1;
			}
			else{
				if (tmp->l && tmp->l->mx > x)tmp = tmp->l;
				else return tmp->val;
			}
		}
		return -1;
	}
};

// int main(){
// 	ios_base::sync_with_stdio(0);
// 	cin.tie(0);

// 	treap drzewiec = treap();
// 	drzewiec.insert(2);
// 	drzewiec.print(drzewiec.head);
// 	cout << '\n';
// 	drzewiec.insert(5);
// 	drzewiec.print(drzewiec.head);
// 	cout << '\n';
// 	drzewiec.insert(1);
// 	drzewiec.print(drzewiec.head);
// 	cout << '\n';
// 	cout << drzewiec.loverbound(1) << '\n';
// }