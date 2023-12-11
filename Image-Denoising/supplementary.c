#include <stdio.h>
#include <stdlib.h>
#include <time.h>


float *image_from_txt(int pixels, int padding){
    int padded_size = pixels*pixels + 4*padding*pixels + 4*padding*padding;
    float *image = (float *)malloc(padded_size*sizeof(float));
    if(image == NULL){
        printf("Cannot allocate space for image.\n");
        return NULL;
    }
	
	// Fill array with -1, so after adding the image's values
	// the padding will have -1 values
    for(int i=0; i<padded_size; i++){
        image[i] = -1;
	}
	
    FILE *f = fopen("noisy_image.txt","r");
	if(f == NULL){
		printf("Cannot open image.txt.\n");
	}
	
    for(int i=padding; i<(pixels+padding); i++){
        for(int j=padding; j<(pixels+padding); j++){
            if (j != (pixels + padding - 1)){
                if(fscanf(f, "%f\t", &image[i*(pixels+(2*padding))+j]) != 1){
                    printf("Error reading image.txt1.\n");
				}
            }
            else{
                if(fscanf(f, "%f\n", &image[i*(pixels+(2*padding))+j]) != 1){
                    printf("Error reading image.txt2.\n\n");
				}
            }
        }
    }
	
    fclose(f);
    return image;
}


double elapsed_time(struct timespec start_time, struct timespec end_time){
    struct timespec temp;
    if ((end_time.tv_nsec - start_time.tv_nsec) < 0)
    {
        temp.tv_sec = end_time.tv_sec - start_time.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end_time.tv_nsec - start_time.tv_nsec;
    }
    else
    {
        temp.tv_sec = end_time.tv_sec - start_time.tv_sec;
        temp.tv_nsec = end_time.tv_nsec - start_time.tv_nsec;
    }
    double returnval = (double)temp.tv_sec +(double)((double)temp.tv_nsec/(double)1000000000);

    return returnval;
}

