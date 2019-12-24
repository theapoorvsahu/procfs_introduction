#!/bin/bash

##------>> MAKING MODULES <<------

## Make .o/.ko files (modules) from .c file 
make -C /usr/src/linux-source-4.18.0/ M=`pwd` modules

## Load the modules
insmod proc_seq_example1.c

## To Remove the modules
#rmmod proc_seq_example1.c

##------>> COMPILING TEST <<------

## compiling test program file (.c)
gcc test.c -o test

##------>> TRACING <<------

## Turn off Tracing
echo 0 > /sys/kernel/debug/tracing/tracing_on

## Clear the Previous Traces (Buffers)
cat /sys/kernel/debug/tracing/trace_pipe

## Set the Current Tracer to Function
echo function > /sys/kernel/debug/tracing/current_tracer

## Add the following filters that needs to be traced
$ echo proc_reg_*                >> /sys/kernel/debug/tracing/set_ftrace_filter
$ echo '*:mod:proc_seq_example1' >> /sys/kernel/debug/tracing/set_ftrace_filter
$ echo seq_open                  >> /sys/kernel/debug/tracing/set_ftrace_filter
$ echo seq_read                  >> /sys/kernel/debug/tracing/set_ftrace_filter
#$ echo vfs_read                  >> /sys/kernel/debug/tracing/set_ftrace_filter

## Check the Trace Filters
$ cat /sys/kernel/debug/tracing/set_ftrace_filter

## Turn on Tracing
echo 1 > /sys/kernel/debug/tracing/tracing_on

## Run the compiled test.c program
./test

## Turn off Tracing
echo 0 > /sys/kernel/debug/tracing/tracing_on

## Check the Trace
#cat /sys/kernel/debug/tracing/trace_pipe | grep proc_test | less
cat /sys/kernel/debug/tracing/trace | grep proc_test | less
