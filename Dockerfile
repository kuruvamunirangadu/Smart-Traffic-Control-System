FROM python:3.10-slim

WORKDIR /app

COPY simulation/ simulation/

CMD ["python", "simulation/traffic_simulator.py"]
