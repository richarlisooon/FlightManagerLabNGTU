#!/bin/bash

function docker_compose {
    sudo docker compose down
    echo "[script] Building database-service ..."
    cd database-service
    sudo chmod +x service.bash
    sudo ./service.bash -bd
    cd ..

    echo "[script] Building identity-service ..."
    cd identity-service
    sudo chmod +x service.bash
    sudo ./service.bash -bd
    cd ..

    echo "[script] Building gateway ..."
    cd gateway
    sudo chmod +x service.bash
    sudo ./service.bash -bd
    cd ..

    echo "[script] Building plane-service ..."

    cd plane-service
    sudo chmod +x service.bash
    sudo ./service.bash -bd
    cd ..

    echo "[script] Starting Docker services ..."
    sudo docker compose up
}
function docker_less {
    echo "not realized yet"
}
function client {
    while read LINE
      do export $LINE
    done < docker-less.env
    cd client
    sudo chmod +x client
    ./client.bash -b
    cd build/src
    ./client
}
function test {
    while read LINE
      do export $LINE
    done < docker-less.env
    cd client
    sudo chmod +x client
    ./client.bash -t
    cd build/src
    ./client
}

case "$1" in
    -d)
      docker_compose
      ;;
    -dl)
      docker_less
      ;;
    -cli)
      client
      ;;
    -t)
      test
      ;;
    *)
      echo "Usage: $0 {-d|-dl}"
      exit 1
      ;;
esac
