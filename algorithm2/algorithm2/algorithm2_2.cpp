//程序7-3-矩阵连乘算法和程序7-4-矩阵连乘算法的备忘录方法
#include "iostream"
#include "math.h"
#include "iomanip"    //输出格式头文件 
using namespace std;


//【程序7-3】  矩阵连乘算法
class MatrixChain
{
public:
	MatrixChain(int mSize, int* q);	//创建二维数组m和s，一维数组p，并初始化
	int MChain();						             //一般动态规划法求最优解值
	int LookupChain();		           	//备忘录方法求最优解值（程序7-4）
	void Traceback();			           	//构造最优解的公有函数
	void Output();
private:
	void Traceback(int i, int j);		 //构造最优解的私有递归函数
	int LookupChain(int i, int j);		//备忘录方法私有递归（程序7-4）
	int* p, ** m, ** s, n;
};

MatrixChain::MatrixChain(int mSize, int* q)
{
	n = mSize;
	m = new int* [n];   s = new int* [n];   p = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		m[i] = new int[n];   m[i][i] = 0;
		s[i] = new int[n];   s[i][i] = 0;
		p[i] = q[i];
	}
	p[n] = q[n];
}

int MatrixChain::MChain()
{
	for (int i = 0; i < n; i++)
		m[i][i] = 0;
	for (int r = 2; r <= n; r++) {
		for (int i = 0; i <= n - r; i++) {
			int j = i + r - 1;
			m[i][j] = m[i + 1][j] + p[i] * p[i + 1] * p[j + 1];
			s[i][j] = i;
			for (int k = i + 1; k < j; k++) {
				int t = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
				if (t < m[i][j]) {
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
	}
	return m[0][n - 1];
}

void MatrixChain::Traceback(int i, int j)
{
	if (i == j) {
		cout << "A" << i;
		return;
	}

	if (i < s[i][j]) cout << "(";
	Traceback(i, s[i][j]);
	if (i < s[i][j]) cout << ")";

	if (s[i][j] + 1 < j) cout << "(";
	Traceback(s[i][j] + 1, j);
	if (s[i][j] + 1 < j) cout << ")";

}

void MatrixChain::Traceback()
{
	cout << "(";
	Traceback(0, n - 1);
	cout << ")";
	cout << endl;

}

//【程序7-4】  矩阵连乘的备忘录方法
int MatrixChain::LookupChain(int i, int j)
{
	if (m[i][j] > 0)
		return m[i][j];
	if (i == j)
		return 0;
	int u = LookupChain(i + 1, j) + p[i] * p[i + 1] * p[j + 1];
	s[i][j] = i;
	for (int k = i + 1; k < j; k++) {
		int t = LookupChain(i, k) + LookupChain(k + 1, j) + p[i] * p[k + 1] * p[j + 1];
		if (t < u) {
			u = t;
			s[i][j] = k;
		}

	}
	m[i][j] = u;
	return u;


}

int MatrixChain::LookupChain()
{

	return LookupChain(0, n - 1);
}

void MatrixChain::Output()
{
	int i, j;

	cout << "  m=" << endl;
	cout << "  ";
	for (j = 0; j < n; j++)
		if (j < 2) cout << setw(4) << j;
		else cout << setw(6) << j;
	cout << endl;

	for (i = 0; i < n; i++)
	{
		cout << "  " << i << " ";
		for (j = 0; j < n; j++)
		{
			if (i < j) cout << setw(6) << m[i][j];  //setw(6), 指定输出域宽为6
			else if (i == j) cout << setw(2) << m[i][j];
			else cout << setw(6) << " ";
		}
		cout << endl;
	}

	cout << "  s=" << endl;
	cout << "    ";
	for (j = 0; j < n; j++) cout << j << " ";
	cout << endl;
	for (i = 0; i < n; i++)
	{
		cout << "  " << i << " ";
		for (j = 0; j < n; j++)
		{
			if (i <= j) cout << s[i][j] << " ";
			else cout << "  ";
		}
		cout << endl;
	}
}

//例7-5: 6个矩阵连乘积A0*A1*A2*A3*A4*A5
//       A0:30*35, A1:35*15, A2:15*5, A3:5*10, A4:10:20, A5:20*25
//p={p0,p1,p2,p3,p4,p5,p6}={30,35,15,5,10,20,25}
void main()
{
	int nn = 6, k;
	int pp[7] = { 30,35,15,5,10,20,25 };
	MatrixChain mm(nn, pp);

	cout << endl << "第一种方法（不用备忘录）" << endl;
	k = mm.MChain();    cout << "  最少数乘次数 k=" << k << endl; //最少数乘次数k=15125
	mm.Traceback();                                      //矩阵连乘次序: ( (A0(A1A2)) ((A3A4)A5) )
	cout << endl;
	mm.Output();

	//下面是备忘录方法
	cout << endl << "第二种方法（用备忘录）" << endl;
	MatrixChain a(nn, pp);
	k = a.LookupChain();   cout << "  最少数乘次数 k=" << k << endl;
	a.Traceback();
	cout << endl;
	a.Output();
}


