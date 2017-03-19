#include <iostream>
#include "disk.h"
using namespace std;
const int level = 4;
disk A(level), B(level), C(level);

void move(disk& left, disk& right) {
	left > right;
	show(A, B, C);
	cout << "-----------------------------------------------------------------------" << endl;
}
void hario(disk& A,disk& B, disk& C, int n) {
	if (n == 1) {
		move(A, C);
		return;
	}
	else {
		hario(A, C, B, n - 1);
		move(A , C);
	}
	hario(B, A, C, n - 1);
}
int main() {
	A.init();
	show(A, B, C);
	cout << "-----------------------------------------------------------------------" << endl;
	hario(A, B, C, level);

}

