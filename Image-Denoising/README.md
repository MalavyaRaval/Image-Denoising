# Non-Local Means

A Non-Local-Means algorithm implementation using NVIDIA CUDA.

`/results/` contains the results produced by using Perlmutter's High Performance Computing (HPC) Nodes.

`/results/image/` contains the visual results produced by running the implementations and  contains the images used to produce the results.

## 1. Before using
`nlm-serial.c:` Serial Implementation

`nlm-cuda.cu:` Implementation using NVIDIA CUDA

`nlm-cuda-shared.cu:` Implementation using NVIDIA CUDA and shared memory between threads

* Pull the directory and save it locally. Within that directory, add an image of strict sizing up to 512x512. The implementations work only for square images. 
* Open each .c and .cu file and edit the global variables (PIXELS, PATCH_SIZE, FILTER_SIGMA, PATCH_SIGMA) at the top of the script according to your needs. 
* PIXELS refers to the size of your image (PIXELSxPIXELS).

## 2. Matlab files
The `.m` files contain supplementary functions in order to convert png/txt files. The image used to run the implementations MUST have the name `image.png`. Running the `image_read` file will produce the *noisy_image.txt* and running the `denoised_image_read` file will produce the *filtered_image.png* and *noise_removed.png* files.

```
module load matlab
matlab
run image_read.m
```

## 3. Local execution
In order to test the implementations locally on your machine, use the files located in the home directory. Follow the commands in the order given below:

```
make clean
make all
./<filename>
```

Make clean should be used if you have already ran the programs before. Instead of filename type the implementation you want to run. All of the above commands are declared in the Makefile.


## 4. Generate png file after running the filter implementation

```
module load matlab
matlab
run denoised_image_read.m
```
