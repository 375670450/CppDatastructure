#pragma once
#include "BinSearchTree.h"

template <typename T, typename Comparator = less<T> >
class AVLTree : public BinSearchTree<T, Comparator> {
protected:
	NODE_PTR Single_Left_Rotation(NODE_PTR root) {
		// Old left child becomes new root
		NODE_PTR old_left = root->Left;
		root->Left = old_left->Right;
		old_left->Right = root;
		_Height_Update(root);
		_Height_Update(old_left);
		root = old_left;
		return root;
	}

	NODE_PTR Single_Right_Rotation(NODE_PTR root) {
		// Old right child becomes new root
		NODE_PTR old_right = root->Right;
		root->Right = old_right->Left;
		old_right->Left = root;
		_Height_Update(root);
		_Height_Update(old_right);
		root = old_right;
		return root;
	}

	NODE_PTR Double_Left_Right_Rotation(NODE_PTR root) {
		// First Right then Left for the convenience of programming,
		// converse from the function name
		root = Single_Right_Rotation(root->Left);
		root = Single_Left_Rotation(root);
		return root;
	}

	NODE_PTR Double_Right_Left_Rotation(NODE_PTR root) {
		root = Single_Left_Rotation(root->Right);
		root = Single_Right_Rotation(root);
		return root;
	}


	inline int _GetHeight(NODE_PTR Node) {
		if ( Node == nullptr ) return -1;
		return Node->Height;
	}

	inline void	_Height_Update(NODE_PTR Node) {
		Node->Height = max(_GetHeight(Node->Left), _GetHeight(Node->Right)) + 1;
	}

	void _Adjust(NODE_PTR & root) {
		if ( _GetHeight(root->Left) - _GetHeight(root->Right) == 2 ) {	// If need right rotation
	// Check the type of unbalance
			if ( _GetHeight(root->Left->Left) - _GetHeight(root->Left->Right) > 0 ) {		// LL type unbalance
				root = Single_Left_Rotation(root);
			} else {								// LR type unbalance
				root = Double_Left_Right_Rotation(root);
			}
		} else if ( _GetHeight(root->Right) - _GetHeight(root->Left) == 2 ) {	// If need left rotation
			if ( _GetHeight(root->Right->Right) - _GetHeight(root->Right->Left) > 0 ) {		// RR type unbalance
				root = Single_Right_Rotation(root);
			} else {								// RL type unbalance
				root = Double_Right_Left_Rotation(root);
			}
		}
		return;
	}


	void _Adjust_All(NODE_PTR & root) {
		if ( root->Left ) _Adjust_All(root->Left);
		if ( root->Right ) _Adjust_All(root->Right);
		_Adjust(root);
		return;
	}


	NODE_PTR _Insert(const T & data, NODE_PTR & root) {
		if ( root == nullptr ) {			// Found a Node to place in			
			root = make_shared<TreeNode>( );
			root->Data = data;
			root->Height = 0;				// The Height of a leave node should be 0
			return root;
		}
		if ( isLessThan(data, root->Data) ) root->Left = _Insert(data, root->Left);		// Check the balance right after an insert operation
		else root->Right = _Insert(data, root->Right);
		_Adjust(root);
		_Height_Update(root);
		return root;
	}
public:
	AVLTree( ) {}

	~AVLTree( ) {}

	virtual void Insert(const T & data) {
		_Insert(data, Root);
	}

	virtual void Delete(const T & data) {
		_Delete(data, Root);
		_Adjust_All(Root);
	}

};
