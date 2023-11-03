#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

extern uint32_t SystemCoreClock;  //SystemCoreClock de�i�kenini main c de g�r�nt�lemek i�in extern edildi ilk de�er verilmez

uint32_t SystemClock;
void RCC_Config(void){

	// 8 000 000 --> 168 000 000

	RCC->CR &=  ~(1<<0); //HSI KAPANDI
	RCC->CR |= (1<<16); //HSE ACILDI

	while(!(RCC->CR & (1<<17)));  // HSE AKT�F OLMASINI BEKLED�K

	RCC->CR |=(1<<19);
	RCC->PLLCFGR =0x00000000;//PLL_CFGR  Reset
	RCC->PLLCFGR |=(1<<22); //PLL Source HSE AKT�F
	RCC->PLLCFGR |=(4<<0); //PLLM = 4
	RCC->PLLCFGR |=(168<<6); //PLLN =168 DEGERI OLDU

	RCC->CR |=(1<<24); //PLL A�IK
	while(!(RCC->CR & (1<<25))); //PLL Aktif Olmas� Beklenir

	RCC->CFGR &= ~(1<<0);
	RCC->CFGR |= (1<<1); //SYSTEM Clock PLL Secildi
	while(!(RCC->CFGR & (1<<1))); // Pll Clock Secilip Secilmedi�i Beklendi

}

int main(void)
{
	// 8 000 000 --> 168 000 000

    RCC_Config();

    SystemCoreClockUpdate();

    SystemClock=SystemCoreClock;

  while (1)
  {

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
