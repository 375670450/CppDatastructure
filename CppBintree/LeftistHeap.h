#pragma once
#include "stdafx.h"
using namespace std;

template <typename T, typename Comparator = less<T> >
class LeftistHeap{
// LeftistHeap is mainly designed for solving the problem of merging two priority_queue 

private:
	struct LHeapNode {
		T Data;
		shared_ptr<LHeapNode> Left;
		shared_ptr<LHeapNode> Right;
		int npl;
		LHeapNode(T _data = 0, int _npl = 0): npl(_npl), Data(_data) {  Left = Right = nullptr; }
	};

	typedef shared_ptr<LHeapNode> NODE_PTR;

	NODE_PTR Root;

	const Comparator isLessThan;

	void SwapChildren(NODE_PTR root) {
		if ( root == nullptr ) return;
		NODE_PTR tmp = root->Left;
		root->Left = root->Right;
		root->Right = tmp;
	}

	int	GetNpl(NODE_PTR Node) {
		if ( Node == nullptr ) return -1;
		else  return Node->npl;
	}

	NODE_PTR HeapMerge(NODE_PTR LH1, NODE_PTR LH2) {
		if ( LH1 == nullptr ) return LH2;
		if ( LH2 == nullptr ) return LH1;
		function< NODE_PTR(NODE_PTR , NODE_PTR) > MergeFunc;
		MergeFunc = 
			[&] (NODE_PTR H1, NODE_PTR H2) {
			// ԭ��: �����ڵ�ϴ����(Ĭ��ΪH2, �ɵ��ú�����֤)�ϲ������ڵ��С����(Ĭ��ΪH1)��ȥ�� 
			//*	1�������ڵ��С����(������һ����)�����������򽫸��ڵ�ϴ������Ϊ�������� 
			//* 2�������ڵ��С���������������򽫸��ڵ�ϴ�����͸��ڵ��С�������������ϲ�����Ϊ���ڵ��С������������ 
			//* 3��������������·����С������������·�������򽻻���������
			//* 4�����ڵ��С��������·��������Ϊ������������·������+1 
			if ( H1->Left == nullptr ) H1->Left = H2;	
			else {
				H1->Right = HeapMerge(H1->Right, H2);
			}
			if ( H1->Right != nullptr ) {
				if ( H1->Left->npl < H1->Right->npl ) {
					SwapChildren(H1);
				}
				//H1->npl = H1->Right->npl + 1;
			}
			H1->npl = GetNpl(H1->Right) + 1;
			return H1;
		};
		if ( isLessThan(LH1->Data, LH2->Data) ) {
			return MergeFunc(LH1, LH2);
		} else {
			return MergeFunc(LH2, LH1);
		}
	}

public:

	LeftistHeap(){ Root = nullptr; }

	~LeftistHeap(){}

	void Print( ) const {
		queue<NODE_PTR> Q;
		map<NODE_PTR, int> mark;
		if ( Root != nullptr ){
			Q.push(Root);
			mark[Root] = 0;
		}
		while ( !Q.empty( ) ) {
			NODE_PTR Node = Q.front( ); Q.pop( );
			cout << Node->Data << " -> ";
			if ( Node->Left ) cout << Node->Left->Data << " ";
			cout << "|";
			if ( Node->Right ) cout << Node->Right->Data << " ";
			cout << endl;
			if ( Node->Left ) {
				//mark[Node->Left] = mark[Node] + 1;
				Q.push(Node->Left);
			}
			if ( Node->Right ) {
				//mark[Node->Right] = mark[Node] + 1;
				Q.push(Node->Right);
			}
		}
		cout << endl;
		return;
	}

	void Insert(T data) {
		NODE_PTR Node = make_shared<LHeapNode>(data);
		Root = HeapMerge(Root, Node);
	}

	void Delete( ){
		if ( Root == nullptr ) return;
		T elem = Root->Data;
		HeapMerge(Root->Left, Root->Right);
		return;	
	}

	const T & GetRoot( ) {
		return Root->Data;
	}
};
