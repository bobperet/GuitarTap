#ifndef TAP_H
#define TAP_H

#include "inttypes.h"
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace tapNamespace
{
	static const uint16_t LEDpin = GPIO_PIN_1;
}

class Tap
{
public:
	Tap(){};
	~Tap(){};
	static Tap& instance(void);
	void init(I2C_HandleTypeDef i2c1, I2S_HandleTypeDef i2cs1);
	void error(void);
	void accelerometerInit(void);
	void ampInit(void);
	void mainLoop(void);

private:
	static I2C_HandleTypeDef _i2c;
	static I2S_HandleTypeDef _i2s;
};

#ifdef __cplusplus
}
#endif
#endif
