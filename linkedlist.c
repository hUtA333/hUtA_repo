#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

// (a) Hiển thị toàn bộ danh sách
void display(struct node* head) {
    struct node* p = head;
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

// (b) Thêm phần tử vào cuối danh sách
struct node* addback(struct node* head, int data) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode == NULL) return head;
    newnode->data = data;
    newnode->next = NULL;

    if (head == NULL) {
        return newnode;
    }

    struct node* p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newnode;
    return head;
}

// (c) Tìm node chứa giá trị data
struct node* find(struct node* head, int data) {
    struct node* p = head;
    while (p != NULL) {
        if (p->data == data)
            return p;
        p = p->next;
    }
    return NULL;
}

// (d) Xóa node được trỏ bởi element
struct node* delnode(struct node* head, struct node* element) {
    if (head == NULL || element == NULL) return head;

    // Nếu element là head
    if (head == element) {
        struct node* newhead = head->next;
        free(head);
        return newhead;
    }

    // Duyệt tìm node trước element
    struct node* p = head;
    while (p->next != NULL && p->next != element) {
        p = p->next;
    }

    if (p->next == element) {
        p->next = element->next;
        free(element);
    }
    return head;
}

// (e) Giải phóng toàn bộ danh sách
void freelist(struct node* head) {
    struct node* p = head;
    while (p != NULL) {
        struct node* temp = p;
        p = p->next;
        free(temp);
    }
}

// (f) Test code
int main() {
    struct node* head = NULL;

    // Thêm các phần tử
    head = addback(head, 10);
    head = addback(head, 20);
    head = addback(head, 30);
    head = addback(head, 40);

    printf("Danh sách sau khi thêm: ");
    display(head);

    // Tìm phần tử
    struct node* found = find(head, 20);
    if (found != NULL)
        printf("Tìm thấy phần tử có giá trị 20\n");
    else
        printf("Không tìm thấy 20\n");

    found = find(head, 99);
    if (found != NULL)
        printf("Tìm thấy 99\n");
    else
        printf("Không tìm thấy 99\n");

    // Xóa phần tử đầu (10)
    struct node* toDelete = find(head, 10);
    head = delnode(head, toDelete);
    printf("Sau khi xóa 10: ");
    display(head);

    // Xóa phần tử giữa (30)
    toDelete = find(head, 30);
    head = delnode(head, toDelete);
    printf("Sau khi xóa 30: ");
    display(head);

    // Giải phóng bộ nhớ
    freelist(head);
    head = NULL;
    printf("Đã giải phóng danh sách.\n");

    return 0;
}
