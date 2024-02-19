SHELL := /bin/bash # Use bash syntax

CC = g++ -std=c++11
CFLAGS = -O3
NVCC = nvcc -arch=sm_80
ARGS = -ptx

default: all

nlm-serial:
	$(CC) $(CFLAGS) -o nlm-serial nlm-serial.c -lm

nlm-cuda: nlm-cuda.cu
	$(NVCC) -o nlm-cuda nlm-cuda.cu

nlm-cuda-shared: nlm-cuda-shared.cu
	$(NVCC) -o nlm-cuda-shared nlm-cuda-shared.cu
.PHONY: clean

all: nlm-serial nlm-cuda nlm-cuda-shared

clean:
	rm -f nlm-serial nlm-cuda nlm-cuda-shared

