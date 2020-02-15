import numpy as np
import matplotlib.pyplot as plt
import sys

import skimage.io
import skimage.feature
# simple filters for comparison
from skimage.filters import roberts, sobel, sobel_h, sobel_v, scharr, \
	scharr_h, scharr_v, prewitt, prewitt_v, prewitt_h, farid_v, farid_h

def getShape(startX, startY, edges):
	# a shape is just an array of a bunch of x and y coords 
	shape = []
	pixelQueue = []
	pixelQueue.append(startX, startY)
	while (not pixelQueue.empty()):
		x1, y1 = pixelQueue.pop()
		shape.append(x1,y1)

		if (edges[y1][x1+1])
			pixelQueue.append(x1+1,y1)
		if (edges[y1][x1-1])
			pixelQueue.append(x1-1,y1)
		if (edges[y1+1][x1])
			pixelQueue.append(x1,y1+1)
		if (edges[y1-1][x1])
			pixelQueue.append(x1,y1-1)

	#sort the shape
	return shape

def containsShape(shape, shapeList):
	return False

def processEdges(edges):
	shapes = []
	for y,row in enumerate(edges):
		for x,pixel in enumerate(edges[row]):
			#print(pixel)
			#if you find a white pixel check to see if we already have the shape
			#if we dont already have the shape then add the new shape to the list
			if (edges[y][x]):
				newShape = getShape(x, y, edges)
				if (not containsShape(newShape, shapes)):
					shapes.append(newShape)
	return shapes

