FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y build-essential && \
    mkdir hello-world

WORKDIR /hello-world

ADD ./hello.c ./Makefile ./

RUN make

ENTRYPOINT [ "./hello" ]
