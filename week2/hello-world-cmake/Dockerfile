FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y build-essential cmake && \
    mkdir -p hello-world/build
    
WORKDIR /hello-world/build

ADD ./CMakeLists.txt ./hello.c ../

RUN cmake .. && make

ENTRYPOINT [ "./hello" ]
