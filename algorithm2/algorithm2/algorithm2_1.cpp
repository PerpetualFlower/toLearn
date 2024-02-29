//习题7-10-用备忘录算法求LCS
//备忘录方法是动态规划法的一个变种，它采用分治法思想，自顶向下直接递 归 求最优解。
//但与分治法不同的是，备忘录方法为每个已经计算的子问题建立备忘录，即保存子问题的计
//算结果以备需要时引用，从而避免子问题的重复求解。
//试改写当前程序的int LCS::LCSLength()函数，用备忘录方法来求解最长公共子序列。
//提示：备忘录方法采用的是递归求解方式，因此需要用一个公有成员函数int LCSLength()
//来调用私有递归成员函数int LCSLength(int i,int j); 共同实现。
#include <iostream>
#include <math.h>
using namespace std;

class LCS
{
public:
    LCS(int nx, int ny, char* a, char* b);
    ~LCS();
    int LCSLength();                 //求c和s数组，返回LCS的长度
    int LCSLength_Memo();            //备忘录算法求c和s数组，返回LCS长度，非递归函数
    void CLCS();                     //构造LCS，非递归

private:
    int LCSLength_Memo(int i, int j); //备忘录算法求c和s数组，返回LCS长度，递归函数
    void CLCS(int i, int j);         //构造LCS，递归
    int** c, ** s, m, n;              // 算法中的二维数组c，二维数组s，字符串 x 和 y 的长度
    char* x, * y;                     // 要求最大公共子串的两个字符串 x 和 y
};

///// <summary>
///// 构造函数
///// 初始化两个字符串的长度，地址；为c数组和s数组申请堆内存
///// </summary>
///// <param name="nx">字符串 x 的长度</param>
///// <param name="ny">字符串 y 的长度</param>
///// <param name="a">字符串 x 的地址</param>
///// <param name="b">字符串 y 的地址</param>
LCS::LCS(int nx, int ny, char* a, char* b)
{
    m = nx;    n = ny;
    x = a;     y = b;
    c = new int* [m + 1];   s = new int* [m + 1];
    for (int i = 0; i <= m; i++)
    {
        c[i] = new int[n + 1];
        s[i] = new int[n + 1];
    }
    //初始化第一个
    c[0][0] = 0;
}

///// <summary>
///// 析构函数
///// 释放c数组和s数组的内存
///// </summary>
LCS::~LCS()
{
    /*for (int i = 0; i <= m; i++)
    {
        delete[] c[i];
        delete[] s[i];
    }*/

    //cout << c;

    delete[]c;
    delete[]s;
}

///// <summary>
///// 求c和s数组，返回LCS的长度
///// 算法描述：
///// 1、初始化c数组：将c数组第0行和第0列除去c[0][0]赋初值0
///// 2、计算c数组：
/////   2.1：如果x[i] == y[j]，c[i][j] 等于其左上角的格子c[i-1][j-1]加1，s[i][j] = 1
/////   2.2：否则，c[i][j] = Max{ c[i-1][j], c[i][j-1] } ,
/////        即c[i][j]等于其左边和上边中值较大的那一个。
/////        如果上边大，s[i][j] = 2；
/////        否则左边大，s[i][j] = 3；
///// 3、返回c数组最后一个元素的值c[m][n]，即公共子序列的长度
///// </summary>
///// <returns></returns>
int LCS::LCSLength()
{
    for (int i = 1; i <= m; i++)
        c[i][0] = 0;
    for (int j = 1; j <= n; j++)
        c[0][j] = 0;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (x[i] == y[j])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                s[i][j] = 1;
            }
            else if (c[i - 1][j] >= c[i][j - 1])
            {
                c[i][j] = c[i - 1][j];
                s[i][j] = 2;
            }
            else
            {
                c[i][j] = c[i][j - 1];
                s[i][j] = 3;
            }
        }
    }
    return c[m][n];

}

///// <summary>
///// 调用递归的重载函数 CLCS(int, int)
///// </summary>
void LCS::CLCS()                     //构造LCS，非递归
{
    CLCS(m, n);
}

///// <summary>
///// 输出最大公共子序列
///// 算法分析：
///// 1、从 s 数组最后一格开始，按照向上或左上的方向查看s数组
///// 2、如果s[i][j] = 1，则输出x[i]，并向左上方向移动
///// 3、如果s[i][j] = 2，则往上移动
///// 4、如果s[i][j] = 3，则往左移动
///// 5、直到i == 0 || j == 0 END
///// </summary>
///// <param name="i"></param>
///// <param name="j"></param>
void LCS::CLCS(int i, int j)          //构造LCS，递归
{
    if (i == 0 || j == 0)
        return;
    if (s[i][j] == 1) {
        CLCS(i - 1, j - 1);
        cout << x[i];
    }
    else if (s[i][j] == 2)
        CLCS(i - 1, j);
    else
        CLCS(i, j - 1);


}                                     //O(m+n)

//备忘录算法求c和s数组，返回LCS长度
int LCS::LCSLength_Memo()
{

    memset(c, INT_MAX, sizeof(c));
    return LCSLength_Memo(m, n);
}

///// <summary>
///// 求解最大公共子序列的备忘录算法
///// </summary>
///// <param name="i"></param>
///// <param name="j"></param>
///// <returns></returns>
int LCS::LCSLength_Memo(int i, int j)
{

    if (c[i][j] < INT_MAX)
        return c[i][j];

    if ((i == 0) || (j == 0))
        c[i][j] = 0;
    else if (x[i - 1] == y[j - 1])
        c[i][j] = LCSLength_Memo(i - 1, j - 1) + 1;
    else
    {
        int p = LCSLength_Memo(i - 1, j);
        int q = LCSLength_Memo(i, j - 1);
        if (p >= q)
            c[i][j] = p;
        else
            c[i][j] = q;
    }

    return c[i][j];

}


void main()
{
    int nx = 7, ny = 6, len1, len2;
    char x[] = "0abcbdab", y[] = "0bdcaba";

    LCS LL(nx, ny, x, y);

    cout << "x[]=\"0abcbdab\"; y[]=\"0bdcaba\"" << endl << endl;
    cout << "1. 方法一（不用备忘录）:" << endl;
    len1 = LL.LCSLength();                      //长度为4
    cout << "   LCS的长度=" << len1 << endl << endl;

    cout << "2. 方法二（用备忘录）:" << endl;
    len2 = LL.LCSLength_Memo();                 //长度为4
    cout << "   LCS的长度=" << len2 << endl << endl;
    cout << "3. LCS=\"";                        //LCS="bcba"
    LL.CLCS();
    cout << "\"" << endl;
}



