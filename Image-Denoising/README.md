<p align="center">
  <img width="600" height="257" src="https://i.imgur.com/DOgejso.png">
</p>

# Parallel-Exercise3

A Non-Local-Means algorithm implementation using NVIDIA CUDA.

`/results/` contains the results produced by using AUTh's High Performance Computing (HPC) infrastructure.

`/results/image_results/` contains the visual results produced by running the implementations. 

`/images/` contains the images used to produce the results.

## **1. Before using**
`nlm-serial.c:` Serial Implementation

`nlm-cuda.cu:` Implementation using NVIDIA CUDA

`nlm-cuda-shared.cu:` Implementation using NVIDIA CUDA and shared memory between threads

* Pull the directory and save it locally. Within that directory, add an image of strict sizing up to 256x256. The implementations work only for square images. 
* Open each .c and .cu file and edit the global variables (PIXELS, PATCH_SIZE, FILTER_SIGMA, PATCH_SIGMA) at the top of the script according to your needs. 
* PIXELS refers to the size of your image (PIXELSxPIXELS).

## **2. Matlab files**
The `.m` files contain supplementary functions in order to convert png/txt files. The image used to run the implementations MUST have the name `image.png`. Running the `image_read` file will produce the *noisy_image.txt* and running the `denoised_image_read` file will produce the *filtered_image.png* and *noise_removed.png* files.

## **3. Local execution**
In order to test the implementations locally on your machine, use the files located in the home directory. Follow the commands in the order given below:

```
make clean
make all
./<filename>
```

Make clean should be used if you have already ran the programs before. Instead of filename type the implementation you want to run. All of the above commands are declared in the Makefile.

## **4. HPC execution**
Everything can be run on AUTh's HPC (for those with an account), by using the same files described above. Use the shell file located in the `/hpc/` directory as well. Edit it according to which implementation you want to run and submit it to the HPC for execution. To do so, run the following command in the shell:

```
sbatch <shell_file_name>.sh
```

## **5. Google Colab execution**
Another option is using Google Colab (https://colab.research.google.com). The steps are as follows:
1. Change runtime type to GPU.
2. Load all files inside the notebook you created.
3. Type the following in the first code cell and execute it: `%load_ext nvcc_plugin`.
4. You can use the same commands as running it locally, but with a `!` in front of each command. For example: `!make all`
#

*Refference:* Antoni Buades, Bartomeu Coll, and J-M Morel. **A non-local algorithm for image denoising.** In 2005 IEEE Computer Society Conference on Computer Vision and Pattern Recognition (CVPR’05), volume 2, pages 60–65. IEEE, 2005.


Repo for the third exercise of course 050 - Parallel and Distributed Systems, Aristotle University of Thessaloniki, Dpt. of Electrical & Computer Engineering.

# Image-Denoising
