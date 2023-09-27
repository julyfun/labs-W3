#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "lib.h"

/**
 * @brief 判断 x 是否是质数。时间复杂度 $O(\sqrt{x})$
 */
int is_prime(int x) {
    if (x == 1) {
        return 0;
    }
    // 若 x 有非 1 和自身的因数，则必然在 2 ~ sqrt(x) 之间
    // 存在因数。
    int s = sqrt(x);
    for (int i = 2; i <= s; i++) {
        // x % i == 0 即 i 是 x 的因数。
        if (x % i == 0) {
            return 0;
        }
    }
    // 若找不到范围内的因数，则是质数。
    return 1;
}

/**
 * @brief 使用 `is_prime()` 逐个判断 x 是否素数。复杂度为 $O(n ^ 1.5)$
 */
Result print_prime_judge(int n) {
    // 用 static 变量存储求解信息，然后用指针返回结果。
    // 这样做是为了比较算法效率时，避免输出的影响。
    static int cnt = 0;
    static int primes[MAX_PRIME_NUM] = { 0 };
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            primes[++cnt] = i;
        }
    }
    // 使用 Result 结构体返回得到的总质数个数和质数数组。
    return (Result) { .cnt = cnt, .primes = primes };
}

/**
 * @brief 使用朴素埃氏筛筛去所有合数。复杂度 $\sum_{i = 1}^{\sqrt n} \dfrac{n}{i}$ i = O(n \log n)$
 */
Result print_prime_sieve_eratosthenes_plain(int n) {
    // not_prime[i] = 1 表示该数不是质数
    static uint8_t not_prime[MAX_T] = { 0 };
    static int cnt = 0;
    static int primes[MAX_PRIME_NUM] = { 0 };

    // 1 不是质数。
    not_prime[1] = 1;
    for (int i = 2; i * i <= n; i++) {
        // 对于每个数，标记其倍数为合数即可。
        for (int j = i * 2; j <= n; j += i) {
            not_prime[j] = 1;
        }
    }
    for (int i = 2; i <= n; i++) {
        // 最后未被标记为合数的数加入到结果数组中。
        if (!not_prime[i]) {
            primes[++cnt] = i;
        }
    }
    return (Result) { .cnt = cnt, .primes = primes };
}

/**
 * @brief 使用优化埃氏筛筛去所有合数。复杂度 $O(n \log\log n)$
 */
Result print_prime_sieve_eratosthenes_optimized(int n) {
    // not_prime[i] = 1 表示该数不是质数
    static uint8_t not_prime[MAX_T] = { 0 };
    static int cnt = 0;
    static int primes[MAX_PRIME_NUM] = { 0 };

    not_prime[1] = 1;
    for (int i = 2; i * i <= n; i++) {
        // 对于每个质数（前面筛去后剩下的就是质数），标记其倍数为合数。
        if (!not_prime[i]) {
            for (int j = i * 2; j <= n; j += i) {
                not_prime[j] = 1;
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        if (!not_prime[i]) {
            primes[++cnt] = i;
        }
    }
    return (Result) { .cnt = cnt, .primes = primes };
}

/**
 * @brief 使用欧拉筛去所有合数。复杂度 $O(n)$. 证明见 README
 */
Result print_prime_sieve_euler(int n) {
    static uint8_t not_prime_eular[MAX_T] = { 0 };
    // 用 prime_eular 存储确定的质数。
    static int primes[MAX_T] = { 0 };
    static int cnt = 0;

    not_prime_eular[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!not_prime_eular[i]) { // 没筛掉
            primes[++cnt] = i; // 将 i 加到素数数组里
        }
        for (int j = 1; j <= cnt && i * primes[j] <= n; j++) {
            // 从 primes[1]，即最小质数 2 开始，逐个枚举已知的质数，并期望 primes[j] 是 i * primes[j] 的
            // 最小质因数。当然，i 肯定比 primes[j]大，因为 primes[j] 是在 i 之前得出的。
            not_prime_eular[i * primes[j]] = 1;
            if (i % primes[j] == 0) {
                // i 中也含有 primes[j] 这个因子，则不必往下筛。
                break;
            }
        }
    }
    return (Result) { .cnt = cnt, .primes = primes };
}
