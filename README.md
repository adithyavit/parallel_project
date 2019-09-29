# parallel_project
# ABSTRACT:
Implementation of noise reduction with adaptive filters.
# Language used:
C++
# Library used:
OPENCV
# OBJECTIVE:
Implementation of median filter with adaptive de-noising.
Euclidian, fuzzy and Canberra metrics are used to detect noise.
# Experiment:
An image was selected and noise was manually added to it using
matlab.
Using c++ program we wrote a function that detects noise in the
algorithm and adds it to an array.
Then the pixels in this array is iterated through and mean filter is
applied on those specific pixels.
# Euclidian metric:
![](images/euclidean_metric.png)

# Fuzzy metric:
![](images/fuzzy_metric)

# Canberra metric:
![](images/fuzzy_metric)

Using one of the above metric we find the distance between two
pixels(in terms of intensity).
For Euclidian and Canberra, if the value is greater than a certain
threshold (65 for the noise we chose), that particular pixel is added
to an array.
For fuzzy metric if the value is less than a particular threshold(0.1
for the noise we chose), that particular pixel is added to an array.
Then the array is iterated through and all the pixels in that
particular array are de-noised using mean filter.

We have implemented code Euclidian and fuzzy metrics by
reference from previous papers and Canberra metric is a new
implementation.

# Parallelization:
We have used multi-processing to parallelize both noise detection
and noise removal algorithms.
Openmp is used to implement multi-processing, it is an
implementation of multi-threading. 

In the papers we referred the implementation was done using GPU,
whereas we have implemented the algorithms using Openmp.

# Output:
Original image:
![](images/Original_image)

Denoised image(using Canberra with filter size 3):
![](images/denoised_image)

Results with Euclidian metric compared to fuzzy in case of few
white pixels.

Eculidean:
![](images/euclidean)

Fuzzy:
![](images/fuzzy)

As you can see from the above pictures, even few very contrasting
pixels were able to escape from the fuzzy metric but Euclidian was
effective in finding them.

Comparison of Euclidian and Canberra in case of very contrasting
colors.

Euclidean:
![](images/euclidean2)

Canberra:
![](images/canberra2)

Results:

| metric    | filter size | avg time    | psnr ratio | mse      | ssim   |
|-----------|-------------|-------------|------------|----------|--------|
| Fuzzy     | 3           | 0.520046    | 22.2587    | 386.555  | 0.7809 |
| Fuzzy     | 5           | 0.480377    | 21.7188    | 437.7252 | 0.7667 |
| Euclidian | 3           | 0.193503333 | 21.1494    | 499.0459 | 0.7823 |
| Euclidian | 5           | 0.205673667 | 20.8222    | 538.0959 | 0.7737 |
| Canberra  | 3           | 0.493391667 | 22.0936    | 401.5285 | 0.7716 |
| Canberra  | 5           | 0.552958667 | 21.4228    | 468.5957 | 0.7469 |

Avg time:
![](images/average_time)

ssim:
![](images/ssim)

mse:
![](images/mse)

psnr ratio
![](images/psnr_ratio)

# Conclusion:
Fuzzy metric performed better in noise reduction whereas the Euclidian metric was faster. The metric Canberra we used gave results faster than fuzzy metric and error less than Euclidian metric.
But fuzzy had a problem of leaving few white pixels unidentified and Canberra was ineffective with contrasting colours. So taking all these parameters into account, we can conclude that Euclidian metric is best for most cases.

# References:

1. http://www.sciencedirect.com/science/article/pii/S1877050913005723

2. http://www.sciencedirect.com/science/article/pii/S1877050914003846







