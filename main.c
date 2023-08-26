/*
 * main.c
 *
 *  Created on: 19 Aug 2023
 *      Author: Rashad
 */
/* LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

/* MCAL */
#include "DIO_Interface.h"
/* HAL */
#include "KPD_Interface.h"
#include "LCD_Interface.h"



int main(void)
{
	label:	LCD_voidInit();
	KPD_voidInit();
u8 G_u8ArrayOfDigit[8]={KPD_KEY_NOT_PRESSED,KPD_KEY_NOT_PRESSED,KPD_KEY_NOT_PRESSED,KPD_KEY_NOT_PRESSED,KPD_KEY_NOT_PRESSED,KPD_KEY_NOT_PRESSED,KPD_KEY_NOT_PRESSED,KPD_KEY_NOT_PRESSED} ;
u8 G_u8StrArray[10];
u64 G_u64Result=0 ;
u32 G_u16Num1=0 ;
u32 G_u16Num2=0 ;
u8 operation=0 ;
while(1)
{


	for(u8 Localcounter=0 ;Localcounter<3;Localcounter++)
	{
		do
			{
				G_u8ArrayOfDigit[Localcounter]=KPD_u8GetKeyValue();

			} while(G_u8ArrayOfDigit[Localcounter]==KPD_KEY_NOT_PRESSED);

			if(G_u8ArrayOfDigit[Localcounter]=='C'||G_u8ArrayOfDigit[Localcounter]=='='||G_u8ArrayOfDigit[Localcounter]=='+'||G_u8ArrayOfDigit[Localcounter]=='-'||G_u8ArrayOfDigit[Localcounter]=='*'||G_u8ArrayOfDigit[Localcounter]=='/')
			{
				LCD_voidSendCommand(LCD_CLEAR);
				goto label ;
			}
			else
			{
				LCD_voidSendChar(G_u8ArrayOfDigit[Localcounter]);
			}

		if(Localcounter==3)
			break;
	}

	G_u16Num1=(G_u8ArrayOfDigit[2]-48)+((G_u8ArrayOfDigit[1]-48)*10)+((G_u8ArrayOfDigit[0]-48)*100);

	do
	{
		G_u8ArrayOfDigit[3]=KPD_u8GetKeyValue();

	}while(G_u8ArrayOfDigit[3]==KPD_KEY_NOT_PRESSED);

	if(G_u8ArrayOfDigit[3]=='C'||G_u8ArrayOfDigit[3]=='=')
	{
		LCD_voidSendCommand(LCD_CLEAR);
		goto label ;
	}
	else
	{
		LCD_voidSendChar(G_u8ArrayOfDigit[3]);
		operation=G_u8ArrayOfDigit[3];
	}


	for(u8 Localcounter=4 ;Localcounter<7;Localcounter++)
		{
		do
				{
					G_u8ArrayOfDigit[Localcounter]=KPD_u8GetKeyValue();

				} while(G_u8ArrayOfDigit[Localcounter]==KPD_KEY_NOT_PRESSED);

				if(G_u8ArrayOfDigit[Localcounter]=='C'||G_u8ArrayOfDigit[Localcounter]=='='||G_u8ArrayOfDigit[Localcounter]=='+'||G_u8ArrayOfDigit[Localcounter]=='-'||G_u8ArrayOfDigit[Localcounter]=='*'||G_u8ArrayOfDigit[Localcounter]=='/')
				{
					LCD_voidSendCommand(LCD_CLEAR);
					goto label ;
				}
				else
				{
					LCD_voidSendChar(G_u8ArrayOfDigit[Localcounter]);
				}

			if(Localcounter==7)
				break;
		}
	G_u16Num2=(G_u8ArrayOfDigit[6]-48)+((G_u8ArrayOfDigit[5]-48)*10)+((G_u8ArrayOfDigit[4]-48)*100);

	do
	{
		G_u8ArrayOfDigit[7]=KPD_u8GetKeyValue();

	}while(G_u8ArrayOfDigit[7]==KPD_KEY_NOT_PRESSED);

	if(G_u8ArrayOfDigit[7]=='=')
	{
		LCD_voidSendChar(G_u8ArrayOfDigit[7]);
		LCD_voidSetLocation(2,0);
		LCD_voidSendString("Result= ");

		switch(operation)
		{
			case '+':
				G_u64Result=G_u16Num1+G_u16Num2;

				//-------->>> Convert to string
				sprintf(G_u8StrArray , "%lu", G_u64Result);
				LCD_voidSendString(G_u8StrArray);
				break;

			case '-' :
				G_u64Result=G_u16Num1-G_u16Num2;
				//-------->>> Convert to string
				sprintf(G_u8StrArray , "%lu", G_u64Result);
				LCD_voidSendString(G_u8StrArray);
				break;

			case '*':
				G_u64Result=G_u16Num1*G_u16Num2;
				//-------->>> Convert to string
				sprintf(G_u8StrArray , "%lu", G_u64Result);
				LCD_voidSendString(G_u8StrArray);
				break;

			case '/':
				if(G_u16Num2 !=0)
				{
					G_u64Result=G_u16Num1/(G_u16Num2);
					//-------->>> Convert to string
					sprintf(G_u8StrArray , "%lu", G_u64Result);
					LCD_voidSendString(G_u8StrArray);
				}
				else
					LCD_voidSendString("Error");
				break;
			default : break;

		}
	}
	else
	{
		LCD_voidSendCommand(LCD_CLEAR);
		goto label ;
	}

	do
		{
			KPD_u8GetKeyValue();

		}while(KPD_u8GetKeyValue()==KPD_KEY_NOT_PRESSED);
	LCD_voidSendCommand(LCD_CLEAR);
}
}
