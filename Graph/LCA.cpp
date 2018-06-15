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

#define SIZE 1005
#define LOGSIZE 15

vector <int> graph[SIZE];
int parent[SIZE][LOGSIZE + 1], depth[SIZE], visited[SIZE];

void dfs(int s){   
	visited[s] = 1;
	for(int i = 0; i < graph[s].size(); i++){
		if(visited[graph[s][i]] == 0){
			depth[graph[s][i]] = depth[s] + 1;
			parent[graph[s][i]][0] = s;
			dfs(graph[s][i]);
		}
	}
}

void setup(){
	for(int j = 1; j < LOGSIZE; j++){
		for(int i = 0; i < SIZE; i++){
			if(parent[i][j - 1] != -1){
				parent[i][j] = parent[parent[i][j - 1]][j - 1];
			}
		}
	}
}

int lca(int A, int B){
	
	if(depth[A] < depth[B]){             // MAKE SURE A HAS MORE DEPTH 
		swap(A, B);
	}

	if(depth[A] != depth[B]){            // HOP IN THE PATH OF A TO HAVE SAME DEPTH
		for(int i = LOGSIZE; i >= 0; i--){
			if(depth[A] - (1 << i) >= depth[B]){
				//cout<<i<<endl;
				A = parent[A][i];
			}
		}
	}

	if(A == B){
		return A;
	}
	else{
		for(int i = LOGSIZE; i >= 0; i--){
			if(parent[A][i] != -1 && parent[B][i] != -1 && parent[A][i] != parent[B][i]){
				A = parent[A][i];
				B = parent[B][i];
			}
		}
	}

	return parent[A][0];

}

int main(){
	
}