FROM python:slim

ENV PYTHONUNBUFFERED=1

COPY Requirements.txt /tmp/Requirements.txt

RUN pip --no-cache-dir install -r /tmp/Requirements.txt

WORKDIR /app

COPY . .

CMD ["python", "/app/main.py"]
