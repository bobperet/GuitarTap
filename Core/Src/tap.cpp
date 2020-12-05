#include "tap.h"
#include "stm32f4xx_hal.h"
#include "sound.h"

// static class variables
I2C_HandleTypeDef Tap::_i2c;
I2S_HandleTypeDef Tap::_i2s;

/**
 * instance()
 */
Tap& Tap::instance(void)
{
	static Tap instance;
	return(instance);
}

/**
 * init()
 * @param i2c1 - Pointer to i2c object
 * @param i2s1 - Pointer to i2s object
 */
void Tap::init(I2C_HandleTypeDef i2c1, I2S_HandleTypeDef i2s2)
{
	_i2c = i2c1;
	_i2s = i2s2;
	Tap::instance().accelerometerInit();
	Tap::mainLoop();
}

/**
 * mainLoop
 */
void Tap::mainLoop(void)
{
	// blink LED
	HAL_GPIO_TogglePin(GPIOC, tapNamespace::LEDpin);// arduino notation: D13
	HAL_Delay(500);
	HAL_GPIO_TogglePin(GPIOC, tapNamespace::LEDpin);
	HAL_Delay(500);

	HAL_I2S_Transmit(&_i2s, sndData, SoundDataSize, 10);
	while(1)
	{
	}

}

/**
 * accelerometer Init
 * LSM6DSOX
 *
 */
void Tap::accelerometerInit(void)
{
	uint8_t buf[16];
	HAL_StatusTypeDef retVal;
	retVal = HAL_I2C_Master_Transmit(&_i2c, 0xD4, buf, 1, HAL_MAX_DELAY);//d4
	if (retVal != HAL_OK)
	{
		error();
	}
}

/**
 * amp init
 * MAX98357
 *
 */
void Tap::ampInit(void)
{
}

/**
 * error()
 * blinks the LED 100ms on, 100ms off
 *
 */
void Tap::error(void)
{
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOC, tapNamespace::LEDpin);
		HAL_Delay(100);
	}
}

/**
 * C interface to init()
 *
 */
#ifdef __cplusplus
extern "C" {
#endif

void init(I2C_HandleTypeDef i2c1, I2S_HandleTypeDef i2s2)
{
	Tap::instance().init(i2c1, i2s2);
}
#ifdef __cplusplus
}
#endif
