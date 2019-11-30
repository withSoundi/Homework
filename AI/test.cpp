#include <bits/stdc++.h>
#define REP(i,x,n) for(int i = (x); i < (n); ++i)
#define PER(i,x,n) for(int i = (n) - 1; i >= (x); --i)
#define inf 0x3f3f3f
#define eps 1e-5
#define PI acos(-1.0)
#define mem(a, b) memset(a, b, sizeof a)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const ll mod = 1e9 + 7;
const int maxn = 100000 + 10;
const int PACK_MAX_W = 80;      //背包最大承受重量
const int PACK_MAX_V = 75;      //背包最大承受容积
const int NUM = 32;             //物品数
const int MAX_GENERATION = 100; //遗传最大代数
const int PS = 500;             //种群规模
const float PC = 0.8;           //交叉率
const float PV = 0.1;           //变异率
const int weight[NUM]={22,15,4,5,10,19,21,20,8,13,2,3,3,17,12,5,12,4,1,21,14,23,17,15,20,22,25,0,22,15,25,13};//重量
const int c[NUM]={11,22,12,21,21,13,1,10,13,8,6,25,13,27,12,23,12,24,23,11,6,24,28,10,20,13,25,23,5,26,30,15};//体积
const int value[NUM]={8,9,15,6,16,9,1,4,14,9,3,7,12,4,15,5,18,5,15,4,6,2,12,14,11,9,13,13,14,13,19,4};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << "重量: ";
    for(int i = 0; i < NUM; i++) {
        if(i == 17) cout << endl << "      ";
        cout << weight[i] << ' ';
    }
    cout << endl;
    cout << "体积: ";
    for(int i = 0; i < NUM; i++) {
        if(i == 17) cout << endl << "      ";
        cout << c[i] << ' ';
    }
    cout << endl;
    cout << "价值: ";
    for(int i = 0; i < NUM; i++) {
        if(i == 17) cout << endl << "      ";
        cout << value[i] << ' ';
    }
    cout << endl;
    return 0;
}