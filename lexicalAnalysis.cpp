// lexicalAnalysis.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<fstream>
using namespace std;

//检查char中是否为空白字符，若是则反复调用getchar直到char中读入一个非空白字符
void getnbc(char c);
//将c连接到token后面
void concat(char* token,char c);
//检测char中字符是否为字母
bool letter(char c);
//检测char中字符是否为数字
bool digit(char c);
//由str查保留字表，若str中字符串为保留字符则返回其类别编码，否则返回值为0
int reserve(string str);
//HASH函数 str转int
constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

int main()
{
    string token = "";
    char ch;
    string str="";
    //读入除取空格符和换行符的字符内容
    ifstream infile;
    infile.open("D:\\textfile.txt", ios::in);    
    if (!infile.is_open()) {
        cout << "文件无法打开！";
        return 1;
    }
    infile >> ch;
    while (!infile.eof()) {
        token = token + ch;
        infile >> ch;
    }
    cout << token << endl;
    infile.close();

    //一个合法词单独一行
    ofstream outfile;
    outfile.open("D:\\newtextfile.txt", ios::out);
    if (!outfile.is_open()) {
        cout << "文件无法打开！";
        return 1;
    }
    
    for (int i=0; i < token.length(); ){
        //数字
        if (digit(token[i])) {
            str = "";                       //初始化str
            while (digit(token[i])) {
                str = str + token[i];
                i++;
            }
            //（2，”main”）
            cout <<"("<<reserve(str)<<","<<"“"<<str <<"”"<<")"<< endl;
            outfile << str + "\n";
        }        
        //标识符
        if (token[i] == '_' || letter(token[i])) { 
            str = "";                       //初始化str
            while (token[i] == '_' || letter(token[i]) || digit(token[i])) {
                str = str + token[i];
                i++;
                if (reserve(str) == 1) {
                    break;
                }
            }
            cout << "(" << reserve(str) << "," << "“" << str << "”" << ")" << endl;
            outfile << str + "\n";
        }
        //符号
        else {
            str = "";
            str = str + token[i];
            i++;
            cout << "(" << reserve(str) << "," << "“" << str << "”" << ")" << endl;
            outfile << str + "\n";
        }
    }


    
    outfile.close();
}

//检查char中是否为空白字符，若是则反复调用getchar直到char中读入一个非空白字符
void getnbc(char* c) {
    
}
//将c连接到token后面
void concat(char* token, char c) {

}
//检测char中字符是否为字母
bool letter(char c) {
    if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z') {
        return true;
    }
    return false;
}
//检测char中字符是否为数字
bool digit(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}
//由str查保留字表，若str中字符串为保留字符则返回其类别编码，否则返回值为0
int reserve(string str) {
    int index = 0;
    const char* c = str.c_str();
    switch (str2int(c))
    {
    //关键字
    case str2int("char"):
    case str2int("int"):
    case str2int("string"):
    case str2int("unsigned"):
    case str2int("return"):
    case str2int("include"):
    case str2int("iostream"):
    case str2int("fstream"):
    case str2int("main"):
        index = 1;
        return index;
        break;
    //界限符
    case str2int("{"):
    case str2int("}"):
    case str2int(";"):
    case str2int("("):
    case str2int(")"):
    case str2int("["):
    case str2int("]"):
    case str2int("#"):
    case str2int("<"):
    case str2int(">"):
    case str2int("\""):
        index = 2;
        return index;
        break;
    //运算符
    case str2int("+"):
    case str2int("-"):
    case str2int("*"):
    case str2int("/"):
    case str2int("%"):
    case str2int("="):
        index = 3;
        return index;
        break;
       
    }
    //数字
    if (digit(str[0])) {
        index = 5;
        return index;
    }
    //标识符 以及 其他
    else {
        int i = 0;
        if (str[0] == '_' || letter(str[0])) {
            i++;
            index = 4;
            for (; i < str.length(); i++) {
                //若不符合标识符规则，则index=0并返回index，若符合标识符规则，则改为或保持index=4
                if (str[i] == '_' || letter(str[i]) || digit(str[i])) {
                    index = 4;
                }
                else {
                    index = 0;
                    return index;
                }
            }
        }
        
    }
    return index;
}

////HASH函数 str转int
//constexpr unsigned int str2int(const char* str, int h = 0)
//{
//    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
//}

