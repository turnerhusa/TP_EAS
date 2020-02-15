import numpy as np
import matplotlib.pyplot as plt
import sys
import itertools
import skimage.io
import skimage.feature
from queue import LifoQueue 
from skimage import measure
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

#shapes = EdgeProcessor.processEdges(edges)
#print(shapes)

contours = measure.find_contours(edges, 0.8)


newContour_stack = LifoQueue()
numOfContours = len(contours)
for n in range(0,numOfContours):
	if (n > 0):
		#insert connection line
		#print(contours[n-1][-1][0],contours[n-1][-1][1])
		#print(n)
		newContour_stack.put(( [contours[n-1][-1][0], contours[n-1][-1][1]], [contours[n][0][0], contours[n][0][1]] ))
	else:
		pass
		#insert start line
		print("Insert starting line")
		newContour_stack.put(([0,0], [contours[n][0][0], contours[n][0][1]]))

reverseIndex = numOfContours-1;
while (not newContour_stack.empty()):
	newContourLine = newContour_stack.get();
	contourInsertPass = [newContourLine[0], newContourLine[1]]
	contours.insert(reverseIndex, np.array(contourInsertPass))
	reverseIndex -= 1;

for n, contour in enumerate(contours):
	#print(contour)
	#print(contour);
	plt.plot(contour[:, 1], contour[:, 0], linewidth=2)

# for a in ax:
#     a.axis('off')

# plt.tight_layout()
plt.show()

#display edges
#viewer = skimage.viewer.ImageViewer(edges)
#viewer.show()

# TODO use this to save the file for processing 
# save binary image; first find beginning of file extension
# dot = filename.index(".")
# binary_file_name = filename[:dot] + "-binary" + filename[dot:]
# skimage.io.imsave(fname=binary_file_name, arr=skimage.img_as_ubyte(binary))
