#include <iostream>
#include <fstream>

using namespace std;

struct SegmentTree {
    int left, right, count;
    SegmentTree *lson, *rson;
};

SegmentTree *buildTree(int l, int r) {
    if (l > r) {
        return nullptr;
    }
    if (l == r) {
        auto *root = new SegmentTree{l, r, 1, nullptr, nullptr};
        return root;
    }
    auto *root = new SegmentTree{l, r, r - l + 1, nullptr, nullptr};
    int mid = (l + r) >> 1;
    root->lson = buildTree(l, mid);
    root->rson = buildTree(mid + 1, r);
    return root;
}

void removeRegion(SegmentTree *root, int regionLeft, int regionRight) {
    if (root->left >= regionLeft && root->right <= regionRight) {
        root->count = 0;
        return;
    }
    if (root->right < regionLeft || root->left > regionRight) {
        return;
    }
    removeRegion(root->lson, regionLeft, regionRight);
    removeRegion(root->rson, regionLeft, regionRight);
    root->count = min(root->count, root->lson->count + root->rson->count);
}

void printTree(ofstream &fout, SegmentTree *root) {
    if (root == nullptr)return;
    fout << "left=" << root->left << "right=" << root->right << "count=" << root->count << endl;
    printTree(fout, root->lson);
    printTree(fout, root->rson);
}

void deleteMem(SegmentTree *root) {
    if (root == nullptr)
        return;
    deleteMem(root->lson);
    deleteMem(root->rson);
    delete root;
};

int main() {

    ifstream fin("a.in");
    ofstream fout("a.out");

    int l, m, i = 0, regionLeft, regionRight;
    fin >> l >> m;
    SegmentTree *root;
    //build segment tree
    root = buildTree(0, l);

    //printTree(fout, root);
    for (i = 0; i < m; i++) {
        fin >> regionLeft >> regionRight;
        removeRegion(root, regionLeft, regionRight);
    }

    fout << root->count;
    deleteMem(root);
    fin.close();
    fout.close();
    return 0;
}