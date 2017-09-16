#pragma once
#include "BinTree.h"


template <typename T, typename Comparator = less<T> >
class BinSearchTree : public BinTree<T> {
protected:
	const Comparator isLessThan;		

	const NODE_PTR & _FindNode(const T & data) const {
		NODE_PTR Node = Root;
		while ( Node ) {
			if ( Node->Data == data ) return Node;
			else {
				if ( data < Node->Data ) Node = Node->Left;
				else Node = Node->Right;
			}
		}
		return nullptr;
	}


	const NODE_PTR & _FindMax(NODE_PTR Node = Root) const {
		if ( Node == nullptr ) return nullptr;
		while ( Node->Right ) {
			Node = Node->Right;
		}
		return Node;
	}


	const NODE_PTR & _FindMin(NODE_PTR Node = Root) const {
		if ( Node == nullptr ) return nullptr;
		while ( Node->Left ) {
			Node = Node->Left;
		}
		return Node;
	}


	void _Delete(const T & data, NODE_PTR & Subtree) {
		if ( Subtree == nullptr ) return;
		if ( isLessThan(data, Subtree->Data) ) {
			_Delete(data, Subtree->Left);
		} else if ( isLessThan(Subtree->Data, data) ) {
			_Delete(data, Subtree->Right);
		} else {																						// Delete this node
			if ( Subtree->Left && Subtree->Right ) {						// if this node has ¡¾two¡¿ children
				Subtree->Data = _FindMin(Subtree->Right)->Data;
				_Delete(Subtree->Data, Subtree->Right);
			} else {
				Subtree = (Subtree->Left ? Subtree->Left : Subtree->Right);
				// We could Delete a node when using the reference type
				// Mainly because the assignment operation '=' would only copy the content
				// while the address won't change
			}
		}
	}
public:

	BinSearchTree( )  {}

	~BinSearchTree( ) {}

	bool Contains(const T &data) const {
		if ( _FindNode(data) != nullptr ) return true;
		return false;
	}

	virtual void Insert(const T & data) {
		NODE_PTR Node = Root;
		if ( Root == nullptr ) {
			Root = make_shared<TreeNode>( );
			Root->Data = data;
		} else {
			while ( Node ) {
				if ( isLessThan(data, Node->Data) ) {
					if ( Node->Left ) {
						Node = Node->Left;
					} else {
						Node->Left = make_shared<TreeNode>( );
						Node->Left->Data = data;
						break;
					}
				} else {
					if ( Node->Right ) {
						Node = Node->Right;
					} else {
						Node->Right = make_shared<TreeNode>( );
						Node->Right->Data = data;
						break;
					}
				}
			}
		}
		return;
	}

	virtual void Delete(const T & data) {
		_Delete(data, Root);
	}
};


