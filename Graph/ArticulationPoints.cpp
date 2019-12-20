#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define si(x) scanf("%d", &x)
#define sc(x) scanf("%c", &x)
#define sl(x) scanf("%lld", &x)
#define pl(x) printf("%lld\n", x)
#define pi(x) printf("%d\n", x)
#define all(x) x.begin(), x.end()
#define pii pair <int, int>
#define pll pair <long long, long long>
#define gu getchar_unlocked
#define pu putchar_unlocked
#define setbits __builtin_popcountll
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define speed ios::sync_with_stdio(false)

const int N = 1e5;

vector <int> graph[N], bridge[N], edges;


// set parent array to -1 before calling articulation_points()
int disc[N], low[N], visited[N], parent[N], AP[N];
int curr_time = 0;

void articulation_points(int s){
	visited[s] = 1;

	// set discovery time and low time equal to curr time
	curr_time++;
	disc[s] = curr_time;
	low[s] = curr_time;

	// number of childs of current vertex = 0
	int num_child = 0;

	for(int i = 0; i < graph[s].size(); i++){
		if(visited[graph[s][i]] == 0){
			// found new child
			num_child++;

			// set parent of child as `s`
			parent[graph[s][i]] = s;

			articulation_points(graph[s][i]);

			// propagate low time and find back edges
			low[s] = min(low[s], low[graph[s][i]]);

			// curr vertex is an AP if root of DFS and has > 1 children
			if(parent[s] == -1 && num_child > 1){
				AP[s] = 1;
			}

			// curr vertex is AP if there exists a back edge from any child to ancestor
			if(parent[s] != -1 && disc[s] <= low[graph[s][i]]){
				AP[s] = 1;
			}

			// the xonnecting edge is a bridge if there is no back edge
			if(low[graph[s][i]] > disc[s]){
				bridge[s].pb(graph[s][i]);
			}
		}

		// Back edge found if the visited vertex is not the parent
		else if(parent[s] != graph[s][i]){
			low[s] = min(low[s], disc[graph[s][i]]);
		}
	}
}