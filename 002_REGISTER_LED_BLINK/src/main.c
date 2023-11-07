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

	GPIOD->MODER |=(1<<24);  //GPIOD 12.Pin Output
	GPIOD->MODER &= ~(1<<25);
	GPIOD->MODER |=(1<<26);  //GPIOD 13.Pin Output
	GPIOD->MODER  &= ~(1<<27);
	GPIOD->MODER |=(1<<28);  //GPIOD 14.Pin Output
	GPIOD->MODER &= ~(1<<29);
	GPIOD->MODER |=(1<<30);  //GPIOD 15.Pin Output
	GPIOD->MODER &= ~(1<<31);

	GPIOD->OSPEEDR |= 0xFF000000;

}

int main(void)
{
	// 8 000 000 --> 168 000 000


     RCC_Config();

    SystemCoreClockUpdate();

    GPIO_Config();


  while (1)
  {

	  GPIOD->ODR |=(1<<12);  //12.Pin set

	  GPIOD->ODR |=(1<<13);  //13.Pin set

	  GPIOD->ODR |=(1<<14);  //14.Pin set

	  GPIOD->ODR |=(1<<15);  //15.Pin set

	  for(int i=0; i<1680000; i ++); // bekleme

	  GPIOD ->ODR &= ~(1<<12); //12.Pin reset
	  GPIOD ->ODR &= ~(1<<13); //13.Pin reset
	  GPIOD ->ODR &= ~(1<<14); //14.Pin reset
	  GPIOD ->ODR &= ~(1<<15); //15.Pin reset

	  for(int i=0; i<1680000; i ++); // bekleme


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
