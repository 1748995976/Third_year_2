int a, b, c;
int d[2][5];
float m, n;
char fuck;
struct TS
{
    int t;
    float s;
} testTs2;

// 斐波拉契
int fibo(int a)
{
    int ac[2][8];
    if (a == 1 || a == 2)
        return 1;
    return fibo(a - 1) + fibo(a - 2);
}

/* 主函数 */
int main()
{
    int m, n, i;
    char hello;
    int ar[2][3][6];
    struct TS testTs1[5];
    string hello2;

    m = read();
    hello = 'a';
    hello2 = "dasfa";
    ar[0][1][5] = 1;
    i = 1;
    testTs1.t = 1;

    while (i <= m)
    {
        n = fibo(i);
        write(n);
        i++;
    }

    for (i = 1; i <= m; i = i + 1)
    {
        i = i + 1;
    }
    i += 1;

    return 1;
}
