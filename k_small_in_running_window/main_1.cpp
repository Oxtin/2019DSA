#include <vector>
#include <algorithm>
#define Size 200001
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

int n, m, k;
vector<int> win(Size);
vector<int>::iterator it = win.begin();

inline int search(int k, int left, int right) {
	while (left <= right) {
		int mid = (left + right) / 2;
		if (win[mid] == k)
			return mid;
		if (win[mid] < k)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return left;
}

int main() {
	Read(&n);
	Read(&m);
	Read(&k);
	int data[n];
	for (int i = 0; i < n; i++)
		Read(data + i);
	win.assign(data, data + m);
	sort(it, it + m);
	Print(win[k - 1]);
	for (int i = m; i < n; i++) {
		win.erase(it + search(data[i - m], 0, m - 1));
		win.insert(it + search(data[i], 0, m - 2), data[i]);
		Print(win[k - 1]);
	}
	return 0;
}
