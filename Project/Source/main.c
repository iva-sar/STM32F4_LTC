#include "main.h"
#define PRINTF(a, b) {char string[100]; sprintf(string, a, b); int i; for(i=0; i<strlen(b); ++i){ USART1_SendChar(string[i]); }};

int main()
{
	gpio_init();
	USART1_Init();
	timer2_init ();
	LTC2440_GPIO_init();

	char polje[32];
	uint8_t i;
	char XX=2;
  double ad;
  char f;
  float a,b;
  double aa,bb;


 while(1){

		ad=Read_LTC2440(SDI);
	  aa=(ad&0X1FFFFFFF);
		// a = aa<<2;
    //bb=aa/256;
    //a= ((XX-1)*a)/XX+(bb)/XX;
		a=(4.68/2.0)*aa/268435456.0; //2^28

		sprintf((char *)polje, "%3.9lf\n",a);

		for (i=0; i<strlen(polje); i++)
			gpio_led_state(LED3_ORANGE_ID, 1);
			USART1_SendChar(polje[i]);
		//USART1_SendChar(0x0D);
		timer2_wait_millisec(1000);
		}
}
