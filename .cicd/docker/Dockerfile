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
    apt-get install -y ruby-dev

#install tools for check coverage
RUN pip install gcovr
RUN gem install coveralls-lcov

#install pacakge menager for c++
RUN pip install conan

#install CMake
COPY scripts/install-cmake.sh /scripts/install-cmake.sh
RUN chmod +x /scripts/install-cmake.sh
RUN /scripts/install-cmake.sh

#install sonar scanner
COPY scripts/install-sonar_scanner.sh /scripts/install-sonar_scanner.sh
RUN chmod +x /scripts/install-sonar_scanner.sh
RUN /scripts/install-sonar_scanner.sh

#clean
RUN apt-get autoremove && \
    apt-get autoclean && \
    apt-get clean