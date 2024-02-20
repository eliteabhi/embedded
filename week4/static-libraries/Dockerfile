FROM ubuntu:latest

RUN apt-get update && apt-get install -y build-essential cmake && mkdir -p /lib_math/build

WORKDIR /lib_math/build

ADD ./libs.tar ./CMakeLists.txt ./main.c ../

RUN cmake .. && make

CMD [ "./lib_math" ]
