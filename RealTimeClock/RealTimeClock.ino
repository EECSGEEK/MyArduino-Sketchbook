//标准预定义宏 Standard Predefined Macros
//最近一次烧录时间：  __TIME__
//最近一次烧录日期：  __DATA__
//程序文件路径： __FILE__
//当前程序指针指到程序文件第几行： __LINE__
//当前程序指针指到哪一个函数： __func__
/* 补充看似没用的__LINE__的用法
fprintf（stderr，“Internal error：”
                 “负字符串长度”
                 “％d at％s，行％d”，
         长度，__FILE__，__LINE__）; //用于检测哪行出错
*/
uint8_t conv2d(const char* p) //所有的RTC时钟库都是这么写 
{
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9') //防止指针指向冒号或者越界访问内存
        v = *p - '0'; //相对ASCII差值才是真实的单位元十进制值
    return 10 * v + *++p - '0';
} //即便等效于uint8_t conv2d(const char* p){return 10*(*p-'0')+*++p - '0'} ,也要写成前者
//浪费存储空间的等效2 const char temp[16] = __TIME__; uint8_t hour = uint8_t(temp[0]- '0')*10+uint8_t(temp[1]- '0');
uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__ + 3), ss = conv2d(__TIME__ + 6); // Get H, M, S from compile time

byte oldmm = 99, oldss = 99; //保存旧的分秒数据，防止进位时屏幕没法显示
void setup() 
{
    Serial.begin(9600);

}

void loop() 
{
    
}
