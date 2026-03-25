#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int data;
    struct tnode* left;
    struct tnode* right;
};

// (a) Cấp phát node mới
struct tnode* talloc(int data) {
    struct tnode* p = (struct tnode*)malloc(sizeof(struct tnode));
    if (p != NULL) {
        p->data = data;
        p->left = NULL;
        p->right = NULL;
    }
    return p;
}

// (b) Thêm node vào cây nhị phân tìm kiếm
struct tnode* addnode(struct tnode* root, int data) {
    // termination condition
    if (root == NULL) {
        // allocate node
        struct tnode* newnode = talloc(data);
        // return new root
        return newnode;
    }
    // recursive call
    else if (data < root->data)
        root->left = addnode(root->left, data);
    else
        root->right = addnode(root->right, data);
    return root;
}

// (c) Duyệt tiền thứ tự (pre-order)
void preorder(struct tnode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

// (d) Duyệt trung thứ tự (in-order) – kết quả được sắp xếp
void inorder(struct tnode* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// (e) Xóa toàn bộ cây, trả về số node đã xóa (dùng hậu thứ tự)
int deltree(struct tnode* root) {
    if (root == NULL) return 0;
    int leftCount = deltree(root->left);
    int rightCount = deltree(root->right);
    free(root);
    return 1 + leftCount + rightCount;
}

// (f) Test code
int main() {
    struct tnode* root = NULL;
    int arr[] = {3, 1, 0, 2, 8, 6, 5, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Thêm các phần tử theo thứ tự
    for (int i = 0; i < n; i++) {
        root = addnode(root, arr[i]);
    }

    printf("Duyệt pre-order: ");
    preorder(root);
    printf("\n");

    printf("Duyệt in-order (sắp xếp): ");
    inorder(root);
    printf("\n");

    int deleted = deltree(root);
    printf("Số node đã xóa: %d\n", deleted);
    root = NULL; // tránh con trỏ treo

    return 0;
}
