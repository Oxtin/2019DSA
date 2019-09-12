#pragma GCC optimize("03", "unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")
#pragma GCC target("avx")
#if __cplusplus > 199711L
#define register      // Deprecated in C++11.
#endif  // #if __cplusplus > 199711L
#include <bits/stdc++.h>
using namespace std;

const uint32_t mx = 11;

const uint32_t MX = 101;

const uint32_t mod = (1e9 + 7);

uint8_t p[mx][mx];

uint64_t d[mx][mx][mx][mx][MX];

uint8_t solved[mx][mx][mx][mx][MX];

uint32_t c[MX][MX];

uint8_t s[MX][MX];

static uint64_t C(int a, int b);

static uint8_t legal1(uint32_t, uint32_t, uint32_t);

static uint8_t legal2(uint32_t, uint32_t, uint32_t);

uint32_t dp(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

static uint64_t C(uint32_t a, uint32_t b) {
	if (s[a][b] == 1)
		return c[a][b];

	s[a][b] = 1;

	if (a == b || b == 0)
		return c[a][b] = 1;
	else
		return c[a][b] = (C(a - 1, b) + C(a - 1, b - 1)) % mod;
}

static uint8_t legal1(uint32_t l2, uint32_t r2, uint32_t line){ // check vertically
	register uint32_t i;

	for (i = l2; i <= r2; i++) {
		if (p[i][line] == 88)
			return 0;
	}
	return 1;
}

static uint8_t legal2(uint32_t l1, uint32_t r1, uint32_t line) { // check horizontally
	register uint32_t i;

	for (i = l1; i <= r1; i++) {
		if (p[line][i] == 88)
			return 0;
	}
	return 1;
}

uint32_t dp(uint32_t l1, uint32_t r1, uint32_t l2, uint32_t r2, uint32_t k) {
	if (k == 0)
		return 1;

	if (l1 == r1 && l2 == r2) // it's not necessary
		return 0;

	if (solved[l1][r1][l2][r2][k])
		return d[l1][r1][l2][r2][k];

	solved[l1][r1][l2][r2][k] = 1;

	register uint64_t sum = 0;
	register uint32_t i, j;
	// delete vertically
	if (l1 != r1) {
		for (i = l1; i <= r1; i++) {
			if (i == l1 && legal1(l2, r2, i))
				sum = (sum + dp(l1 + 1, r1, l2, r2, k - 1)) % mod;
			else if (i == r1 && legal1(l2, r2, i))
				sum = (sum + dp(l1, r1 - 1, l2, r2, k - 1)) % mod;
			else {
				if (legal1(l2, r2, i))
					for (j = 0; j < k; j++)
						sum = (sum + (C(k - 1, j) * dp(l1, i - 1, l2, r2, j) % mod * dp(i + 1, r1, l2, r2, k - 1 - j) % mod)) % mod;
			}
		}
	}
	// delete horizontally
	if (l2 != r2) {
		for (i = l2; i <= r2; i++) {
			if (i == l2 && legal2(l1, r1, i))
				sum = (sum + dp(l1, r1, l2 + 1, r2, k - 1)) % mod;
			else if (i == r2 && legal2(l1, r1, i))
				sum = (sum + dp(l1, r1, l2, r2 - 1, k - 1)) % mod;
			else {
				if (legal2(l1, r1, i))
					for (j = 0; j < k; j++)
						sum = (sum + (C(k - 1, j) * dp(l1, r1, l2, i - 1, j) % mod * dp(l1, r1, i + 1, r2, k - 1 - j) % mod)) % mod;
				}
		}
	}
	return d[l1][r1][l2][r2][k] = sum;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	time_t start, end;
	register uint32_t n, m, i, j;

	start = clock();
	cin >> n >> m;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			cin >> p[i][j];

	register long long sum = 0, tmp;
	i = 0;
	while (1) {
		tmp = dp(1, m, 1, n, i);
		if (tmp == 0)
			break;
		sum = (sum + tmp) % mod;
//		cout << sum << '\n';
		i++;
	}
	cout << sum << '\n';
	end = clock();
	cout << (double)(end - start) / CLOCKS_PER_SEC << '\n';
	return 0;
}
