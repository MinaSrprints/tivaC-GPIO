/*
 * main.c
 */
#include "GPIO.h"

void Delay(long int x)
{
    volatile long int Loop;
    for(Loop = 0; Loop < x; Loop++);
}

int main(void){
    GPIO_Init();
    GPIO_SetPinDirection(PORTF, PINF2, OUTPUT);
    GPIO_SetPinDirection(PORTF, PINF1, OUTPUT);
    GPIO_SetPinDirection(PORTF, PINF3, OUTPUT);
    GPIO_SetPinDirection(PORTF, PINF0, INPUT);
    GPIO_SetPinDirection(PORTF, PINF4, INPUT);
    //	/*enable Clock Gate*/
    //	SYSCTL_RCGC2_R |= 0x20;
    //	/*clear Alternate function*/
    //	GPIO_PORTF_AFSEL_R &= ~(0x02);
    //	/*Set the direction to putput*/
    //	GPIO_PORTF_DIR_R |= (0x02);
    //	/*Disable open drain*/
    //	GPIO_PORTF_ODR_R &= ~(0x02);
    //	/*enable the Digital function*/
    //	GPIO_PORTF_DEN_R |= 0x02;
    //	/*Select pull down resistor*/
    //	GPIO_PORTF_PDR_R |= 0x02;
    //	/*select 2mA Current*/
    //	GPIO_PORTF_DR2R_R |= 0x02;
    uint8 b1=0;
    uint8 b2=0;
    while(1)
    {
        b1=GPIO_ReadPin(PORTF, PINF0);
        b2=GPIO_ReadPin(PORTF, PINF4);
        if(!b2)
        {
            GPIO_WritePin(PORTF, PINF2, HIGH);
            GPIO_WritePin(PORTF, PINF1, LOW);
            GPIO_WritePin(PORTF, PINF3, LOW);
        }
        else if(!b1)
        {
            GPIO_WritePin(PORTF, PINF3, HIGH);
            GPIO_WritePin(PORTF, PINF1, LOW);
            GPIO_WritePin(PORTF, PINF2, LOW);
        }
        else
          {
              GPIO_WritePin(PORTF, PINF1, HIGH);
              GPIO_WritePin(PORTF, PINF2, LOW);
              GPIO_WritePin(PORTF, PINF3, LOW);
          }

    }

    return 0;
}
