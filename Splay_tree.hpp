#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct SplayNode
{
	SplayNode() {}
	SplayNode(T value_arg) : value{value_arg} {}
	T value{};					   //!< Value associated with node
	array<SplayNode *, 2> child{}; //!< Left and right children
	SplayNode *parent{};		   //!< Pointer to parent
	bool side() const
	{
		/*! Returns true if child is on the right, and false otherwise*/
		return parent->child[1] == &this;
	}
	void rotate()
	{
		/*! Rotate node x around its parent */
		const auto p = parent;
		const bool i = side();

		if (p->parent)
		{
			p->parent->attach(p->side(), &this);
		}
		else
		{
			parent = nullptr;
		}
		p->attach(i, child[!i]);
		attach(!i, p);
	}
	void splay()
	{
		/*! Splay node x. x will become the root of the tree*/
		for (; parent; rotate())
		{
			if (parent->parent)
			{
				(side() == parent->side() ? parent : &this)->rotate();
			}
		}
	}
	array<SplayNode *, 2> split()
	{
		splay();
		// TODO use detach function
		const auto right = child[1];
		if (right)
		{
			right->parent = nullptr;
		}
		this->right = nullptr;
		return {&this, right};
	}
	void attach(bool side, SplayNode *const new_)
	{
		/*! Attach node new_ as the node's side children*/
		if (new_)
		{
			new_->parent = &this;
		}
		child[side] = new_;
	}
};

// int main()
// {
// 	ios_base::sync_with_stdio(0);
// 	cin.tie(0);

// 	int n;
// 	cin >> n;
// 	SplayNode<int> tree;
// }