#!/bin/sh

gcc message_buffer_semaphore.h message_buffer_semaphore.c consumer.c
mv a.out consumer

gcc message_buffer_semaphore.h message_buffer_semaphore.c producer.c
mv a.out producer

gcc message_buffer_semaphore.h message_buffer_semaphore.c destroy.c
mv a.out destroy
