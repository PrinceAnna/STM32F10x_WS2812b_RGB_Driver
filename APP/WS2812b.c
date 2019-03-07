/* Includes ------------------------------------------------------------------*/
#include "WS2812b.h"
/* Private typedef -----------------------------------------------------------*/
//Seven basic colors
const RGBColor_TypeDef RED      = {255,0,0};
const RGBColor_TypeDef GREEN    = {0,255,0};
const RGBColor_TypeDef BLUE     = {0,0,255};
const RGBColor_TypeDef YELLOW   = {255,255,0};
const RGBColor_TypeDef MAGENTA  = {255,0,255};
const RGBColor_TypeDef BLACK    = {0,0,0};
const RGBColor_TypeDef WHITE    = {255,255,255};
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void SPI1_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
  
  /* PCLK2 = HCLK/2 */
  RCC_PCLK2Config(RCC_HCLK_Div2);
  
  /* Enable peripheral clocks ------------------------------------------------*/
  /* GPIOA,SPI1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);
  
  /* Configure SPI1 pins: SCK, MISO ------------------------------------------*/
  /* Confugure SCK and MOSI pins as Alternate Function Push Pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* SPI1 configuration ------------------------------------------------------*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);

  /* Enable SPI1 CRC calculation */
  SPI_CalculateCRC(SPI1, DISABLE);

  /* Enable SPI1 */
  SPI_Cmd(SPI1, ENABLE);
  
  /* Clear RGB Series */
  RGB_BLACK(Pixel_LEN1);
}

/**
  * @brief  Transmits one bit (for ws2812b) through the SPIx peripheral.
  * @param  Data: where x can be
  *   - 0   CODE0
  *   - >0  CODE1
  * @retval None
  */
void SPI_Send_1bit(volatile u8 Data)
{
  /* Wait for SPI1 Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  
  /* Send SPI1 data */
  SPI_I2S_SendData(SPI1, Data);
  switch(Data)
  {
  case 0:SPI_I2S_SendData(SPI1, CODE0); break;
  default:SPI_I2S_SendData(SPI1, CODE1); break;
  }
}

/**
  * @brief  Configure a color to a RGB pixel.
  * @param  RGBColor_TypeDef: pointer to a RGBColor_TypeDef structure that
  *         contains the color configuration information for the RGB pixel.
  * @retval None
  */
void Pixel_Send( RGBColor_TypeDef RGBColor)
{
  u8 R = RGBColor.R, G = RGBColor.G ,B = RGBColor.B;
  u8 i;
  
  /* Composition of 24bit data: 
    G7 G6 G5 G4 G3 G2 G1 G0 R7 R6 R5 R4 R3 R2 R1 R0 B7 B6 B5 B4 B3 B2 B1 B0 --*/
  /* Follow the order of GRB to sent data and the high bit sent at first. ----*/
  for(i=0;i<8;i++)
    SPI_Send_1bit(G & (1<<(7-i)));
  for(i=0;i<8;i++)
    SPI_Send_1bit(R & (1<<(7-i)));
  for(i=0;i<8;i++)
    SPI_Send_1bit(B & (1<<(7-i)));
}





/* Basic Color Effects -------------------------------------------------------*/
/**
  * @brief  Configure serial RGB pixels to red.
  * @param  Pixel_LEN: the account of RGB pixels in serial
  * @retval None
  */
void RGB_RED(u16 Pixel_LEN)
{
  u8 i;
  for(i=0;i<Pixel_LEN;i++)
    Pixel_Send( RED );
}

/**
  * @brief  Configure serial RGB pixels to green.
  * @param  Pixel_LEN: the account of RGB pixels in serial
  * @retval None
  */
void RGB_GREEN(u16 Pixel_LEN)
{
  u8 i;
  for(i=0;i<Pixel_LEN;i++)
    Pixel_Send( GREEN );
}

/**
  * @brief  Configure serial RGB pixels to blue.
  * @param  Pixel_LEN: the account of RGB pixels in serial
  * @retval None
  */
void RGB_BLUE(u16 Pixel_LEN)
{
  u8 i;
  for(i=0;i<Pixel_LEN;i++)
    Pixel_Send( BLUE );
}

/**
  * @brief  Configure serial RGB pixels to yellow.
  * @param  Pixel_LEN: the account of RGB pixels in serial
  * @retval None
  */
void RGB_YELLOW(u16 Pixel_LEN)
{
  u8 i;
  for(i=0;i<Pixel_LEN;i++)
    Pixel_Send( YELLOW );
}

/**
  * @brief  Configure serial RGB pixels to magenta.
  * @param  Pixel_LEN: the account of RGB pixels in serial
  * @retval None
  */
void RGB_MAGENTA(u16 Pixel_LEN)
{
  u8 i;
  for(i=0;i<Pixel_LEN;i++)
    Pixel_Send( MAGENTA );
}


/**
  * @brief  Configure serial RGB pixels to black/all-off.
  * @param  Pixel_LEN: the account of RGB pixels in serial
  * @retval None
  */
void RGB_BLACK(u16 Pixel_LEN)
{
  u8 i;
  for(i=0;i<Pixel_LEN;i++)
    Pixel_Send( BLACK );
}

/**
  * @brief  Configure serial RGB pixels to white.
  * @param  Pixel_LEN: the account of RGB pixels in serial
  * @retval None
  */
void RGB_WHITE(u16 Pixel_LEN)
{
  u8 i;
  for(i=0;i<Pixel_LEN;i++)
    Pixel_Send( WHITE );  
}




/* Complicated Color Effects -------------------------------------------------*/
RGBColor_TypeDef Colourful_Wheel(u8 WheelPos)
{
  WheelPos = 255 - WheelPos;
  RGBColor_TypeDef color;
  if(WheelPos < 85) 
  {
    color.R = 255 - WheelPos * 3;
    color.G = 0;
    color.B = WheelPos * 3;
  return color;
  }
  if(WheelPos < 170) 
  {
    WheelPos -= 85;
    color.R = 0;
    color.G = WheelPos * 3;
    color.B = 255 - WheelPos * 3;
  return color;
  }
  
  WheelPos -= 170;
  color.R = WheelPos * 3; 
  color.G = 255 - WheelPos * 3;
  color.B = 0;
  
  return color;  
}

void rainbowCycle(u16 Pixel_LEN)  
{
  long int i, j=0;
  volatile u32 wait;
  for( j=0; j<256 * 5; j++)  // 1 cycles of all colors on wheel
  { 
#ifdef MODE_TEST
    DEBUG_LED_ON();
#endif
    for( i=0; i < Pixel_LEN; i++) 
      Pixel_Send( Colourful_Wheel( ( ( i*255/Pixel_LEN ) + j)&255) );
#ifdef MODE_TEST    
    DEBUG_LED_OFF();
#endif
    
    wait = 300000;
    Delay( wait );
  }
}
