#include "carConnection.h"
#include "RFbyteType.h"
#include "KeyConstantDefine.h"
unsigned char TX_ADDRESS[ADDRESS_WEIGHT]  =  {0x34, 0x43, 0x10, 0x10, 0x01}; 
unsigned char rx_buf[PLOAD_WIDTH] = {0};
unsigned char status; 

void setup()
{
    initL298();
    init2401();
    Serial.begin(9600);
    RX_Mode();
    status = SPI_Read(STATUS);
//    Serial.print("status = ");    
//    Serial.println(status, HEX); // read the status register, the default value should be ‘E’
//    Serial.println("*******************RX_Mode Start****************************");
}

void loop()
{
    digitalWrite(L1, LOW); digitalWrite(L2, LOW); digitalWrite(L3, LOW); digitalWrite(L4, LOW);
    digitalWrite(R1, LOW); digitalWrite(R2, LOW); digitalWrite(R3, LOW); digitalWrite(R4, LOW);
    status = SPI_Read(STATUS); // read register STATUS's value
    if (status & RX_DR) // if receive data ready (TX_DS) interrupt
    {
        SPI_Read_Buf(RD_RX_PLOAD, rx_buf, PLOAD_WIDTH); // read playload to rx_buf
        SPI_RW_Reg(FLUSH_RX, 0); // clear RX_FIFO
//        for (int i=0; i<PLOAD_WIDTH; i++)
//        {
//            Serial.print("   ");
//            Serial.print(rx_buf[i], DEC);
//        }
//        Serial.println(" ");

        analogWrite(PWM, rx_buf[0]);
        if (0 <= rx_buf[0] && rx_buf[0] <= 63)
            Serial.write('b');
        if (64 <= rx_buf[0] && rx_buf[0] <= 127)
            Serial.write('g');
        if (128 <= rx_buf[0] && rx_buf[0] <= 191)
            Serial.write('y');
        if (192 <= rx_buf[0] && rx_buf[0] <= 255)
            Serial.write('r');
        digitalWrite(L1, HIGH); digitalWrite(L3, HIGH);
        digitalWrite(R1, HIGH); digitalWrite(R3, HIGH);
        if (rx_buf[Down] == 1)
        {
            digitalWrite(L2, HIGH); digitalWrite(L4, HIGH);
            digitalWrite(R2, HIGH); digitalWrite(R4, HIGH);
        }
        if (rx_buf[Left] == 1) // 左转右边正转，左边反转
        {
            digitalWrite(L2, HIGH); digitalWrite(L4, HIGH);
            digitalWrite(R1, HIGH); digitalWrite(R3, HIGH);

        }
        if (rx_buf[Right] == 1)
        {
            digitalWrite(R2, HIGH); digitalWrite(R4, HIGH);
            digitalWrite(L1, HIGH); digitalWrite(L3, HIGH);
        }
    }
    SPI_RW_Reg(WRITE_REG+STATUS, status); 
    delay(100);
}

/**************************************************
 * Description:
 *   init all pin connected to 2401 
 **************************************************/
void init2401()
{
    pinMode(CE, OUTPUT); digitalWrite(CE, LOW); // chip enable
    pinMode(SCK, OUTPUT);
    pinMode(CSN, OUTPUT); digitalWrite(CSN, HIGH); // SPI disable  
    pinMode(MOSI, OUTPUT);
    pinMode(MISO, INPUT);
}
/**************************************************/

/**************************************************
 * Description:
 *   init two L298Ns' all logic pin and EN pin 
 **************************************************/
void initL298()
{
    pinMode(PWM, OUTPUT); analogWrite(PWM, 255);
    pinMode(L1, OUTPUT); pinMode(L2, OUTPUT);
    pinMode(L3, OUTPUT); pinMode(L4, OUTPUT);
    pinMode(R1, OUTPUT); pinMode(R2, OUTPUT);
    pinMode(R3, OUTPUT); pinMode(R4, OUTPUT);
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
        if (Byte & 0x80) // 1000 0000 按位与 同1出1，后面七个0可以让被按位与的数后七位清零
        { // 不完全等价于if (Byte == 0x80),前者只要byte首位是1其余不管，就得到if (128)，否则都不通过
          // 别把按位与和按位异或搞混
            digitalWrite(MOSI, HIGH);
        }
        else
        {
            digitalWrite(MOSI, LOW);
        }
        digitalWrite(SCK, HIGH);
        Byte <<= 1; // shift next bit into MSB.. 左移一位接受新数据
        if (digitalRead(MISO) == HIGH)
        {
            Byte |= 1; // capture(捕获) current MISO bit
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
    
    digitalWrite(CSN, LOW);  // CSN low, init SPI transaction
    status = SPI_RW(reg);    // select register
    SPI_RW(value);           // ..and write value to it..
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
    
    digitalWrite(CSN, LOW);  // CSN low, initialize SPI communication...
    SPI_RW(reg);             // Select register to read from..
    reg_val = SPI_RW(0);     // ..then read register value
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
    unsigned char status,i;
    
    digitalWrite(CSN, LOW); // Set CSN low, init SPI tranaction
    status = SPI_RW(reg);   // Select register to write to and read status unsigned char
    
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
    
    digitalWrite(CSN, LOW);  // Set CSN low, init SPI tranaction
    status = SPI_RW(reg);    // Select register to write to and read status unsigned char
    for (i=0; i<bytes; i++)  // then write all unsigned char in buffer(*pBuf)
    {
        SPI_RW(*pBuf++);
    }
    digitalWrite(CSN, HIGH); // Set CSN high again
    return(status);          // return nRF24L01 status unsigned char
}
/**************************************************/

/**************************************************
 * Description:
 * This function initializes one nRF24L01 device to
 * RX Mode, set RX address, writes RX payload width,
 * select RF channel, datarate & LNA HCURR.
 * After init, CE is toggled high, which means that
 * this device is now ready to receive a datapacket.
/**************************************************/
void RX_Mode()
{
    digitalWrite(CE, LOW);
    SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, ADDRESS_WEIGHT); // Use the same address on the RX device as the TX device
    SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      // Enable Auto.Ack:Pipe0
    SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  // Enable Pipe0
    SPI_RW_Reg(WRITE_REG + RF_CH, 40);        // Select RF channel 40
    SPI_RW_Reg(WRITE_REG + RX_PW_P0, PLOAD_WIDTH); // Select same RX payload width as TX Payload width
    SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   // TX_PWR:0dBm, Datarate:2Mbps, LNA:HCURR
    SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);     // Set PWR_UP bit, enable CRC(2 unsigned chars) & Prim:RX. RX_DR enabled..
    digitalWrite(CE, HIGH);                   // Set CE pin high to enable RX device
    //  This device is now ready to receive one packet of 16 unsigned chars payload from a TX device sending to address
    //  '3443101001', with auto acknowledgment, retransmit count of 10, RF channel 40 and datarate = 2Mbps.
}
/**************************************************/

