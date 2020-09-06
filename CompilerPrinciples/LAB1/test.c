int a, b, c;
float m, n;
char fuck;
int test1[2];
int test2[2][3];
struct TS
{

    int t;
    float s;
};
struct TS testStr;

// 斐波拉契
int fibo(int a)
{
    if (a == 1 || a == 2)
        return 1;
    return fibo(a - 1) + fibo(a - 2);
}

/* 主函数*/
int main()
{
    int m, n, i;
    char hello;
    int ar[2][3];
    int onear[2];
    struct TS testTs1;
    a++;
    a--;
    ++b;
    --b;
    m = read();
    hello = 'a';
    ar[0][1] = 1;
    c=ar[1][2];
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
    if(c>0){
        c=1;
    }else{
        c=0;
    }
    i += 1;
    return 1;
}
