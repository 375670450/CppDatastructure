#pragma once

#include "stdafx.h"

using namespace std;


//typedef shared_ptr<TreeNode> NODE_PTR

template<typename T, typename Comparator = std::less<T> >
class BinTree {
protected:

	struct TreeNode {
		T Data;
		int		 Height;
		shared_ptr<TreeNode> Left;
		shared_ptr<TreeNode> Right;
		TreeNode ( ) : Data (0), Height (0), Left (NULL), Right (NULL) { cout << "TreeNode()" << endl; }
		TreeNode(T _data, shared_ptr<TreeNode> _left, shared_ptr<TreeNode> _right) :
			Data(_data), Left(_left), Right(_right) {}
	};

	typedef shared_ptr<TreeNode> NODE_PTR;

	Comparator isLessThan;

	NODE_PTR Root;


	NODE_PTR _FindParent(const T & data) {
		NODE_PTR result = nullptr;
		queue<NODE_PTR> Q;
		Q.push(Root);
		while ( !Q.empty( ) ) {
			result = Q.front( ); Q.pop( );
			if ( result == nullptr ) continue;
			if ( result->Left && result->Left->Data==data || result->Right && result->Right->Data==data ) {
				while ( !Q.empty( ) ) Q.pop( );		// Find answer, Clear the queue
				return result;
			}
			Q.push(result->Left);
			Q.push(result->Right);
		}
		return nullptr;
	}

	void _Transplant(NODE_PTR from, NODE_PTR to) {
		NODE_PTR to_parent = FindParent(to->Data);
		if ( to_parent == nullptr ) {			// to is the Root Node
			Root = from;
		} else {
			if ( to_parent->Left == to ) to_parent->Left = from;
			else to_parent->Right = from;
		}

		return;
	}

	void _TransToVector(vector<T> & vec, int Index, NODE_PTR Node) const {
		if ( Node == nullptr ) return;
		vec[Index] = Node->Data;
		TransToVector(vec, Index * 2, Node->Left);
		TransToVector(vec, Index * 2 + 1, Node->Right);
		return;
	}


public:

	BinTree( ) {
		Root = nullptr;
	}

	BinTree(const BinTree & rhs) {
		*this = rhs;
	}


	virtual	~BinTree( ) {
		Root = nullptr;
	}

	virtual const T	FindMax(NODE_PTR root = nullptr, T maxData = numeric_limits<T>::min( )) const{
		// TODO: 在此处插入 return 语句
		if ( root == nullptr ) root = Root;
		if ( isLessThan(maxData, root->Data) ) maxData = root->Data;
		if ( root->Left )  maxData = FindMax(root->Left, maxData);
		if ( root->Right ) maxData = FindMax(root->Right, maxData);
		return maxData;
	}

	virtual const T	FindMin(NODE_PTR root = nullptr, T minData = numeric_limits<T>::max( )) const {
		// TODO: 在此处插入 return 语句
		if ( root == nullptr ) root = Root;
		if ( isLessThan(root->Data, minData) ) minData = root->Data;
		if ( root->Left )  minData = FindMin(root->Left, minData);
		if ( root->Right ) minData = FindMin(root->Right, minData);
		return minData;
	}


	virtual bool	Contains(const T & data) const {
		NODE_PTR Node = nullptr;
		queue<NODE_PTR> Q;
		Q.push(Root);
		while ( !Q.empty( ) ) {
			Node = Q.front( ); Q.pop( );
			if ( Node->Data == data ) {
				return true;
			}
			if ( Node->Left )  Q.push(Node->Left);
			if ( Node->Right ) Q.push(Node->Right);
		}
		return false;
	}


	bool			isEmpty( ) const {
		return Root == nullptr;
	}


	virtual	int		GetHeight(NODE_PTR root = nullptr) const {
		if ( root == nullptr ) root = Root;
		int left_h, right_h;
		left_h = right_h = 0;
		if ( root->Left )  left_h = GetHeight(root->Left);
		if ( root->Right ) right_h = GetHeight(root->Right);
		return max(left_h + 1, right_h + 1);
	}

	virtual	int		GetLeaves(NODE_PTR root = nullptr) const {
		if ( root == nullptr ) root = Root;
		int leaves = 0;
		if ( root->Left )  leaves += GetLeaves(root->Left);
		if ( root->Right ) leaves += GetLeaves(root->Right);
		return max(leaves, 1);
	}


	void BuildTreePreorder(NODE_PTR root = nullptr, const T & data = 0) {
		// 输入一串数据, 按先序遍历的顺序放到树中
		T input;
		if ( Node == NULL ) {						// 处理Root
			cin >> input;
			if ( input != '#' ) {
				Root = make_shared<TreeNode>( );
				BuildTreePreorder(Root, input);
			}
		} else {
			Node->Data = data;
			cin >> input;
			if ( input != '#' ) {
				Node->Left = make_shared<TreeNode>( );
				BuildTreePreorder(Node->Left, input);
			}
			cin >> input;
			if ( input != '#' ) {
				Node->Right = make_shared<TreeNode>( );
				BuildTreePreorder(Node->Right, input);
			}
		}
		return;
	}	

	void PrintTree( ) const {
		queue<NODE_PTR> Q;
		Q.push(Root);
		while ( !Q.empty( ) ) {
			NODE_PTR Node = Q.front( ); Q.pop( );
			cout << Node->Data << " -> ( ";
			if ( Node->Left ) {
				Q.push(Node->Left);
				cout << Node->Left->Data << " ";
			}
			if ( Node->Right ) {
				Q.push(Node->Right);
				cout << Node->Right->Data << " ";
			}
			cout << ")" << endl;
		}
		cout << endl;
		return;
	}


	void PrintTreeStruct(NODE_PTR root = nullptr, int Incident = 0) const {
		// Unfinished
		if ( root == nullptr ) root = Root;
		if ( root ) {
			int i;
			for ( i = 0; i < (Incident - 1) * 4; i++ ) cout << " ";
			for ( ; i < Incident * 4; i++ ) cout << "-";
			cout << root->Data << endl;
		} else {
			return;
		}
		if ( root->Left ) PrintTreeStruct(root->Left, Incident + 1);
		if ( root->Right ) PrintTreeStruct(root->Right, Incident + 1);
	}


	void PreorderTrav(NODE_PTR root = nullptr) const {
		if ( Root == nullptr ) return;
		if ( root == nullptr ) root = Root;
		cout << root->Data << " ";
		if ( root->Left )  PreorderTrav(root->Left);
		if ( root->Right ) PreorderTrav(root->Right);
		if ( root == Root ) cout << endl;
	}


	void InorderTrav(NODE_PTR root = nullptr) const {
		if ( root == nullptr ) root = Root;
		if ( root->Left )  InorderTrav(root->Left);
		cout << root->Data << " ";
		if ( root->Right ) InorderTrav(root->Right);
		if ( root == Root ) cout << endl;
	}


	void PostorderTrav(NODE_PTR root = nullptr) const {
		if ( root == nullptr ) root = Root;
		if ( root->Left )  PostorderTrav(root->Left);
		if ( root->Right ) PostorderTrav(root->Right);
		cout << root->Data << " ";
		if ( root == Root ) cout << endl;
	}


	void LevelorderTrav( ) const {
		queue<NODE_PTR> Q;
		NODE_PTR pTree = nullptr;
		if ( Root != nullptr ) Q.push(Root);
		while ( !Q.empty( ) ) {
			pTree = Q.front( ); Q.pop( );
			cout << pTree->Data << " ";
			if ( pTree->Left )  Q.push(pTree->Left);
			if ( pTree->Right ) Q.push(pTree->Right);
		}
		cout << endl;
		return;
	}

	void LevelorderTrav_DFS ( ) const {
		
	}


	//NODE_PTR		Clone(NODE_PTR pNode) const;
};



void GeneratePermutation(std::vector<int> & arr, int Size) {
	srand(clock( ));
	arr.clear( );
	std::map<int, bool> isMark;
	int tmp;

	for ( int cnt = 0; cnt < Size; cnt++ ) {
		do {
			tmp = rand( ) % Size;
		} while ( tmp >= 0 && isMark[tmp] );
		isMark[tmp] = true;
		arr.push_back(tmp);
	}

	return;
}
