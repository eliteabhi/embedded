FROM alpine:latest

RUN apk add --no-cache build-base cmake && mkdir -p /lib_math/build

WORKDIR /lib_math/build

ADD dirs.tar ../

RUN cmake .. && make

ENTRYPOINT [ "./lib_math" ]
