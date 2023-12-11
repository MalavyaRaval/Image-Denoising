#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "supplementary.h"
#include <chrono>

//!------------------------------------------------------------------
//! EDIT THESE VALUES ACCORDING TO THE IMAGE SIZE AND SPECIFICATIONS

#define PIXELS 64 // PIXELS x PIXELS
#define PATCH_SIZE 3
#define FILTER_SIGMA 0.0185
#define PATCH_SIGMA 3.1550

//!------------------------------------------------------------------

// Global variables
float *image;
int padding = PATCH_SIZE / 2;

// Functions
float *gaussian_filter();
float *nonLocalMeans();
float compare_patches(int i, int j, float *G);


int main() {
    // read image from txt
    image = image_from_txt(PIXELS, padding);
    int padded_size = PIXELS * PIXELS + 4 * padding * PIXELS + 4 * padding * padding;
    int start = PIXELS * padding + 2 * padding * padding + padding; // skip first padding rows

    {
        auto tic = std::chrono::high_resolution_clock::now();
        image = nonLocalMeans();
        auto toc = std::chrono::high_resolution_clock::now();

        FILE *f = fopen("filtered_image.txt", "w");
        if (f == NULL) {
            printf("Cannot open filtered_image.txt\n");
            exit(1);
        }

        int pixels_counter = 0;
        for (int i = start; i < (padded_size - start); i++) {
            fprintf(f, "%f ", image[i]);
            pixels_counter++;
            if (pixels_counter == PIXELS) {
                pixels_counter = 0;
                i += 2 * padding;
                fprintf(f, "\n");
            }
        }

        fclose(f);
        free(image);

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(toc - tic).count();
        printf("*NLM-Serial Duration = %f second(s)* || (Pixels, Patch) = (%d, %d)\n", duration / 1e6, PIXELS, PATCH_SIZE);
    }

    return 0;
}

float *nonLocalMeans(){
    int padded_size = PIXELS*PIXELS + 4*(padding*PIXELS + padding*padding);
    float *filtered_image = (float *)malloc(padded_size*sizeof(float));
	if(filtered_image == NULL){
        exit(1);
    }
	// Fill array with -1, so after adding the image's values
	// the padding will have -1 values
    for(int i=0; i<padded_size; i++){
        filtered_image[i] = (float)-1;
	}
    float *G = (float *)malloc(0*sizeof(float));
	if(G == NULL){
		exit(1);
	}
    G = gaussian_filter();
	
	int row_size = PIXELS + 2*padding;
    for(int it1=padding; it1<(PIXELS + padding); it1++){
        for(int it2=padding; it2<(PIXELS + padding); it2++){
            filtered_image[it1*row_size + it2] = 0;
			float weight;
            float Z = 0;
            for(int it3=padding; it3<(PIXELS + padding); it3++){
                for(int it4=padding; it4<(PIXELS + padding); it4++){
					weight = (float)(exp(-compare_patches(it1*row_size+it2, it3*row_size+it4, G)/(float)(FILTER_SIGMA*FILTER_SIGMA)));
					filtered_image[it1*row_size+it2] += weight * image[it3*row_size+it4];
                    Z += weight;
                }
            }
            filtered_image[it1*row_size+it2] = filtered_image[it1*row_size+it2] / Z;
        }
    }
    return filtered_image;
}

//! Compute the gaussian filter
float *gaussian_filter(){
    float *G = (float *)malloc(PATCH_SIZE*PATCH_SIZE*sizeof(float));
    if(G == NULL){
        exit(1);
	}
	// bound for the 2D Gaussian filter
    int bound = PATCH_SIZE/2;
    for(int x=-bound; x<=bound; x++){
        for(int y=-bound; y<=bound; y++){
			int index = (x+bound)*PATCH_SIZE + (y+bound);
            G[index] = exp( -(float)(x*x+y*y)/(float)(2*PATCH_SIGMA*PATCH_SIGMA) ) / (float)(2*M_PI*PATCH_SIGMA*PATCH_SIGMA);
        }
    }
    return G;
}

//! Compares the patches of pixels i and j
float compare_patches(int i, int j, float *G){
    float patch_comp = 0;
    for(int m=0; m<PATCH_SIZE; m++){
        for(int n=0; n<PATCH_SIZE; n++){
			int first_index = i + (m-padding)*(PIXELS+2*padding) + n - padding; // reffering to a pixel from i's patch
			int second_index = j + (m-padding)*(PIXELS+2*padding) + n - padding; // reffering to a pixel from j's patch
			
			// image[x] == -1 means it's the added padding
            if((image[first_index] != (float)-1) && (image[second_index] != (float)-1)){
                float diff = image[first_index] - image[second_index];
                patch_comp += G[m*PATCH_SIZE+n]*(diff*diff);
            }
        }
    }
    return patch_comp;
}





