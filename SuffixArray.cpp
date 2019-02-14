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

// Build SUFFIX ARRAY

struct suffix{ 
	int index; 
	int rank[2]; 
}; 

int cmp(struct suffix a, struct suffix b){ 
	return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) : (a.rank[0] < b.rank[0] ? 1 : 0); 
} 

vector <int> buildSA(string s){ 
	int n = s.size();
	struct suffix suffixes[s.size()]; 
	for (int i = 0; i < n; i++){ 
		suffixes[i].index = i; 
		suffixes[i].rank[0] = s[i] - 'a'; 
		suffixes[i].rank[1] = ((i+1) < n) ? (s[i + 1] - 'a') : -1; 
	} 

	sort(suffixes, suffixes+n, cmp); 
	int ind[n]; 
	for(int k = 4; k < 2 * n; k = k * 2){ 
		int rank = 0; 
		int prev_rank = suffixes[0].rank[0]; 
		suffixes[0].rank[0] = rank; 
		ind[suffixes[0].index] = 0; 
		for (int i = 1; i < n; i++){ 
			if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i-1].rank[1]){ 
				prev_rank = suffixes[i].rank[0]; 
				suffixes[i].rank[0] = rank; 
			} 
			else{ 
				prev_rank = suffixes[i].rank[0]; 
				suffixes[i].rank[0] = ++rank; 
			} 
			ind[suffixes[i].index] = i; 
		} 
		for (int i = 0; i < n; i++) { 
			int nextindex = suffixes[i].index + k/2; 
			suffixes[i].rank[1] = (nextindex < n) ? suffixes[ind[nextindex]].rank[0] : -1; 
		} 
		sort(suffixes, suffixes+n, cmp); 
	} 

	vector <int> SA;
	for (int i = 0; i < n; i++){
		SA.pb(suffixes[i].index); 
	} 
	return SA; 
}

// BUILD INVERSE SUFFIX ARRAY

vector <int> invSuffix(vector <int> SA){
	vector <int> SA1(n, 0);
	for(int i = 0; i < n; i++){
		SA1[SA[i]] = i;
	}
	return SA1;
}

// LCP - KASAI

vector <int> kasai(string s, vector <int> SA){
	int n = s.size();
	vector <int> lcp(n, 0);
	
	int k = 0;
	for(int i = 0; i < n; i++){
		if(invSA[i] == n - 1){
			k = 0;
		}
		else{
			int j = SA[invSA[i] + 1];
			while(i + k < n && j + k < n && s[i + k] == s[j + k]){
				k++;
			}
			lcp[invSA[i]] = k;
			if(k > 0){
				k--;
			}
		}
	}
	return lcp;
} 