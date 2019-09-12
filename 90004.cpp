#pragma GCC optimize("O3")
#include <iostream>
#include <ctype.h>
#include <vector>
#include <string>
#include <unordered_map>
#define MAX(x, y) ( ((x) > (y)) ? (x) : (y) )
#define MIN(x, y) ( ((x) < (y)) ? (x) : (y) )
#define upper 200
#define lower -200
using namespace std;

typedef struct card {
	int suit;
	int val;
}card;

card alice[20], bob[20];
int cards;
int aval1[20], aval2[20];
unordered_map<long long int, int> data;

long long int hash_function(int aval1[], int aval2[], int turn, int suit, int value, int alpha, int beta) {
	long long int hash = 0;

	for (int i = 0; i < cards; i++) {
		hash += aval1[i];
		hash <<= 1;
	}
	for (int i = 0; i < cards; i++) {
		hash += aval2[i];
		hash <<= 1;
	}
	hash += turn - 1;
	hash <<= 3;
	
	hash += suit;
	hash <<= 4;

	hash += value;
	hash <<= 9;

	hash += alpha;
	hash <<= 9;

	hash += beta;
	return hash;
}

int dfs(int turn, int aval1[], int aval2[], int suit, int val, int remain1, int remain2, int alpha, int beta) {
	if (remain1 == 0) {
		int sum = 0;
		for (int i = 0; i < cards; i++) {
			if (aval2[i])
				sum += bob[i].val;
		}
//		cout << "Alice "  << sum << '\n';
		return sum;
	}
	if (remain2 == 0) {
		int sum = 0;
		for (int i = 0; i < cards; i++) {
			if (aval1[i])
				sum += alice[i].val;
		}
//		cout << "Bob " << sum << '\n';
		return -sum;
	}
	
	long long int hash = hash_function(aval1, aval2, turn, suit, val, alpha, beta);

	if (data.find(hash) != data.end())
		return data[hash];
	else {
		if (turn == 1) {
			int res, best = lower;

			if (val) {
				int flag = 1;
				for (int i = 0; i < cards; i++) {
					if (aval1[i]) {
						if (alice[i].suit == suit || alice[i].val == val) {
//							cout << "Alice " << alice[i].suit << alice[i].val << '\n';
							aval1[i] = 0;
							res = dfs(2, aval1, aval2, alice[i].suit, alice[i].val, remain1 - 1, remain2, alpha, beta);
							aval1[i] = 1;
							flag = 0;

							best = MAX(best, res);
							alpha = MAX(alpha, best);

							if (alpha >= beta)
								break;
						}
					}
				}

				if (flag) {
	//				cout << "Alice passes" << '\n';
					return dfs(2, aval1, aval2, 0, 0, remain1, remain2, alpha, beta);
				}
				else {
					data[hash] = best;
					return best;
				}
			}
			else {
				for (int i = 0; i < cards; i++) {
					if (aval1[i]) {
						aval1[i] = 0;
	//					cout << "Alice " << alice[i].suit << alice[i].val << '\n';
						res = dfs(2, aval1, aval2, alice[i].suit, alice[i].val, remain1 - 1, remain2, alpha, beta);
						aval1[i] = 1;
						best = MAX(best, res);
						alpha = MAX(alpha, best);
						if (alpha >= beta)
							break;
					}
				}

				data[hash] = best;
				return best;
			}
		}
		
		else {
			int res, best = upper;

			if (val) {
				int flag = 1;
				for (int i = 0; i < cards; i++) {
					if (aval2[i]) {
						if (bob[i].suit == suit || bob[i].val == val) {
							aval2[i] = 0;
	//						cout << "Bob " << bob[i].suit << bob[i].val << '\n';
							res = dfs(1, aval1, aval2, bob[i].suit, bob[i].val, remain1, remain2 - 1, alpha, beta);
							aval2[i] = 1;
							flag = 0;
						
							best = MIN(best, res);
							beta = MIN(beta, best);
							if (beta <= alpha)
								break;
						}
					}
				}
				if (flag) {
	//				cout << "Bob passes" << '\n';
					return dfs(1, aval1, aval2, 0, 0, remain1, remain2, alpha, beta);
				}
				else {
					data[hash] = best;
					return best;
				}
			}
			else {
				for (int i = 0; i < cards; i++) {
					if (aval2[i]) {
						aval2[i] = 0;
	//					cout << "Bob " << bob[i].suit << bob[i].val << '\n';
						res = dfs(1, aval1, aval2, bob[i].suit, bob[i].val, remain1, remain2 - 1, alpha, beta);
						aval2[i] = 1;
					
						best = MIN(best, res);
						beta = MIN(beta, best);
						if (beta <= alpha)
							break;
					}
				}
				data[hash] = best;
				return best;
			}
		}
	}

/*	for (int i = 0; i < cards; i++)
		cout << aval1[i] << ' ';
	cout << '\n';
	for (int i = 0; i < cards; i++)
		cout << aval2[i] << ' ';
	cout << '\n'; */
}

int alphatoval(char a) {
	if (a == 'A')
		return 1;
	else if (a == 'T')
		return 10;
	else if (a == 'J')
		return 11;
	else if (a == 'Q')
		return 12;
	else
		return 13;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string input;
	int ALPHA[100];

	ALPHA['C'] = 1;
	ALPHA['D'] = 2;
	ALPHA['H'] = 3;
	ALPHA['S'] = 4;

	cin >> cards;
	for (int i = 0; i < cards; i++) {
		cin >> input;
		alice[i].suit = ALPHA[input[0]];
		if (isalpha(input[1]))
			alice[i].val = alphatoval(input[1]);
		else
			alice[i].val = input[1] - '0';
		aval1[i] = 1;
	}
	for (int i = 0; i < cards; i++) {
		cin >> input;
		bob[i].suit = ALPHA[input[0]];
		if (isalpha(input[1]))
			bob[i].val = alphatoval(input[1]);
		else
			bob[i].val = input[1] - '0';
		aval2[i] = 1;
	}

	int ans = dfs(1, aval1, aval2, 0, 0, cards, cards, lower, upper);
	if (ans > 0)
		cout << "Alice\n" << ans << '\n';
	else
		cout << "Bob\n" << -ans << '\n';
	return 0;
}
