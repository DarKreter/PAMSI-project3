#!/bin/bash

cd myBuild

for i in {0..10}
do
    ./firmware/firmware 2> /dev/null | grep 'WON'
done