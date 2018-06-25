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

#define ROWS 3
#define COLS 3

ll matrix[ROWS][COLS] = {{1, 1, 1}, {0, 1, 1}, {0, 1, 0}};
ll matrix_copy[ROWS][COLS] = {{1, 1, 1}, {0, 1, 1}, {0, 1, 0}};
ll answer[ROWS][COLS];

// Matrix Multiplication - Multiplies A[][] and B[][] - Stores in C[][]

void matmul(ll A[ROWS][COLS], ll B[ROWS][COLS], ll C[ROWS][COLS]){
	ll mat1[ROWS][COLS], mat2[ROWS][COLS], mat3[ROWS][COLS];
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++){
			mat1[i][j] = A[i][j];
			mat2[i][j] = B[i][j];
		}
	}
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++){
			ll sum = 0;
			for(int k = 0; k < ROWS; k++){
				sum = (sum + ((mat1[i][k] * mat2[k][j]) % MOD)) % MOD;
			}
			mat3[i][j] = sum % MOD;
		}
	}
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++){
			C[i][j] = mat3[i][j];
		}
	}
}

ll bin(ll b){

	// SETUP AN IDENTITY MATRIX

	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++){
			if(i == j){
				answer[i][j] = 1;
			}
			else{
				answer[i][j] = 0;
			}
			matrix[i][j] = matrix_copy[i][j];	
		}
	}

	// MATRIX EXPONENTIATION

	while(b > 0){
		if(b % 2 == 1){
			matmul(answer, matrix, answer);
		}
		matmul(matrix, matrix, matrix);
		b /= 2;
	}
}

int main(){

}