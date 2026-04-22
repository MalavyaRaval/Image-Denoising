# Non-Local Means (NLM) Denoising

An efficient image denoising implementation featuring Serial CPU, standard CUDA, and optimized CUDA Shared Memory versions.

## Results
This project was benchmarked on Perlmutter High Performance Computing (HPC) nodes. 
*   `/results/` contains the raw data generated on the HPC nodes.
*   `/results/images/` contains the visual outputs and performance plots (e.g., `speedup.png`, `runtime-GPU.png`).

---

## 1. Prerequisites
*   **Hardware:** NVIDIA GPU (for CUDA implementations).
*   **Software:** NVIDIA CUDA Toolkit, GCC, and MATLAB (for image conversion).

## 2. Configuration
Before running, open each `.c` or `.cu` file and adjust the global variables at the top of the script:
*   `PIXELS`: The dimension of your square image (e.g., 512 for 512x512).
*   `PATCH_SIZE`: The size of the comparison window (typically 3-7).
*   `FILTER_SIGMA`: Controls the smoothness of the result.
*   `PATCH_SIGMA`: Controls the sensitivity to patch similarity.

*Note: Higher sigma values result in more aggressive denoising but risk blurring fine details.*

## 3. Workflow
The workflow requires MATLAB to convert images to text files, the C/CUDA code to perform the filtering, and MATLAB again to reconstruct the PNG output.

### Step-by-Step Execution:
1.  **Prepare your image:** Place your input image (must be square, max 512x512) in the directory and rename it to `image.png`.
2.  **Convert to text:**
    ```bash
    matlab -batch "run image_read.m"
    ```
3.  **Compile and Run:**
    ```bash
    make clean
    make all
    ./nlm-cuda        # Or use ./nlm-serial or ./nlm-cuda-shared
    ```
4.  **Reconstruct output:**
    ```bash
    matlab -batch "run denoised_image_read.m"
    ```
    *This generates `filtered_image.png` and `noise_removed.png`.*
