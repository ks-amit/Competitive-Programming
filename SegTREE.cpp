#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define si(x) scanf("%d", &x)
#define sc(x) scanf("%c", &x)
#define sl(x) scanf("%lld", &x)
#define pl(x) printf("%lld\n", x)
#define pi(x) printf("%d\n", x)
#define MOD 1000000007
#define speed ios::sync_with_stdio(false)

#define SIZE 100005

int arr[SIZE];
int segTree[4 * SIZE];

void buildST(int left, int right, int index){
	if(left == right){
		segTree[index] = arr[left];
	}
	else{
		int mid = (left + right) / 2;
		buildST(left, mid, 2 * index);
		buildST(mid + 1, right, (2 * index) + 1);
		segTree[index] = max(segTree[2 * index], segTree[(2 * index) + 1]);
	}
}

void updateST(int left, int right, int index, int upindex, int upvalue){
	if(left == right){
		segTree[index] = upvalue;
	}
	else{
		int mid = (left + right) / 2;
		if(upindex >= left && upindex <= mid){
			updateST(left, mid, 2 * index, upindex, upvalue);
		}
		else{
			updateST(mid + 1, right, (2 * index) + 1, upindex, upvalue);
		}
		segTree[index] = max(segTree[2 * index], segTree[(2 * index) + 1]);
	}
}

int queryST(int qleft, int qright, int left, int right, int index){
	if(qleft > right || qright < left || qright < qleft){
		return INT_MIN;
	}
	else if(qleft <= left && qright >= right){
		return segTree[index];
	}
	else{
		int mid = (left + right) / 2;
		int p = queryST(qleft, qright, left, mid, 2 * index);
		int q = queryST(qleft, qright, mid + 1, right, (2 * index) + 1);
		return max(p, q);
	}
}

