#include <stdio.h>
#include <stdlib.h>

//트리 노드 구조체
typedef struct treenode {
	int data; // 노드의 값 변수
	struct treenode* left, * right; // 노드의 왼쪽, 오른쪽 노드 가리킴
}treenode;

//노드 추가 함수 
treenode* createnode(int data) {
	treenode* newnode = (treenode*)malloc(sizeof(treenode));
	newnode->data = data;
	newnode->left = newnode->right = NULL;

	return newnode;
}

//노드 중위 순회 함수(재귀)
void inorder(treenode* root, int* node_count) {
	if (root == NULL) return;
	inorder(root->left,node_count);
	(*node_count)++;
	printf("%d ", root->data);
	inorder(root->right, node_count);
}

// 트리에서 가장 작은 값을 찾는 함수(최소값 노드 반환)
treenode* minValueNode(treenode* node) {
	treenode* current = node;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

//노드 삭제 함수(재귀)
treenode* delete_recursive(treenode* root, int data, int* node_count) {
	if (root == NULL) {
		return root;
	}

	// 삭제할 노드 찾기
	(*node_count)++;
	if (data < root->data) {
		root->left = delete_recursive(root->left, data, node_count);
	}
	else if (data > root->data) {
		root->right = delete_recursive(root->right, data, node_count);
	}
	else {
		if (root->left == NULL) {
			treenode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			treenode* temp = root->left;
			free(root);
			return temp;
		}

		// 두 개의 자식 노드가 있는 경우
		treenode* temp = minValueNode(root->right);
		root->data = temp->data;
		root->right = delete_recursive(root->right, temp->data, node_count);
	}

	return root;
}

//노드 삭제 함수(반복)
treenode* delete_iterative(treenode* root, int data, int* node_count) {
	treenode* current = root;
	treenode* parent = NULL;
	treenode* parent_stack[100]; // 부모 노드를 저장하는 스택 (충분한 크기로 조절)

	// 노드를 찾아가며 스택에 부모 노드 저장
	while (current != NULL && current->data != data) {
		parent = current;
		parent_stack[*node_count] = parent;
		(*node_count)++;

		if (data < current->data) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	if (current == NULL) {
		// 삭제할 노드가 존재하지 않음
		return root;
	}

	// 삭제할 노드를 찾았을 경우
	if (current->left == NULL) {
		// 왼쪽 자식이 없는 경우
		if (parent == NULL) {
			// 루트 노드를 삭제하는 경우
			treenode* temp = current->right;
			free(current);
			return temp;
		}
		if (parent->left == current) {
			parent->left = current->right;
		}
		else {
			parent->right = current->right;
		}
		free(current);
	}
	else if (current->right == NULL) {
		// 오른쪽 자식이 없는 경우
		if (parent == NULL) {
			// 루트 노드를 삭제하는 경우
			treenode* temp = current->left;
			free(current);
			return temp;
		}
		if (parent->left == current) {
			parent->left = current->left;
		}
		else {
			parent->right = current->left;
		}
		free(current);
	}
	else {
		// 두 개의 자식 노드가 있는 경우
		treenode* temp = minValueNode(current->right); // 오른쪽 서브트리에서 가장 작은 값을 찾음
		current->data = temp->data; // 삭제할 노드의 값을 가장 작은 값으로 대체

		// 대체된 값을 가진 노드를 삭제 (재귀적으로 삭제 함수 호출)
		current->right = delete_recursive(current->right, temp->data, node_count);
	}

	return root;
}

//노드 삽입 함수(반복)
treenode* insert_iterative(treenode* root, int data, int* node_count) {
	treenode* newnode = createnode(data);
	if (root == NULL) {
		(*node_count)++;
		return newnode;
	}

	treenode* current = root;
	treenode* parent = NULL;

	while (current != NULL) {
		parent = current;
		if (data < current->data) {
			(*node_count)++;
			current = current->left;
		}
		else if (data > current->data) {
			(*node_count)++;
			current = current->right;
		}
		else {
			// 중복된 값은 여기에서 처리할 수 있습니다.
			free(newnode); // 중복 값은 무시하고 메모리 해제
			return root; // 기존 루트를 반환
		}
	}

	if (data < parent->data) {
		parent->left = newnode;
	}
	else {
		parent->right = newnode;
	}

	return root;
}

// 노드 삽입 함수(재귀)
treenode* insert(treenode* root, int data, int* node_count) {

	if (root == NULL) {
		(*node_count)++;
		return createnode(data);
	}
	if (data < root->data) {
		(*node_count)++;
		root->left = insert(root->left, data, node_count);
	}
	else if (data > root->data) {
		(*node_count)++;
		root->right = insert(root->right, data, node_count);
	}
	return root;
}

//노드 검색 함수(반복)
void search(treenode* root, int data) {
	int node_count = 0; //방문한 노드의 수 변수

	while (root != NULL)
	{
		if (data == root->data) { //root의 값과 찾고자 하는 노드의 값이 일치할 경우  검색 성공 + 방문 노드의 수 출력
			node_count += 1;
			printf("검색 성공 : %d\n", root->data);
			printf("방문한 노드의 수 : %d\n", node_count);
			return root;
		}
		//data의 값이 현재 노드 값보다 작으면 왼쪽 서브 트리로 이동
		else if (data < root->data) {
			node_count += 1;
			root = root->left;
		}
		//data의 값이 현재 노드 값보다 크면 오른쪽 서브 트리로 이동
		else {
			node_count += 1;
			root = root->right;
		}
	}

	return NULL;
}

//노드 중위 순회 함수(재귀)
void inorderwithcount(treenode* root) {
	int node_count = 0;
	inorder(root, &node_count);
	printf("\n방문한 노드의 수 : %d\n", node_count);
}

//노드 삭제 함수(검색용)
treenode* node_delete(treenode* root, char choice) {
	int data, node_count=0;
	printf("삭제할 값 입력 : ");
	scanf("%d", &data);
	while (getchar() != '\n'); // 엔터 키('\n')를 읽어서 버퍼를 비웁니다.
	if (choice == 'd')
		root = delete_recursive(root, data, &node_count);
	else if (choice == 'D')
		root = delete_iterative(root, data, &node_count);

	printf("방문한 노드 수 : %d\n", node_count);
	inorder(root,&node_count); // 노드 삭제 후 중위 순회를 다시 수행하여 트리 상태를 출력
	return root; // 수정된 루트 노드를 반환합니다.
}

// 노드 삽입 함수(검색용)
treenode* node_insert(treenode* root, char choice) {
	int data, node_count = 1;
	printf("삽입할 값 입력 : ");
	scanf("%d", &data);
	while (getchar() != '\n'); // 엔터 키('\n')를 읽어서 버퍼를 비웁니다.
	if (choice == 'i')
		root = insert(root, data, &node_count);
	else if (choice == 'I')
		root = insert_iterative(root, data, &node_count);

	printf("방문한 노드 수 : %d\n", node_count);
	inorder(root, &node_count); // 노드 삭제 후 중위 순회를 다시 수행하여 트리 상태를 출력
	return root; // 수정된 루트 노드를 반환합니다.
}

//노드 검색 함수(검색용)
void node_search(treenode* root) {
	int find_num, node_count = 0;
	printf("검색할 값 입력 : ");
	scanf("%d", &find_num);
	while (getchar() != '\n'); // 엔터 키('\n')를 읽어서 버퍼를 비웁니다.
	search(root, find_num);
	inorder(root, &node_count); // 노드 삭제 후 중위 순회를 다시 수행하여 트리 상태를 출력
}

void look_menu() {
	printf("------------------------\n");
	printf("| s : 검색             |\n");
	printf("| i : 노드 추가        |\n");
	printf("| d : 노드 삭제        |\n");
	printf("| t : 중위 순회        |\n");
	printf("| I : 노드 추가(반복)  |\n");
	printf("| D : 노드 삭제(반복)  |\n");
	printf("| c : 종료             |\n");
	printf("------------------------\n");
	printf("\n");
}

int main() {

	//기본 노드 설정
	treenode* root = createnode(60);
	//레벨 1
	root->left = createnode(41);
	root->right = createnode(74);
	//레벨 2
	root->left->left = createnode(16);
	root->left->right = createnode(53);
	root->right->left = createnode(65);
	//레벨 3
	root->left->left->right = createnode(25);
	root->left->right->left = createnode(46);
	root->left->right->right = createnode(55);
	root->right->left->left = createnode(63);
	root->right->left->right = createnode(70);
	//레벨 4
	root->left->right->left->left = createnode(42);
	root->right->left->left->left = createnode(62);
	root->right->left->left->right = createnode(64);

	//메뉴 보여주는 함수 부르기
	look_menu();
	char choice; //메뉴 선택 변수 선언


	while (1)
	{
		printf("메뉴 입력 : ");
		scanf("%c", &choice);

		if (choice == 's') {
			node_search(root);
			printf("\n\n");
		}
		else if (choice == 'i' || choice == 'I') {
			root = node_insert(root, choice);
			printf("\n\n");
		}
		else if (choice == 'd' || choice == 'D') {
			root = node_delete(root, choice);
			printf("\n\n");
		}
		else if (choice == 't') {
			inorderwithcount(root);
			printf("\n");
		}
		else if (choice == 'c')
			break;
	}

	return 0;
}