#include <iostream>
  
using namespace std;
 
int fibonacci(int &x) {
    int x0 = 1 ;
    int x1 = 1 ;
    if ( (x==1) || (x==2) ) 
        cout << 1;
    int s;
    for (int i = 3; i <= x; i++) {
        s = x0 + x1;
        x0 = x1;
        x1 = s;
    }
        cout << s;
}
 
int main() {
    int x;
    cout <<"nhap so x \n";
    cin >> x;
    if ( (x<1) || (x>30) )
        cout << "So " << x << " khong nam trong khoanrg [1;30] \n";
    else 
        fibonacci(x);
    return 0;
    
}
