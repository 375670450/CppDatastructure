#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <map>
using namespace std;

struct problem {
	string name;
	int t;
	int d;
};

int H, N;
int totaltime, besttime;
bool solved[20];
vector<problem> vec;
vector<int> order;
vector<int> bestorder;

 void solve (int index, int currenttime) {
	problem p = vec[index];
	int rejects = ( currenttime + p.t - 1 ) / 60;
	int solvetime = rejects*p.d + p.t;
	if ( currenttime + solvetime >= H )
		return;
	totaltime += currenttime + solvetime + rejects * 20;
             	solved[index] = 1;
	order.push_back (index);

	if ( order.size ( ) > bestorder.size ( ) || totaltime < besttime ) {
		// this try is good, choose next problem
		if ( order.size ( ) > bestorder.size ( ) ) {
			bestorder = order;
			besttime = totaltime;
		}
		for ( int i = 0; i < N; i++ ) {
			if ( !solved[i] )
				solve (i, currenttime + solvetime);
		}
	}

	order.pop_back ( );
	totaltime -= currenttime + solvetime + rejects * 20;
	solved[index] = 0;
}

int main ( ) {

	ios_base::sync_with_stdio (false);
	problem p;
	int begintime;
	while ( ( cin >> H ) && H > 0 ) {
		H *= 60;
		cin >> N >> begintime;
		besttime = 0x7fffffff;

		memset (solved, 0, sizeof (solved));
		vec.clear ( );
		for ( int i = 0; i < N; i++ ) {
			cin >> p.name >> p.t >> p.d;
			vec.push_back (p);
		}
		for ( int i = 0; i < N; i++ ) {
			totaltime = 0;
			solve (i, begintime);
		}
		cout << "Total Time = " << besttime << endl;
		for ( int i = 0; i < bestorder.size ( ); i++ ) {
			cout << vec[bestorder[i]].name << endl;
		}
	}


}