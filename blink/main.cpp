
#include <stdio.h>
#include "pico/stdlib.h"

#include "FreeRTOS.h"

#include "task.h"


// class test {
//    public: int i;
// };

void vBlinkTask() {

   for (;;) {

      gpio_put(PICO_DEFAULT_LED_PIN, 1);
      printf("LED ON !\n");
      vTaskDelay(5000);

      gpio_put(PICO_DEFAULT_LED_PIN, 0);
      printf("LED OFF !\n");
      vTaskDelay(5000);

   }

}

int main() {

   gpio_init(PICO_DEFAULT_LED_PIN);
   stdio_init_all();

   gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

   xTaskCreate((TaskFunction_t) vBlinkTask, "Blink Task", 128, NULL, 1, NULL);
   // test temp;
   // temp.i = 1;

   vTaskStartScheduler();

   return 0;

}