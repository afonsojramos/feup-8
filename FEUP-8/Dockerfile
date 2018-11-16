FROM ubuntu:18.04

WORKDIR /app

RUN apt-get update

RUN apt-get install libpq-dev git cmake libgtk-3-dev libglvnd-dev libglu1-mesa-dev -y
COPY . /app

RUN apt install lcov

CMD sh ./docker_run.sh
