#include "controllerConnection.h"
#include "RFbyteType.h"
#include "KeyConstantDefine.h"
unsigned char TX_ADDRESS[ADDRESS_WEIGHT]  =  {0x34, 0x43, 0x10, 0x10, 0x01}; 
unsigned char tx_buf[PLOAD_WIDTH] = {0};

void setup()
{                                  // 0-1023的变量存进8bit的数组里面溢出了
    pinMode(Potentiometer, INPUT); // 与有无设置电位器input无关，数据溢出导致错误 
    Serial.begin(9600);
    init_io(); // Initialize IO port
    TX_Mode(); // set TX mode
    unsigned char status = SPI_Read(STATUS);
    Serial.print("status = ");     
    lcd.begin(16, 2);
}

void loop()
{
    tx_buf[0] = map(analogRead(Potentiometer), 0, 1023, 0, 255);
    lcd.setCursor(5, 0); lcd.print( float( analogRead(Potentiometer) ), 2);
    int x = analogRead(horizontal);
    int y = analogRead(vertical);
    tx_buf[Up] = 0; tx_buf[Down] = 0; tx_buf[Left] = 0; tx_buf[Right] = 0;
    if ( (x<=503 || x>=513) || (y<=490 || y>=500) )
    {
        if (x >= 550) tx_buf[Up]    = 1;
        if (x <= 490) tx_buf[Down]  = 1;
        if (y <= 475) tx_buf[Left]  = 1; // 以固定好的joystick为标准
        if (y >= 525) tx_buf[Right] = 1;     
    }
            
    unsigned char status = SPI_Read(STATUS); // read register STATUS's value
    if (status & TX_DS)                      // if receive data ready (TX_DS) interrupt
    {
        SPI_RW_Reg(FLUSH_TX, 0);                                  
        SPI_Write_Buf(WR_TX_PLOAD, tx_buf, PLOAD_WIDTH); // write playload to TX_FIFO
    }
    if (status & MAX_RT) //if receive data ready (MAX_RT) interrupt, this is retransmit than  SETUP_RETR                          
    {
        SPI_RW_Reg(FLUSH_TX, 0);
        SPI_Write_Buf(WR_TX_PLOAD, tx_buf, PLOAD_WIDTH); // disable standy-mode
    }
    SPI_RW_Reg(WRITE_REG+STATUS, status); // clear RX_DR or TX_DS or MAX_RT interrupt flag
    delay(100);
}

/**************************************************
 * Description:
 **************************************************/
void init_io()
{
    pinMode(CE, OUTPUT); digitalWrite(CE, LOW); // chip enable
    pinMode(SCK, OUTPUT);
    pinMode(CSN, OUTPUT); digitalWrite(CSN, HIGH); // SPI disable  
    pinMode(MOSI, OUTPUT);
    pinMode(MISO, INPUT);
    pinMode(IRQ, INPUT); digitalWrite(IRQ, LOW);
}
/**************************************************/

/**************************************************
 * Description:
 *   Writes one unsigned char to nRF24L01, and return the unsigned char read
 *   from nRF24L01 during write, according to SPI protocol
 **************************************************/
unsigned char SPI_RW(unsigned char Byte)
{
    unsigned char i;
    for (i=0; i<8; i++) // output 8-bit
    {
        if (Byte & 0x80) //1000 0000 按位与 同1出1，后面七个0可以让被按位与的数后七位清零
        { //不完全等价于if (Byte == 0x80),前者只要byte首位是1其余不管，就得到if (128)，否则都不通过
          //别把按位与和按位异或搞混
            digitalWrite(MOSI, HIGH);
        }
        else
        {
            digitalWrite(MOSI, LOW);
        }
        digitalWrite(SCK, HIGH);
        Byte <<= 1; //shift next bit into MSB.. 左移一位接受新数据
        if (digitalRead(MISO) == HIGH)
        {
            Byte |= 1; //capture(捕获) current MISO bit
        }
        digitalWrite(SCK, LOW);
    }
    return(Byte); // return read unsigned char
}
/**************************************************/

/**************************************************
 * Description:
 *   Writes value 'value' to register 'reg'
/**************************************************/
unsigned char SPI_RW_Reg(unsigned char reg, unsigned char value)
{
    unsigned char status;
    
    digitalWrite(CSN, LOW); // CSN low, init SPI transaction
    status = SPI_RW(reg);   // select register
    SPI_RW(value);          // ..and write value to it..
    digitalWrite(CSN, HIGH); // CSN high again
    
    return(status); // return nRF24L01 status unsigned char
}
/**************************************************/

/**************************************************
 * Description:
 *   Read one unsigned char from nRF24L01 register, 'reg'
/**************************************************/
unsigned char SPI_Read(unsigned char reg)
{
    unsigned char reg_val;
    
    digitalWrite(CSN, LOW); // CSN low, initialize SPI communication...
    SPI_RW(reg);            // Select register to read from..
    reg_val = SPI_RW(0);    // ..then read register value
    digitalWrite(CSN, HIGH); // CSN high, terminate SPI communication
    
    return(reg_val);      // return register value
}
/**************************************************/

/**************************************************
 * Description:
 *   Reads 'unsigned chars' #of unsigned chars from register 'reg'
 *   Typically used to read RX payload, Rx/Tx address
/**************************************************/
unsigned char SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
    unsigned char status, i;
    
    digitalWrite(CSN, LOW);  // Set CSN low, init SPI tranaction
    status = SPI_RW(reg);    // Select register to write to and read status unsigned char
    
    for( i=0; i<bytes; i++)
    {
        pBuf[i] = SPI_RW(0); // Perform SPI_RW to read unsigned char from nRF24L01
    }
    
    digitalWrite(CSN, HIGH); // Set CSN high again
    
    return(status);       // return nRF24L01 status unsigned char
}
/**************************************************/

/**************************************************
 * Description:
 *   Writes contents of buffer '*pBuf' to nRF24L01
 *   Typically used to write TX payload, Rx/Tx address
/**************************************************/
unsigned char SPI_Write_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
    unsigned char status,i;
    
    digitalWrite(CSN, LOW); // Set CSN low, init SPI tranaction
    status = SPI_RW(reg);   // Select register to write to and read status unsigned char
    for (i=0; i<bytes; i++) // then write all unsigned char in buffer(*pBuf)
    {
        SPI_RW(*pBuf++);
    }
    digitalWrite(CSN, HIGH); // Set CSN high again
    return(status);          // return nRF24L01 status unsigned char
}
/**************************************************/

/**************************************************
 * Description:
 *   This function initializes one nRF24L01 device to
 *   TX mode, set TX address, set RX address for auto.ack,
 *   fill TX payload, select RF channel, datarate & TX pwr.
 *   PWR_UP is set, CRC(2 unsigned chars) is enabled, & PRIM:TX.
 * 
 * TODO: 
 *   One high pulse(>10us) on CE will now send this
 *   packet and expext an acknowledgment from the RX device.
 **************************************************/
void TX_Mode(void)
{
    digitalWrite(CE, LOW);
    
    SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, ADDRESS_WEIGHT);    // Writes TX_Address to nRF24L01
    SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, ADDRESS_WEIGHT); // RX_Addr0 same as TX_Adr for Auto.Ack
    
    SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      // Enable Auto.Ack:Pipe0
    SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  // Enable Pipe0
    SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x1a); // 500us + 86us, 10 retrans...
    SPI_RW_Reg(WRITE_REG + RF_CH, 40);        // Select RF channel 40
    SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   // TX_PWR:0dBm, Datarate:2Mbps, LNA:HCURR
    SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);     // Set PWR_UP bit, enable CRC(2 unsigned chars) & Prim:TX. MAX_RT & TX_DS enabled..
    SPI_Write_Buf(WR_TX_PLOAD, tx_buf, PLOAD_WIDTH);
    
    digitalWrite(CE, HIGH);
}

