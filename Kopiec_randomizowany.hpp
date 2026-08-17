#include <bits/stdc++.h>
using namespace std;

mt19937 x=mt19937(chrono::high_resolution_clock::now().time_since_epoch().count());

bool next_bit(){
	return x()&1;
}

struct heap{
	struct node{
		node* lewo;
		node* prawo;
		int val;
	}* head = new node;

	node* merge(node* first, node* second){
		if (!first || !second){
			return first?first:second;
		}
		if(first->val < second->val)swap(first, second);
		if(next_bit())swap(first->lewo, first->prawo);
		first->lewo = merge(first->lewo, second);
		return first;
	}
	
	int top() const{
		return head->val;
	}
	
	void pop(){
		node* tmp=merge(head->lewo,head->prawo);
		head->lewo=tmp->lewo;
		head->prawo=tmp->prawo;
		head->val=tmp->val;
	}
	
	void push(int x){
		node* tmp = new node;
		tmp->val=x;
		node* tmp2=merge(head,tmp);
		head->lewo=tmp2->lewo;
		head->prawo=tmp2->prawo;
		head->val=tmp2->val;
	}
};

// int main(){
// 	ios_base::sync_with_stdio(0);
// 	cin.tie(0);

// 	heap kopiec;
// 	kopiec.head->val=0;
// 	kopiec.push(1);
// 	cout << kopiec.top() << endl;
// 	kopiec.push(2);
// 	cout << kopiec.top() << endl;
// 	kopiec.push(3);
// 	cout << kopiec.top() << endl;
// 	kopiec.push(4);
// 	cout << kopiec.top() << endl;
// 	kopiec.pop();
// 	cout << kopiec.top() << endl;
// 	kopiec.pop();
// 	cout << kopiec.top() << endl;
// 	kopiec.pop();
// 	cout << kopiec.top() << endl;
// 	kopiec.pop();
// 	cout << kopiec.top() << endl;
// }