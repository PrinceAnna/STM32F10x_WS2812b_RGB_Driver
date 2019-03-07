/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WS2812B_H
#define __WS2812B_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Exported types ------------------------------------------------------------*/
typedef struct
{
  u8 R;
  u8 G;
  u8 B;
}RGBColor_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* 16bit RGB TestMode */
#define Pixel_LEN1      24

#define CODE0 0xC0
#define CODE1 0xFC

#define Delay(n)        while((n)--)
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void SPI1_Configuration(void);
void Pixel_Send(RGBColor_TypeDef RGBColor);

/* Basic Color Effects -------------------------------------------------------*/
void RGB_RED(u16 Pixel_LEN);
void RGB_GREEN(u16 Pixel_LEN);
void RGB_BLUE(u16 Pixel_LEN);
void RGB_YELLOW(u16 Pixel_LEN);
void RGB_MAGENTA(u16 Pixel_LEN);
void RGB_BLACK(u16 Pixel_LEN);
void RGB_WHITE(u16 Pixel_LEN);

/* Complicated Color Effects -------------------------------------------------*/
void rainbowCycle(u16 Pixel_LEN);









#endif /* __WS2812B_H */