#!/bin/bash

service_name="plane-service"

function clean {
    echo "[script] cleaning $service_name ..."
    rm -rf build
    echo "[script] cleaning $service_name finished"
}

function build_docker_less {
    echo "[script] building $service_name exec ..."
    mkdir build
    cmake -G "MinGW Makefiles" -B ./build
    cd build || exit
    make
    cd ../
    echo "[script] building $service_name exec finished"
}

function build_docker {
    echo "[script] building $service_name image ..."
    if sudo docker images -q "$service_name" | grep -q .; then
        sudo docker rmi -f "$service_name"
    fi
    sudo docker build . -t "$service_name"
    echo "[script] building $service_name image finished"
}

case "$1" in
    -cl)
        clean
        ;;
    -bdl)
        build_docker_less
        ;;
    -bd)
        build_docker
        ;;
    *)
        echo "Usage: $0 {-cl|-bdl|-bd}"

esac
