#!/bin/bash

CC_IMAGE_NAME="eliteabhi/duo-sdk:latest"
CWD=$(pwd)
IFS=" "
COMMAND="$@"
BUILD_COMMAND=""

# See if element is in list
contains() {
  local list="$1"
  local item="$2"
  if [[ $list =~ (^|[[:space:]])"$item"($|[[:space:]]) ]] ; then
    # yes, list include item
    result=0
  else
    result=1
  fi
  return $result
}


if contains COMMAND "cmake"; then

  if contains COMMAND ".."; then

    BUILD_COMMAND="bash -c \"mkdir -p /app/build && cd /app/build && $COMMAND\""
    
  fi

  if contains COMMAND "--build"; then

    BUILD_COMMAND="bash -c \"cd /app/build && $COMMAND\""

  fi

else

  BUILD_COMMAND=$COMMAND

fi

sudo docker pull $CC_IMAGE_NAME
sudo docker run -v "$CWD:/app" $CC_IMAGE_NAME $BUILD_COMMAND

