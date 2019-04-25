FROM debian:buster

LABEL maintainer="elie.taillardat@wiifor.com"

RUN apt-get -q update \
    && apt-get -qy --no-install-recommends --no-install-suggests install  \
    gcc \
    git \
    wget \
    make \
    libncurses-dev \
    flex \
    bison \
    gperf \
    python \
    python-pip \
    python-setuptools \
    python-serial \
    python-cryptography \
    python-future \
    python-pyparsing \
    python-pyelftools \
    python3 \
    python3-pip \
    python3-setuptools \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Get the ESP32 toolchain
ENV ESP_TCHAIN_BASEDIR /opt/esp
RUN mkdir -p $ESP_TCHAIN_BASEDIR \
    && wget -O $ESP_TCHAIN_BASEDIR/esp32-toolchain.tar.gz \
    https://dl.espressif.com/dl/xtensa-esp32-elf-linux64-1.22.0-80-g6c4433a-5.2.0.tar.gz \
    && tar -xzf $ESP_TCHAIN_BASEDIR/esp32-toolchain.tar.gz \
    -C $ESP_TCHAIN_BASEDIR/ \
    && rm $ESP_TCHAIN_BASEDIR/esp32-toolchain.tar.gz

# Install required packages
COPY requirements.txt /tmp/requirements.txt
RUN pip3 install pipenv \
    && pip install wheel \
    && pip install -r /tmp/requirements.txt \
    && rm /tmp/requirements.txt \
    && rm -r ~/.cache/pip

# Add the toolchain binaries to PATH
ENV PATH $PATH:$ESP_TCHAIN_BASEDIR/xtensa-esp32-elf/bin
ENV NEXUS_ESP32_BUILD true

ENTRYPOINT ["/usr/bin/make"]