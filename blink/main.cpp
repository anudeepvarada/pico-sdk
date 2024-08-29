#include "pico/stdlib.h"

#include "FreeRTOS.h"

#include "task.h"


// class test {
//    public: int i;
// };

void vBlinkTask() {

   for (;;) {

      gpio_put(PICO_DEFAULT_LED_PIN, 1);

      vTaskDelay(5000);

      gpio_put(PICO_DEFAULT_LED_PIN, 0);

      vTaskDelay(5000);

   }

}

int main() {

   gpio_init(PICO_DEFAULT_LED_PIN);

   gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

   xTaskCreate((TaskFunction_t) vBlinkTask, "Blink Task", 128, NULL, 1, NULL);
   // test temp;
   // temp.i = 1;

   vTaskStartScheduler();

   return 0;

}