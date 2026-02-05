from gpiozero import DistanceSensor


class SensorReader:
    def __init__(self, echo_pin=24, trigger_pin=23):
        self.sensor = DistanceSensor(echo=echo_pin, trigger=trigger_pin)

    def read_distance(self):
        return self.sensor.distance
