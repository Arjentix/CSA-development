# Building --------------
FROM ubuntu:latest AS build

# Name of the service folder
ARG SERVICE='Лаб. 3'

# Downloading dependencies
RUN apt-get update && \
    apt-get install -y \
		cmake \
		g++ \
		libmysqlclient-dev

# Configuring working environment
RUN mkdir -p /app
COPY ${SERVICE}/CMakeLists.txt /app
COPY ${SERVICE}/src /app/src

RUN mkdir -p /app/build
WORKDIR /app/build

# Building
RUN cmake .. && \
	cmake --build . --target install

# Running ---------------
FROM ubuntu:latest

# Copying libs
COPY --from=build /usr/lib/x86_64-linux-gnu/libmysqlclient.so.20 /usr/lib/x86_64-linux-gnu/
COPY --from=build /usr/lib/x86_64-linux-gnu/libssl.so.1.1 /usr/lib/x86_64-linux-gnu/
COPY --from=build /usr/lib/x86_64-linux-gnu/libcrypto.so.1.1 /usr/lib/x86_64-linux-gnu/

EXPOSE 2525

RUN mkdir -p /app/log

WORKDIR /app
COPY --from=build /app/bin/AnimalStore .
ENTRYPOINT [ "./AnimalStore" ]
