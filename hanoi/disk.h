#ifndef DISK_H
#define DISK_H
#include <string>
#include <iostream>
using namespace std;
class disk {
private:
	int level;
	int* _disk;
	int top;

public:
	disk(int n = 0);
	void init();
	void show();
	void operator>(disk& d);
	bool push(int);
	bool pop(int&);

	friend void show(const disk& a, const disk& b, const disk& c);
};
#endif