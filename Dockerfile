# docker run -ti --rm -v $(pwd)/roms/:/input/ -v $(pwd):/output/ atari_xe_multicart
FROM ubuntu:latest

RUN 	apt-get update && \
	apt-get install -y gpg curl git make gcc python3 && \
	echo 'deb http://download.opensuse.org/repositories/home:/strik/Debian_10/ /' | tee /etc/apt/sources.list.d/home:strik.list && \
	curl -fsSL https://download.opensuse.org/repositories/home:strik/Debian_10/Release.key | gpg --dearmor | tee /etc/apt/trusted.gpg.d/home:strik.gpg > /dev/null && \
	apt-get update && \
	apt-get install cc65 -y

RUN	cd / && \
	git clone https://github.com/Idorobots/atari-xe-multicart.git && \
	mkdir /input && \
	mkdir /output

WORKDIR /atari-xe-multicart

ENTRYPOINT make ROMS=/input && mv cart.bin /output/cart.bin
