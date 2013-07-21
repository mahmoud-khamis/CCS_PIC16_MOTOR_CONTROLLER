/*
PIC16F877A and L298 H-Bridge Motor Speed/Direction Controller

Badr Ghatasheh
badr.ghatasheh@gmail.com
*/

#include <16f877a.h>
#fuses XT,NOLVP,NOWDT,NOPROTECT
#use delay(clock=4000000)

#define  Wire1 PIN_B6
#define  Wire2 PIN_B7
#define  Up    PIN_A0
#define  Down  PIN_A1
#define  Dir   PIN_A2

int16 duty_cycle=512;

void main()
{
   setup_adc(ADC_OFF);           // Turn ADC OFF
   setup_adc_ports(NO_ANALOGS);  // All Ports are digital I/O
   output_high(Wire1);           
   output_low(Wire2);            // Set the motor to CW direction
   
   /* PWM Configurations */
   setup_timer_2(T2_DIV_BY_1,255,1);   // Set PWM frequency
   setup_ccp1(CCP_PWM);          // Configure CCP1 to PWM mode
   set_pwm1_duty(512L);          // default duty cycle = 50% (Half Speed)

   while(1)
   {
      while(input(Up) && input(Down) && input(Dir)); // Hold until a button is pressed
      
      if(!input(Up))    // Button (Up) Selected?
      {
         duty_cycle+=64;   // increase the duty cycle by some percentage (+6.25%)
         set_pwm1_duty(duty_cycle); // set the duty cycle
      }
      if(!input(Down))  // Button (Down) Selected?
      {
         duty_cycle-=64;   // decrease the duty cycle
         set_pwm1_duty(duty_cycle); // set the duty cycle
      }
      if(!input(Dir))   // Button (Direction) Selected?
      {
         output_toggle(Wire1);   // Toggle the polarity of IN1 IN2
         output_toggle(Wire2);   // 0 becomes 1 , 1 becomes 0
      }
      
      delay_ms(500); // 0.5 second delay to release the selected button
   }
}
   
