#include <pigpio.h>
#include <stdio.h>
#include <unistd.h>

#define RED_LED 17
#define YELLOW_LED 27
#define GREEN_LED 22

#define TRIG 23
#define ECHO 24

static float measure_distance(void) {
    gpioWrite(TRIG, 0);
    usleep(2);
    gpioWrite(TRIG, 1);
    usleep(10);
    gpioWrite(TRIG, 0);

    while (gpioRead(ECHO) == 0) {
    }
    uint32_t start = gpioTick();

    while (gpioRead(ECHO) == 1) {
    }
    uint32_t end = gpioTick();

    float distance_cm = (end - start) / 58.0f;
    return distance_cm / 100.0f;
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
    if (gpioInitialise() < 0) {
        printf("pigpio init failed\n");
        return 1;
    }

    gpioSetMode(RED_LED, PI_OUTPUT);
    gpioSetMode(YELLOW_LED, PI_OUTPUT);
    gpioSetMode(GREEN_LED, PI_OUTPUT);
    gpioSetMode(TRIG, PI_OUTPUT);
    gpioSetMode(ECHO, PI_INPUT);

    while (1) {
        float distance = measure_distance();
        int green_time = adaptive_green_time(distance);

        printf("Distance: %.2f m | Green: %d s\n", distance, green_time);

        gpioWrite(GREEN_LED, 1);
        sleep((unsigned int)green_time);

        gpioWrite(GREEN_LED, 0);
        gpioWrite(YELLOW_LED, 1);
        sleep(3);

        gpioWrite(YELLOW_LED, 0);
        gpioWrite(RED_LED, 1);
        sleep(5);

        gpioWrite(RED_LED, 0);
    }

    gpioTerminate();
    return 0;
}
