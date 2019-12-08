/*
 * main.c
 *
 *  Created on: Dec 3, 2019
 *      Author: ahmed
 */

#include "led.h"
#include "gpio.h"
#include "softwareDelay.h"
#include "pushButton.h"
#include "timers.h"


int main(){

    Led_Init(0);
    Led_Init(1);
    Led_Init(2);

    pushButton_Init(1);


    timer2Init(T2_NORMAL_MODE,T2_OC2_DIS,T2_PRESCALER_64,0,0,0,T2_POLLING);


       uint8 u8_checkStatus_1; 		//To store the status of every update

       uint8 u8_checkPressed=0; 	//To store if led is on or off before go in release status condition

       while(1)
   	{

   	pushButton_Update();

   	u8_checkStatus_1=pushButton_GetStatus(1);

   	if(u8_checkStatus_1==Pressed)
   	    {
   		Led_On(1);
   		u8_checkPressed=1; //Store that led has pressed

   	    }
   	else if(u8_checkStatus_1==Released && u8_checkPressed) // to check the release state after pressed state
   	    {
   		timer2Delay_ms(u8_checkPressed*1000);
   		Led_Off(1);
   		u8_checkPressed=0; //reset pressed state to zero
   	    }
   	}
}
