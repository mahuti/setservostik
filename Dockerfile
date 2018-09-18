FROM alpine:latest
LABEL maintainer="Support <support@silverfieldstech.com>"

RUN apk update && apk add --virtual build-dependencies build-base clang cmake libusb-dev bash make

