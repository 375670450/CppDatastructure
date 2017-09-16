#pragma once
#include "stdafx.h"

using namespace std;
/*
B+Trees only store data on the leaf nodes as pointers. 
BTrees may store data on every node.
In general, BTrees are better at holding the actual data, 
and B+Trees are much more efficient as indexes.
*/

template <typename T, typename Comparator = less<T> >
class BTree {
private:

	static const int MAXKEYNUM = 10;

	const int MaxDegree;
	
	struct BTreeNode;

	struct Element {

		T	Key;

		bool isLeaf;

		shared_ptr<BTreeNode> Child;

		const Comparator isLessThan;

		void Clear( ) {
			Key = 0;
			isLeaf = false;
			Child = nullptr;
		}

		Element(T _val = 0):Key(_val), isLeaf(false) { Child = nullptr; }

		bool operator <(const Element & j) const {
			if( isLessThan(Key, j.Key) ) return true;
			return false;
		}

		Element & operator= (const Element& j) {
			Key = j.Key;
			Child = j.Child;
			isLeaf = j.isLeaf;
			return *this;
		}
		
	};

	struct BTreeNode{
		int KeyNum;
		shared_ptr<BTreeNode> Parent;
		//shared_ptr<BTreeNode> Childs[MAXKEYNUM];
		//T	 Keys[MAXKEYNUM];

		Element Elems[MAXKEYNUM];		// Elem[0].Key MUST be invalid for every node

		BTreeNode() :KeyNum(0) {
			ClearElem( );
		}

		void ClearElem( ) {
			KeyNum = 0;
			for ( int i = 0; i < MAXKEYNUM; i++ ) {
				Elems[i].Clear( );
			}
		}
	};

	typedef shared_ptr<BTreeNode> Node_Ptr;

	Node_Ptr Root;

	void _InsertNode(Node_Ptr & Node, const Element & data) {
		// Ensure the Keys are always in order
		//if ( Node->KeyNum >= MaxDegree ) return false;
		int i = ++Node->KeyNum;
		for ( ; i > 1 && data < Node->Elems[i]; i++ ) {	// Insertion sort
			Node->Elems[i] = Node->Elems[i - 1];
		}
		Node->Elems[i] = data;
		if ( Node->KeyNum == MaxDegree ) {
			_SplitNode(Node);
		}
	}

	void _SplitNode(Node_Ptr & Node) {
		if ( Node->KeyNum < MaxDegree ) return;
		int Mid = MaxDegree / 2;
		Element	MidElem = Node->Elems[Mid];
		Node_Ptr leftSibling = make_shared<BTreeNode>( ), rightSibling = make_shared<BTreeNode>();
		
		for ( int i = 1; i < Mid; i++ ) {
			_InsertNode(leftSibling, Node->Elems[i]);
		}
		for ( int i = Mid+1; i <= Node->KeyNum; i++ ) {
			_InsertNode(rightSibling, Node->Elems[i]);
		}
		MidElem.Child = rightSibling;

		if ( Node->Parent == nullptr ) {	// This Node is the  Root Node
			Node->ClearElem( );
			_InsertNode(Node, MidElem);
			Node->Elems[0].Child = leftSibling;
			Node->Elems[1].Child = rightSibling;
		} else {
			Node_Ptr parent = Node->Parent;
			parent->Elems[parent->KeyNum].Child = leftSibling;
			Node->Elems[Mid].Child = rightSibling;
			_InsertNode(parent, Node->Elems[Mid]);
			Node = parent;
		}
		return;
	}

public:

	BTree(int _max = 4) : MaxDegree(_max) {
		Root = nullptr;
	}

	virtual void Insert(const Element & data) {
		if ( Root == nullptr ) {
			Root = make_shared<BTreeNode>( );
			Root->Parent = nullptr;
		}
		bool isFinished = false;
		Node_Ptr & curNode = Root;
		while ( !isFinished ) {
			int i;
			for ( i = 0; i <= MaxDegree; i++ ) {		// To find a proper Child Node of current Node to insert
				if ( i == 0 || data < curNode->Elems[i].Key ) {
					if ( curNode->Elems[i].Child != nullptr ) {	// If the child node has been created
						curNode = curNode->Elems[i].Child;
						isFinished = true;
						break;
					}
				}
			}
			if ( i > MaxDegree ) isFinished = true;
			//if ( curNode->KeyNum < MaxDegree ) {	// Current Node wasn't full
			//	_InsertNode(curNode, data);
			//	isFinished = true;
			//} else {
			//	for (int i = 0; i < MaxDegree; i++ ) {		// To find a proper Child Node of current Node to insert
			//		if ( i==0 || data < curNode->Elems[i].Key ) {	
			//			if( curNode->Elems[i].Child == nullptr ) {	// If the child node has not been created
			//				curNode->Elems[i].Child = make_shared<BTreeNode>( );
			//				curNode->Elems[i].Child->Parent = curNode;
			//				_InsertNode(curNode->Elems[i].Child, data);
			//				isFinished = true;
			//				break;	// break for loop
			//			}
			//			curNode = curNode->Elems[i].Child;			// Go deeper
			//			break;		// break for loop
			//		}
			//	}
			//}
		}
		_InsertNode(curNode, data);
		//Print( );
		return;
	}

	virtual void Delete( ) {

	}

	void PreorderTrav() const {
		function<void(Node_Ptr ) > TravFunc;
		TravFunc = 
			[&TravFunc] (Node_Ptr Node) {
			if ( Node == nullptr ) return;
			TravFunc(Node->Elems[0].Child);
			for ( int i = 1; i <= Node->KeyNum; i++ ) {
				TravFunc(Node->Elems[i].Child);
				cout << Node->Elems[i].Key << " ";
			}
		};
		TravFunc(Root);
		cout << endl;
		return;
	}

	void Print() const{
		queue<Node_Ptr> Q;
		if ( Root != nullptr ) Q.push(Root);
		while ( !Q.empty( ) ) {
			Node_Ptr Node = Q.front( ); Q.pop( );
			if ( Node->Elems[0].Child != nullptr ) {
				Q.push(Node->Elems[0].Child);
			}
			for ( int i = 1; i <= Node->KeyNum; i++ ) {
				cout << Node->Elems[i].Key << " ";
				if ( Node->Elems[i].Child != nullptr ) {
					Q.push(Node->Elems[i].Child);
				}
			}
			cout << endl;
		}
		return;
	}
};