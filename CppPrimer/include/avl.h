#ifndef AVL_H
#define AVL_H
#include <iostream>
using namespace std;
/* 二叉平衡排序树的实现 */
template <class DataType>
class TreeNode {
public:
    DataType data;
    TreeNode *left,*right;
    int height;
    TreeNode(DataType d) : data(d),left(nullptr),right(nullptr),height(1) {}
};

template <class DataType>
class AVL {
    typedef TreeNode<DataType>  _TreeNode ;
private:
    /* 递归的辅助插入函数 */
    _TreeNode* _insert(DataType& elem,_TreeNode* root);
    /* 获取节点的高度（根据子节点高度）*/
    void height(_TreeNode* root) {
        int lefth = root->left ? root->left->height : 0;
        int righth = root->right ? root->right->height : 0;
        root->height = max(lefth,righth)+1;
    }
    /* 比较左右孩子的高度差，以决定进行何种旋转操作 */
    int diffh(_TreeNode* left,_TreeNode* right) {
        int lefth = left ? left->height : 0;
        int righth = right ? right->height : 0;
        return lefth-righth;
    }
    /*
     *      A             B
     *     /             / \
     *    B     ==>     C  A
     *   /
     *  C
    */
    _TreeNode* LL(_TreeNode* A) {
        _TreeNode* B = A->left;
        A->left = B->right;
        B->right = A;
        height(A);
        height(B);
        return B;
    }
    /*
     *   A              B
     *    \            / \
     *     B     ==>  A   C
     *      \
     *       C
    */
    _TreeNode* RR(_TreeNode* A) {
        _TreeNode* B = A->right;
        A->right = B->left;
        B->left = A;
        height(A);
        height(B);
        return B;
    }
    /*
     *     A             A            C
     *    /             /            / \
     *   B      ==>    C     ==>    B  A
     *    \           /
     *     C         B
    */
    _TreeNode* LR(_TreeNode* A) {
        A->left = RR(A->left);
        return LL(A);
    }
    /*
     *   A             A            C
     *    \           /            / \
     *     B   ==>   C   ==>      B  A
     *    /         /
     *   C         B
    */
    _TreeNode* RL(_TreeNode* A) {
        A->right = LL(A->right);
        return LL(A);
    }
public:
    _TreeNode *root;

    AVL() : root(nullptr) {}
    ~AVL() {}

    void insert(DataType elem);
};

template <class DataType>
TreeNode<DataType>* AVL<DataType>::_insert(DataType& elem,TreeNode<DataType>* r) {
    if(!r) {
        return new TreeNode<DataType>(elem);
    }
    if(elem < r->data) {
        r->left = _insert(elem,r->left);
    } else if(elem > r->data) {
        r->right = _insert(elem,r->right);
    } else {
        return r;
    }

    /* 旋转操作 */
    int fh = diffh(r->left,r->right);
    if(fh == 2) {
        if(r->left->left)
            r = LL(r);
        else
            r = LR(r);
    } else if(fh == -2) {
        if(r->right->right)
            r = RR(r);
        else
            r = RL(r);
    }
    height(r);
    return r;
}

template <class DataType>
void AVL<DataType>::insert(DataType elem) {
    root = _insert(elem,root);
}
#endif // AVL_H
