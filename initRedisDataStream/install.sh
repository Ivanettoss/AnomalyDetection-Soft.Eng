#!/bin/bash

cd src
sudo make
cd ../bin

# Se sono presenti parametri aggiuntivi, passali a ./main
if [ "$#" -gt 0 ]; then
    sudo ./main "$@"
else
    sudo ./main
fi

