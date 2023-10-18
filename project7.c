#include <stdio.h>

//정수 교환 함수
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

//최댓 값 구하는 함수
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    //왼쪽 서브트리 비교 후 최댓값 변환
    if (left < n && arr[left] > arr[largest])
        largest = left;

    //오른쪽 서브트리 비교 후 최댓값 변환
    if (right < n && arr[right] > arr[largest])
        largest = right;

    //최댓값이 i 값이 아닐 경우
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

//힙 정렬
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    //힙 정렬하는 부분 출력
    for (int i = 0; i < n; i++) {
        printf("Step %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");

        //2개의 정수 변경
        swap(&arr[0], &arr[n - i - 1]);
        heapify(arr, n - i - 1, 0);
    }
}

int main() {
    //정렬 할 리스트 선언
    int arr[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 34, 85, 29, 78, 41, 56, 86 };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("힙 정렬\n");
    heapSort(arr, n); //힙 정렬

    printf("\n");
    printf("힙 정렬 후 배열: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}