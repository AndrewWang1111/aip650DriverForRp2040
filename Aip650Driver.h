#include <stdio.h>
#include <hardware/i2c.h>

class Aip650
{

public:
    Aip650();
    ~Aip650();
    void AipInit(i2c_inst_t *i, uint8_t clk, uint8_t sda, uint8_t addr);
    void WriteValueFloat(float value);
    void WriteValueInt(uint8_t add, uint8_t value);

private:
    uint8_t i2cAddr = 0x0;
    i2c_inst_t *i2cInst;
    uint8_t getIndexFromChar(uint8_t c, char x[6]);
};