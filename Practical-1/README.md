# Practical 1: 2D Convolution Analysis

## Overview

Practical 1 focuses on understanding and implementing 2D convolution, a fundamental operation in image processing and computer vision. You will implement manual convolution from scratch and compare it with MATLAB's built-in functions to understand performance trade-offs between custom and optimised implementations.

---

## Problem Description

### 2D Convolution for Edge Detection

Convolution is a mathematical operation that applies a filter kernel to an image to produce outputs like edge detection, blurring, sharpening, etc. In this practical, you will implement edge detection using the **Sobel operator**.

#### The Sobel Operator

The Sobel operator consists of two 3×3 kernels for detecting edges in the horizontal (Gx) and vertical (Gy) directions:

**Sobel Kernel for Horizontal Edges (Gx):**

$$
G_x = \begin{bmatrix}
-1 & 0 & +1 \\
-2 & 0 & +2 \\
-1 & 0 & +1
\end{bmatrix}
$$

**Sobel Kernel for Vertical Edges (Gy):**\

$$
G_y = \begin{bmatrix}
-1 & -2 & -1 \\
0 & 0 & 0 \\
+1 & +2 & +1
\end{bmatrix}
$$

The magnitude of edges at each pixel is computed as:

$$
G = \sqrt{G_x^2 + G_y^2}
$$


---
## Folder Structure

```
Practical-1/
├── README.md                    # This file
├── run_analysis.m              # Main MATLAB script with TODO sections
└── sample_images/              # Sample images for testing
    ├── image_128x128.png
    ├── image_256x256.png
    ├── image_512x512.png
    ├── image_1024x1024.png
    └── image_2048x2048.png
```
---
## Implementation Requirements

### Part 1: Manual 2D Convolution Implementation


**Requirements:**
- ✓ DO NOT use MATLAB's `conv2()` function
- ✓ DO NOT use `imfilter()` or similar built-in convolution functions
- ✓ Implement convolution using nested loops
- ✓ Handle image boundaries using appropriate padding. This is crucial as you will need to match the padding style you used in this implementation to the ones available in MATLAB to allow for peformance comparison


### Part 2: Built-in 2D Convolution Implementation

**Requirements:**
- ✓ MUST use MATLAB's `conv2()` function
- ✓ Ensure consistent output with manual implementation
- ✓ Document any padding or mode choices



### Part 3: Testing and Analysis


**Expected Analysis:**
- Load images from `sample_images/`
- Define Sobel operators (Gx, Gy)
- For each image:
  - Run both convolution implementations multiple times for accuracy
  - Measure execution time using `tic` and `toc`
  - Compute speedup: $Speedup = T_{manual} / T_{builtin}$
  - Verify correctness by comparing outputs
  - Store results (image size, times, speedup)


### Convolution Output Modes

- **'full':** Output size = input_size + kernel_size - 1
- **'same':** Output size = input_size (centered kernel)
- **'valid':** Output size = input_size - kernel_size + 1



---
## Running the Practical

### Prerequisites

- MATLAB (R2020a or later recommended) or OCTAVE
- Image Processing Toolbox (for imread/imshow)
- Basic knowledge of MATLAB functions

### Execution Steps

1. **Edit the script:**
   ```bash
   cd Practical-1
   matlab run_analysis.m
   ```

2. **Implement functions:**
   - Complete `my_conv2()` function
   - Complete `inbuilt_conv2()` function
   - Complete `run_analysis()` function

3. **Run the analysis:**
   ```matlab
   run_analysis()
   ```

4. **View results:**
   - Console output with timing comparisons
   - Performance plots (if implemented)
   - Saved edge detection results

### MATLAB Script Structure

```matlab
%% PART 1: Manual 2D Convolution
function output = my_conv2(varargin)
    % YOUR IMPLEMENTATION HERE
end

%% PART 2: Built-in 2D Convolution
function output = inbuilt_conv2(varargin)
    % YOUR IMPLEMENTATION HERE
end

%% PART 3: Testing and Analysis
function run_analysis()
    % Load images
    % Define kernels
    % Measure performance
    % Store results
    % Plot comparison
end
```
### Common Issues

| Issue | Solution |
|-------|----------|
| Images don't load | Check file paths, ensure sample_images/ directory exists |
| Dimension mismatch | Verify convolution output size handling (padding/trimming) |
| Unexpected timing | Use longer runs or `timeit()` for more accurate measurements |
| Wrong edge detection | Verify kernel values match Sobel operator definition |
| Memory issues on large images | Process images in blocks or use smaller test set first |

---
## References

### MATLAB Functions Reference

- `imread()` - Load image from file
- `imshow()` - Display image
- `conv2()` - 2D convolution (built-in)
- `tic/toc` - Timing measurement
- `timeit()` - Precise function timing
- `rgb2gray()` - Convert RGB to grayscale
- `padarray()` - Add padding to array

### Image Processing Resources

- [MATLAB Image Processing Toolbox Documentation](https://www.mathworks.com/help/images/)
- [Sobel Operator Wikipedia](https://en.wikipedia.org/wiki/Sobel_operator)
- [Digital Image Processing](https://www.imageprocessingplace.com/) - General reference

### Performance Analysis

- MATLAB Profiler for detailed performance analysis
- `profile on / profile off` for code profiling
- Memory profiling with `memory()` function

---
## Version History

- **Initial Release**: Practical-1 2026
- **Last Updated**: February 15th 2026

---

## Contact & Support

For questions about this practical, refer to:
- Course syllabus and lecture notes
- TA/Tutors during lab sessions
- Practical Manual
