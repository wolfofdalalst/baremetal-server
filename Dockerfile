FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y gcc make libc6-dev && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN make clean && make

EXPOSE 8080

CMD ["./bin/baremetal"]
