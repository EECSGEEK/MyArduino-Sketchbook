//硬件连接和I/O分配的定义 --- 引脚常量的定义
//对于一个大程序而言,我们可能要定义很多常量( 不管是放在源文件还是头文件 )
//所以很有必要需要用头文件定义一些常量，使得源程序更精炼，可读性更高
//也是为了安全性，防止被人/用户乱改源程序中的重要变量

#ifndef HardwareConnection_h //标识可以是自由命名的，但每个头文件的这个“标识”都应该是唯一的
#define HardwareConnection_h //标识的命名规则一般是头文件名全大写，前后加下划线
                             //windows里面有个头文件的定义前后加了两个下划线，为了唯一表示
/*  >如果HardwareConnection.h头文件没被包含，那就包含这个头文件并且一直预编译到下一个#endif
 *  >if not define通常和define连着一起用
 *  >如果预编译时没有
 *  >示例
    #ifndef x //先测试x是否被宏定义过
    #define x
    程序段1 //如果x没有被宏定义过，定义x，并编译程序段 1
    #else
    程序段2 //如果x已经定义过了则编译程序段2的语句，“忽视”程序段 1。
    #endif//终止if
 *  >为什么需要#ifndef
    防止头文件被多次include，从而节省预编译时间，提高效率
    主要用于避免重复包含宏，避免变量重复定义的错误
    一般.h文件里【最外层】的  //最外层这个措辞真美 
    #if !defined XXX_XXX 
    #define XXX_XXX 
    #endif 
    是为了防止这个.h头文件被重复include
*/
//-----------------------------------------------------------------
/////////////////////////↓无线模块2401的硬件连接↓////////////////////////
//注意2401模块的VCC接的是Arduino的3.3V，该模块逻辑电平是3.3V
//Arduino Digital Output to Module
#define CE       8  //Chip Enable In, Activates RX or TX mode
#define CSN      9  //SPI Chip Select In
#define SCK      10 //SPI clock In
#define MOSI     11 //SPI Slave Data Input
//Arduino Digital Input from Module
#define MISO     12 //SPI Slave Data Output, with tri-state option, module->Arduino
#define IRQ      13 //Interrupt output, module->Arduino
////////////////////////↑无线模块2401的硬件连接↑////////////////////////

#define Potentiometer A0

//-----------------------------------------------------------------
#define Up    1
#define Down  2
#define Left  3 
#define Right 4
//-----------------------------------------------------------------
#define vertical A1   //connect to Joystick.VRY
#define horizontal A2 //connect to Joystick.VRX

/////////////////////////↓LCD1602的硬件连接↓////////////////////////
#include <LiquidCrystal.h>
#define RS 7
#define E  6
#define D4 5
#define D5 4
#define D6 3
#define D7 2
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

#endif
