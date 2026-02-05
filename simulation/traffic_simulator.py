import random
import time


def get_simulated_distance():
    return round(random.uniform(0.2, 1.0), 2)


def adaptive_green_time(distance):
    if distance < 0.3:
        return 15
    if distance < 0.6:
        return 10
    return 5


while True:
    distance = get_simulated_distance()
    green_time = adaptive_green_time(distance)

    print(f"[SENSOR] Distance: {distance} m")
    print(f"[SIGNAL] GREEN for {green_time}s")
    time.sleep(green_time)

    print("[SIGNAL] YELLOW for 3s")
    time.sleep(3)

    print("[SIGNAL] RED for 5s")
    time.sleep(5)
