#include <bits/stdc++.h>

using namespace std;

#define next __next

int const N = 55;
int const SIZE = 25;
int const CHARS = 45;
int const MASK = 1 << 3;


int n, minLen, maxLen, nodes = 0;

int next[N * SIZE][CHARS], link[N * SIZE];
bool is_last[N * SIZE];
string all_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

int val_char(char p) {
	if (p >= 'a' && p <= 'z') {
		return (p - 'a');
	}

	if (p >= 'A' && p <= 'Z') {
		return (p - 'A');
	}

	if (p == '0') return val_char('o');
	if (p == '1') return val_char('i');
	if (p == '3') return val_char('e');
	if (p == '5') return val_char('s');
	if (p == '7') return val_char('t');
	return 26 + (p - '0');
}

int get_mask(char p) {
	if (p >= 'a' && p <= 'z') {
		return 1;
	}
	if (p >= 'A' && p <= 'Z') {
		return 2;
	}
	return 4;
}


void push_trie(string s) {
	int root = 0;
	for (int i = 0; i < s.size(); i++) {
		int val = val_char(s[i]);
		if (next[root][val] == 0) {
			next[root][val] = ++nodes;
		}
		root = next[root][val];
	}
	is_last[root] = true;
}


int que[N * SIZE];

void build_aho() {
	int top = 0;
	int bot = 1;
	que[++top] = 0;
	while (bot <= top) {
		int u = que[bot]; bot++;
		int v = link[u];
		if (!is_last[u]) {
			is_last[u] = is_last[v];
		}
		//cout << "u : " << u << " " << v << endl;
		for (int i = 0; i < CHARS; i++) {
			if (next[u][i]) {
				link[next[u][i]] = u ? next[v][i] : 0;
				que[++top] = next[u][i];
			} else {
				next[u][i] = next[v][i];
			}
		}
	}
}


int dp[N][N * SIZE][MASK];

int const MOD =  1000003;

void add_mod(int &x, int y) {
	x += y;
	if (x >= MOD) {
		x -= MOD;
	}
}

int main() {
	cin >> minLen >> maxLen;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		push_trie(s);
	}

	build_aho();

	dp[0][0][0] = 1;
	for (int i = 0; i <= maxLen; i++) {
		for (int u = 0; u <= nodes; u++) {
			for (int mask = 0; mask < MASK; mask++) {
				if (is_last[u]) {
					dp[i][u][mask] = 0;
				}
				for (char p : all_chars) {
					int val = val_char(p);
					add_mod(dp[i + 1][next[u][val]][mask | get_mask(p)], dp[i][u][mask]);
					//cout << i + 1 << " " << next[u][val] << " " << (mask | get_mask(p)) << " " << dp[i + 1][next[u][val]][mask | get_mask(p)] << endl;
					//return 0;
				}
			}
		}
	}



	int ans = 0;
	//cout << dp[3][0][7] << endl;
	for (int i = minLen; i <= maxLen; i++) {
		for (int u = 0; u <= nodes; u++) {
			add_mod(ans, dp[i][u][MASK - 1]);
		}
	}
	cout << ans << endl;

}