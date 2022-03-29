#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <wchar.h>
#include <fcntl.h> 
#include <io.h>    
#pragma warning(disable : 4996)
typedef long double lb;
typedef struct {
	lb Elements[100];
	int last;
}List;

void makeNull_List(List* L);
int firstList(List L);
int endList(List L);
void insertList(lb x, int position, List* L);
void readListFromKeyboard(List* listX, List* listY);
void writeTheAnswerInTheScreen(List listX, List listY);
void readListFromFile(List* listX, List* listY);
void writeTheAnswerToTheFile(List listX, List listY);
void display(List listX, List listY);
void solutionStepSetails(List listX, List listY);

lb summation(lb* A, int n);
lb multiplication(lb* A, lb* B, int n);
lb sumOfSquares(lb* A, int n);
void logarithm(lb* A, int n);
lb findResultA(List listX, List listY);
lb findResultB(List listX, List listY);
void removeTheLastCharacter(wchar_t* x);
void gotoxy(short x, short y);

int main() {
	List Lx, Ly;
	_setmode(_fileno(stdout), _O_U16TEXT); 
    _setmode(_fileno(stdin), _O_U16TEXT); 
	wprintf(L"______________________________ PBL1: Dự án lập trình tính toán ______________________________\n");
	wprintf(L"Tên đề tài: 910\n");
	wprintf(L"Người thực hiện:\n");
	wprintf(L"\tPhan Thành Ngân\n");
	wprintf(L"\tNguyễn Ngọc Huy\n");
	wprintf(L"_____________________________________________________________________________________________\n\n");
	while (1)
	{
		wprintf(L"*****************************************************************\n");
		wprintf(L"|\tCác chức năng của chương trình\t\t\t\t|\n");
		wprintf(L"|1/ Đọc n, các phần tử của vector x, vector y từ file.\t\t|\n");
		wprintf(L"|2/ Đọc n, các phần tử của vector x, vector y từ bàn phím.\t|\n");
		wprintf(L"|3/ In kết quả hệ số a, b ra màn hình.\t\t\t\t|\n");
		wprintf(L"|4/ Lưu kết quả hệ số a, b vào file.\t\t\t\t|\n");
		wprintf(L"|5/ Xem chi tiết các bước giải.\t\t\t\t\t|\n");
		wprintf(L"|6/ Kết thúc chương trình.\t\t\t\t\t|\n");
		wprintf(L"*****************************************************************\n\n");
		wprintf(L"*Vui lòng chọn chức năng bạn muốn thực hiện: ");
		int select;
		wscanf_s(L"%d", &select);
		switch (select)
		{
		case 1:
			readListFromFile(&Lx, &Ly);
			wprintf(L"\nDữ liệu trong file là: ");
			display(Lx, Ly);
			break;
		case 2:
			readListFromKeyboard(&Lx, &Ly);
			wprintf(L"\nDữ liệu trong file là: ");
			display(Lx, Ly);
			break;
		case 3:
			writeTheAnswerInTheScreen(Lx, Ly);
			break;
		case 4:
			writeTheAnswerToTheFile(Lx, Ly);
			break;
		case 5:
			solutionStepSetails(Lx, Ly);
			break;
		case 6:
			exit(1);
			break;
		default:
			wprintf(L"Chức năng bạn chọn không hợp lệ. Vui lòng nhập lại\n\n");
			break;
		}
	}
	return 0;
}
void makeNull_List(List* L) {
	L->last = 0;
}
int firstList(List L) {
	return 1;
}
int endList(List L) {
	return L.last + 1;
}
void insertList(lb x, int position, List* L) {
	for (int i = L->last; i >= position; i--)
		L->Elements[i] = L->Elements[i - 1];
	L->Elements[position - 1] = x;
	L->last++;
}
void readListFromKeyboard(List* listX, List* listY) {
	int n;
	makeNull_List(listX);
	makeNull_List(listY);
	lb x, y;
	wprintf(L"Nhập n số lượng các phần tử của x và y: ");
	wscanf_s(L"%d", &n);
	for (int i = 0; i < n; i++) {
		wprintf(L"Nhập phần tử thứ %d của x:\t", i + 1);
		wscanf_s(L"%Lf", &x);
		insertList(x, endList(*listX), listX);
	}
	for (int i = 0; i < n; i++) {
		wprintf(L"Nhập phần tử thứ %d của y:\t", i + 1);
		wscanf_s(L"%Lf", &y);
		insertList(y, endList(*listY), listY);
	}
}
void readListFromFile(List* listX, List* listY) {
	lb x, y;
	int len;
	makeNull_List(listX);
	makeNull_List(listY);
	wchar_t name[50];
	FILE* myFile;
	do
	{
		fflush(stdin);
		wprintf(L"\nNhập đường dẫn hoặc tên file (phải có định dạng *.INP) \n");
		wscanf(L"%s", name);
		removeTheLastCharacter(name);
		myFile = _wfopen(name, L"r");
	} while (myFile == NULL);
	fwscanf(myFile, L"%d", &len);
	lb** A = malloc(2 * sizeof(lb*));
	for (int i = 0; i < 2; i++) {
		A[i] = malloc(len * sizeof(lb));
	}
	if (A) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < len; j++) {
				fwscanf(myFile, L"%Lf", &A[i][j]);
			}
		}
		for (int i = 0; i < len; i++) {
			x = A[0][i];
			y = A[1][i];
			insertList(x, endList(*listX), listX);
			insertList(y, endList(*listY), listY);
		}
		for (int i = 0; i < 2; i++) {
			free(A[i]);
		}
		free(A);
	}
	fclose(myFile);
}
void writeTheAnswerInTheScreen(List listX, List listY) {
	wprintf(L"a = %0.3Lf\t", pow(10, findResultA(listX, listY)));
	wprintf(L"b = %0.3Lf\t", findResultB(listX, listY));
	wprintf(L"\n\n");
}
void writeTheAnswerToTheFile(List listX, List listY) {
	wchar_t name[100];
	fflush(stdin);
	wprintf(L"\nNhập đường dẫn hoặc tên file cần lưu kết quả:\n");
	wscanf(L"%s", name);
	removeTheLastCharacter(name);
	FILE* myFile;
	myFile = _wfopen(name, L"w+");
	if (myFile == NULL) {
		wprintf(L"\nLỗi ghi file\n");
		exit(1);
	}
	fwprintf(myFile, L"%c = %0.3Lf\t%c = %0.3Lf", 'a', pow(10, findResultA(listX, listY)), 'b', findResultB(listX, listY));
	fclose(myFile);
	wprintf(L"\nĐã ghi file thành công\n");
}
void display(List listX, List listY) {
	int len = listX.last;
	wprintf(L"\nn = %d\n", len);
	wprintf(L"X\t|\t");
	for (int i = 0; i < len; i++) {
		wprintf(L"%0.3Lf ", listX.Elements[i]);
	}
	wprintf(L"\nY\t|\t");
	for (int i = 0; i < len; i++) {
		wprintf(L"%0.3Lf ", listY.Elements[i]);
	}
	wprintf(L"\n\n");
}
void solutionStepSetails(List listX, List listY) {
	int len = listX.last;
	wprintf(L"Các bước giải gồm: \n");
	wprintf(L"Quy định kí hiệu:  Sigma = '[' \n");
	wprintf(L"Ban đầu ta có \n");
	display(listX, listY);
	wprintf(L"Bước 1: \n");
	wprintf(L"Lấy Logarit cơsố 10 hai vế: Lgy = lga + blgx \n");
	wprintf(L"Đặt Y = lgy; A = lga; B = b; X = lgx \n");
	wprintf(L"Ta đưa về dạng:\tY = A + BX\n\n");
	lb A = findResultA(listX, listY);
	lb B = findResultB(listX, listY);
	logarithm(listX.Elements, listX.last);
	logarithm(listY.Elements, listX.last);
	display(listX, listY);
	wprintf(L"Bước 2: \n");
	wprintf(L"Tính [Xi : ");
	wprintf(L"[Xi = %0.3Lf\n", summation(listX.Elements, len));
	wprintf(L"Tính [Xi^2 : ");
	wprintf(L"[Xi^2 = %0.3Lf\n", sumOfSquares(listX.Elements, len));
	wprintf(L"Tính [XiYi : ");
	wprintf(L"[XiYi = %0.3Lf\n", multiplication(listX.Elements, listY.Elements, len));
	wprintf(L"Tính [Yi : ");
	wprintf(L"[Yi = %0.3Lf\n\n", summation(listY.Elements, len));
	wprintf(L"Bước 3: \n");
	wprintf(L"Phương pháp bình phương bé nhất: A, B là nghiệm hệ phương trình\n");
	wprintf(L"\tn*A + B*[Xi = [Yi \n");
	wprintf(L"\t[Xi*A + B *[Xi^2 = [XiYi \n");
	wprintf(L"<=>\n");
	wprintf(L"\t%d*A + B*%0.3Lf = %0.3Lf \n", len, summation(listX.Elements, len), summation(listY.Elements, len));
	wprintf(L"\t%0.3Lf*A + B*%0.3Lf = %0.3Lf \n", summation(listX.Elements, len), sumOfSquares(listX.Elements, len), multiplication(listX.Elements, listY.Elements, len));
	wprintf(L"Giải hệ phương trình ta được: A = %0.3Lf,\tB = %0.3Lf \n\n", A, B);
	wprintf(L"Suy ra: a = 10^A = %0.3Lf,\tb = B = %0.3Lf\n\n", pow(10, A), B);
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
lb findResultA(List listX, List listY) {
	logarithm(listX.Elements, listX.last);
	logarithm(listY.Elements, listX.last);
	lb det = listX.last * sumOfSquares(listX.Elements, listX.last) - pow(summation(listX.Elements, listX.last),2);
	lb det1 = sumOfSquares(listX.Elements, listX.last) * summation(listY.Elements, listX.last) - summation(listX.Elements, listX.last) * multiplication(listX.Elements, listY.Elements, listX.last);
	return det1 / det;
}
lb findResultB(List listX, List listY) {
	logarithm(listX.Elements, listX.last);
	logarithm(listY.Elements, listX.last);
	lb det = listX.last * sumOfSquares(listX.Elements, listX.last) - pow(summation(listX.Elements, listX.last), 2);
	lb det2 = multiplication(listX.Elements, listY.Elements, listX.last) * listX.last - summation(listX.Elements, listX.last) * summation(listY.Elements, listX.last);
	return det2 / det;
}
void removeTheLastCharacter(wchar_t* x) {
	size_t len = wcslen(x);
	if (x[len - 1] == '\n') {
		x[len - 1] = '\0';
	}
}
void gotoxy(short x, short y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
