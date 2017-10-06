// BINARY INDEXED TREE

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
#define SIZE 100005

int BIT1[SIZE], BIT2[SIZE];

void updateFT(int BIT[], int n, int index, int value){
	for(; index <= n; index += index&-index){
		BIT[index] += value;
	}
}

int queryFT(int BIT[], int index){
	int sum = 0;
	while(index > 0){
		sum += BIT[index];
		index -= index&-index;
	}
	return sum;
}


void rangeupdateFT(int BIT1[], int BIT2[], int n, int left, int right, int value){
	updateFT(BIT1, n, left, value);
	updateFT(BIT1, n, right + 1, - value);
	updateFT(BIT2, n, left, value * (left - 1));
	updateFT(BIT2, n, right + 1, -value * right);
}

// returns the sum of first 'index' elements if range updates are done
int sumFT(int BIT1[], int BIT2[], int index){
	return ((queryFT(BIT1, index) * index) - queryFT(BIT2, index));
}

int rangequeryST(int BIT1[], int BIT2[], int left, int right){
	return sumFT(BIT1, BIT2, right) - sumFT(BIT1, BIT2, left - 1);
}
