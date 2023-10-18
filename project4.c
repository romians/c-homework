#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef struct tree {
    int data; // 노드의 값 변수
    struct tree* left, * right; // 노드의 왼쪽, 오른쪽 노드 가리킴
    int is_thread; // 만약 오른쪽 링크가 스레드이면 True
} treenode;

// 노드 초기화
// 왼쪽
treenode n1 = { 4, NULL, NULL, 1 };
treenode n2 = { 5, NULL, NULL, 1 };
treenode n3 = { 3, &n1, &n2, 0 };
treenode n4 = { 6, NULL, NULL, 1 };
treenode n5 = { 2, &n3, &n4, 0 };

// 오른쪽
treenode n6 = { 10, NULL, NULL, 1 };
treenode n7 = { 11, NULL, NULL, 0 };
treenode n8 = { 9, &n6, &n7, 0 };
treenode n9 = { 8, NULL, NULL, 1 };
treenode n10 = { 7, &n9, &n8, 0 };

// 중앙
treenode n11 = { 1, &n5, &n10, 0 };
treenode* root = &n11;

// 트리에서 중위 후속자(노드)를 반환하는 함수
treenode* find_successor(treenode* root) {
    treenode* q = root->right;
    if (q == NULL || root->is_thread == true)
        return q;
    while (q->left != NULL)
        q = q->left;
    return q;
}

// 스레드 중위 순회 함수
void thread_inorder(treenode* root) {
    treenode* q = root; // 복사본 만들기
    while (q->left != NULL)
        q = q->left;
    do {
        printf("%d ", q->data);
        q = find_successor(q);
    } while (q);
}

treenode* parent_helper(treenode* root, treenode* child) {
    if (root == NULL) //root 노드가 NULL일 경우 NULL을 반환함
        return NULL;
    if (root->left == child || root->right == child) //child가 root의 오른쪽, 왼쪽 자식 노드인지 확인 후 root 노드 반환
        return root;
    treenode* left_parent = parent_helper(root->left, child); //root의 왼쪽 노드에 child 노드의 부모 노드가 있는지 확인
    if (left_parent != NULL) //만일 left_parent 가 null이 아니면 left_parent 노드를 반환
        return left_parent;

    return parent_helper(root->right, child); //아닐 경우에는 root의 오른쪽 노드에 child 노드의 부모 노드가 있는지 확인
}

treenode* parent(treenode* child) {
    treenode* parent = parent_helper(root, child); //child 노드의 부모 노드 검색
    return printf("노드 %d의 부모 노드 : %d", child->data, parent->data); //검색 후 찾은 부모노드의 저장된 값을 출력하게 함.
}

int main() {

    n1.right = &n3; //node 4 스레드 설정
    n2.right = &n5; //node 5 스레드 설정
    n4.right = &n11;//node 6 스레드 설정
    n9.right = &n10;//node 8 스레드 설정
    n6.right = &n8; //node 10 스레드 설정

    printf("1. 중위 순회 결과\n");
    thread_inorder(root);
    printf("\n");

    //노드 4의 부모 노드 출력
    treenode* child = &n1; // node 4
    printf("\n2. ");
    treenode* parent_node = parent(child);

    //노드 5의 부모 노드 출력
    child = &n2; // node 5
    printf("\n3. ");
    parent_node = parent(child);

    //노드 6의 부모 노드 출력
    child = &n4; // node 6
    printf("\n4. ");
    parent_node = parent(child);
     
    return 0;
}