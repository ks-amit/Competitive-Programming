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


// DISJOINT SUBSET

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