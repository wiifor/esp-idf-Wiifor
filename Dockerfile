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
RUN pip install wheel \
    && pip install -r /tmp/requirements.txt \
    && rm /tmp/requirements.txt \
    && rm -r ~/.cache/pip

# Setup IDF_PATH
ENV IDF_PATH $ESP_TCHAIN_BASEDIR/esp-idf
# Add the toolchain binaries to PATH
ENV PATH $ESP_TCHAIN_BASEDIR/xtensa-esp32-elf/bin:$PATH
# Add PWD environment variable to prevent warnings
ENV PWD /data

WORKDIR $PWD
ENTRYPOINT ["/usr/bin/make"]
