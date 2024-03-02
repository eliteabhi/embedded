#!/bin/bash

CC_IMAGE_NAME="eliteabhi/duo-sdk"
CWD=$(PWD)
IFS=" "
COMMAND="$*"
BUILD_COMMAND=""


if [[ $COMMAND == *"cmake"* ]]; then

  if [[ $COMMAND == *".."* ]]; then

    BUILD_COMMAND="bash -c \"mkdir -p /app/build && cd /app/build && $COMMAND\""
    
  fi

  if [[ $COMMAND == *"--build"* ]]; then

    BUILD_COMMAND="bash -c \"cd /app/build && $COMMAND\""

  fi

else

  BUILD_COMMAND=$COMMAND

fi

sudo docker run -v $CWD:/app $CC_IMAGE_NAME $BUILD_COMMAND

