#pragma once

#include "stdafx.h"

/*
为int类型特化
*/

const int MaxVerteices = 100;

template<typename Vertex, typename WeightT = int>
class DirectedGraph {			
/*  Directed Graph In CrossList  */	
private:
	
	struct EdgeNode {				// Edge as the element of crosslist
		Vertex from;							
		Vertex to;
		WeightT weight;
		std::shared_ptr<EdgeNode>  right;								// Out Edge
		std::shared_ptr<EdgeNode>  down;							// In Edge
		EdgeNode (Vertex _u, Vertex _v, WeightT _w = 0) { right = down = nullptr; from = _u; to = _v; weight = _w; }
		void Print ( ) { std::cout << from << " -> " << to << "  "; }
	} ;
	typedef std::shared_ptr<EdgeNode> Node_Ptr;
	std::map<Vertex, int> VertexID;
	std::vector<Node_Ptr> CrossList;									// List with a dummy head
	int Nv, Ne;
	
public:
	
	DirectedGraph ( ) { 
		Nv = Ne = 0;
	};
	~DirectedGraph ( ) { };

	void AddVertex (Vertex u);

	void AddEdge (Vertex _u, Vertex _v, WeightT _w = 0);

	int size ( ) { return VertexID.size ( ); }

	void BFS ( );

	void DFS ( );

	void TopologicalSort ( );

	void Tarjan ( );

	void Kosaraju ( );

	//void DeleteVertex (Vertex v);

	void Print ( );

};

template<typename Vertex, typename WeightT>
void DirectedGraph<Vertex, WeightT>::AddVertex (Vertex u) {
	//if ( VertexID.find (u) != VertexID.end ( ) ) return;
	VertexID[u] = VertexID.size ( );
	CrossList.push_back (make_shared<EdgeNode> (EdgeNode (u, -1)));
}



template<typename Vertex, typename WeightT>
inline void DirectedGraph<Vertex, WeightT>::AddEdge (Vertex _u, Vertex _v, WeightT _w) {
	if ( VertexID.find (_u) == VertexID.end ( ) ) AddVertex (_u);
	if ( VertexID.find (_v) == VertexID.end ( ) ) AddVertex (_v);
	int u = VertexID[_u], v = VertexID[_v];
	//EdgeNode newEdge (_u, _v, _w);
	Node_Ptr ptr = CrossList.at (u), newEdge = make_shared<EdgeNode> (EdgeNode( _u, _v, _w ));

	while ( ptr->right ) ptr = ptr->right;
	ptr->right = newEdge;
	ptr = CrossList.at (v);
	while ( ptr->down ) ptr = ptr->down;
	ptr->down = newEdge;
}

template<typename Vertex, typename WeightT>
inline void DirectedGraph<Vertex, WeightT>::BFS ( ) {
	std::map<Vertex, bool> isVisited;
	std::queue<Vertex> Q;
	Node_Ptr ptr;

	for ( int i = 0; i < CrossList.size ( ); i++ ) {
		ptr = CrossList.at (i);
		if ( !isVisited[ptr->from] ) {
			isVisited[ptr->from] = true;
			Q.push (ptr->from);
			while ( !Q.empty ( ) ) {
				ptr = CrossList.at (VertexID[Q.front ( )]); Q.pop ( );
				ptr = ptr->right;
				while ( ptr ) {
					if( !isVisited[ptr->to] ) {
						isVisited[ptr->to] = true;
						Q.push (ptr->to);
						ptr->Print ( );
					}
					ptr = ptr->right;
				}
			}
		}
		cout << endl;			// New line for another component(if any)
	}
}

template<typename Vertex, typename WeightT>
inline void DirectedGraph<Vertex, WeightT>::DFS ( ) {
	std::map<Vertex, bool> isVisited;
	std::stack<Vertex> S;
	Node_Ptr ptr;

	for ( int i = 0; i < CrossList.size ( ); i++ ) {
		ptr = CrossList.at (i);
		if ( !isVisited[ptr->from] ) {
			isVisited[ptr->from] = true;
			S.push (ptr->from);
			while ( !S.empty ( ) ) {
				ptr = CrossList.at (VertexID[S.top ( )]); S.pop ( );
				ptr = ptr->right;
				while ( ptr ) {
					if ( !isVisited[ptr->to] ) {
						isVisited[ptr->to] = true;
						S.push (ptr->to);
						ptr->Print ( );
					} else {
						ptr = ptr->right;
					}
				}

			}
		}
	}
}

template<typename Vertex, typename WeightT>
inline void DirectedGraph<Vertex, WeightT>::Kosaraju ( ) {
	// Two DFS
	stack<int> stk;			// Non_Recursive 
	vector<int> post_order;
	map<int, bool> isVisited;
	WeightT ReverseGraph[MaxVerteices][MaxVerteices];
	// First DFS, number the vertices
	for ( int i = 0, cur; i < CrossList.size ( ); i++ ) {
		if ( !isVisited[i] ) {
			stk.push (i);
			while ( !stk.empty() ) {
				cur = stk.top ( ); 
				isVisited[cur] = true;
				Node_Ptr ptr = CrossList.at(cur)->right;
				while ( ptr != nullptr ) {
					if ( !isVisited[ptr->to] ) {
						stk.push (ptr->to);
						break;
					}
					ptr = ptr->right;
				}
				if ( cur == stk.top ( ) ) {
					post_order.push_back (cur);
					stk.pop ( );
				}
			}
		}
		
	}
	
	// Ordinary DFS
	// 待补充的点: 把地图放进去, 碰撞检测(状态机?)
	isVisited.clear ( );
	for ( int i = post_order.size ( ) - 1, cur; i >= 0; i-- ) {
		cur = post_order[i];
		if ( !isVisited[cur] ) {
			stk.push (cur);
			while ( !stk.empty ( ) ) {
				cur = stk.top ( );
				cout << cur << endl;
				Node_Ptr ptr = CrossList.at (cur)->right;
				isVisited[cur] = true;
				while ( ptr ) {
					if ( !isVisited[ptr->to] ) {
						stk.push (ptr->to);
						break;
					}
					ptr = ptr->right;
				}
				if ( cur == stk.top ( ) ) {
					stk.pop ( );
				}
			}
		}
	}
}

template<typename Vertex, typename WeightT>
inline void DirectedGraph<Vertex, WeightT>::Print ( ) {
	for ( int i = 0; i < CrossList.size ( ); i++ ) {
		Node_Ptr ptr = CrossList.at (i);
		std::cout << ptr->from << " : " << endl << "Right : ";
		for ( ptr = ptr->right; ptr; ptr = ptr->right ) ptr->Print ( );
		ptr = CrossList.at (i);
		std::cout << endl << "Down : ";
		for ( ptr = ptr->down; ptr; ptr = ptr->down ) ptr->Print ( );
		std::cout << endl;
	}

}


/////////////////////////////////////////////////////////////////////////////

/////////////////////////			Graph Base		//////////////////////////////

//////////////////////////////////////////////////////////////////////////////



template<typename T, typename WeightT = int>
class GraphBase {
protected:
	struct  Edge {
		T				from, to;
		WeightT			weight;
		Edge(T _from, T _to, WeightT _weight = 1): 
			from(_from), to(_to), weight(_weight) { }
		bool operator <(const Edge & e) const {
			if ( from != e.from ) return from < e.from;
			if ( to != e.to ) return to < e.to;
			if ( weight != e.weight ) return weight < e.weight;
		}
	};
	std::set<T>											Vertices;
	std::map<T, std::set<Edge> >		Edges;
	void										_DFS(T v, std::map<T, bool> & isVisited);
	void										_BFS(T v, std::map<T, bool> & isVisited);

public:
	GraphBase(){}
	GraphBase(const GraphBase & G) {
		Vertices = G.Vertices;
		Edges = G.Edges;
	}
	~GraphBase( ) {}
	void										MinTree_Prim( T root);
	void										MinTree_Kruskal( );
	void										AddVertex(T vertex);
	void										DFS( );
	void										BFS( );
	void										FindPath_Dijkstra(T start, std::map<T, WeightT> & Distance);
	void										FindPath_Floyd(T start, std::map<T, WeightT> & Distance);
	virtual void							AddEdge(T u, T v, WeightT weight);
	virtual void							DeleteVertex(T vertex);
	void										test( ) {
		std::set<T>::iterator vit = Vertices.begin( );
		std::set<Edge>::iterator eit;
		while ( vit != Vertices.end( ) ) {
			eit = Edges[*vit].begin( );
			while ( eit != Edges[*vit].end( ) ) {
				std::cout << eit->from << " " << eit->to << std::endl;
				eit++;
			}
			vit++;
		}
	}
};

template<typename T, typename WeightT = int>
class UndirectedGraph : public GraphBase<T, WeightT> {
public:
	UndirectedGraph(){}
	~UndirectedGraph( ) {}
	void														AddEdge(T u, T v, WeightT weight);
	//void														Delete(T vertex);
};

template<typename T, typename WeightT>
inline void GraphBase<T, WeightT>::_DFS(T v, std::map<T, bool> & isVisited) {
	isVisited[v] = true;
	std::cout << v << " ";
	std::set<Edge>::iterator it = Edges[v].begin( );
	while ( it != Edges[v].end( ) ) {
		if ( !isVisited[it->to] ) {
			_DFS(it->to, isVisited);
		}
		it++;
	}
}

template<typename T, typename WeightT>
inline void GraphBase<T, WeightT>::_BFS(T v, std::map<T, bool>& isVisited) {
	std::queue<T> Q;
	Q.push(v);
	isVisited[v] = true;
	while ( !Q.empty( ) ) {
		T cur = Q.front( );		Q.pop( );
		std::cout << cur << " ";
		std::set<Edge>::iterator it = Edges[cur].begin( );
		while ( it != Edges[cur].end( ) ) {
			if ( !isVisited[it->to] ) {
				isVisited[it->to] = true;
				Q.push(it->to);
			}
			it++;
		}
	}
}

template<typename T, typename WeightT>
inline void GraphBase<T, WeightT>::MinTree_Prim(T root ) {
	/*
		Optimize this graph to be a MinTree.
		Mainly change the container Edges
	*/
	map<T, set<T> > newEdges;
	map<T, bool>	isVisited;

	Edges = newEdges;
	return;
}

template<typename T, typename WeightT>
inline void GraphBase<T, WeightT>::AddVertex(T vertex) {
	Vertices.insert(vertex);
}

template<typename T, typename WeightT>
inline void GraphBase<T, WeightT>::DFS( ) {
	std::map<T, bool> isVisited;
	std::set<T>::iterator it = Vertices.begin( );
	while ( it != Vertices.end( ) ) {
		if( !isVisited[*it] )	_DFS(*it, isVisited);
		it++;
		std::cout << std::endl;
	}
	return;
}

template<typename T, typename WeightT>
inline void GraphBase<T, WeightT>::BFS( ) {
	std::map<T, bool> isVisited;
	std::set<T>::iterator it = Vertices.begin( );
	while ( it != Vertices.end( ) ) {
		if ( !isVisited[*it] )	_BFS(*it, isVisited);
		it++;
		std::cout << std::endl;
	}
}

template<typename T, typename WeightT>
inline void GraphBase<T, WeightT>::FindPath_Dijkstra(T start, std::map<T, WeightT> & Distance) {
	/* This Algorithm return an array in which there are the shortest distance from 
		 start to this node.
	 */
	std::map<T, bool>	isVisited;
	int hasVisited = 1;
	const WeightT INF = std::numeric_limits<WeightT>::max( );
	auto v_it = Vertices.begin( );
	while ( v_it != Vertices.end( ) ) {
		Distance[*v_it] = INF;
		v_it++;
	}
	T v = start;
	Distance[start] = 0;
	while ( hasVisited < Vertices.size() ) {
		isVisited[v] = true;
		auto e_it = Edges[v].begin( );
		// Update the distance info of all vertices not visited
		while ( e_it != Edges[v].end( ) ) {
			if ( Distance[v] + e_it->weight < Distance[e_it->to] ) {
				Distance[e_it->to] = Distance[v] + e_it->weight;
			}
			e_it++;
		}
		// Find the nearest vertex to be next vertex
		auto v_it = Vertices.begin( );
		T nextV = v;
		while ( v_it != Vertices.end( ) ) {
			if ( !isVisited[*v_it] ) {
				if (	!isVisited[nextV]  && 	// both are not visited
						Distance[*v_it] < Distance[nextV] ) {
					nextV = *v_it;
				} else if ( nextV == v ) {
					nextV = *v_it;
				}
			}
			v_it++;
		}
		v = nextV;
		hasVisited++;
	}
	return;
}


template<typename T, typename WeightT>
inline void GraphBase<T, WeightT>::AddEdge(T u, T v, WeightT weight) {
	AddVertex(u);		AddVertex(v);
	Edges[u].insert(Edge(u, v, weight));
}

template<typename T, typename WeightT>
inline void GraphBase<T, WeightT>::DeleteVertex(T vertex) {
	std::set<T>::iterator vit = Vertices.begin( );
	std::set<Edge>::iterator eit;
	while ( vit != Vertices.end( ) ) {
		eit = Edges[*vit].begin( );
		while ( eit != Edges[*vit].end( ) ) {
			if ( eit->to == vertex ) {
				Edges[*vit].erase(eit++);
			} else {
				eit++;
			}
		}
		vit++;
	}
	Edges.erase(vertex);
	Vertices.erase(vertex);
}

template<typename T, typename WeightT>
inline void UndirectedGraph<T, WeightT>::AddEdge(T u, T v, WeightT weight) {
	AddVertex(u);		AddVertex(v);
	Edges[u].insert(Edge(u, v, weight));
	Edges[v].insert(Edge(v, u, weight));
}


