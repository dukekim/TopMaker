/*
 * GPIODigitalOut.h
 *
 *  Created on: Sep 12, 2019
 *      Author: Duke Kim
 *
 *	Easy GPIO Digital Output
 */


#ifndef __GPIO_DIGITAL_OUT_H__
#define __GPIO_DIGITAL_OUT_H__

#include <peripheral_io.h>



class GPIO_Digital_Out {

private:

	peripheral_gpio_h m_hGPIO;

	int	m_nGPIO_PIN;
	int	m_nGPIO_Value;

public:

	/** Create a DigitalOut connected to the specified pin
     *
     *  @param pin DigitalOut pin to connect to
     */

	GPIO_Digital_Out(int pGPIO_PIN, int pINITIALLY_HIGH=0) : m_hGPIO (NULL), m_nGPIO_PIN(-1)
	{
		int ret = PERIPHERAL_ERROR_NONE;

		ret = peripheral_gpio_open(pGPIO_PIN, &m_hGPIO);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(m_hGPIO);

			dlog_print(DLOG_ERROR, LOG_TAG, "%s : %s (%s=>%d)", "peripheral_gpio_open failed.", rindex(__FILE__, '/') + 1, __func__, __LINE__);

			m_nGPIO_PIN = NULL;
			return;
		}

		if( pINITIALLY_HIGH ) {
			ret = peripheral_gpio_set_direction(m_hGPIO, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_HIGH);
		}
		else {
			ret = peripheral_gpio_set_direction(m_hGPIO, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_LOW);
		}


		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(m_hGPIO);

			dlog_print(DLOG_ERROR, LOG_TAG, "%s : %s (%s=>%d)", "peripheral_gpio_set_direction failed.", rindex(__FILE__, '/') + 1, __func__, __LINE__);

			m_nGPIO_PIN = NULL;
			return;
		}

		m_nGPIO_PIN = pGPIO_PIN;
    }


	~GPIO_Digital_Out()
	{
		if (!m_hGPIO) return;

		peripheral_gpio_close(m_hGPIO);

		m_hGPIO		= NULL;
		m_nGPIO_PIN = -1;
	}


    int write(int pValue)
    {
    	int ret 		= PERIPHERAL_ERROR_NONE;

    	if( !m_hGPIO ) {

			dlog_print(DLOG_ERROR, LOG_TAG, "%s : %s (%s=>%d)", "peripheral_write failed.", rindex(__FILE__, '/') + 1, __func__, __LINE__);
    		return -1;
    	}

    	ret = peripheral_gpio_write(m_hGPIO, pValue);

    	if(ret < 0) {

			dlog_print(DLOG_ERROR, LOG_TAG, "%s : %s (%s=>%d)", "peripheral_write failed.", rindex(__FILE__, '/') + 1, __func__, __LINE__);
    		return -1;
    	}

    	m_nGPIO_Value = pValue;

    	return pValue;
    }


    int read()
    {
    	//	peripheral_gpio_read 확인 후 변경 필요
        return m_nGPIO_Value;
    }

    int is_connected()
    {
    	if( m_hGPIO ) {
    		return 1;
    	} else {
    		return 0;
    	}
	 }

    //
    //	Opeator
    //
    GPIO_Digital_Out &operator= (int value)
    {
        write(value);

        return *this;
    }

    //	GPIO_Digital_Out &operator= (GPIO_Digital_Out &rhs);
};


#endif /* __GPIO_DIGITAL_OUT_H__ */
