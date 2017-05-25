# cVideoProcessing_OpenCV
Video Processing using OpenMP

The cVideoProcessor performs the following functions :
1. Reads Video File.
2. Processes the video file frame by frame
3. Calculated mean and frame number of each frame and prints it on the top left corner of the image
4. Converts each frame to Gray image
5. Define a region of Interest in the image to segment the foreground from background 
6. Applies threshold on the extracted foreground in the region of interests 
7. perform erosion and flooding to identify each object in th e image
