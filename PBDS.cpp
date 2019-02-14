#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
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

using namespace __gnu_pbds;

typedef tree<
pair<int, int>,
null_type,
less< pair<int, int> >,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int main(){
	ordered_set X;
    X.insert(mp(1, 1));
    X.insert(mp(2, 2));
    X.insert(mp(4, 3));
    X.insert(mp(4, 4));
    X.insert(mp(8, 5));
    X.insert(mp(16, 6));

    pair<int, int> p;
    p = *X.find_by_order(5);
    cout<<p.first<<" "<<p.second<<endl; // 2
    //cout<<*X.find_by_order(2)<<endl; // 4
    //cout<<*X.find_by_order(4)<<endl; // 16
    //cout<<(end(X)==X.find_by_order(6))<<endl; // true

    cout<<X.order_of_key({2, INT_MAX})<<endl;  // 0
    //cout<<X.order_of_key(1)<<endl;   // 0
    //cout<<X.order_of_key(3)<<endl;   // 2
    //cout<<X.order_of_key(4)<<endl;   // 2
    //cout<<X.order_of_key(400)<<endl; // 6

    for(auto it = begin(X); it != end(X); it++){
        pair <int, int> P = *it;
        cout<<P.first<<" "<<P.second<<endl;
    }

}