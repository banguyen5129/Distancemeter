/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include "math.h"

#define USED_EEPROM_SECTOR          (1u)
#define IS_METRIC_BYTE          ((USED_EEPROM_SECTOR * CYDEV_EEPROM_SECTOR_SIZE) + 0x00)


int a1 = 0b1110;
int a2 = 0b1101;
int a3 = 0b1011;
int a4 = 0b0111;
int b1, b2, b3 ,b4;
int int2bin(int i);
int group_no = 135;
int dist;
uint8 adcResult;
int adcVolts;
char tmpStr[30];
char tmpStr1[30];
uint16 counter1;
uint16 counter2;

void sendPulse() {
    //send 10x 40kHz pulse
    
    Control_Reg_3_Write(1);
    Control_Reg_3_Write(0);
    
    uint8 status = Timer_1_ReadStatusRegister();
    Timer_Reset_Write(1);
    Timer_Reset_Write(0);
    
    //counter1 = Timer_1_ReadCapture();
    //sprintf(tmpStr, " counter1 %d  \n", counter1); 	 	            		//Create text string
    //UART_1_PutString(tmpStr);                  		 	    	//Print string to console
            

}

void display_unit(){
    if(EEPROM_1_ReadByte(IS_METRIC_BYTE)){
        //display unit: cm
        Control_Reg_2_Write(a4);
        Control_Reg_1_Write(0b10100111);
        CyDelay(1000);
    }
    else {
        //display unit: inch
        Control_Reg_2_Write(a4);
        Control_Reg_1_Write(0b11111001);
        CyDelay(1000);
    }
}
void display(int a, int n){
    //Display group number

    for(int x=0;x<250;x++){
        Control_Reg_2_Write(a1);
        b1 = int2bin((a%10000 - a%1000)/1000);
        Control_Reg_1_Write(b1);
        CyDelay(1);
        Control_Reg_2_Write(a2);
        b2 = int2bin((a%1000 - a%100)/100);
        if(n == 1) b2 += 0b10000000;
        Control_Reg_1_Write(b2);
        CyDelay(1);
        Control_Reg_2_Write(a3);
        b3 = int2bin((a%100 - a%10)/10);
        Control_Reg_1_Write(b3);
        CyDelay(1);
        Control_Reg_2_Write(a4);
        b4 = int2bin(a%10);
        Control_Reg_1_Write(b4);
        CyDelay(1); 
    }
    Control_Reg_2_Write(0b1111);
    
}
void startup(){
    Control_Reg_2_Write(a1);
    Control_Reg_1_Write(0b00000000);
    CyDelay(1000);
    Control_Reg_2_Write(a2);
    Control_Reg_1_Write(0b00000000);
    CyDelay(1000);
    Control_Reg_2_Write(a3);
    Control_Reg_1_Write(0b00000000);
    CyDelay(1000);
    Control_Reg_2_Write(a4);
    Control_Reg_1_Write(0b00000000);
    CyDelay(1000);
    
    //Display group number
    display(group_no,0);
    
    display_unit();
    
}

void sleepmode(){
    // sleep mode
    Control_Reg_2_Write(a4);
    Control_Reg_1_Write(0b11111111);
    CyDelay(500);
    Control_Reg_1_Write(0b01111111);
    CyDelay(500);
        
        
}

void beep() {
    beeperpin_Write(0);
    CyDelay(200);
    beeperpin_Write(1);
    return;
}

float cm2Inch(float value) {
    //1 cm = 0.393700787 inches
    return (value*0.3937);
}

uint16 counter;
CY_ISR(timer_handler){
    
    counter2 = Timer_1_ReadPeriod() - Timer_1_ReadCapture();
                		 	    	
    
    
}
CY_ISR(measurehandlerisr)                  //This is the ISR
{
    
    beep();
    
    sendPulse();
    if(EEPROM_1_ReadByte(IS_METRIC_BYTE)){        
        dist = counter2*34 ;
        
    }
    else{
        dist = counter2*34;
        dist = cm2Inch(dist);
    }
    display(dist,1);
        
    sprintf(tmpStr1, " dist %d  \n", dist); 	 //Print string to console	            		//Create text string
    UART_1_PutString(tmpStr1); 
}
CY_ISR(startupisr)                  //This is the ISR to display information
{
    beep();
    startup();
}
CY_ISR(convertunitisr)                  //This is the ISR for converting unit
{
    beep();
    EEPROM_1_WriteByte(~EEPROM_1_ReadByte(IS_METRIC_BYTE),IS_METRIC_BYTE);
    
    display_unit();
}
CY_ISR(increasegroupnoisr)                  //This is the ISR for changing group number
{
    beep();
    group_no++;
    display(group_no,0);
}
CY_ISR(decreasegroupnoisr)                  //This is the ISR
{
    beep();
    group_no = group_no -1;
    display(group_no,0);
}
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
     /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    isr_1_ClearPending();
    isr_1_StartEx(timer_handler);
    isr_2_ClearPending();
    isr_2_StartEx(measurehandlerisr);
    isr_3_ClearPending();
    isr_3_StartEx(startupisr);
    isr_4_ClearPending();
    isr_4_StartEx(convertunitisr);
    isr_5_ClearPending();
    isr_5_StartEx(increasegroupnoisr);
    isr_6_ClearPending();
    isr_6_StartEx(decreasegroupnoisr);
    
    timer_clock_Start();    // Start timer clock
    Timer_1_Start();        // Start timer
    Clock_2_Start();        // Start debouncer clock
    Opamp_1_Start();        // Start Opamp
    PGA_1_Start();      
    Comp_1_Start(); 
    Clock_1_Start();        // Produce 40kHz pulse
    Count7_1_Start();
    UART_1_Start();			 //Start the UART
    EEPROM_1_Start();
    
    
    
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    startup();
    
    for(;;)
    {
        
        sleepmode();
        
        
    }
}

int int2bin(int i){
    int b;
    switch(i){
        case 0: {
            b= 0b11000000;
            break;
        }
        case 1: {
            b= 0b11111001;
            break;
        }
        case 2: {
            b= 0b10100100;
            break;
        }
        case 3: {
            b= 0b10110000;
            break;
        }
        case 4: {
            b = 0b10011001;
            break;
        }
        case 5: {
            b= 0b10010010;
            break;
        }
        case 6: {
            b= 0b10000010;
            break;
        }
        case 7: {
            b = 0b11111000;
            break;
        }
        case 8: {
            b = 0b10000000;
            break;
        }
        case 9: {
            b = 0b10010000;
            break;
        }
    }
    return b;
}

/* [] END OF FILE */
