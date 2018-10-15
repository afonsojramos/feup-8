FROM ubuntu:14.04

WORKDIR /app

RUN apt-get update

#RUN apt-get install libpq-dev git cmake libgtk-3-dev \   #CMD for 
#libglvnd-dev -y

RUN apt-get install git wget libgtk-3-dev libgles1-mesa-dev libglu-dev -y #FOR Ubuntu 14.04

RUN wget "https://cmake.org/files/v3.12/cmake-3.12.0-Linux-x86_64.sh" #FOR Ubuntu 14.04 

RUN sh cmake-3.12.0-Linux-x86_64.sh --skip-license --prefix=/usr #FOR Ubuntu 14.04

COPY . /app

CMD sh ./docker_run.sh
