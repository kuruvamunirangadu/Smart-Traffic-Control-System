import csv
import time
from gpiozero import DistanceSensor, LED

# Traffic lights
red = LED(17)
yellow = LED(27)
green = LED(22)

# Distance sensor (HC-SR04)
sensor = DistanceSensor(echo=24, trigger=23)

LOG_FILE = "../data/traffic_log.csv"


def log_data(distance, green_time):
    with open(LOG_FILE, "a", newline="") as file:
        writer = csv.writer(file)
        writer.writerow([time.time(), distance, green_time])


def adaptive_green_time(distance):
    if distance < 0.3:  # heavy traffic
        return 15
    if distance < 0.6:  # medium traffic
        return 10
    return 5  # low traffic


while True:
    distance = sensor.distance
    green_time = adaptive_green_time(distance)

    green.on()
    red.off()
    yellow.off()
    time.sleep(green_time)

    green.off()
    yellow.on()
    time.sleep(3)

    yellow.off()
    red.on()
    time.sleep(5)

    log_data(distance, green_time)
