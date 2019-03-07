# STM32F10x_WS2812b_RGB_Driver
A new way to drive ws281x-controlled rgb-leds but not to tongle gpio with time-delay

Thanks to @j3qq4hch.Your STM8_WS2812B project(https://github.com/j3qq4hch/STM8_WS2812B) shows the basic method of driving some amount of ws2812-controlled egb-leds.The core of the project is to tongle a STM8S's gpio with time delay,and it's in assembler.

But I'm wondering it may not suit any mcu such as stm32 or even STM8L.

And some day I found a new way.

The peripheral I use is the SPI1 in the stm32f103 mcu.

The sending speed of ws2812's data is @ 800Kbps,same as 1.25us/1bit.Data transfer time is TH+TL(=1.25μs±600ns).To drive a ws2812b-controlled rgb-led, it need 24 continuous bits.But every bits only contains alternate code of the two codes--0-code and 1-code.

So I config the SPI1 run @ 9MHz,whitch means 0.89us/8bit@spi.Obviously，it's inside the range of TH+TL.And I use 0xC0(0b11000000) instead of 0-code,0xFC(0b11111100) instead of 1-code as the data in SPI->DR.

Note: rainbowCycle(u16 Pixel_LEN) in the WS2812b.c is similar to @j3qq4hch's.
