#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

#include <time.h>
#include <cstdlib>

using namespace std;
const double eps = 1e-10;
/*
种群规模(P,population size)：即种群中染色体个体的数目。
字串长度(l, string length)
交叉概率(pc, probability of performing crossover)：控制着交叉算子的使用频率。交叉操作可以加快收敛，
使解达到最有希望的最优解区域，因此一般取较大的交叉概率，但交叉概率太高也可能导致过早收敛。
变异概率(pm, probability of mutation)：控制着变异算子的使用频率，决定了遗传算法的局部搜索能力。
中止条件(termination criteria)
*/
const int PS = 150;
const int GS = 140;
const double PC = 0.75;
const double PM = 0.09;
const int DEEP = 1000;
const double P_PS = 1.0 / PS;
const int DS = 10;
const int CMaxLen = 20;
const int MMaxLen = 10;
const int SucessValue = 440;

bool findAns;
int ansId, ansLen;

struct node {
    int tab[3][3];///table
    int r, c;///0的位置
    int h;
}st, ed;
int ed_map[10][2];
int dir_i[4] = {0, 0, 1, -1};
int dir_j[4] = {1, -1, 0, 0};
///00 01 10 11
char print_op[4] = {'r', 'l', 'd', 'u'};

struct Chromsome{
    string gene;
    double fitness;
    double p;
    bool operator<(const Chromsome &x) const {
        return fitness > x.fitness;
    }
};
vector<Chromsome>population[2];
double psum[2];
int now, nxt;
int nextn;

inline int randomIdx(int x){ return rand()%x; }
inline double ran(){ return (double)rand()/RAND_MAX; }
inline int check(int i, int j) {
    if (i > 2 || i < 0 || j > 2 || j < 0) return 0;
    return 1;
}

int get_h(node a)
{
    int h = 0;
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)
        if (a.tab[i][j] && a.tab[i][j] == ed.tab[i][j]) h += 100 - a.tab[i][j] * 10;
    return h;
}

int getFitnessValue(int id, node a)
{
    int ret = 0;
    int nextr, nextc;
    string s = population[now][id].gene;
    for (int i = 0; i < GS; i += 2)
    {
        int x = (s[i] + s[i]) + s[i + 1];
        nextr = a.r + dir_i[x]; nextc = a.c + dir_j[x];
        if (check(nextr, nextc))
        {
            swap(a.tab[nextr][nextc], a.tab[a.r][a.c]);
            swap(nextr, a.r); swap(nextc, a.c);
            ret = max(ret, get_h(a));
            if (ret == SucessValue)
            {
                findAns = true;
                ansId = id;
                ansLen = i + 2;
                return ret;
            }
        }
    }
    return ret;
}

void calc()
{
    psum[now] = 0;
    for (int i = 0; i < PS; i++)
    {
        population[now][i].fitness = getFitnessValue(i, st);
        if (findAns) return ;
        psum[now] += population[now][i].fitness;
    }
    sort(population[now].begin(), population[now].end());
   for (int i = 0; i < PS; i++)
        population[now][i].p = (1.* population[now][i].fitness) / psum[now];
}

void init() {
    srand((unsigned long)time(0));
//    srand(1);
    population[0].clear(); population[1].clear();
    now = 0; nxt = now ^ 1;
    for (int i = 0; i < PS; i++)
    {
        Chromsome ss;
        population[now].push_back(ss);///
        population[nxt].push_back(ss);
        for (int j = 0; j < GS; j++)
        {
            population[now][i].gene += randomIdx(2);
//            cout << char('0' + population[now][i].gene[j]);
//            if ( (j + 1) % 2 == 0) cout << ' ';
        }
//        cout << endl;

    }
}


int Selection()
{
    double nn = 0;
    double mm = ran();
    for (int i = 0; i < PS; i++)
    {
        nn += population[now][i].p;
        if (nn >= mm)
        {
            if (population[now][i].p < P_PS) population[now][i].p = 0;
            else population[now][i].p -= P_PS;
            return i;
        }
    }
    return PS - 1;
}
void crossover(int x, int y)
{
    int low = randomIdx(GS);
//    int iup = randomIdx(GS);
//    if (ilow > iup) swap(ilow, iup);

//    cout << ilow << " Crossover " << iup << endl;
//    for (int i = ilow; i <= iup; i++) cout << char('0' + population[nxt][x].gene[i]) << ' ';
//    cout << endl;
//    for (int i = ilow; i <= iup; i++) cout << char('0' + population[nxt][y].gene[i]) << ' ';
//    cout << endl;

    int len = randomIdx(CMaxLen);
    len = min(len, GS - low - 1);
    for (int i = low; i <= low + len; i++)
        swap(population[nxt][x].gene[i], population[nxt][y].gene[i]);

//    for (int i = ilow; i <= iup; i++) cout << char('0' + population[nxt][x].gene[i]) << ' ';
//    cout << endl;
//    for (int i = ilow; i <= iup; i++) cout << char('0' + population[nxt][y].gene[i]) << ' ';
//    cout << endl;
}
void mutation(int x)
{
    int i = randomIdx(GS);
    int low = x;
    int len = randomIdx(MMaxLen);
    len = min(len, GS - low - 1);
//    cout << x << " mutation " << char('0' + population[nxt][x].gene[i]) << ' ';
    for (int i = x; i < low + len; i++)
    population[nxt][x].gene[i] ^= 1;
//    cout << char('0' + population[nxt][x].gene[i]) << endl;
}

void out(string s, int len)
{
    vector<int>ans;
    ans.clear();
    int nextr, nextc;
    int r = st.r, c = st.c;
    for (int i = 0; i < len; i += 2)
    {
        int x = (s[i] + s[i]) + s[i + 1];

        nextr = r + dir_i[x]; nextc = c + dir_j[x];
        if (check(nextr, nextc))
        {
            swap(nextr, r); swap(nextc, c);
            int vs = ans.size();
            if (vs && ans[vs - 1] != x && ans[vs - 1] / 2 == x / 2)
            {
                ans.pop_back();
                continue;
            }
            ans.push_back(x);
        }
    }
    for (int i = 0; i < ans.size(); i++)
        putchar(print_op[ans[i]]);
    puts("");
}

void out_table(node a);
void GA()
{
    init();
    int x, y;
    int dep = 0;
    findAns = 0, ansId = -1, ansLen = GS;
//    double pmm = 0.08;
//    double pcc = 0.8;
    while (dep != DEEP)
    {
        calc();
        if (findAns) break;
        nextn = 0;
        for (int i = 0; i < DS; i++)
            population[nxt][nextn++] = population[now][i];

        while (nextn < PS)
        {
            Chromsome tmp;
            int fla = 0;

            x = Selection();
            y = Selection();
            while(x == y) y = Selection();

            population[nxt][nextn++] = population[now][x];
            population[nxt][nextn++] = population[now][y];

            double xx = ran();

            if (xx < PC)
            {
                crossover(nextn - 1, nextn - 2);
            }
            xx = ran();
            if (xx < PM)
            {
                for(int i = 0; i <= 2 * dep / 10; i++)
                mutation(nextn - 1);
            }
            xx = ran();
            if (xx < PM)
            {
                for(int i = 0; i <= 2 * dep / 10; i++)
                mutation(nextn - 2);
            }
        }

//        pcc -= 0.0005;
//        pmm += 0.0001;

        nxt = now;
        now ^= 1;
        dep++;
    }
    if (findAns) out(population[now][ansId].gene, ansLen);
    cout  << "deep： " << dep << endl;
}
void solve()
{
    if (get_h(st) == SucessValue) return ;///st == ed;
    else GA();
}

void out_table(node a) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
        cout << a.tab[i][j] << ' ';
        cout <<endl;
    }
    cout <<endl;
}
void input(node &st) {
    char ch;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            scanf(" %c", &ch);
            if (ch <= '9' && ch >= '0') st.tab[i][j] = ch - '0';
            else { st.r = i; st.c = j; st.tab[i][j] = 0; }
        }
}
void In(char s[], node &st)
{
    char ch;
    int nxt = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            while (s[nxt] == ' ') nxt++;
            ch = s[nxt++];
            if (ch <= '9' && ch >= '0') st.tab[i][j] = ch - '0';
            else { st.r = i; st.c = j; st.tab[i][j] = 0; }
        }
}
void pre()
{
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)
        ed.tab[i][j] = (i * 3) + j + 1;
    ed.tab[2][2] = 0;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        if (ed.tab[i][j]) {
                ed_map[ed.tab[i][j]][0] = i; ed_map[ed.tab[i][j]][1] = j;
        }
}

int get_preval(node a) {
    int ret = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            if (!a.tab[i][j]) continue;
            int x = 0;
            for (int jj = j + 1; jj < 3; jj++)
                    if (a.tab[i][jj] && a.tab[i][jj] < a.tab[i][j]) x++;///
            for (int ii = i + 1; ii < 3; ii++)
                for (int jj = 0; jj < 3; jj++)
                    if (a.tab[ii][jj] && a.tab[ii][jj] < a.tab[i][j]) x++;
            ret += x;
        }
    return ret % 2;
}
bool pre_solve() {
    return (get_preval(st) ^ get_preval(ed));
}

int main()
{
    pre();
    char ss[12];
    while (gets(ss))
    {
        In(ss, st);
//        input(st);
    //    input(ed);
//        out_table(st);
//        out_table(ed);

        if (pre_solve()) puts("unsolvable");
        else solve();
    }
    return 0;
}

/*

x 2 3 1 4 6 7 5 8
1 2 3 x 4 6 7 5 8
1 2 3 4 5 x 7 8 6
1 2 3 4 x 8 7 6 5
x 4 3 2 1 8 7 6 5
2 3 4 1 5 x 7 6 8

1 8 4 3 0 5 7 2 6
7 1 2 8 0 3 6 4 5

4 1 5 8 0 2 7 6 3
4 1 0 3 8 6 7 2 5
4 6 5 7 3 1 0 8 2
7 1 2 6 0 8 4 5 3
7 1 5 6 0 2 3 4 8
3 5 1 8 7 2 4 6 0
6 7 2 5 0 4 8 1 3
*/