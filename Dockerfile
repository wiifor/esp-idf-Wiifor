FROM debian:buster

LABEL maintainer="elie.taillardat@wiifor.com"

ARG ESP_TCHAIN_VER="xtensa-esp32-elf-linux64-1.22.0-80-g6c4433a-5.2.0"
ARG JLINK_VER="JLink_Linux_V644f_x86_64"

RUN apt-get -q update \
    && apt-get -qy --no-install-recommends --no-install-suggests install  \
       gcc git wget make \
       libncurses-dev flex bison gperf \
       python python-pip python-setuptools \
       python-serial python-cryptography python-future python-pyparsing python-pyelftools \
       python3 python3-pip python3-setuptools \
       libusb-1.0-0-dev libusb-dev libncurses5 libpython2.7 \
       fuse libfuse-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Get the ESP32 toolchain
ENV ESP_TCHAIN_BASEDIR /opt/dedale/esp32
RUN mkdir -p $ESP_TCHAIN_BASEDIR \
    && wget -O $ESP_TCHAIN_BASEDIR/esp32-toolchain.tar.gz \
       https://dl.espressif.com/dl/$ESP_TCHAIN_VER.tar.gz \
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

# Install JLink for JTAG debugging
COPY $JLINK_VER.deb /tmp/$JLINK_VER.deb
RUN dpkg -i /tmp/$JLINK_VER.deb \
    && rm /tmp/$JLINK_VER.deb

# Setup littlefs-fuse tool
ENV LITTLEFS_FUSE_BASEDIR /opt/littlefs-fuse
COPY littlefs-fuse $LITTLEFS_FUSE_BASEDIR
RUN cd $LITTLEFS_FUSE_BASEDIR && make

# Add the toolchain binaries to PATH
ENV PATH $PATH:$ESP_TCHAIN_BASEDIR/xtensa-esp32-elf/bin

# Environment variable for jenkins pipeline purpose
ENV NEXUS_ESP32_BUILD true

# Expose port for gdb server and openOCD connexion
EXPOSE 3333

# For debug command purpose
VOLUME $ESP_TCHAIN_BASEDIR
RUN cd /tmp && mkdir -p esp32 && cd esp32 && cp -avr $ESP_TCHAIN_BASEDIR/* .
ADD debug-entrypoint.sh /opt/dedale
RUN chmod +x /opt/dedale/debug-entrypoint.sh

# Install the dedale CLI package
ENV DEDALE_CLI_PATH /opt/dedale
COPY "dedale*whl" $DEDALE_CLI_PATH
RUN cd $DEDALE_CLI_PATH \
    && pip3 install dedale*whl

ENTRYPOINT ["/usr/bin/make"]