#include "Aip650Driver.h"
#include "hardware/gpio.h"
extern "C"
{
#include "ssd1306.h"
}
unsigned char dig1[11] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x40};
// 0、1、2、3、4、5、6、7、8、9、-//不带小数点

unsigned char dig2[11] = {0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef, 0xc0};
// 0、1、2、3、4、5、6、7、8、9、-//带小数点
extern ssd1306_t disp;

#define NUMBER1 0x34
#define NUMBER2 0x35
#define NUMBER3 0x36
#define NUMBER4 0x37

Aip650::Aip650(){};
Aip650::~Aip650(){};

void Aip650::AipInit(i2c_inst_t *i, uint8_t clk, uint8_t sda, uint8_t add)
{
    i2cInst = i;
    uint8_t startByte = 0x01;
    i2cAddr = add;
    i2c_write_blocking(i2cInst, 0x24, &startByte, 1, 0);
}

void Aip650::WriteValueFloat(float value)
{

    uint8_t CharValue[6] = {0, 0, 0, 0, 0};
    uint8_t LcdString[5] = {0, 0, 0, 0};

    if ((value < -99.9) || (value > 999.9))
    {
        LcdString[0] = 0xbf;
        LcdString[1] = 0xbf;
        LcdString[2] = 0xbf;
        LcdString[3] = 0xbf;
        uint8_t tempByte = LcdString[0];
        i2c_write_blocking(i2cInst, NUMBER1, &tempByte, 1, 0);
        tempByte = LcdString[1];
        i2c_write_blocking(i2cInst, NUMBER2, &tempByte, 1, 0);
        tempByte = LcdString[2];
        i2c_write_blocking(i2cInst, NUMBER3, &tempByte, 1, 0);
        tempByte = LcdString[3];
        i2c_write_blocking(i2cInst, NUMBER4, &tempByte, 1, 0);
        return;
    }

    sprintf((char *)CharValue, "%3.3f", value);
    uint8_t str[20];
    uint8_t index = 0;
    for (int i = 0; i < 6; i++)
    {
        uint8_t data = getIndexFromChar(i, (char *)CharValue);
        LcdString[index] = data;
        if ((uint8_t)data > 0x80)
        {
            i++;
        }
        index++;
    }

    sprintf((char *)str, "%s-%s-%3.1f", CharValue, LcdString, value);
    ssd1306_clear(&disp);
    ssd1306_draw_string(&disp, 0, 0, 1, (char *)str);
    ssd1306_show(&disp);

    uint8_t tempByte = LcdString[0];
    i2c_write_blocking(i2cInst, NUMBER1, &tempByte, 1, 0);
    tempByte = LcdString[1];
    i2c_write_blocking(i2cInst, NUMBER2, &tempByte, 1, 0);
    tempByte = LcdString[2];
    i2c_write_blocking(i2cInst, NUMBER3, &tempByte, 1, 0);
    tempByte = LcdString[3];
    i2c_write_blocking(i2cInst, NUMBER4, &tempByte, 1, 0);
}

uint8_t Aip650::getIndexFromChar(uint8_t index, char x[6])
{
    char c = x[index];
    switch (c)
    {
    case '-':
        return dig1[10];
        break;
    case '0':
        if (x[index + 1] == '.')
            return dig2[0];
        return dig1[0];
        break;
    case '1':
        if (x[index + 1] == '.')
            return dig2[1];
        return dig1[1];
        break;
    case '2':
        if (x[index + 1] == '.')
            return dig2[2];
        return dig1[2];
        break;

    case '3':
        if (x[index + 1] == '.')
            return dig2[3];
        return dig1[3];
        break;

    case '4':
        if (x[index + 1] == '.')
            return dig2[4];
        return dig1[4];
        break;

    case '5':
        if (x[index + 1] == '.')
            return dig2[5];
        return dig1[5];
        break;

    case '6':
        if (x[index + 1] == '.')
            return dig2[6];
        return dig1[6];
        break;

    case '7':
        if (x[index + 1] == '.')
            return dig2[7];
        return dig1[7];
        break;

    case '8':
        if (x[index + 1] == '.')
            return dig2[8];
        return dig1[8];
        break;

    case '9':
        if (x[index + 1] == '.')
            return dig2[9];
        return dig1[9];
        break;
    default:
        break;
    }
    return 0;
}