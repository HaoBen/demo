#include "disk.h"

disk::disk(int n) :level(n) {
	top =level-1;
	_disk = new int[level];
	for (int i = 0; i < level; ++i) {
		_disk[i] = 0;
	}

}

void disk::init() {
	for (int i = 0; i < level; ++i) {
		_disk[i] = i+1;
	}
	top =-1;
}

bool disk::push(int elem) {
	if (top != -1) {
		_disk[top] = elem;
		--top;
		return true;
	}
	else
		return false;
}

bool disk::pop(int& elem) {
	if (top != level-1) {
		++top;
		elem = _disk[top];
		_disk[top] = 0;
		return true;
	}
	else
		return false;
}

void disk::operator>(disk& d) {
	int elem;
	pop(elem);
	d.push(elem);
}

void show(const disk& a, const disk& b, const disk& c) {
	for (int i = 0; i < a.level; ++i) {
		cout << a._disk[i] << '\t';
		cout << b._disk[i] << '\t';
		cout << c._disk[i] << '\t';
		cout << endl;
	}
	cout << endl;
}