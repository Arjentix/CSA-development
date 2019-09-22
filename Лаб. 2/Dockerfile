# Building --------------

FROM gcc:7.4 as build

# Downloading cmake package
RUN apt-get update && \
    apt-get install -y \
      cmake 

# Configuring working environment
RUN mkdir -p /app
COPY CMakeLists.txt /app
COPY src /app/src
RUN mkdir -p /app/build
WORKDIR /app/build

# Building
RUN cmake .. && \
	cmake --build .

# Running ---------------

FROM ubuntu:latest

# Creating new user cause Docker uses root by default which is not good
RUN groupadd -r sample && useradd -r -g sample sample
USER sample

WORKDIR /app
EXPOSE 1500
COPY --from=build /app/build/src/server .
ENTRYPOINT [ "./server" ]
