FROM ubuntu:22.04

RUN apt-get update && \
  apt-get install -y pkg-config build-essential cmake wget && \
  rm -rf /var/lib/apt/lists/* && \
  mkdir ./app
  
WORKDIR ./app

COPY ./envsetup.sh ./entrypoint.sh ./

RUN chmod +x ./*.sh 

ENTRYPOINT ["../envsetup.sh"]

