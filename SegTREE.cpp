#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define si(x) scanf("%d", &x)
#define sc(x) scanf("%c", &x)
#define sl(x) scanf("%lld", &x)
#define pl(x) printf("%lld\n", x)
#define pi(x) printf("%d\n", x)
#define setbits __builtin_popcountll
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define speed ios::sync_with_stdio(false)

// SEGMENT TREE - Range Minimum Query, Range Maximum Query and Range Sum Query

struct newtype{
	ll min;
	ll max;
	ll sum;
};
typedef struct newtype node;

ll arr[100005];
node segTree[4 * 100005];

void buildST(int left, int right, int index){
	if(left == right){
		segTree[index].min = arr[left];
		segTree[index].max = arr[left];
		segTree[index].sum = arr[left];
	}
	else{
		int mid = (left + right) / 2;
		buildST(left, mid, 2 * index);
		buildST(mid + 1, right, (2 * index) + 1);
		segTree[index].max = max(segTree[2 * index].max, segTree[(2 * index) + 1].max);
		segTree[index].min = min(segTree[2 * index].min, segTree[(2 * index) + 1].min);
		segTree[index].sum = segTree[2 * index].sum + segTree[(2 * index) + 1].sum;
	}
}

void updateST(int left, int right, int index, int upindex, ll upvalue){
	if(left == right){
		segTree[index].min = upvalue;
		segTree[index].max = upvalue;
		segTree[index].sum = upvalue;
	}
	else{
		int mid = (left + right) / 2;
		if(upindex >= left && upindex <= mid){
			updateST(left, mid, 2 * index, upindex, upvalue);
		}
		else{
			updateST(mid + 1, right, (2 * index) + 1, upindex, upvalue);
		}
		segTree[index].max = max(segTree[2 * index].max, segTree[(2 * index) + 1].max);
		segTree[index].min = min(segTree[2 * index].min, segTree[(2 * index) + 1].min);
		segTree[index].sum = segTree[2 * index].sum + segTree[(2 * index) + 1].sum;
	}
}

ll querymaxST(int qleft, int qright, int left, int right, int index){
	if(qleft > right || qright < left || qright < qleft){
		return INT_MIN;
	}
	else if(qleft <= left && qright >= right){
		return segTree[index].max;
	}
	else{
		int mid = (left + right) / 2;
		ll p = querymaxST(qleft, qright, left, mid, 2 * index);
		ll q = querymaxST(qleft, qright, mid + 1, right, (2 * index) + 1);
		return max(p, q);
	}
}

ll queryminST(int qleft, int qright, int left, int right, int index){
	if(qleft > right || qright < left || qright < qleft){
		return INT_MAX;
	}
	else if(qleft <= left && qright >= right){
		return segTree[index].min;
	}
	else{
		int mid = (left + right) / 2;
		ll p = queryminST(qleft, qright, left, mid, 2 * index);
		ll q = queryminST(qleft, qright, mid + 1, right, (2 * index) + 1);
		return min(p, q);
	}
}

ll querysumST(int qleft, int qright, int left, int right, int index){
	if(qleft > right || qright < left || qright < qleft){
		return 0;
	}
	else if(qleft <= left && qright >= right){
		return segTree[index].sum;
	}
	else{
		int mid = (left + right) / 2;
		ll p = querysumST(qleft, qright, left, mid, 2 * index);
		ll q = querysumST(qleft, qright, mid + 1, right, (2 * index) + 1);
		return p + q;
	}
}

// SEGMENT TREE - LAZY PROPAGATION - NUMBER OF EVEN AND ODD NUMBERS IN A RANGE

struct newtype{
	ll even;
	ll odd;
};
typedef struct newtype node;

ll arr[100005];
node segTree[4 * 100005];
ll lazy[4 * 100005];

void buildST(int left, int right, int index){
	if(left == right){
		if(arr[left % 2] == 0){
			segTree[index].even = 1;
			segTree[index].odd = 0;
		}
		else{
			segTree[index].odd = 1;
			segTree[index].even = 0;
		}
	}
	else{
		ll mid = (left + right) / 2;
		buildST(left, mid, 2 * index);
		buildST(mid + 1, right, (2 * index) + 1);
		segTree[index].even = segTree[2 * index].even + segTree[(2 * index) + 1].even;
		segTree[index].odd = segTree[2 * index].odd + segTree[(2 * index) + 1].odd;
	}
}

void updateST(int left, int right, int index, int a, int b, ll value){
	if(lazy[index] != 0){ // node needs an update
		if(lazy[index] % 2 == 1){
			ll temp = segTree[index].even;
			segTree[index].even = segTree[index].odd;
			segTree[index].odd = temp;
		}
		if(left != right){
			lazy[2 * index] += lazy[index];
			lazy[(2 * index) + 1] += lazy[index];
			lazy[2 * index] %= 2;
			lazy[(2 * index) + 1] %= 2;
		}
		lazy[index] = 0;
	}

	if(left > right || b < left || right < a){
		return;
	}
	if(a <= left && right <= b){
		if(value % 2 == 1){
			ll temp = segTree[index].even;
			segTree[index].even = segTree[index].odd;
			segTree[index].odd = temp;
		}
		if(left != right){
			lazy[2 * index] += value;
			lazy[(2 * index) + 1] += value;
			lazy[2 * index] %= 2;
			lazy[(2 * index) + 1] %= 2;
		}
		return;
	}

	ll mid = (left + right) / 2;
	updateST(left, mid, 2 * index, a, b, value);
	updateST(mid + 1, right, (2 * index) + 1, a, b, value);
	segTree[index].even = segTree[2 * index].even + segTree[(2 * index) + 1].even;
	segTree[index].odd = segTree[2 * index].odd + segTree[(2 * index) + 1].odd;
}

node queryST(int qleft, int qright, int left, int right, int index){
	if(left > right || qright < left || right < qleft){
		node R; R.even = 0; R.odd = 0; return R;
	}
	if(lazy[index] != 0){ // node needs an update
		if(lazy[index] % 2 == 1){
			ll temp = segTree[index].even;
			segTree[index].even = segTree[index].odd;
			segTree[index].odd = temp;
		}
		if(left != right){
			lazy[2 * index] += lazy[index];
			lazy[(2 * index) + 1] += lazy[index];
			lazy[2 * index] %= 2;
			lazy[(2 * index) + 1] %= 2;
		}
		lazy[index] = 0;
	}
	if(qleft <= left && right <= qright){
		return segTree[index];
	}
	ll mid = (left + right) / 2;
	node L = queryST(qleft, qright, left, mid, 2 * index);
	node R = queryST(qleft, qright, mid + 1, right, (2 * index) + 1);
	node A;
	A.even = L.even + R.even;
	A.odd = L.odd + R.odd;
	return A;
}
