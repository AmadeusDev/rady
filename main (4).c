#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int comp(const void * a, const void * b) {
	return (*(int*)a - *(int*)b);
}

int main(int argc, char *argv[]) {

	int sizeOfArray = 1000;
	int histVal = 0;
	int val = 0;
	int cnt = 0;

	scanf("%d", &histVal);
	if (histVal <= 0)
	{
		fprintf(stderr, "Histogram size error\n");
		return 100;
	}
	int *histArr = (int *)malloc(sizeof(int) * (histVal));

	int *vals = (int *)malloc(sizeof(int) * sizeOfArray);

	while (scanf("%d", &val) == 1) {
		cnt++;

		if (cnt >= sizeOfArray) {
			sizeOfArray++;
			int *vals2;
			vals2 = (int *)realloc(vals, sizeOfArray * sizeof(int));
			vals = (int *)vals2;
		}

		vals[cnt - 1] = val;
	}



	qsort(vals, cnt, sizeof(*vals), comp);

	printf("Median %.2f\n", (cnt % 2) ? (*(vals + cnt / 2)) : (*(vals + cnt / 2 - 1) + *(vals + cnt / 2)) / (float)2);
	printf("Number count: %d\n", cnt);
	printf("Min: %d\n", vals[0]);
	printf("Max: %d\n", vals[cnt - 1]);

	double histSize = (double)(vals[cnt - 1] - vals[0]) / histVal;

	for (int j = 0; j < histVal; j++) {
		histArr[j] = 0;
	}


	printf("Histogram:\n");

	for (int i = 0; i < cnt; i++) {
		double result = (vals[i] - vals[0]) / histSize;

		int index = (int)result;
		index = index > histVal - 1 ? index - 1 : index;
		histArr[index]++;
	}

	int max = 0, maxIndex = 0;

	for (int k = 0; k < histVal; k++) {
		if (histArr[k] > max) {
			max = histArr[k];
			maxIndex = k;
		}
	}

	double maxQ = (double)histArr[maxIndex] / 25;

	for (int k = 0; k < histVal; k++) {
		histArr[k] = histArr[k] / maxQ;

		printf("%5.1f - %5.1f|", vals[0] + (k*histSize), vals[0] + ((k + 1)*histSize));

		for (int i = 0; i < histArr[k]; i++) {
			printf("=");
		}

		
		printf("\n");
	}
	free(vals);
	free(histArr);
	return 0;
}
