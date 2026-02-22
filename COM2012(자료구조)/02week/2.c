//2. 임의로 정수 값 20개로 구성된 배열을 생성한 후 배열에서 최댓값과 최솟값을 동시에 찾는 함수를 작성하고 최댓값과 최솟값을 각각 다른 변수에 저장하고, 저장된 값을 반환
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//최대값과 최소값을 동시에 찾는 함수
int find_min_max(int a[])
{
	int max, min, i;
	max = 0; // 최대값: 범위 내에서 가장 작은 값으로 초기화
	min = 100; // min=2147483649, 최소값: 범위 내에서 가장 큰 값으로 초기화

	for (i = 0; i < 10; i++)
	{
		if (a[i] > max) max = a[i]; // 더 큰값을 최대값으로 한다.
		if (a[i] < min) min = a[i]; // 더 작은 값을 최소값으로 한다.
	}

	printf("최대값: %d\n", max);
	printf("최소값: %d\n", min);

	return 0;
}

int main() {
    //임의의 정수 값 20개로 구성된 배열 생성
    int arr[20];
    srand(time(NULL));
    printf(("임의의 정수 값 20개로 구성된 배열: "));
    for (int i = 0; i < 20; i++) {
        arr[i] = rand() % 100 + 1; //임의의 정수는 1~100
    }
    for (int i = 0; i < 20; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    find_min_max(arr);
    return 0;
}
