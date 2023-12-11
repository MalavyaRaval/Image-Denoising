%% SCRIPT: TXT to PNG conversion and noise visualization
%
% Converting a .txt to .png, after running a CPU/GPU implementation 
% of a non local means (NLM) algorithm as described in [1], in C, to
% visualize the effectivenes of the algorithm.
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
% [2] Angelos Spyrakis. "image_read.m" file contained within the same 
%     directory, for pre-processing the image used by the NLM algorithm.
%
%

clear all %#ok
close all
clc

%% IMPORT .TXT FILES OF NOISY AND FILTERED IMAGE

delimiterIn = '\t';
headerlinesIn = 0;

filename1 = 'noisy_image.txt';
noisy_image = importdata(filename1, delimiterIn, headerlinesIn);

delimiterIn = ' ';
filename2 = 'filtered_image.txt';
filtered_image = importdata(filename2, delimiterIn, headerlinesIn);

%% EXPORT TO .PNG

imwrite(filtered_image, 'filtered_image.png');

% calculate noise removed & export
noise = filtered_image - noisy_image;
noise = mat2gray(noise);
imwrite(noise, 'noise_removed.png');

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