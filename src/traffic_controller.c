#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// GPIO pin definitions (BCM numbering)
#define RED_LED 17
#define YELLOW_LED 27
#define GREEN_LED 22

static void gpio_on(int pin) {
    printf("[GPIO %d] ON\n", pin);
}

static void gpio_off(int pin) {
    printf("[GPIO %d] OFF\n", pin);
}

static float get_simulated_distance(void) {
    return (float)(rand() % 100) / 100.0f;
}

static int adaptive_green_time(float distance) {
    if (distance < 0.3f) {
        return 15;
    }
    if (distance < 0.6f) {
        return 10;
    }
    return 5;
}

int main(void) {
    srand((unsigned int)time(NULL));

    while (1) {
        float distance = get_simulated_distance();
        int green_time = adaptive_green_time(distance);

        printf("[SENSOR] Distance: %.2f m\n", distance);

        gpio_on(GREEN_LED);
        sleep((unsigned int)green_time);

        gpio_off(GREEN_LED);
        gpio_on(YELLOW_LED);
        sleep(3);

        gpio_off(YELLOW_LED);
        gpio_on(RED_LED);
        sleep(5);

        gpio_off(RED_LED);
    }

    return 0;
}
