#include <stdio.h>
#include <algorithm>

int64_t c[1000001];
int64_t A, B;
int n;

int main() {
    scanf("%d %d %d", &n, &A, &B);
    for (int i = 1; i <= n; ++i) scanf("%d", c + i), c[i] += c[i - 1];
    int64_t best = c[n];
    for (int i = n - 1; i > 0; --i) best = std::min(best, std::max(A + B - best + c[i] + 1, c[i]));
    printf("%s\n", A >= best ? "ALICE" : "BOB");
}