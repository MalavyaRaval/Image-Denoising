%% SCRIPT: Image pre-processing (RGB to Grayscale & Noise)
%
% Image preprocessing for a CPU/GPU implementation of a 
% non local means algorithm as described in [1], in C.
%
% The C code can be found in the author's github (see bottom of script).
%
% DEPENDENCIES
%
% [1] Antoni Buades, Bartomeu Coll, and J-M Morel. A non-local
%     algorithm for image denoising. In 2005 IEEE Computer Society
%     Conference on Computer Vision and Pattern Recognition (CVPR '05),
%     volume 2, pages 60-65. IEEE, 2005.
%

clear all %#ok
close all
clc

%% USEFUL FUNCTION(S)

% image normalizer
normImg = @(I) (I - min(I(:))) ./ max(I(:) - min(I(:)));

%% READ IMAGE, CONVERT TO GRAYSCALE & NORMALIZE

% change file name accordingly
image = imread('image.png', 'png');
image = rgb2gray(image);
image = mat2gray(image);
% normalize the image
image = normImg(image);

%% APPLY NOISE AND EXPORT TO .PNG

% apply noise to image
noiseParams = {'gaussian', 0, 0.001};
image = imnoise( image, noiseParams{:} );
imwrite(image, 'noisy_image.png');

%% EXPORT NOISY IMAGE TO .TXT FILE

fileID = fopen('noisy_image.txt', 'wt');
for iter = 1:size(image, 1)
    fprintf(fileID, '%g\t', image(iter,:));
    fprintf(fileID, '\n');
end
fclose(fileID);

%%------------------------------------------------------------
%
% AUTHORS
%
%   Angelos Spyrakis                        aspyrakis@auth.gr
%
% VERSION
%
%   0.1 - February 1, 2021
%
% CHANGELOG
%
%   0.1 (FEB 1, 2021) - Angelos
%       * initial implementation
%
% GITHUB REPOSITORY
%   
%   https://github.com/ReaverAUTh/pad_auth_3
%
% --
% An Aristotle University of Thessaloniki ECE Department
% project for course 050 - Parallel & Distributed Systems.
% ------------------------------------------------------------