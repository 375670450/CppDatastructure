#pragma once

#include "AVLTree.h"

// Top-Bottom Splay Tree

template<typename T, typename Comparator = less<T> >
class SplayTree : public AVLTree<T, Comparator>  {
public:
	SplayTree ( ) { }
	
	~SplayTree ( ){ }

	 void Insert (const T & Data) {
		BinSearchTree::Insert (Data);
		Root = Splay (Root, Data);
		return;
	}

	 void Delete (const T & Data) {
		BinSearchTree::Delete (Data);
		return;
	}

	void Find (const T & Data) {
		Root = Splay (Root, Data);
		return Root;
	}

private:

	NODE_PTR Splay (NODE_PTR root, const T & Element) {
		if ( root == nullptr || root->Data == Element ) {
			return root;
		} else if ( Element < root->Data && root->Left ) {
			if ( Element < root->Left->Data ) {					// Zig-Zig(Left Left)
				root->Left->Left = Splay (root->Left->Left, Element);
				root = Single_Left_Rotation (root);
			}else if( Element > root->Left->Data ) {			// Zig-Zag(Left Right)
				root->Left->Right = Splay (root->Left->Right, Element);
				if ( root->Left->Right != nullptr ) {
					root->Left = Single_Right_Rotation (root->Left);
				}
			}
			return root->Left == nullptr ? root : Single_Left_Rotation(root);
		} else if ( Element > root->Data && root->Right ) {
			if ( Element < root->Right->Data ) {					// Zig-Zag(Right Left)
				root->Right->Left = Splay (root->Right->Left, Element);
				if ( root->Right->Left != nullptr ) {
					root->Right = Single_Left_Rotation (root->Right);
				}
			} else if ( Element > root->Right->Data ) {		// Zig-Zig(Right Right)
				root->Right->Right = Splay (root->Right->Right, Element);
				root = Single_Right_Rotation (root);
			}
			return root->Right == nullptr ? root : Single_Right_Rotation (root);
		}
		return nullptr;
	}

};

