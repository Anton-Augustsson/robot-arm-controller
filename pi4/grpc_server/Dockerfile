FROM gcc:9.4.0 

ENV DEBIAN_FRONTEND noninteractive

# Increased size due to certain runners failing
RUN echo 'APT::Cache-Start "100000000";' > /etc/apt/apt.conf.d/02cache
# Install dependencies
RUN apt update \
    && apt install -y libabseil-dev build-essential autoconf libtool pkg-config \
    && wget https://github.com/Kitware/CMake/releases/download/v3.22.1/cmake-3.22.1-linux-x86_64.sh -O cmake_installer.sh \
    && chmod +x cmake_installer.sh \
    && ./cmake_installer.sh --skip-license


# Install gRPC
# https://grpc.io/docs/languages/cpp/quickstart/
RUN export MY_INSTALL_DIR=$HOME/.local \
    && mkdir -p $MY_INSTALL_DIR \
    && export PATH="$MY_INSTALL_DIR/bin:$PATH" \
    && git clone --recurse-submodules -b v1.62.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc \
    && cd grpc \
    && mkdir -p cmake/build \
    && cd cmake/build \ 
    && cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
      ../.. \
    && make -j 4 \
    && make install

