#include <iostream>
using namespace std;
int main() {
	int dd, yy, mmmm;
	do {
	cout << "nhap nam, nhap thang, nhap ngay \n";
	cin >> mmmm >> yy >> dd ;
	}
	while ( (mmmm <=0 ) || (yy <= 0) || (yy > 12) || (dd <= 0) || (dd > 31) ) ;
	if ( ( (mmmm % 4==0) || (mmmm % 400==0) ) && (mmmm%100 !=0) ) 
		{
			if (yy==2) {
				if ( dd > 29) 
					cout << "day khong phai la ngay thang nam";
				else 
					cout << "ngay " << dd << " " <<"thang " << yy << " " <<"nam " << mmmm;
			}
			else if ( (yy==4) || (yy==6) || (yy==9) || (yy==11) ) {
				if ( dd > 30) 
					cout << "day khong phai la ngay thang nam";
				else 
					cout << "ngay " << dd << " " <<"thang " << yy << " " <<"nam " << mmmm;
			}
			else 
				cout << "ngay " << dd << " " <<"thang " << yy << " " <<"nam " << mmmm;
		}	
	else 
		{
			if (yy==2) {
				if ( dd > 28) 
					cout << "day khong phai la ngay thang nam";
				else 
					cout << "ngay " << dd << " " <<"thang " << yy << " " <<"nam " << mmmm;
			}
			else if ( (yy==4) || (yy==6) || (yy==9) || (yy==11) ) {
				if ( dd > 30) 
					cout << "day khong phai la ngay thang nam";
				else 
					cout << "ngay " << dd << " " <<"thang " << yy << " " <<"nam " << mmmm;
			}
			else 
				cout << "ngay " << dd << " " <<"thang " << yy << " " <<"nam " << mmmm;	
		}
}
	
