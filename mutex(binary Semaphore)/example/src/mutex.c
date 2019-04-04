
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/
// Semaphore handler for each color

xSemaphoreHandle Red_led ;

xSemaphoreHandle Blue_led ;

xSemaphoreHandle Green_led;
/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
}

// task to control led
static void vledControl(void *pvParameters)
{


	while (1) {
	xSemaphoreGive(Red_led);
		vTaskDelay(1000);
	xSemaphoreGive(Blue_led);
			vTaskDelay(1000);
	xSemaphoreGive(Green_led);
			vTaskDelay(1000);
	}
}

// task to turn on red led and off others
static void vRedled(void *pvParameters) {


	while (1) {
		if(xSemaphoreTake(Red_led,portMAX_DELAY)){
		Board_LED_Set(Blue,true);
		Board_LED_Set(Green,true);
		Board_LED_Set(Red,false);
		}
	}
}

// task to turn on Blue led and off others
static void vBlueled(void *pvParameters) {

	while (1) {


		if(xSemaphoreTake(Blue_led,portMAX_DELAY)){
		Board_LED_Set(Green,true);
		Board_LED_Set(Red,true);
		Board_LED_Set(Blue,false);}
	}
}

// task to turn on Green led and off others
static void vGreenled(void *pvParameters) {

	while (1) {
		if(xSemaphoreTake(Green_led,portMAX_DELAY)){
		Board_LED_Set(Blue,true);
		Board_LED_Set(Red,true);
		Board_LED_Set(Green,false);}

	}
}



int main(void)
{
	prvSetupHardware();
	vSemaphoreCreateBinary(Red_led);
	vSemaphoreCreateBinary(Blue_led);
	vSemaphoreCreateBinary(Green_led);

	xTaskCreate(vledControl,(signed char*)"led control",configMINIMAL_STACK_SIZE,NULL,1,NULL);

	xTaskCreate(vRedled,(signed char*)"Red led",configMINIMAL_STACK_SIZE,NULL,2,NULL);

	xTaskCreate(vBlueled,(signed char*)" Blue led",configMINIMAL_STACK_SIZE,NULL,2,NULL);
	xTaskCreate(vGreenled,(signed char*)"Green led",configMINIMAL_STACK_SIZE,NULL,2,NULL);


	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}

/**
 * @}
 */
