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

#define SIZE 100005

vector <ll> graph[SIZE];
ll subtree[SIZE];
ll visited[SIZE];
ll parent[SIZE];
ll value[SIZE];
ll subsum[SIZE];


void subtree_dfs(ll s){
	visited[s] = 1;
	subtree[s] = 1;
	subsum[s] = value[s];
	if(graph[s].size() == 0){
		return;
	}

	for(ll i = 0; i < graph[s].size(); i++){
		if(visited[graph[s][i]] == 0){
			visited[graph[s][i]] = 1;
			subtree_dfs(graph[s][i]);
			parent[graph[s][i]] = s;
			subtree[s] += subtree[graph[s][i]];
			subsum[s] += subsum[graph[s][i]];
		}
	}
}

//-------------HLD-------------//

ll chainNo = 1, chainHead[SIZE], chainPos[SIZE], chainInd[SIZE], chainSize[SIZE];

void HLD(ll s){
	visited[s] = 1;
	if(chainHead[chainNo] == -1){
		chainHead[chainNo] = s;
	}
	chainInd[s] = chainNo;
	chainPos[s] = ++chainSize[chainNo];

	ll ind = -1, mai = -1;
	for(ll i = 0; i < graph[s].size(); i++){
		if(visited[graph[s][i]] == 0 && subtree[graph[s][i]] > mai){
			mai = subtree[graph[s][i]];
			ind = i;
		}
	}

	if(ind >= 0){
		HLD(graph[s][ind]);
	}

	for(ll i = 0; i < graph[s].size(); i++){
		if(i != ind && visited[graph[s][i]] == 0){
			chainNo++;
			HLD(graph[s][i]);
		}
	}
}

//-------------HLD-------------//

int main(){
	ll n, i, q, x, j;
	sl(n); sl(q); sl(x);
	for(i = 0; i < n - 1; i++){
		ll x, y;
		sl(x); sl(y);
		graph[x].pb(y);
		graph[y].pb(x);
	}
	for(i = 1; i <= n; i++){
		sl(value[i]);
	}
	subtree_dfs(1);
	memset(chainHead, -1, sizeof(chainHead));
	memset(visited, 0, sizeof(visited));
	HLD(1);

}
