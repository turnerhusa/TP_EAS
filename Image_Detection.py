#from https://datacarpentry.org/image-processing/08-edge-detection/

import skimage
import skimage.feature
import skimage.io
# import skimage.viewer
import sys
import PIL
from PIL import Image
import cv2

#filename == .png name
#sigma == the value of the Gaussian smoothing
filename = sys.argv[1]
sigma = float(sys.argv[2])
low_threshold = float(sys.argv[3])
high_threshold = float(sys.argv[4])

#load and display original image as grayscale
image = skimage.io.imread(fname=filename, as_gray=True)
# viewer = skimage.viewer(image=image)
# viewer.show()

#apply Canny edge detection
edges = skimage.feature.canny(
    image=image,
    sigma=sigma,
    low_threshold=low_threshold,
    high_threshold=high_threshold,
)

print(edges)

cv2.imwrite(edges, 'test-output.jpg', params=(cv2.IMWRITE_JPEG_QUALITY, 0));

#display edges
# viewer = skimage.viewer.ImageViewer(edges)
# viewer.show()

# TODO use this to save the file for processing 
# save binary image; first find beginning of file extension
# dot = filename.index(".")
# binary_file_name = filename[:dot] + "-binary" + filename[dot:]
# skimage.io.imsave(fname=binary_file_name, arr=skimage.img_as_ubyte(binary))
