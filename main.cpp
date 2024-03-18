#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "src/motor/servo_motor.hpp" 
#include "src/motor/mg996r.hpp" 
#include "src/utils/types.hpp" 

const int LED_PIN = 25;
auto test = 2;

int main ()
{
    bi_decl(bi_program_description("Sample binary"));
    bi_decl(bi_1pin_with_name(LED_PIN, "on-board PIN"));


    MotorParameters motorParameters0 = {
      "mg996r",
      0,
      PwmRange {
        3,
        12,
      },
      AngleRange {
        0,
        90,
      },
    };

    Mg996r motor0 = Mg996r(motorParameters0);

    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while(1)
    {
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
        gpio_put(LED_PIN, 1);
        puts("Hello Word\n");
        sleep_ms(1000);
    }
}
