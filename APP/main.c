/**
  ******************************************************************************
  * @file    APP/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    19-December-2018
  * @brief   Main program body
  *****************************************************************************/  

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */
  
  SPI1_Configuration();
  
  /* Infinite loop */
  while (1)
  {
    rainbowCycle(Pixel_LEN1);
  }
}
