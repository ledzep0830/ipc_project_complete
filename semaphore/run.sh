#!/bin/sh

gcc no_semaphore.c -o no_semaphore
gcc semaphore.c -o semaphore
gcc destroy.c -o destroy

./no_semaphore & ./no_semaphore

./semaphore & ./semaphore

./destroy
