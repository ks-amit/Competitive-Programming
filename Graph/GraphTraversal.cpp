#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define si(x) scanf("%d", &x)
#define sc(x) scanf("%c", &x)
#define sl(x) scanf("%lld", &x)
#define pl(x) printf("%lld\n", x)
#define pi(x) printf("%d\n", x)
#define gu getchar_unlocked
#define pu putchar_unlocked
#define setbits __builtin_popcountll
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define speed ios::sync_with_stdio(false)

// Depth First Search ( Recursive )

int visited[100002];
vector <int> graph[100002];

void DFS(int s){
	visited[s] = 1;
	
	// PROCESS THE CURRENT VERTEX
	
	for(int i = 0; i < graph[s].size(); i++){
		if(visited[graph[s][i]] == 0){
			visited[graph[s][i]] = 1;
			
			// PRE-PROCESS THE CHILD OF THE CURRENT VERTEX
			// parent[graph[s][i]] = s;
			// depth[graph[s][i]] = depth[s] + 1;
			
			DFS(graph[s][i]);
		}
	}
}

// EULER TOUR TREE

vector <int> graph[100002];
int visited[100002];
vector <int> ETT;

void travel(int s){
	visited[s] = 1;
	ETT.pb(s);
	for(i = 0; i < graph[s].size(); i++){
		if(visited[graph[s][i]] == 0){
			visited[graph[s][i]] = 1;
			travel(graph[s][i]);
		}
	}
	ETT.pb(s);
}

// Breadth First Search Algorithm for a matrix

bool visited[1000][1000];
int graph[1000][1000];

// (a, b) --> starting index
// (m, n) --> order of the matrix

void BFS(int m, int n, int a, int b){
	queue <int> q;
	memset(visited, false, sizeof(visited[0][0]) * m * n);
	q.push(a);
	q.push(b);
	while(q.size() > 0){
		int x = (q.front());
		q.pop();
		int y = (q.front());
		q.pop();
		visited[x][y] = true;
		
		// PROCESS THE CURRENT VERTEX
		
		if(x - 1 >= 0 && x - 1 < m && y >= 0 && y < n && visited[x - 1][y] == 0){
			q.push(x - 1); q.push(y);
			visited[x - 1][y] = true;
		}
		if(x + 1 >= 0 && x + 1 < m && y >= 0 && y < n && visited[x + 1][y] == 0){
			q.push(x + 1); q.push(y);
			visited[x + 1][y] = true;
		}
		if(x >= 0 && x < m && y - 1 >= 0 && y - 1 < n && visited[x][y - 1] == 0){
			q.push(x); q.push(y - 1);
			visited[x][y - 1] = true;
		}
		if(x >= 0 && x < m && y + 1 >= 0 && y + 1 < n && visited[x][y + 1] == 0){
			q.push(x); q.push(y + 1);
			visited[x][y + 1] = true;
		}
	}
}

// Breadth First Search Algorithm for a vector representation of a graph
		// CALCULATE SHORTEST DISTANCE FROM STARTING VERTEX TO EVERY OTHER VERTEX

vector <int> graph[10002];
int dist[10002];                 // distance array
int visited[10002];

// s --> starting vertex

void BFS(int s){
	queue <int> q;
	q.push(s);
	dist[s] = 0;
	while(q.size() > 0){
		int ver = q.front();
		visited[ver] = 1;

		// PROCESS THE CURRENT VERTEX

		q.pop();
		for(int i = 0; i < graph[ver].size(); i++){
			if(visited[graph[ver][i]] == 0){
				q.push(graph[ver][i]);
				visited[graph[ver][i]] = 1;
				dist[graph[ver][i]] = min(dist[graph[ver][i]], dist[ver] + 1);
				
				// PRE-PROCESS THE CHILD OF THE CURRENT VERTEX

			}
		}
	}
}
