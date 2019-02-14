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

const int N = 100005;	// Max number of nodes

vector <int> graph[N];	// graph
vector <int> graph_t[N];	// transpose graph
vector <int> info[N];	// store SCC nodes

int visited[N];
vector <int> st;	// store Order of nodes (fillOrder)

void dfs_fillOrder(int s){
	visited[s] = 1;
	for(int i = 0; i < graph[s].size(); i++){
		if(visited[graph[s][i]] == 0){
			dfs_fillOrder(graph[s][i]);
		}
	}
	st.pb(s);
}

void create_transpose(int n){
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < graph[i].size(); j++){
			graph_t[graph[i][j]].pb(i);
		}
	}
}

void dfs_SCC(int s, int ind){
	visited[s] = 1;
	info[ind].pb(s);
	for(int i = 0; i < graph_t[s].size(); i++){
		if(visited[graph_t[s][i]] == 0){
			dfs_SCC(graph_t[s][i], ind);
		}
	}
}

void kosaraju(int n){	// get SCC into 'info'
	memset(visited, 0, sizeof(visited));
	for(int i = 1; i <= n; i++){
		if(visited[i] == 0){
			dfs_fillOrder(i);
		}
	}
	create_transpose(n);
	memset(visited, 0, sizeof(visited));
	int counter = 0;
	while(st.size() > 0){
		int curr = st[st.size() - 1];
		st.pop_back();
		if(visited[curr] == 0){
			dfs_SCC(curr, ++counter);
		}
	}
}

// TAKE INPUT IN GRAPH (1 based indexing)
// RUN kosaraju (n = number of nodes)