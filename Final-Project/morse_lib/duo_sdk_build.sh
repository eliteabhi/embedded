#!/bin/bash

CC_IMAGE_NAME="ejortega/duo-sdk:latest"
CWD=$(pwd)
IFS=" "
COMMAND="$*"
BUILD_COMMAND=""
UID=$(id -u)
GID=$(id -g)

while getopts i:p:u:g:r OPTION; do

  case "${OPTION}" in

    i)
      CC_IMAGE_NAME="${OPTARG}";;
    
    p)
      sudo docker pull ${CC_IMAGE_NAME};;

    u)
      UID=${OPTARG};;

    g)
      GID=${OPTARG};;

    r)
      UID=0
      GID=0;;

  esac
done

if [[ "$COMMAND" == *"cmake"* ]]; then

  BUILD_COMMAND="rm -rf /app/*CMakeCache* && "

  if [[ "$COMMAND" == *".."* ]]; then

    BUILD_COMMAND="${BUILD_COMMAND}if [[ -d /app/build ]]; then rm -rf /app/build; fi && mkdir -p /app/build && cd /app/build && ${COMMAND}"  

  elif [[ "$COMMAND" == *"--build"* ]]; then

    BUILD_COMMAND="${BUILD_COMMAND}cd /app/build && ${COMMAND}"

  else

    BUILD_COMMAND="${BUILD_COMMAND}${COMMAND}"

  fi

else

  BUILD_COMMAND="cd /app/build && ${COMMAND}"

fi

echo
echo "Build Command: ${BUILD_COMMAND}"
echo

echo "Full Command: sudo docker run --rm --user \"${UID}\":\"${GID}\" -v \"${CWD}\":/app -t ${CC_IMAGE_NAME} /bin/bash -c \"${BUILD_COMMAND}\""
echo

read -sn 1 -p "Is the command correct?[y/N]: " correct
echo
echo

if [[ "$correct" == "y" ]]; then

  sudo docker run --rm --user "${UID}":"${GID}" -v "${CWD}":/app -t ${CC_IMAGE_NAME} /bin/bash -c "${BUILD_COMMAND}"
  ERROR=$?

fi

echo
echo "Have a nice day!!"

exit $ERROR

