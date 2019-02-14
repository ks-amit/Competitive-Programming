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

const int N = 100005;
const int LOGN = 100;

int arr[N];

// PERSISTENT SEGMENT TREE (ARRAY BASED)

int segTree[N * LOGN];	// POOL OF NODES
int L[N * LOGN];	
int R[N * LOGN];
int heads[N];	// START POINT OF SEGMENT TREES

int next_free_node;

void buildST(int left, int right, int index){
	if(left == right){
		segTree[index] = arr[left];
	}
	else{
		int mid = (left + right) / 2;
		L[index] = next_free_node++;
		R[index] = next_free_node++;
		buildST(left, mid, L[index]);
		buildST(mid + 1, right, R[index]);
		segTree[index] = segTree[L[index]] + segTree[R[index]];
	}
}

int updateST(int left, int right, int index, int upindex, int upvalue){
	if(left == right){
		int new_index = next_free_node++;
		segTree[new_index] = segTree[index] + upvalue;
		return new_index;
	}
	else{
		int new_index = next_free_node++;
		int mid = (left + right) / 2;
		L[new_index] = L[index];
		R[new_index] = R[index];
		if(upindex >= left && upindex <= mid){
			L[new_index] = updateST(left, mid, L[new_index], upindex, upvalue);
		}
		else{
			R[new_index] = updateST(mid + 1, right, R[new_index], upindex, upvalue);
		}
		segTree[new_index] = segTree[L[new_index]] + segTree[R[new_index]];
		return new_index;
	}
}

int queryST(int qleft, int qright, int left, int right, int index){
	if(qleft > right || qright < left || qright < qleft){
		return 0;
	}
	else if(qleft <= left && qright >= right){
		return segTree[index];
	}
	else{
		int mid = (left + right) / 2;
		ll p = queryST(qleft, qright, left, mid, L[index]);
		ll q = queryST(qleft, qright, mid + 1, right, R[index]);
		return p + q;
	}
}

int main(){

}