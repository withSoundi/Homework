#include <bits/stdc++.h>
using namespace std;
const int maxn = 100;
double mass[maxn][maxn] = {
    {0.4, 0.2},
    {0.3, 0.2},
    {0.1, 0.05},
    {0.1, 0.5},
    {0.1, 0.05}
};
int r[maxn] = {1, 2, 4, 3, 11};
double ans[maxn], tmp[maxn];
int main() {
    // memset(mass, 0, sizeof mass);
    cout << "原证据表: " << endl;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 2; j++) {
            cout << fixed << setprecision(2) << mass[i][j] << "\t";
        }
        cout << endl;
    }
    double k = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 5; j++) {
            if(!(r[i] & r[j])) k += mass[i][0] * mass[j][1];
        }
    }
    k = 1 - k;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 5; j++) {
            if(r[i] & r[j]) mass[i][2] += mass[i][0] * mass[j][1];
        }
    }
    for(int i = 0; i < 3; i++) {
        for(int j = 3; j < 5; j++) {
            mass[i][2] += mass[i][1] * mass[j][0];
        }
    }
    mass[3][2] = 0;
    for(int i = 2; i < 5; i++) {
        mass[3][2] += mass[i][1];
    }
    mass[3][2] *= mass[2][0];
    mass[4][2] = mass[4][0] * mass[4][1];
    cout << "归一化常数K = " << fixed << setprecision(3) << k << endl;
    cout << "组合结果: " << endl;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 3; j++) {
            cout << fixed << setprecision(3) << mass[i][j] / k << "\t";
        }
        cout << endl;
    }
    return 0;
}