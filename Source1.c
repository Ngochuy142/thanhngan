#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#pragma warning(disable : 4996)
typedef long double lb;
typedef struct {
	lb Elements[100];
	int Last;
}List;
void MakeNull_List(List* L);
int First(List L);
int EndList(List L);
void Insert_List(lb X, int P, List* L);
void ReadList(List* LX, List *LY);
void PrintList(List LX, List LY);
lb tong(lb* A, int n);
lb tongBinhPhuong(lb* A, int n);
lb tich(lb* A, lb* B, int n);
void tinhLog(lb* A, int n);

int main() {
	List LX;
	List LY;
	ReadList(&LX, &LY);
	PrintList(LX, LY);
	return 0;
}

void MakeNull_List(List* L) {
	L->Last = 0;
}
int First(List L) {
	return 1;
}
int EndList(List L) {
	return L.Last + 1;
}
void Insert_List(lb X, int P, List* L) {
	for (int Q = (L->Last - 1) + 1; Q >= P; Q--)
		L->Elements[Q] = L->Elements[Q - 1];
	L->Elements[P - 1] = X;
	L->Last++;
}
void ReadList(List* LX, List *LY) {
	lb X, Y;
	MakeNull_List(LX);
	MakeNull_List(LY);
	FILE* myFile = NULL;
	fopen_s(&myFile, "D:\\def.INP.txt", "r");
	if (myFile == NULL) {
		exit(1);
	}
	int n = fgetc(myFile) - 48;
	lb** A = malloc(2 * sizeof(lb*));
	for (int i = 0; i < 2; i++) {
		if (A) {
			A[i] = malloc(n * sizeof(lb));
		}
	}
	if (A) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < n; j++) {
				fscanf(myFile, "%Lf", &A[i][j]);
			}
		}
		for (int i = 0; i < n; i++) {
			X = A[0][i];
			Y = A[1][i];
			Insert_List(X, EndList(*LX), LX);
			Insert_List(Y, EndList(*LY), LY);
		}
		for (int i = 0; i < 2; i++) {
			free(A[i]);
		}
		free(A);
		
	}
	fclose(myFile);
}

void PrintList(List LX, List LY) {
	int n = LX.Last;
	printf("n = %d\n\n", LX.Last);
	printf("X |\t");
	for (int i = 0; i < n; i++) {
		printf("%0.3Lf\t", LX.Elements[i]);
	}
	printf("\n\n");
	printf("Y |\t");
	for (int i = 0; i < n; i++) {
		printf("%0.3Lf\t", LY.Elements[i]);
	}
	printf("\n\n");
	tinhLog(LX.Elements, n);
	tinhLog(LY.Elements, n);
	printf("LogX |\t");
	for (int i = 0; i < n; i++) {
		printf("%0.3Lf\t", LX.Elements[i]);
	}
	printf("\n\n");
	printf("LogY |\t");
	for (int i = 0; i < n; i++) {
		printf("%0.3Lf\t", LY.Elements[i]);
	}
	printf("\n\n");
	lb Xi = tong(LX.Elements, n);
	lb Xi2 = tongBinhPhuong(LX.Elements, n);
	lb XiYi = tich(LX.Elements, LY.Elements, n);
	lb Yi = tong(LY.Elements, n);
	lb det = n * Xi2 - Xi * Xi;
	lb det1 = Xi2 * Yi - Xi * XiYi;
	lb det2 = XiYi * n - Xi * Yi;
	/*printf("%0.3Lf\t%0.3Lf\t%0.3Lf\t%0.3Lf\n\n", Xi, Xi2, XiYi, Yi);
	printf("%0.3Lf\t%0.3Lf\n\n", det1 / det, det2 / det);*/

	printf("a = %0.3Lf\tb = %0.3Lf\n\n", pow(10, (det1 / det)), det2 / det);
}
lb tong(lb* A, int n) {
	lb s = 0;
	for (int i = 0; i < n; i++) {
		s += *(A + i);
	}
	return s;
}
lb tongBinhPhuong(lb* A, int n) {
	lb s = 0;
	for (int i = 0; i < n; i++) {
		s += pow(*(A + i), 2);
	}
	return s;
}
lb tich(lb* A, lb* B, int n) {
	lb s = 0;
	for (int i = 0; i < n; i++) {
		s += *(A + i) * *(B + i);
	}
	return s;
}
void tinhLog(lb* A, int n) {
	for (int i = 0; i < n; i++) {
		*(A + i) = (lb)log10(*(A + i));
	}
}