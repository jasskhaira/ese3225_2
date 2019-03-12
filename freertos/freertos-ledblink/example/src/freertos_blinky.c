
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#define LED0_GPIO_PORT_NUM                      0
#define LED0_GPIO_BIT_NUM                       22
#define LED1_GPIO_PORT_NUM                      3
#define LED1_GPIO_BIT_NUM                       26
#define LED2_GPIO_PORT_NUM                      3
#define LED2_GPIO_BIT_NUM                       25
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
}

/* LED1 toggle thread */
static void vLEDTask1(void *pvParameters) {


	while (1) {
		Chip_GPIO_WriteDirBit(LPC_GPIO, LED2_GPIO_PORT_NUM, LED2_GPIO_BIT_NUM, 0);
		Chip_GPIO_WriteDirBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, 0);
		Chip_GPIO_WriteDirBit(LPC_GPIO, LED0_GPIO_PORT_NUM, LED0_GPIO_BIT_NUM, 1);




		vTaskDelay(configTICK_RATE_HZ /1);

	}
}

/* LED2 toggle thread */
static void vLEDTask2(void *pvParameters) {


	while (1) {
		Chip_GPIO_WriteDirBit(LPC_GPIO, LED2_GPIO_PORT_NUM, LED2_GPIO_BIT_NUM, 0);
		Chip_GPIO_WriteDirBit(LPC_GPIO, LED0_GPIO_PORT_NUM, LED0_GPIO_BIT_NUM, false);
		Chip_GPIO_WriteDirBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, 1);
		vTaskDelay(configTICK_RATE_HZ / 2);
	}
}

static void vLEDTask3(void *pvParameters) {


	while (1) {
		Chip_GPIO_WriteDirBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, 0);
		Chip_GPIO_WriteDirBit(LPC_GPIO, LED0_GPIO_PORT_NUM, LED0_GPIO_BIT_NUM, false);
		Chip_GPIO_WriteDirBit(LPC_GPIO, LED2_GPIO_PORT_NUM, LED2_GPIO_BIT_NUM, 1);
		vTaskDelay(configTICK_RATE_HZ / 4);
	}
}



/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{
	prvSetupHardware();

	/* LED1 toggle thread */
	xTaskCreate(vLEDTask1, (signed char *) "vTaskLed1",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	/* LED2 toggle thread */
	xTaskCreate(vLEDTask2, (signed char *) "vTaskLed2",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2UL),
				(xTaskHandle *) NULL);

	xTaskCreate(vLEDTask3, (signed char *) "vTaskLed2",
					configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 3UL),
					(xTaskHandle *) NULL);


	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}

/**
 * @}
 */
