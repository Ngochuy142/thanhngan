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
lb summation(lb* A, int n);
lb sumOfSquares(lb* A, int n);
lb multiplication(lb* A, lb* B, int n);
void logarithm(lb* A, int n);

int main() {
	//printf("_________________________________________ Do An PBL 1: Phuong phap tinh _________________________________________ \n\n");
	//printf("\t\tTen de tai: 910\n");
	//printf("\t\tNguoi thuc hien:\n");
	//printf("\t\t1/ Phan Thanh Ngan \n");
	//printf("\t\t2/ Nguyen Ngoc Huy\n");
	//printf("\t\t Cac chuc nang cua chuong trinh:\n");
	//printf("\t\t 1/ Doc n, cac phan tu cua vecto x, vector y tu file\n");
	//printf("\t\t 2/ Doc n, cac phan tu cua vecto x, vector y tu ban phim\n");
	//printf("\t\t 3/ In ket qua he so a, b ra man hinh \n");
	//printf("\t\t 4/ Luu ket qua he so a, b vao file\n");
	//printf("\t\t 5/ Ket thuc chuong trinh \n");
	List LX;
	List LY;
	/*while (1) {
		printf("Chon chuc nang ban muon thuc hien:\n");
		int n;
		scanf("%d", &n);
		switch (n)
		{
		case 1:
		default:
			break;
		}*/
		ReadList(&LX, &LY);
		PrintList(LX, LY);
	//}
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
	char s[100];
	scanf_s("%s", s);
	lb X, Y;
	int n;
	MakeNull_List(LX);
	MakeNull_List(LY);
	FILE* myFile = NULL;
	fopen_s(&myFile, "Text.txt", "r");
	if (myFile == NULL) {
		exit(1);
	}
	fscanf(myFile, "%d", &n);
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
	logarithm(LX.Elements, n);
	logarithm(LY.Elements, n);
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
	lb Xi = summation(LX.Elements, n);
	lb Xi2 = sumOfSquares(LX.Elements, n);
	lb XiYi = multiplication(LX.Elements, LY.Elements, n);
	lb Yi = summation(LY.Elements, n);
	lb det = n * Xi2 - Xi * Xi;
	lb det1 = Xi2 * Yi - Xi * XiYi;
	lb det2 = XiYi * n - Xi * Yi;
	printf("%0.3Lf\t%0.3Lf\t%0.3Lf\t%0.3Lf\n\n", Xi, Xi2, XiYi, Yi);
	printf("%0.3Lf\t%0.3Lf\n\n", det1 / det, det2 / det);

	printf("a = %0.3Lf\tb = %0.3Lf\n\n", pow(10, (det1 / det)), det2 / det);
}
lb summation(lb* A, int n) {
	lb s = 0;
	for (int i = 0; i < n; i++) {
		s += *(A + i);
	}
	return s;
}
lb sumOfSquares(lb* A, int n) {
	lb s = 0;
	for (int i = 0; i < n; i++) {
		s += pow(*(A + i), 2);
	}
	return s;
}
lb multiplication(lb* A, lb* B, int n) {
	lb s = 0;
	for (int i = 0; i < n; i++) {
		s += *(A + i) * *(B + i);
	}
	return s;
}
void logarithm(lb* A, int n) {
	for (int i = 0; i < n; i++) {
		*(A + i) = (lb)log10(*(A + i));
	}
}
