#include <stdio.h>
#include <time.h>

#include "lib.h"

// 输入的 n 大于此常数时，结果输出到文件中。
const char* FILE_PATH = "result.txt";
const int DIRECT_OUTPUT_N = 2000;

int main() {
    // 将交互信息重定向到 stderr，这样就可以自由重定向 stdout 到终端或者文件里了。
    fprintf(
        stderr,
        "\
Input a number `n` and the program will output all the prime numbers\n\
between 1 and n in three methods and how much TIME they spent.\n\
`n` should be no more than %d. If `n` is greater than %d, \n\
stdout will be redirected to %s.\n",
        MAX_N,
        DIRECT_OUTPUT_N,
        FILE_PATH
    );
    int n = 0;
    scanf("%d", &n);
    // 当 n 过大，不便于输出到终端的时候，输出结果到文件。
    if (n > DIRECT_OUTPUT_N) {
        freopen(FILE_PATH, "w", stdout);
        fprintf(stderr, "Stdout has been redirected to %s, see results there.\n", FILE_PATH);
    }
    // 使用函数指针数组存储所有函数，方便后续统计输出时间时统一调用格式。
    Result (*func[])(int) = { print_prime_judge,
                              print_prime_sieve_eratosthenes_plain,
                              print_prime_sieve_eratosthenes_optimized,
                              print_prime_sieve_euler };
    const char algorithm_names[][30] = { "Judge Directly",
                                         "Plain Eratosthenes Sieve",
                                         "Optimized Eratosthenes Sieve",
                                         "Eular Sieve" };
    // 分别使用几个算法计算结果，统计计算部分的时间再输出。
    for (int i = 0; i < 4; i++) {
        fprintf(stderr, "-----\nExecuting algorithm: %s...\n", algorithm_names[i]);
        // 使用 <time.h> 的 clock_t 计时。
        clock_t start = clock();
        Result result = func[i](n);
        clock_t end = clock();
        fprintf(
            stderr,
            "%s spent %lf seconds\n",
            algorithm_names[i],
            (double)(end - start) / CLOCKS_PER_SEC
        );
        // 时间统计完毕，接下来才输出结果，避免输出时间占用计算时间。
        // 标记是否是第一个输出的数。如果不是，则需要输出一个空格再输出数字。这样格式规范一点。
        int first_output = 1;
        for (int i = 1; i <= result.cnt; i++) {
            first_output == 1 ? first_output = 0 : putchar(' ');
            printf("%d", result.primes[i]);
        }
        // puts() 自带换行符。
        puts("");
    }
    return 0;
}
