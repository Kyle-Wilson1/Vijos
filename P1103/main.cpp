#include <iostream>
#include <fstream>

using namespace std;

struct Region {
    int left, right;
};

Region node[100];

int main() {
    ifstream fin("a.in");
    ofstream fout("a.out");

    int l, m, i = 0;
    fin >> l >> m;

    for (i = 0; i < m; i++) {
        fin >> node[i].left >> node[i].right;
    }

    for (i = 0; i < m; i++) {
        fout << node[i].left << "  " << node[i].right << endl;
    }

    fin.close();
    fout.close();
    return 0;
}