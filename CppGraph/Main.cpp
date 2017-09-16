#pragma warning(disable:4996)
#include "CppGraph.h"

using namespace std;
/*
Test Data:
4 5
0 1
1 2
2 0
3 1
3 2
*/
int main( ) {

	//freopen("input.txt", "r", stdin);
	char a, b;
	int c, u, v, N, E;
	UndirectedGraph<char> G;
	DirectedGraph<int> DG;

	cin >> N >> E;
	for ( int i = 0; i < E; i++ ) {
		cin >> u >> v;
		DG.AddEdge (u, v);
	}
	DG.Kosaraju ( );
	//DG.DFS ( );
	system ("pause");
	return 0;
	while ( cin >> a >> b >> c && c > 0 ) {
		G.AddEdge(a, b, c);
	}
	map<char, int> shortDist;
	G.FindPath_Dijkstra('A', shortDist);
	auto it = shortDist.begin( );
	while ( it != shortDist.end( ) ) {
		cout << it->first << " : " << it->second << endl;
		it++;
	}
	cout << endl;
	system("pause");
	return 0;
}   