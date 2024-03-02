#!/bin/bash

CC_IMAGE_NAME="eliteabhi/duo-sdk:latest"
CWD=$(pwd)
IFS=" "
COMMAND="$@"
BUILD_COMMAND="bash -c \""

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

find_index() {

  local list="$1"
  local item="$2"

  for i in "${!list[@]}"; do
   if [[ "${list[$i]}" = "${item}" ]]; then
       return ${i};
   fi
  done

}

if contains COMMAND "--image"; then

  local image_arg_index=$(find_index COMMAND "--image") + 1

  CC_IMAGE_NAME="$COMMAND[$image_arg_index]"

fi

if contains COMMAND "cmake"; then

  BUILD_COMMAND="${BUILD_COMMAND}rm -rf /app/*CMake* && "

  if contains COMMAND ".."; then

    BUILD_COMMAND="${BUILD_COMMAND}if [[ -d /app/build ]]; then rm -rf /app/build; fi && /app/build && mkdir -p /app/build && cd /app/build && ${COMMAND}\""
    
  fi

  if contains COMMAND "--build"; then

    BUILD_COMMAND="cd /app/build && ${COMMAND}\""

  fi

else

  BUILD_COMMAND="${BUILD_COMMAND}${COMMAND}\""

fi

if contains COMMAND "--pull-image" || contains "-p"; then 

  sudo docker pull ${CC_IMAGE_NAME}

fi

echo
echo "Build Command: ${BUILD_COMMAND}"
echo
sudo docker run -v "${CWD}:/app" ${CC_IMAGE_NAME} ${BUILD_COMMAND}

