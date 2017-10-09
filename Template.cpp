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


// FAST I/O

void fastscan(int &x){
	register int c = getchar_unlocked();
	x = 0;
	for(; (c<48 || c>57); c = getchar_unlocked());
	for(; c>47 && c<58; c = getchar_unlocked()){
		x = (x<<1) + (x<<3) + c - 48;
	}
}

// GCD - EUCLID'S ALGORITHM

ll gcd(ll a, ll b){
	if(b == 0){
		return a;
	}
	else{
		return gcd(b, a % b);
	}
}

// MILLER RABIN PRIMALITY TEST

bool millerrabin(ll n){
	if(n <=1 || n % 2 == 0){
		if(n != 2){
			return false;
		}
	}
	if(n == 2 || n == 3){
		return true;
	}
	ll d = n-1;
	while(d % 2 == 0){
		d /= 2;
	}
	ll a[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for(int i = 0; i < 12 && a[i] < n; ++i){
		ll temp = d;
		ll mod = largepow(a[i], temp, n);
		if( mod == 1 || mod == n-1){
			continue;
		}
		while(temp != n-1 && mod != n-1){
			mod = fastmul(mod, mod, n);
			temp *= 2;
		}
		if(mod != n-1){
			return false;
		}
	}
	return true;
}

// DISJOINT SUBSET

// two arrays arr[] and size[] of size <n> required

void setupDS(int arr[], int size[], int n){
	for(int i = 0; i < n; i++){
		arr[i] = i;
		size[i] = 1;
	}
}

int rootDS(int arr[], int n, int A){
	while(arr[A] != A){
		arr[A] = arr[arr[A]];
		A = arr[A];
	}
	return A;
}

void unionDS(int arr[], int size[], int n, int A, int B){
	int rootA = rootDS(arr, n, A);
	int rootB = rootDS(arr, n, B);
	if(size[rootA] < size[rootB]){
		arr[rootA] = arr[rootB];
		size[rootB] += size[rootA];
	}
	else{
		arr[rootB] = arr[rootA];
		size[rootA] += size[rootB];
	}
}
