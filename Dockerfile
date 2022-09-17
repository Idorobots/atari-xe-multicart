# docker run -ti --rm -v $(pwd)/roms/:/input/ -v $(pwd):/output/ atari_xe_multicart
FROM ubuntu:latest

RUN 	apt-get update && \
	apt-get install -y gpg curl git make gcc python3 cc65

RUN	cd / && \
	git clone https://github.com/Idorobots/atari-xe-multicart.git && \
	mkdir /input && \
	mkdir /output

WORKDIR /atari-xe-multicart

ENTRYPOINT make ROMS=/input && mv cart.bin /output/cart.bin
