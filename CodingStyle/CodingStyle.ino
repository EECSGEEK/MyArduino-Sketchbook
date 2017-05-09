/* ★Arduino代码规范★ */
#if 0 //这种屏蔽代码的方法确实好用
主要参考 D:\编程规范\编程规范.txt
1-5的补充规则
3>注释>3.4 
    利用ArduinoIDE"//"比"/**/"深色
    进行重点内容的注释
//额外规则
#define 项目 超过400行的.ino文件
文件保存
    保存到默认路径
    C:\Users\76320\Documents\Arduino
    这样你就能在File->Sketchbook里面
    收藏了你写过的所有Arduino程序
    //个人程序本+样例程序本+网上别人的程序本
    //等于无穷无尽的优质资源
    //这也是开源的魅力
    
    ★一个项目程序文件夹必须【包含电路图】★
    
命名
    文件名的命名
        首要规则：
            文件名尽可能短，只写核心模块名称

        一个项目文件命名示例
        示例1： AngleSenor.ino
          评1： 两个单词合起来指的是一个东西
                两个单词的首字母大写中间不要下划线
        示例2： Keypad-1602
          评2： 两个模块为核心的程序
                "-"表示连接，加的意思

        一个元器件的程序，
        可以无缝加到任何项目里面的代码
        一个项目的最小单位
        所以它的命名应该全小写//但是LM35这种模块必须大写才能好认
        示例3： button(最好在项目文件夹配上图片)

    常量的命名
        引脚名第一个字母大写，其余小写，
        但是四个字母以内的名字全大写
        示例4： const int LED = 13;
        示例5： const int Accept = 5;

        常量名全大写以下划线区分单词
        示例6： #define MAX_ANTICLOCKWISE 297

        但是有些严格规定数据类型的变量也用const
        这样的奇葩首字母小写其余全大写
        示例7： const long iNTERVAL = 1000;
        本来Arduino的const就是只给引脚变量用

    变量的命令
        arduino基本只用全局变量
        变量命名参考《编程规范》

        穿插知识点：
        Arduino对【没有初始化的变量会默认赋值-1】
        但是char类型范围是0-127，所以char会向下溢出

    函数的命名
        没有体现类与对象的函数的函数
        首字母大写，下划线连接

        类似analogWrite的函数
        建议加入规范，
        两个单词命名的函数/标识符，
        体现首单词是个类，第二个单词是类中的一个成员
        次单词包含于首单词中，次要单词是直接显示功能价值的
        所以次单词的首字幕应该大写
        比如analogRead中的重点是Read，它属于analog类中
        除了首单词的首字母不大写
        示例8： void numberDisplay(int number) 
                //首单词不大写的话突出显示Display意思

缩进：
    if (1 == mode)
    在loop中应当向左顶格

★干扰问题
    <1> Arduino引脚13预外接一个LED，不建议使用 INPUT_PULLUP
        禁止 pinMode(13, INPUT_PULLUP);
    <2> 上传程序时拔去0和1两脚的硬件连接线，以免上传失败
★优化代码★
    [★]尽可能减少looptime
        如果你走一遍loop要几十毫秒那就太慢了
    [1] 检测按键的函数不应该放在loop里
        好比看一页书就看一下手机，
        这样效率太低了，用中断检测更好
    [2] 中断里的语句尽可能少，保留实时采集显示
        甚至可以不保留实时角度采集显示
        中断时间越短对时钟影响越小
    [3] 减少程序行数，精简程序
        把重复代码提炼成函数 
        loop里面尽可能简单
    
#endif//因为它很好地避免了注释嵌套

#if 0
___________________________
程序结构(自上而下)
[0]版权信息
/***********************************************************
  Copyright (C) TUTE 1979-2016. All rights reserved.   
  Department：Institute of Electronic Engineering 
  Author: Wu Aoxiang    ID：09970150226 
  
  File Name:   C、C++结构.txt  File folder:      D:\编程规范  
  Description: C/C++结构       Description File: functions' call.xls
  Calls Files:                 Called By:        编程规范.txt
          
  History:       
    <Date>        <Author>   <Version>    <Modification>
  2016-4-27     Wu Aoxiang    1.0        Fix a bug  
  2016-11-28    Wu Aoxiang    1.1        Add a function
************************************************************/
[1]/* ★'程序的中文名'★ */
   //默认的开发板是UNO，如果用2560或者Due的话在这里声明一下

[2]定义 头文件/库 的变量，配置

[3]//硬件连接与IO分配
const int LED = 13;

[4]//全局变量的定义
bool STATE = LOW;

[5]void setup()

[6]void loop()

[7]函数定义,Arduino不需要函数声明

[8]//注释目录
#endif
/* ArduinoIDE热键shortcut */
/* 
 * [1] 先Ctrl+F锁定关键词
 *     然后通过Ctrl+G查找下一个
 *     Ctrl+Shift+G查找上一个
 * [2] Ctrl+/ 快速单行注释
 * [3] Ctrl+Shift+L = ???
 * [4] Ctrl+L 跳到指定行
 */
void setup() 
{
    pinMode(6, OUTPUT);
    bool STATE = LOW;
}

void loop() 
{
}

