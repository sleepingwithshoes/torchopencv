FROM nvidia/cuda:12.2.2-cudnn8-devel-ubuntu22.04

ARG GCC_VERSION=12
ARG CLANG_VARION=17
ARG CMAKE_VERSION=3.28.3
ARG NINJA_VERSION=1.11.1
ARG LIBTORCH_VERSION=2.2.1

RUN apt-get update && apt-get install -y \
    gdb \
    git \
    python3 \
    python3-dev \
    tar \
    tree \
    unzip \
    wget \
    && apt-get clean

# Install CMake
RUN CMAKE_VERSION_MOC=$(echo ${CMAKE_VERSION} | rev | cut -c3- | rev) && wget "https://cmake.org/files/v${CMAKE_VERSION_MOC}/cmake-${CMAKE_VERSION}-linux-x86_64.sh" -q -O /tmp/cmake-install.sh
RUN chmod u+x /tmp/cmake-install.sh
RUN mkdir /opt/cmake-${CMAKE_VERSION}
RUN /tmp/cmake-install.sh --skip-license --prefix=/opt/cmake-${CMAKE_VERSION}
RUN rm /tmp/cmake-install.sh
RUN ln -s /opt/cmake-${CMAKE_VERSION}/bin/cmake /usr/bin/cmake

#Install GCC
RUN apt-get update && apt-get install -y software-properties-common && rm -rf /var/lib/apt/lists/*
RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt-get update && apt-get install -y \
    gcc-${GCC_VERSION} \
    g++-${GCC_VERSION}
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-${GCC_VERSION} ${GCC_VERSION} --slave /usr/bin/g++ g++ /usr/bin/g++-${GCC_VERSION}

# Install Clang
RUN apt-get update && apt-get install -y lsb-release software-properties-common gnupg
RUN wget https://apt.llvm.org/llvm.sh && chmod u+x llvm.sh
RUN ./llvm.sh ${CLANG_VARION} all
RUN ln -s /usr/bin/clang-${CLANG_VARION} /usr/bin/clang && ln -s /usr/bin/clang++-${CLANG_VARION} /usr/bin/clang++

# Install Ninja
RUN wget "https://github.com/ninja-build/ninja/releases/download/v${NINJA_VERSION}/ninja-linux.zip"
RUN unzip ninja-linux.zip
RUN mv ninja /usr/bin

# Install LibTorch
RUN wget "https://download.pytorch.org/libtorch/cu121/libtorch-cxx11-abi-shared-with-deps-${LIBTORCH_VERSION}%2Bcu121.zip"
RUN unzip libtorch-cxx11-abi-shared-with-deps-${LIBTORCH_VERSION}+cu121.zip -d /usr/local/lib/
RUN rm libtorch-cxx11-abi-shared-with-deps-${LIBTORCH_VERSION}+cu121.zip

# Install OpenCV
RUN apt-get update && apt-get install -y build-essential libgtk2.0-dev python3-dev
RUN mkdir -p opencv-build/build
RUN cd opencv-build && git clone https://github.com/opencv/opencv.git && git clone https://github.com/opencv/opencv_contrib.git
RUN cd opencv-build/build && \
    cmake -D WITH_GTK=ON \
    -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules \
    ../opencv
RUN cd opencv-build/build && make -j$(nproc) && make install
RUN rm -rf opencv-build

# Add user
ARG UID=1000
RUN useradd -m -u ${UID} -s /bin/bash builder
RUN usermod -aG video builder
USER builder