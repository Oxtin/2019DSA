#include <bits/stdc++.h>
#define MAXL (100000 + 5)
using namespace std;

typedef unsigned long long ull;

char s[MAXL];

int len, m;

ull d[MAXL], base[MAXL];

inline void init() {
	d[0] = s[0];
	base[0] = 1;

	for (int i = 1; i < len; i++) {
		d[i] = d[i - 1] * 29 + s[i];
		base[i] = base[i - 1] * 29;
		// cout << d[i] << \n';
	}
}

int hashFn(int l) {
	unordered_map<ull, int> record; // hash_value / times
	int index = -1;
	ull hash_value;

	record[d[l - 1]] = 1;
	if (m == 1)
		index = 0;
	// cout << d[l - 1] << '\n';
	for (int i = 1; i <= len - l; i++) {
		hash_value = d[i + l - 1] - d[i - 1] * base[l];
		// cout << hash_value << '\n';
		auto it = record.find(hash_value);
		if (it != record.end()) {
			it->second++;
			if (it->second >= m)
				index = i;
		}
		else
			record[hash_value] = 1;
	}
	return index;
}

inline bool isEqual(int l) {
	ull hash_value = d[len - 1] - d[len - l - 1] * base[l];

	return d[l - 1] == hash_value;
}

inline bool isExist(int l) {
	ull compared = d[l - 1];

	for (int i = 1; i <= len - l - 1; i++) {
		if (compared == d[i + l - 1] - d[i - 1] * base[l])
			return true;
	}
	return false;
}

void prbm1() {
	int index = -1, tmp, maxLen;
	int l = 1, r = len, mid;

	while (l <= r) {
		mid = (l + r) / 2;
		tmp = hashFn(mid);
		if (tmp >= 0) {
			maxLen = mid;
			index = tmp;
			l = mid + 1;
		}
		else
			r = mid - 1;
	}

	if (index >= 0)
		cout << maxLen << ' ' << index << '\n';
	else
		cout << "none\n";
}

void prbm2() {
	if (len < 3) {
		cout << "Just a legend\n";
		return;
	}

	int pre_suf[MAXL], pfNum = 0;

	memset(pre_suf, 0, MAXL);
	for (int i = 1; i <= len - 2; i++) {
		if (isEqual(i)) {
			pre_suf[pfNum] = i;
			pfNum++;
		}
	}

	int l = 0, r = pfNum - 1, mid, maxLen = 0;

	while (l <= r) {
		mid = (l + r) / 2;
		if (isExist(pre_suf[mid])) {
			maxLen = pre_suf[mid];
			l = mid + 1;
		}
		else
			r = mid - 1;
	}

	if (maxLen == 0)
		cout << "Just a legend\n";
	else {
		// cout << maxLen << '\n';
		char ans[MAXL];
		strncpy(ans, s, maxLen);
		ans[maxLen] = '\0';
		cout << ans << '\n';
	}
//	for (int i = 0; i < pfNum; i++)
//		cout << pre_suf[i] << '\n';
}

int main() {
	cin.tie(nullptr), ios_base::sync_with_stdio(0);

	while (cin >> m && m) {
		cin >> s;
		len = strlen(s);
		init();
		prbm1();
		prbm2();
	}
	return 0;
}
