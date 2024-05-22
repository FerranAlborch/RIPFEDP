# Use the latest Ubuntu image
FROM ubuntu:latest

# Set environment variables to avoid prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    libgmp-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Create a directory for the library source code
WORKDIR /usr/src/mycpp-lib

# Copy the library source code and Makefile into the container
COPY . .

# Compile the library using the Makefile
RUN make release

ENTRYPOINT /bin/bash
