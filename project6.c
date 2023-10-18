#include <stdio.h>
#include <stdlib.h>
#define MAX_HEAP_SIZE 100

typedef struct Heap {
	int array[MAX_HEAP_SIZE];//heap 배열
	int size;
}Heap;

// 두 값을 바꾸는 함수
void change(int* a, int* b) {
	int tmp;
}

void insert_menu() {
	int data;
	printf("추가할 값 입력 : ");
	scanf("%d", &data);
}

void menu() {
	printf("----------------------\n");
	printf("| i   : 노드 추가    |\n");
	printf("| d   : 노드 삭제    |\n");
	printf("| p   : 레벨별 출력  |\n");
	printf("| c   : 종료         |\n");
	printf("----------------------\n");
}

int main() {



	menu(); // 메뉴 보여주기
	char choice; // 메뉴 입력 변수

	while (1)
	{
		printf("메뉴 입력 : ");
		scanf("%s", &choice);
		if (choice == 'i') {
			insert_menu();
		}
	}

	return 0;
}