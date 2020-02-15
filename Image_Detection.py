import numpy as np
import matplotlib.pyplot as plt
import sys
import itertools
import skimage.io
import skimage.feature
from queue import LifoQueue 
from skimage import measure
from skimage.draw import ellipse
from skimage.measure import find_contours, approximate_polygon, subdivide_polygon
# simple filters for comparison
from skimage.filters import roberts, sobel, sobel_h, sobel_v, scharr, \
    scharr_h, scharr_v, prewitt, prewitt_v, prewitt_h, farid_v, farid_h

#project files
import Image_Process_Edges as EdgeProcessor
import stepperMotorSerialControl as serialControl
import resizeImage as resizer

filename = sys.argv[1]
sigma = float(sys.argv[2])
low_threshold = float(sys.argv[3])
high_threshold = float(sys.argv[4])

resizer.resize(filename)
filename = 'resized-'+filename

#load and display original image as grayscale
image = skimage.io.imread(fname=filename, as_gray=True)


edge_roberts = roberts(image)
edge_sobel = prewitt(image)

edges = skimage.feature.canny(
    image=image,
    sigma=sigma,
    low_threshold=low_threshold,
    high_threshold=high_threshold,
)

contours = measure.find_contours(edges, .08)

new_contour = contours[0]
for _ in range(5):
    new_contour = subdivide_polygon(new_contour, degree=2, preserve_ends=True)



print(str(len(contours)) + ", " + str(len(contours[0])))
# contours_unsort = measure.find_contours(edges, 0.8)

# dtype = [('x',float), ('y',float)]
# contours = np.ndarray(contours_unsort, dtype=dtype)
# contours.sort(order='x')

newContour_stack = LifoQueue()
numOfContours = len(contours)
for n in range(0,numOfContours):
	#contours[n] = np.array(( [contours[n][0][0], contours[n][0][1]], [contours[n][-1][0], contours[n][-1][1]] ))
	if (n > 0):
		#insert connection line
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

fig, (ax1, ax2, ax3) = plt.subplots(ncols=3, sharex=True, sharey=True, figsize=(9, 4))
ax1.plot(new_contour[:, 0], new_contour[:, 1])

for n, contour in enumerate(contours):
	#print(contour)
	ax2.plot(contour[:, 1], contour[:, 0], linewidth=2)

ax3.imshow(edges, cmap=plt.cm.gray)


plt.show()


for n,contour in enumerate(contours):
	for coord in contour:
		serialControl.drawLine(coord[0], coord[1])


# fig, ax = plt.subplots(ncols=2, sharex=True, sharey=True, figsize=(8, 4))

# ax[0].imshow(edges, cmap=plt.cm.gray)
# ax[0].set_title('Canny (Not contour)')

# ax[1].imshow(edge_sobel, cmap=plt.cm.gray)
# ax[1].set_title('Sobel Edge Detection')

# for a in ax:
#     a.axis('off')

# plt.tight_layout()
# plt.show()

