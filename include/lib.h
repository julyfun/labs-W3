#include <stdint.h>

// n 以内素数大致数量 = n / ln(n)
enum { MAX_N = (int)(3e7), MAX_T = MAX_N + 10, MAX_PRIME_NUM = (int)(2e6 + 10) };

// 使用结构体存储计算结果。
typedef struct ResultInner Result;
struct ResultInner {
    int cnt; // 素数个数
    int* primes; // 素数数组
};

Result print_prime_judge(int n);

Result print_prime_sieve_eratosthenes_plain(int n);
Result print_prime_sieve_eratosthenes_optimized(int n);

Result print_prime_sieve_euler(int n);
