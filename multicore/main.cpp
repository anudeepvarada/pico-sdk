
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/irq.h"
#include "hardware/adc.h"

// class test {
//    public: int i;
// };

// core 1 interrupt handler
void core1_interrupt_handler() 
{
   //receive raw value 
   while(multicore_fifo_rvalid())
   {
      uint16_t raw = multicore_fifo_pop_blocking();
      const float conversionfactor = 3.3f/(1<<12);
      float result = raw *conversionfactor;
      float temp = 27 - (result-0.76)/0.001721;
      printf("Temp = %f C\n", temp);
      
   }
   multicore_fifo_clear_irq();

}

//Core 1 Main Code
void core1_entry() {
   //configure core 1 interrupt
   multicore_fifo_clear_irq();
   irq_set_exclusive_handler(SIO_IRQ_PROC1, core1_interrupt_handler);
   irq_set_enabled(SIO_IRQ_PROC1, true);

   //Infiite loop which waits for interrupt
   while (1)
   {
      tight_loop_contents();
   }
   
}

//Coer0 main code
int main(void) {

   gpio_init(PICO_DEFAULT_LED_PIN);
   stdio_init_all();

   // Start core 1 must be called before configuring interrupts
   multicore_launch_core1(core1_entry);

   //configure ADC
   adc_init();
   adc_set_temp_sensor_enabled(true);
   adc_select_input(4);
   gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

   //primary core 0 loop
   while(1)
   {
      uint16_t raw = adc_read();
      static bool state = false;
      multicore_fifo_push_blocking(raw);
      if(state)
      {
         state = false;
         gpio_put(PICO_DEFAULT_LED_PIN, 1);
      }
      else
      {
         state = true;
         gpio_put(PICO_DEFAULT_LED_PIN, 0);
      }
      sleep_ms(1000);
   }


   return 0;

}