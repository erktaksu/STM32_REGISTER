#include "stm32f4xx.h"
#include "stm32f4_discovery.h"



void RCC_Config(void){

	// 8 000 000 --> 168 000 000

	RCC->CR &=  ~(1<<0); //HSI KAPANDI
	RCC->CR |= (1<<16); //HSE ACILDI

	while(!(RCC->CR & (1<<17)));  // HSE AKTÝF OLMASINI BEKLEDÝK

	RCC->CR |=(1<<19);
	RCC->PLLCFGR =0x00000000;//PLL_CFGR  Reset
	RCC->PLLCFGR |=(1<<22); //PLL Source HSE AKTÝF
	RCC->PLLCFGR |=(4<<0); //PLLM = 4
	RCC->PLLCFGR |=(168<<6); //PLLN =168 DEGERI OLDU

	RCC->CR |=(1<<24); //PLL AÇIK
	while(!(RCC->CR & (1<<25))); //PLL Aktif Olmasý Beklenir

	RCC->CFGR &= ~(1<<0);
	RCC->CFGR |= (1<<1); //SYSTEM Clock PLL Secildi
	while(!(RCC->CFGR & (1<<1))); // Pll Clock Secilip Secilmediði Beklendi


}

void GPIO_Config(void)
{
	RCC->AHB1ENR |=(1<<3);  //GPIOD AHB1 CLOCK ENABLE

	RCC->AHB1ENR |=(1<<0);  //GPIOA AHB1 CLOCK ENABLE


	GPIOD->MODER |=(1<<24);  //GPIOD 12.Pin Output
	GPIOD->MODER &= ~(1<<25);
	GPIOD->MODER |=(1<<26);  //GPIOD 13.Pin Output
	GPIOD->MODER  &= ~(1<<27);
	GPIOD->MODER |=(1<<28);  //GPIOD 14.Pin Output
	GPIOD->MODER &= ~(1<<29);
	GPIOD->MODER |=(1<<30);  //GPIOD 15.Pin Output
	GPIOD->MODER &= ~(1<<31);


	GPIOA->PUPDR &= ~(1<<0);
	GPIOA->PUPDR |=(1<<1); //A portu için pull down swcilid
	GPIOD->PUPDR= 0x00000000;  //D Portu için no pull seçildi
	GPIOA->OSPEEDR |=(1<<0);
	GPIOA->OSPEEDR |=(1<<1);  //A pini max gücte calýþýr
	GPIOD->OSPEEDR |= 0xFF000000; //D pini max gücte calýþýr

}

void delay(uint32_t time){
	while(time--);
}
uint32_t count;
int main(void)
{
	// 8 000 000 --> 168 000 000

    RCC_Config();
    GPIO_Config();
    SystemCoreClockUpdate();


  while (1)
  {

	  if(GPIOA->IDR & 0x00000001){
		  while(GPIOA->IDR & 0x00000001);
		  delay(18000000);
		  count++;

	  }
	 if(count % 2 ==0){

		 GPIOD->ODR |=(1<<12);
		 GPIOD->ODR |=(1<<13);
		 GPIOD->ODR |=(1<<14);
		 GPIOD->ODR |=(1<<15);

	  }
	 else{
		 GPIOD->ODR &= ~(1<<12);
		 GPIOD->ODR &= ~(1<<13);
		 GPIOD->ODR &= ~(1<<14);
		 GPIOD->ODR &= ~(1<<15);

	 }
 }
}



void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}

