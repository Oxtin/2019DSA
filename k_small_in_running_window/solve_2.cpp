#include <stdio.h>
#include <set>
#define MAXD 200000
#define MAXW 100000
using namespace std;

inline void Read(int *x) {
	char c;
	while ((c = getchar()) < '0');
	*x =  c - '0';
	while ((c = getchar()) >= '0')
		*x = (*x << 3) + (*x << 1) + c - '0';
}

inline void Print(int x) {
	int ind = 0;
	char buf[15];
	while (x) {
		buf[++ind] = x % 10 + '0';
		x /= 10;
	}
	while (ind)
		putchar(buf[ind--]);
	putchar('\n');
}

int main() {
	static int n, m, k;
	multiset<int> window;
	int data[MAXD], i;

	Read(&n);
	Read(&m);
	Read(&k);
	for (i = 0; i < n; i++)
		Read(data + i);
	window.insert(data, data + m);
	auto it = window.begin();
	for (i = 0; i < k - 1; i++)
		it++;
	Print(*it);
	for (i = m; i < n; i++) {
		// printf("current it: %d. ", *it);
		window.insert(it, data[i]);
		if (data[i] <= *it)
			--it;
		// printf("after insert %d, it: %d. ",data[i], *it);
		if (data[i - m] <= *it)
			++it;
		window.erase(window.lower_bound(data[i - m]));
		// printf("after erase %d, it: %d. ",data[i - m], *it);
		Print(*it);
	}
	return 0;
}
