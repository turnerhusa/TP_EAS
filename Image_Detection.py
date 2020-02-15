import numpy as np
import matplotlib.pyplot as plt
import sys

import skimage.io
import skimage.feature
# simple filters for comparison
from skimage.filters import roberts, sobel, sobel_h, sobel_v, scharr, \
    scharr_h, scharr_v, prewitt, prewitt_v, prewitt_h, farid_v, farid_h

#project files
import Image_Process_Edges as EdgeProcessor

filename = sys.argv[1]
sigma = float(sys.argv[2])
low_threshold = float(sys.argv[3])
high_threshold = float(sys.argv[4])

#load and display original image as grayscale
image = skimage.io.imread(fname=filename, as_gray=True)
#skimage.io.imread(fname="citySkyLine.jpeg", as_gray=True)


edge_roberts = roberts(image)
edge_sobel = prewitt(image)

edges = skimage.feature.canny(
    image=image,
    sigma=sigma,
    low_threshold=low_threshold,
    high_threshold=high_threshold,
)

shapes = EdgeProcessor.processEdges(edges)
print(shapes)

#displaying data
fig, ax = plt.subplots(ncols=2, sharex=True, sharey=True,
                       figsize=(8, 4))

ax[0].imshow(edges, cmap=plt.cm.gray)
ax[0].set_title('Canny')

ax[1].imshow(edge_sobel, cmap=plt.cm.gray)
ax[1].set_title('Sobel Edge Detection')

for a in ax:
    a.axis('off')

plt.tight_layout()
plt.show()

#display edges
#viewer = skimage.viewer.ImageViewer(edges)
#viewer.show()

# TODO use this to save the file for processing 
# save binary image; first find beginning of file extension
# dot = filename.index(".")
# binary_file_name = filename[:dot] + "-binary" + filename[dot:]
# skimage.io.imsave(fname=binary_file_name, arr=skimage.img_as_ubyte(binary))
