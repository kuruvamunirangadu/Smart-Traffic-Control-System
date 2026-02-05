FROM gcc:12

WORKDIR /app

COPY src/ src/

RUN gcc src/traffic_controller.c -o traffic_controller

CMD ["./traffic_controller"]
