# STM32F10x_WS2812b_RGB_Driver
A new way to drive ws281x-controlled rgb-leds but not to tongle gpio with time-delay

Thanks to @j3qq4hch.Your STM8_WS2812B project(https://github.com/j3qq4hch/STM8_WS2812B) shows the basic method of driving some amount of ws2812-controlled egb-leds.The core of the project is to tongle a STM8S's gpio with time delay,and it's in assembler.
But I'm wondering it may not suit any mcu such as stm32 or even STM8L.
And someday I found a new way.

The peripheral I use is the SPI1 in the stm32f103 mcu.

The sending speed of ws2812's data is @ 800Kbps,same as 1.25us/1bit.
To drive a ws2812b-controlled rgb-led, it need 24 continuous bits.But every bits only contains either of the two codes--0-code and 1-code.


Data transfer time( TH+TL=1.25μs±600ns)  very inpotrant
T0H       0 code ,high voltage time       0.35us      ±150ns
T0L       0 code , low voltage time       0.8us       ±150ns
T1H       1 code ,high voltage time       0.7us       ±150ns
T1L       1 code ,low voltage time        0.6us       ±150ns
RES       low voltage time                Above 50μ

So I config the SPI1 run @ 9MHz,whitch means 0.89us/8bit@spi.Obviously，it's in the range of TH+TL.
And I use 0xC0(0b11000000) instead of 0-code,0xFC(0b11111100) instead of 1-code.

Note: rainbowCycle(u16 Pixel_LEN) in the WS2812b.c is similar to @j3qq4hch's.
