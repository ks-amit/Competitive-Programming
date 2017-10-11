#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define si(x) scanf("%d", &x)
#define sc(x) scanf("%c", &x)
#define sl(x) scanf("%lld", &x)
#define pl(x) printf("%lld\n", x)
#define pi(x) printf("%d\n", x)
#define setbits __builtin_popcountll
#define MOD 1000000007
#define speed ios::sync_with_stdio(false)

const int N = 100005;

int prime[N];
ll divisors[N];
ll sod[N];
ll lprime[N];
ll hprime[N];
vector <ll> pf;
vector <int> pr;

// STANDARD SIEVE

void sieve(int N){
	int i, j;
	memset(prime, 0, sizeof(prime));
	prime[0] = 1; prime[1] = 1;
	for(i = 2; i * i <= N; i++){
		if(prime[i] == 0){
			for(j = i * i; j <= N; j += i){
				prime[j] = 1;
			}
		}
	}
}

// NUMBER OF DIVISORS USING SIEVE

void sieve(int N){
	int i, j;
	memset(divisors, 0, sizeof(divisors));
	for(i = 1; i <= N; i++){
		for(j = i; j <= N; j += i){
			divisors[j]++;
		}
	}
}

// SUM (OR PRODUCT) OF DIVISORS USING SIEVE 

void sieve(int N){
	int i, j;
	memset(sod, 0, sizeof(sod));
	for(i = 1; i <= N; i++){
		for(j = i; j <= N; j += i){
			sod[j] += i; // ( USE * FOR PRODUCT OF DIVISORS )
		}
	}
}

// LOWEST PRIME FACTOR USING SIEVE

void sieve(int N){
	int i, j;
	memset(lprime, 0, sizeof(lprime));
	lprime[1] = 0;
	for(i = 2; i * i <= N; i++){
		if(lprime[i] == 0){
            lprime[i] = i;
			for(j = i * i; j <= N; j += i){
				if(lprime[j] == 0){
					lprime[j] = i;
				}
			}
		}
	}
}

// HIGHEST PRIME FACTOR USING SIEVE AND PRIME FACTORISATION

void sieve(int N){
	int i, j;
	memset(hprime, 0, sizeof(hprime));
	hprime[1] = 0;
	for(i = 2; i <= N; i++){
		if(hprime[i] == 0){
			for(j = i; j <= N; j += i){
				hprime[j] = i;
			}
		}
	}
}

void pfactor(int a){
	pf.clear();
	while(a > 1){
		pf.push_back(hprime[a]);
		a /= hprime[a];
	}
}

// LINEAR RUNTIME SIEVE - LOWEST PRIME IN O(n)

void sieve1(int N){
	int i, j;
	memset(lprime, 0, sizeof(lprime));
	for(i = 2; i <= N; i++){
		if(lprime[i] == 0){
			lprime[i] = i;
			pr.push_back(i);
		}
		for(j = 0; j < pr.size() && pr[j] <= lprime[i] && i * pr[j] <= N; j++){
			lprime[i * pr[j]] = pr[j];
		}
	}
}

