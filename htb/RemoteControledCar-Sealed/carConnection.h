#ifndef carConnection_h 
#define carConnection_h 
/////////////////////////↓无线模块2401的硬件连接↓////////////////////////
//注意2401模块的VCC接的是Arduino的3.3V，该模块逻辑电平是3.3V
#define CE   9  // Chip Enable In, Activates RX or TX mode
#define CSN  10 // SPI Chip Select In
#define SCK  11 // SPI clock In
#define MOSI 12 // SPI Slave Data Input
#define MISO 13 // SPI Slave Data Output, with tri-state option, module->Arduino
/////////////////////////↑无线模块2401的硬件连接↑////////////////////////

/////////////////////////↓L298N电机驱动的硬件连接↓///////////////////////
#define PWM 6
#define L4 16 // A2
#define L3 17 // A3
#define L2 18 // A4
#define L1 19 // A5
#define R1 14 // A0
#define R2 15 // A1
#define R3 7
#define R4 8
/////////////////////////↑L298N电机驱动的硬件连接↑////////////////////////
#endif
