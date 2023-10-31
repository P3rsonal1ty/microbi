#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int stop = 0;
int intreload(char s) {
    if (s == 'X') return 1;
    else return 0;
}
void  smic(int x, int y, int f[21][21], int m[21][21]) {
    int count = 0;
    if (x != 0) { if (m[x - 1][y] > 0) { count++; } }
    if (x != 20) { if (m[x + 1][y] > 0) { count++; } }
    if (y != 0) { if (m[x][y - 1] > 0) { count++; } }
    if (y != 20) { if (m[x][y + 1] > 0) { count++; } }
    if (y != 20 && x != 20) { if (m[x + 1][y + 1] > 0) { count++; } }
    if (y != 20 && x != 0) { if (m[x - 1][y + 1] > 0) { count++; } }
    if (y != 0 && x != 20) { if (m[x + 1][y - 1] > 0) { count++; } }
    if (y != 0 && x != 0) { if (m[x - 1][y - 1] > 0) { count++; } }
    if ((count == 2 || count == 3) && m[x][y] != 0) {
        f[x][y] = m[x][y] + 1;
        stop = 1;
    }
    else if (m[x][y] == 0) {
        f[x][y] = 1;
        stop = 1;
    }
    else {
        f[x][y] = 0;
    }
}
int prov(int m[21][21]) {
    int count = 0;
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            if (m[i][j] == 13) { m[i][j] = 0; }
            if (m[i][j] > 0) { count++; }
        }
    }
    return count;
}
int main()
{
    int pres[21][21];
    int bud[21][21];
    char elem;
    string s1;
    ifstream dat("dat.txt");
    for (int i = 0; i < 21; i++) {
        dat >> s1;
        for (int j = 0; j < 21; j++) {
            pres[i][j] = intreload(s1[j]);
        }
    }
    dat.close();
    int l = 0;
    ofstream out("out.txt");
    int N = 1; cout << "Press pokol: "; cin >> N;
    for (int b = 0; b < N; b++) {
        for (int i = 0; i < 21; i++) {
            for (int j = 0; j < 21; j++) {
                if (pres[i][j] != -1) {
                    smic(i, j, bud,pres);
                }
                else {
                    bud[i][j] = -1;
                }
            }
        }
        for (int u = 0; u < 21; u++) {
            for (int h = 0; h < 21; h++) {
                pres[h][u] = bud[h][u];
            }
        }
        if (stop== 0) { cout << "all dead"; exit; }
        stop= 0;
        l = prov(pres);
        cout << "Live: " << l << endl;
        for (int i = 0; i < 21; i++) {
            for (int j = 0; j < 21; j++) {
                out << pres[i][j];  
                if (pres[i][j] == -1 || pres[i][j] >= 9) { out << " "; }
                else { out << "  "; }
            }
            out << "\n";
        }
        out << "\n";
    }
    out.close();
}
