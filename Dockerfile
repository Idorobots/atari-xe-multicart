# docker run -ti --rm -v $(pwd)/roms/:/input/ -v $(pwd):/output/ atari_xe_multicart
FROM ubuntu:focal

RUN 	apt update && \
	apt install -y gpg curl git make gcc python3 && \
	echo 'deb http://download.opensuse.org/repositories/home:/strik/Debian_10/ /' | tee /etc/apt/sources.list.d/home:strik.list && \
	curl -fsSL https://download.opensuse.org/repositories/home:strik/Debian_10/Release.key | gpg --dearmor | tee /etc/apt/trusted.gpg.d/home:strik.gpg > /dev/null && \
	apt update && \
	apt install cc65 -y

RUN	cd / && \
	git clone https://github.com/Idorobots/atari-xe-multicart.git && \
	mkdir /input && \
	mkdir /output

WORKDIR /atari-xe-multicart

ENTRYPOINT make ROMS=/input && mv cart.bin /output/cart.bin
