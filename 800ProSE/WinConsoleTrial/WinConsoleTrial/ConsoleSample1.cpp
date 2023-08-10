﻿//c/c++ console(控制台)编程详解
// 控制台文本窗口的控制是基于win32 api(win32 api可理解为微软给我们提供的一系列函数的集合)实现的;
//https://www.cnblogs.com/flowingwind/p/8159035.html

//例：设置文本属性（文本颜色、移动控制）

#include <iostream>
#include <windows.h>
using namespace std;
int main()
{
    /*设置文本属
    BOOL SetConsoleTextAttribute(HANDLE hConsoleOutput, WORD wAttributes);//句柄, 文本属性*/

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
    WORD wr1 = 0xfa;//定义颜色属性；第一位为背景色，第二位为前景色
    SetConsoleTextAttribute(hOut, wr1);
    cout << "hello world!" << endl;

    WORD wr2 = FOREGROUND_RED | FOREGROUND_INTENSITY;//方法二用系统宏定义颜色属性
    SetConsoleTextAttribute(hOut, wr2);
    cout << "hello world!" << endl;

    /*移动文本位置位置
    BOOL ScrollConsoleScreenBuffer(HANDLE hConsoleOutput, CONST SMALL_RECT* lpScrollRectangle, CONST SMALL_RECT* lpClipRectangle,
                                   COORD dwDestinationOrigin,CONST CHAR_INFO* lpFill);
                                  // 句柄// 裁剪区域// 目标区域 // 新的位置// 填充字符*/
                                  //输出文本
    SetConsoleTextAttribute(hOut, 0x0f);
    cout << "01010101010101010101010101010" << endl;
    cout << "23232323232323232323232323232" << endl;
    cout << "45454545454545454545454545454" << endl;
    cout << "67676767676767676767676767676" << endl;

    SMALL_RECT CutScr = { 1, 2, 10, 4 }; //裁剪区域与目标区域的集合行成剪切区域
    SMALL_RECT PasScr = { 7, 2, 11, 9 }; //可以是NULL，即全区域
    COORD pos = { 1, 8 };     //起点坐标，与裁剪区域长宽构成的区域再与目标区域的集合为粘贴区

    //定义填充字符的各个参数及属性
    SetConsoleTextAttribute(hOut, 0x1);
    CONSOLE_SCREEN_BUFFER_INFO Intsrc;
    GetConsoleScreenBufferInfo(hOut, &Intsrc);
    CHAR_INFO chFill = { 'A',  Intsrc.wAttributes }; //定义剪切区域填充字符
    string inp;
    cout << "Press any key to move texts:";
    cin >> inp;
    ScrollConsoleScreenBuffer(hOut, &CutScr, &PasScr, pos, &chFill); //移动文本

    CloseHandle(hOut); // 关闭标准输出设备句柄
    return 0;
}