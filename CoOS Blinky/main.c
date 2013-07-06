#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include <CoOS.h>                                            /*!< CoOS header file */

#define STACK_SIZE_DEFAULT 512								/*! Same as MCU flash size*/

OS_STK task1_stk[STACK_SIZE_DEFAULT];
OS_STK task2_stk[STACK_SIZE_DEFAULT];

void initializeBoard(){

        GPIO_InitTypeDef GPIO_InitStructure_Led;
        GPIO_InitTypeDef GPIO_InitStructure_Button;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//for LEds
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//for buttons

        GPIO_InitStructure_Led.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
        GPIO_InitStructure_Led.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure_Led.GPIO_Speed = GPIO_Speed_50MHz;

        GPIO_InitStructure_Button.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure_Button.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure_Button.GPIO_Speed = GPIO_Speed_50MHz;

        GPIO_Init(GPIOC,&GPIO_InitStructure_Led);
        GPIO_Init(GPIOA,&GPIO_InitStructure_Button);

}

void task1 (void* pdata){
        while(1){
                GPIO_WriteBit(GPIOC,GPIO_Pin_8,Bit_SET);
                CoTickDelay (500);
                GPIO_WriteBit(GPIOC,GPIO_Pin_8,Bit_RESET);
                CoTickDelay (500);
        		}
}

void task2 (void* pdata){
        int i;
        while(1){
          		}
}

int main(void)
{
        initializeBoard();
        CoInitOS();
        CoCreateTask(task1,0,0,&task1_stk[STACK_SIZE_DEFAULT-1],STACK_SIZE_DEFAULT);
        CoCreateTask(task2,0,1,&task2_stk[STACK_SIZE_DEFAULT-1],STACK_SIZE_DEFAULT);
        CoStartOS();
    while(1);
}
