#pragma once
#include "stdafx.h"

using namespace std;

template <typename T, typename Comparator = less<T> >
class RedBlackTree  {
private:

	typedef enum {
		RED = 1, BLACK = 2
	} NodeColor;


	struct RBTNode {
		T Data;
		NodeColor Color;
		shared_ptr<RBTNode> Parent;
		shared_ptr<RBTNode> Left, Right;
		RBTNode () : Color(BLACK) { Parent = Left = Right = nullptr; }
		RBTNode (T data) : Data(data) {  }
		void Print (shared_ptr<RBTNode> RBT_NIL) {
			cout << Data << "-" << ( Color == BLACK ? "BLACK" : "RED" ) << " -> ( ";
			if ( Left != RBT_NIL ) cout << Left->Data;
			cout << " , ";
			if ( Right != RBT_NIL ) cout << Right->Data;
			cout << " )" << endl;
		}
	} ;

	typedef shared_ptr<RBTNode> RBTNODE_PTR;

	RBTNODE_PTR RBT_NIL;
	RBTNODE_PTR Root;

	void Insert_FixUp (RBTNODE_PTR x) {		
		/*
			Do not need to change Parent pointer in this function, which would be done in rotate function	
		*/
		RBTNODE_PTR uncle = nullptr;								// Point to the uncle node 
		while ( x->Parent->Color == RED ) {

			if ( x->Parent == x->Parent->Parent->Left ) {	// Locate x->Parent
				uncle = x->Parent->Parent->Right;							
				if ( uncle->Color == RED ) {									// Case 1
					x->Parent->Parent->Color = RED;
					uncle->Color = x->Parent->Color = BLACK;
					x = x->Parent->Parent;
				} else if ( uncle->Color == BLACK ) {				
					if( x == x->Parent->Right )	{							// Case 2
						x = x->Parent;
						x = Single_Right_Rotation (x);
					} else if ( x == x->Parent->Left ) {					// Case 3(Zig-Zig), Only this case may change the Root node
						x->Parent->Color = BLACK;
						x->Parent->Parent->Color = RED;
						x = Single_Left_Rotation (x->Parent->Parent);
					}
				}
			} else if ( x->Parent == x->Parent->Parent->Right ) {		// Similar to the other case
				uncle = x->Parent->Parent->Left;
				if ( uncle->Color == RED ) {									// Case 1
					x->Parent->Parent->Color = RED;
					uncle->Color = x->Parent->Color = BLACK;
					x = x->Parent->Parent;
				} else if ( uncle->Color == BLACK ) {
					if ( x == x->Parent->Left ) {							// Case 2
						x = x->Parent;
						x = Single_Left_Rotation (x);
					} else if ( x == x->Parent->Right ) {			// Case 3(Zig-Zig)
						x->Parent->Color = BLACK;
						x->Parent->Parent->Color = RED;
						x->Parent = Single_Right_Rotation (x->Parent->Parent);
					}
				}
			} else {
				x = x->Parent;
			}
			//this->PrintChildren ();
		}	// End While( x->Parent->color == RED ) 
		Root->Color = BLACK;
	}

	void Delete_FixUp (RBTNODE_PTR x) {
		RBTNODE_PTR sibling = nullptr;
		for ( ; ; ) {
			if ( x->Color == RED || x == Root ) {				// Exit Situation
				x->Color = BLACK;
				break;
			}
			if ( x == x->Parent->Left ) {
				sibling = x->Parent->Right;
				if ( sibling->Color == RED ) {						// Case 1
					sibling->Parent->Color = RED;
					sibling->Color = BLACK;
					Single_Right_Rotation (x->Parent);
				} else if( sibling->Left->Color == BLACK && sibling->Right->Color == BLACK	){	// Case 2
					sibling->Color = RED;
					x = x->Parent;
				} else if( sibling->Left->Color == RED && sibling->Right->Color == BLACK ){			// Case 3
					sibling->Color = RED;
					sibling->Left->Color = BLACK;
					Single_Left_Rotation (sibling);
				} else if ( sibling->Right->Color == RED ) {				// Case 4, The final turn
					sibling->Color = x->Parent->Color;
					x->Parent->Color = BLACK;
					sibling->Right->Color = BLACK;
					Single_Right_Rotation (x->Parent);
					break;
				}
			} else {
				sibling = x->Parent->Left;
				if ( sibling->Color == RED ) {						// Case 1
					sibling->Parent->Color = RED;
					sibling->Color = BLACK;
					Single_Left_Rotation (x->Parent);
				} else if ( sibling->Right->Color == BLACK && sibling->Left->Color == BLACK ) {	// Case 2
					sibling->Color = RED;
					x = x->Parent;
				} else if ( sibling->Right->Color == RED && sibling->Left->Color == BLACK ) {			// Case 3
					sibling->Color = RED;
					sibling->Right->Color = BLACK;
					Single_Right_Rotation (sibling);
				} else if ( sibling->Left->Color == RED ) {				// Case 4
					sibling->Color = x->Parent->Color;
					x->Parent->Color = BLACK;
					sibling->Left->Color = BLACK;
					Single_Left_Rotation (x->Parent);
					break;
				}
			}
		}
		return;
	}

	RBTNODE_PTR Single_Right_Rotation (RBTNODE_PTR root) {//	 Different from AVL rotation
		if ( root->Right == nullptr ) return root;										// Cannot rotate
		Root = ( root == Root ? root->Right : Root );							// Change pointer Root
		RBTNODE_PTR old_right = root->Right;
		root->Right = old_right->Left;
		if ( old_right->Left != RBT_NIL ) 
			old_right->Left->Parent = root;
		if ( root->Parent != RBT_NIL ) {
			if ( root->Parent->Left == root ) root->Parent->Left = old_right;
			else root->Parent->Right = old_right;
		}
		old_right->Left = root;
		old_right->Parent = root->Parent;				
		root->Parent = old_right;								
		root = old_right;
		return root;
	}

	RBTNODE_PTR Single_Left_Rotation (RBTNODE_PTR root) {//	 Different from AVL rotation
		if ( root->Right == nullptr ) return root;
		Root = ( root == Root ? root->Left : Root );							// Change pointer Root
		RBTNODE_PTR old_left = root->Left;
		root->Left = old_left->Right;
		if ( old_left->Right != RBT_NIL ) old_left->Right->Parent = root;
		if ( root->Parent != RBT_NIL ) {
			if ( root->Parent->Left == root ) root->Parent->Left = old_left;
			else root->Parent->Right = old_left;
		}
		old_left->Right = root;
		old_left->Parent = root->Parent;				
		root->Parent = old_left;							
		root = old_left;
		return root;
	}


public:
	
	RedBlackTree ( ) { 
		RBT_NIL = make_shared<RBTNode> ( );
		RBT_NIL->Left = RBT_NIL->Right = RBT_NIL->Parent = Root;
		Root = nullptr;
	}

	int GetHeight ( ) const{
		if ( Root == nullptr ) return 0;

		auto getheight = function<int (RBTNODE_PTR)> ( );
		getheight = [&] (RBTNODE_PTR root) -> int {
			if ( root == RBT_NIL ) return 0;
			int LH = 0, RH = 0;
			LH = getheight (root->Left) + 1;
			RH = getheight (root->Right) + 1;
			return max (LH, RH);
		};
		return getheight (Root);
	}

	int GetBlackHeight ( ) const{
		// Remember the features of RBT
		if ( Root == nullptr ) return 0;
		int Height = 0;
		RBTNODE_PTR cur = Root;
		while ( cur != RBT_NIL ) {
			Height++;
			cur = cur->Left;
		}
		return Height;
	}

	RBTNODE_PTR FindMin (RBTNODE_PTR root) {
		if ( root == nullptr || root == RBT_NIL ) 
			return RBT_NIL;
		while ( root->Left != RBT_NIL ) {
			root = root->Left;
		}
		return root;
	}

	RBTNODE_PTR Find (const T & data) {				// If cannot find, return RBT_NIL
		if ( Root == nullptr ) return RBT_NIL;
		RBTNODE_PTR cur = Root;
		while ( cur != RBT_NIL ) {
			if ( data < cur->Data ) cur = cur->Left;
			else if( data > cur->Data) cur = cur->Right;
			else break;
		}
		return cur;
	}
	
	void PrintChildren ( ) {
		if ( !Root ) return;
		queue<RBTNODE_PTR> Queue;
		RBTNODE_PTR cur = Root;
		Queue.push (cur);
		while ( !Queue.empty() ) {
			cur = Queue.front ( ); Queue.pop ( );
			cur->Print (RBT_NIL);
			if ( cur->Left != RBT_NIL ) Queue.push (cur->Left);
			if ( cur->Right != RBT_NIL ) Queue.push (cur->Right);
		}
		cout << "-------------------------------------------" << endl;
		return;
	}

	void Insert (const T & data) {
		RBTNODE_PTR newNode = make_shared<RBTNode> (data), cur = Root;
		newNode->Left = newNode->Right = newNode->Parent = RBT_NIL;
		newNode->Color = BLACK;
		if ( Root == nullptr ) {
			Root = newNode;
		} else {
			for ( ;; ) {
				if ( data < cur->Data ) {
					if ( cur->Left == RBT_NIL ) {
						cur->Left = newNode;
						break;
					} else {
						cur = cur->Left;
					}
				} else if ( data > cur->Data ) {
					if ( cur->Right == RBT_NIL ) {
						cur->Right = newNode;
						break;
					} else {
						cur = cur->Right;
					}
				} else {
					return;
				}
			}
			newNode->Color = RED;
			newNode->Parent = cur;
			Insert_FixUp (newNode);
		}
		
		RBT_NIL->Left = RBT_NIL->Right = RBT_NIL->Parent = Root;
		return;
	}

	void Delete (const T & data) {
		if ( Root == nullptr ) return;
		RBTNODE_PTR cur = Root, subtitude = nullptr;
		cur = Find (data);
		if ( cur == RBT_NIL ) return;

		if ( cur->Left == RBT_NIL && cur->Right == RBT_NIL ) {				// Have no children nodes
			if ( cur == Root ) Root = nullptr;
			subtitude = RBT_NIL;
		} else if ( cur->Left != RBT_NIL || cur->Right != RBT_NIL ) {			// have exactly one child node
			if ( cur == Root ) Root = subtitude;
			subtitude = ( cur->Left != RBT_NIL ? cur->Left : cur->Right );
		} else {																											// have two child nodes
			subtitude = FindMin (cur->Right);
			cur->Data = subtitude->Data;
		}

		subtitude->Parent = cur->Parent;
		if ( cur == cur->Parent->Left ) {
			cur->Parent->Left = subtitude;
		} else {
			cur->Parent->Right = subtitude;
		}
		Delete_FixUp (subtitude);																		// Must fix up in every situation
		RBT_NIL->Left = RBT_NIL->Right = RBT_NIL->Parent = Root;
		//cur->reset ( );														// Smart pointer no need free
		return;
	}

};

