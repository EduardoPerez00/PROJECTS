README:**ENUNCIADO**
In this section we propose three basic problems[^1] to be implemented by launching an OpenCL kernel with the core computations for each one. As a result and in order to check the correctness of each problem, plot on the screen the corresponding results, either numerical or transformed images.

Image flip. Transform an image by flipping it over a central vertical axis. That is, this transformation has the same effect as seeing that image reflected in a mirror. The transformation should be done in-place, meaning that the same source buffer for the former image should hold the transformed image after the kernel execution.

Histogram. Process a given image and calculate the histogram for each color channel: red, green, and blue. Each histogram has 256 entries to classify any possible value of the given image.

Image rotation. Transform an image by rotating it over the center of the image. The rotation angle should be given as an argument to the kernel. The resulting rotated image should be stored in a new output buffer. Remember the following equations:

x2 = cos(angle) * (x1 - x0) - sin(angle) * (y1 - y0) + x0

y2 = sin(angle) * (x1 - x0) + cos(angle) * (y1 - y0) + y0

In these equations, (x0, y0) stand for the coordinates of the center point of the rotation transformation. (x1, y1) stand for the source point in the image and (x2, y2) refer to the destination point after the rotation transformations for the former point (x1, y1). More information at https://homepages.inf.ed.ac.uk/rbf/HIPR2/rotate.htm

[^1]: Feel free to implement any other problem of your consideration as far as the complexity is similar.

Overall Task. For this final part of the lab description, measure or elaborate the following metrics for at least one of the previous exercises. These metrics are intended for characterizing the application itself, specially the OpenCL key points. Consider the methodological approaches seen in the course or anything else you consider. In any case, please, describe your approach in the report.

Execution time of the overall program
Execution time of the kernel
Bandwidth to/from memory to/from kernel. Amount data interchanged with memory for every second
Throughput of the kernel. Effective work per second
Memory footprint of the program. Pay special attention to the OpenCL kernel