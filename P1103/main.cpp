#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Region {
    int left, right;
};

struct SegmentTree {
    int left, right, count;
    bool remove;
};

void buidTree(vector<SegmentTree> &sgTree, int root, int l, int r) {
    if (l > r) {
        return;
    }
    if (l == r) {
        sgTree[root].remove = false;
        sgTree[root].left = l;
        sgTree[root].right = r;
        sgTree[root].count = 1;
        return;
    }
    sgTree[root].remove = false;
    sgTree[root].left = l;
    sgTree[root].right = r;
    sgTree[root].count = r - l + 1;
    int mid = (l + r) >> 1;
    buidTree(sgTree, root * 2 + 1, l, mid);
    buidTree(sgTree, root * 2 + 2, mid + 1, r);
}

void upDate(vector<SegmentTree> &sgTree, int root, int regionLeft, int regionRight, int l, int r) {

    if (l >= regionLeft && r <= regionRight) {
        sgTree[root].count = 0;
        sgTree[root].remove = true;
        return;
    }
    if (r < regionLeft || l > regionRight || sgTree[root].remove) {
        return;
    }

    int mid = (l + r) >> 1;
    upDate(sgTree, root * 2 + 1, regionLeft, regionRight, l, mid);
    upDate(sgTree, root * 2 + 2, regionLeft, regionRight, mid + 1, r);
    if (sgTree[root * 2 + 1].remove && sgTree[root * 2 + 2].remove) {
        sgTree[root].remove = true;
    }
}

void queryTree(vector<SegmentTree> sgTree, int root, int l, int r, int &removeTree) {
    if (sgTree[root].remove) {
        //removeTree += sgTree[root].count;
        return;
    }
    if (l > r) {
//        if (sgTree[root].remove) {
//            removeTree += sgTree[root].count;
//        }
        return;
    }
    if (l == r) {
        removeTree++;
        return;
    }

    int mid = (l + r) >> 1;
    queryTree(sgTree, root * 2 + 1, l, mid, removeTree);
    queryTree(sgTree, root * 2 + 2, mid + 1, r, removeTree);
}

int main() {
    ifstream cin("a.in");
    ofstream cout("a.out");

    int l, m, i = 0, regionLeft, regionRight, removeTree = 0;
    cin >> l >> m;
    //vector<SegmentTree> sgTree(static_cast<unsigned long>(2 * l - 1), SegmentTree{0, 0, 0});
    vector<SegmentTree> sgTree(200000, SegmentTree{0, 0, 0});
    //build segment tree
    buidTree(sgTree, 0, 0, l);

    for (i = 0; i < m; i++) {
        //cin >> node[i].left >> node[i].right;
        cin >> regionLeft >> regionRight;
        upDate(sgTree, 0, regionLeft, regionRight, 0, l);
    }

//    i = 0;
//    for (SegmentTree sg:sgTree) {
//        cout << "key=" << i++ << "left=" << sg.left << "right=" << sg.right << "count=" << sg.count << "remove="
//             << sg.remove << endl;
//    }
    queryTree(sgTree, 0, 0, l, removeTree);
//
    cout << removeTree;
    cin.close();
    cout.close();
    return 0;
}