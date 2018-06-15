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
ll *BIT1[SIZE];
ll *BIT2[SIZE];

void updateFT(ll BIT[], ll n, ll index, ll value){
	for(; index <= n; index += index&-index){
		BIT[index] += value;
	}
}

ll queryFT(ll BIT[], ll index){
	ll sum = 0;
	while(index > 0){
		sum += BIT[index];
		index -= index&-index;
	}
	return sum;
}


void rangeupdateFT(ll BIT1[], ll BIT2[], ll n, ll left, ll right, ll value){
	updateFT(BIT1, n, left, value);
	updateFT(BIT1, n, right + 1, - value);
	updateFT(BIT2, n, left, value * (left - 1));
	updateFT(BIT2, n, right + 1, -value * right);
}

// returns the sum of first 'index' elements if range updates are done
ll sumFT(ll BIT1[], ll BIT2[], ll index){
	return ((queryFT(BIT1, index) * index) - queryFT(BIT2, index));
}

ll rangequeryFT(ll BIT1[], ll BIT2[], ll left, ll right){
	return sumFT(BIT1, BIT2, right) - sumFT(BIT1, BIT2, left - 1);
}

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

void Setup(ll n){
	ll i;
	for(i = 1; i <= n; i++){
		ll Cno = chainInd[i];
		ll Cpos = chainPos[i];
		ll Csize = chainSize[Cno];
		rangeupdateFT(BIT1[Cno], BIT2[Cno], Csize, Cpos, Cpos, subsum[i]);
	}
}

void traverse(ll s){
	
	ll i;

	ll Cno = chainInd[s];
	ll Cpos = chainPos[s];
	ll Csize = chainSize[Cno];

	while(1){
		for(i = Cpos; i >= 1; i--){
			cout<<rangequeryFT(BIT1[Cno], BIT2[Cno], i, i)<<endl;
		}
		ll Chead = chainHead[Cno];
		ll par = parent[Chead];
		if(par == 0){
			break;
		}
		Cno = chainInd[par];
		Cpos = chainPos[par];
		Csize = chainSize[Cno];
	}

}

ll bs1(ll Cno, ll pos, ll X){

	ll left = pos, right = 1;
//	cout<<left<<" "<<right<<endl;
	while(abs(right - left) > 1){
		ll mid = (left + right) / 2;
		//cout<<"MID : "<<mid<<endl;
		ll val1 = rangequeryFT(BIT1[Cno], BIT2[Cno], mid, mid);
		ll val2 = rangequeryFT(BIT1[Cno], BIT2[Cno], mid + 1, mid + 1);
		if(val2 < X && val1 >= X){
			return mid;
		}
		else if(val1 < X && val2 < X){
			left = mid;
		}
		else{
			right = mid;
		}
	}
	ll lval = rangequeryFT(BIT1[Cno], BIT2[Cno], left, left);
	ll rval = rangequeryFT(BIT1[Cno], BIT2[Cno], right, right);
	if(rval >= X && lval < X){
		return right;
	}
	else if(lval >= X && rval >= X){
		return left;
	}
}

ll bs2(ll Cno, ll pos, ll X){
	ll left = pos, right = 1;
	while(abs(right - left) > 1){
		ll mid = (left + right) / 2;
		ll val1 = rangequeryFT(BIT1[Cno], BIT2[Cno], mid, mid);
		ll val2 = rangequeryFT(BIT1[Cno], BIT2[Cno], mid - 1, mid - 1);
		if(val1 <= X && val2 > X){
			return mid;
		}
		else if(val1 > X){
			right = mid;
		}
		else{
			left = mid;
		}
	}
	ll lval = rangequeryFT(BIT1[Cno], BIT2[Cno], left, left);
	ll rval = rangequeryFT(BIT1[Cno], BIT2[Cno], right, right);
	if(lval <= X && rval > X){
		return left;
	}
	else{
		return right;
	}

}

ll countX(ll Cno, ll pos, ll X1, ll X2){
	//cout<<"CHAIN : "<<Cno<<endl;
	ll sval = rangequeryFT(BIT1[Cno], BIT2[Cno], pos, pos);
	ll eval = rangequeryFT(BIT1[Cno], BIT2[Cno], 1, 1);
	//cout<<"Smallest : "<<sval<<" and Largest : "<<eval<<endl;
	if((sval < X1 && eval < X1) || (sval > X2 && eval > X2)){
		//cout<<"FIRST PASS FAILED"<<endl;
		return 0;
	}
	else{
		//cout<<"FIRST PASS DONE"<<endl;
		//cout<<"BS1"<<endl;
		//cout<<"POS : "<<pos<<endl;
		ll start = bs1(Cno, pos, X1);
		//cout<<endl;
		ll end = bs2(Cno, pos, X2);
		//cout<<"Start : "<<start<<" and End : "<<end<<endl;
		if(start - end + 1 > 0){
			return start - end + 1;
		}
		else{
			return 0;
		}
		
	}
}

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
	//cout<<"DONE"<<endl;
	subtree_dfs(1);
	memset(chainHead, -1, sizeof(chainHead));
	memset(visited, 0, sizeof(visited));
	HLD(1);

	for(i = 1; i <= n; i++){
		ll Csize = chainSize[i];
		if(Csize == 0){
			break;
		}
		BIT1[i] = (ll *)malloc((Csize + 2) * sizeof(ll));
		BIT2[i] = (ll *)malloc((Csize + 2) * sizeof(ll));
	}

	Setup(n);

	ll ans = 0;
	for(i = 1; i <= n; i++){
		if(subsum[i] > x){
			ans++;
		}
	}

	while(q--){
		ll ind, val;
		sl(ind); sl(val);
		ll k, Cno = chainInd[ind], Cpos = chainPos[ind], Csize = chainSize[Cno];
		while(1){
			//cout<<"BS VALUE : "<<countX(Cno, Cpos, x - val + 1, x)<<endl;
			//traverse(ind);
			ans += countX(Cno, Cpos, x - val + 1, x);
			rangeupdateFT(BIT1[Cno], BIT2[Cno], Csize, 1, Cpos, val);
			ll Chead = chainHead[Cno];
			ll par = parent[Chead];
			if(par == 0){
				break;
			}
			Cno = chainInd[par];
			Cpos = chainPos[par];
			Csize = chainSize[Cno];
		}
		pl(ans);
		//cout<<endl;
	}
}