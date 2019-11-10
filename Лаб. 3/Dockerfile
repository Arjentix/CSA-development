# Building --------------
FROM ubuntu:latest AS build

# Name of the service folder
# ARG SERVICE=Animal-Store

# Downloading dependencies
RUN apt-get update && \
    apt-get install -y \
		cmake \
		g++

# Configuring working environment
RUN mkdir -p /app
COPY CMakeLists.txt /app
COPY src /app/src

RUN mkdir -p /app/build
WORKDIR /app/build

# Building
RUN cmake .. && \
	cmake --build . --target install

# Running ---------------
FROM ubuntu:latest

EXPOSE 2525

RUN mkdir -p /app/log

WORKDIR /app
COPY --from=build /app/bin/AnimalStore .
ENTRYPOINT [ "./AnimalStore" ]
