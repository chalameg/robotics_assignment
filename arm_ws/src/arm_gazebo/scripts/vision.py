import cv2 as cv
import numpy as np
img = cv.imread('car.jpg', cv.IMREAD_GRAYSCALE)

# filter = np.array([
#     [1,1,1],
#     [1,1,1],
#     [1,1,1]
# ])

filter = np.array([
    [-1,0,1],
    [-2,0,2],
    [-1,0,1]
])

k = 3
new_img = np.zeros_like(img)

for i in range(img.shape[0] - 2):
    for j in range(img.shape[1] - 2):
        patch = img[i:i+k, j:j+k]
        #convolution
        # result = filter*patch
        # result = [
        #     result[:, :, 0].mean(),
        #     result[:, :, 1].mean(),
        #     result[:, :, 2].mean(),
        # ]
        # new_img[i,j] = result
        #edge detection
        Gx = (filter*patch).sum()
        Gy = (filter.T*patch).sum()
        G = np.sqrt(Gx**2+Gy**2)
        new_img[i,j] = G

# print(img.shape)

cv.imshow('Image', new_img)

cv.waitKey(0)