FROM ubuntu:12.04
MAINTAINER Victor Vieux <victorvieux@gmail.com>

RUN apt-get update
RUN apt-get install build-essential ncurses-dev -y

ADD . .

RUN make

ENTRYPOINT ["./dcpu-vv", "FOX.bin"]
