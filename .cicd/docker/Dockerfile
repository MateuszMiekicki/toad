FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y ninja-build && \
    apt-get install -y g++-11 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 11 && \
    apt-get install -y gcc-11 && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 11 && \
    update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-11 11 && \
    apt-get install -y doxygen && \
    apt-get install -y git && \
    apt-get install -y wget && \
    apt-get install -y unzip && \
    apt-get install -y lcov && \
    apt-get install -y python3 pip && \
    apt-get install -y ruby-dev && \
    apt-get install -y clang-format-15

#install Rust
RUN wget -O - https://sh.rustup.rs | bash -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

#install tools for check coverage
RUN pip install gcovr
RUN gem install coveralls-lcov

#install pacakge menager for c++
RUN pip install "conan<2"
RUN conan profile new default --detect
RUN conan profile update settings.compiler.libcxx=libstdc++11 default

#install formater for CMake
RUN pip install cmake-format

#preapare for install tools from scripts
COPY scripts /cicd/scripts
WORKDIR /cicd/scripts

# #install CMake
RUN chmod +x install-cmake.sh
RUN ./install-cmake.sh

# #install sonar scanner
RUN chmod +x install-sonar_scanner.sh
RUN ./install-sonar_scanner.sh

# #clean
RUN apt-get autoremove && \
    apt-get autoclean && \
    apt-get clean