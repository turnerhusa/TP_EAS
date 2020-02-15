import numpy as np
import matplotlib.pyplot as plt
import sys

import skimage.io
import skimage.feature
# simple filters for comparison
from skimage.filters import roberts, sobel, sobel_h, sobel_v, scharr, \
	scharr_h, scharr_v, prewitt, prewitt_v, prewitt_h, farid_v, farid_h
from queue import Queue 


def getShape(startX, startY, edges):
	# a shape is just an array of a bunch of x and y coords 
	shape = []
	pixelQueue = Queue()
	visited = edges

	#init visited
	for row in visited:
		for pixel in row:
			pixel = False

	pixelQueue.put([startX, startY])
	visited[startY][startX] = True
	while (not pixelQueue.empty()):
		#get the pixel to add to shape
		coords = pixelQueue.get()
		x1 = coords[0]
		y1 = coords[1]
		shape.append([x1,y1])

		#check up, down, left, right
		#if it hasnt been visited and is True add to queue to be added to shape
		if ((edges[y1][x1+1] and not visited[y1][x1+1]) and (x1+1 <= len(edges[y1])) ):
			visited[y1][x1+1] = True
			pixelQueue.put([x1+1,y1])
		if ((edges[y1][x1-1] and not visited[y1][x1+1]) and (x1-1 >= 0)):
			visited[y1][x1-1] = True
			pixelQueue.put([x1-1,y1])
		if ((edges[y1+1][x1] and not visited[y1][x1+1]) and (y1+1 <= len(edges))):
			visited[y1+1][x1] = True
			pixelQueue.put([x1,y1+1])
		if ((edges[y1-1][x1] and not visited[y1][x1+1]) and (y1-1 >= 0)):
			visited[y1-1][x1] = True
			pixelQueue.put([x1,y1-1])

	#sort the shape
	return shape

def containsShape(shape, shapeList):
	return False

def processEdges(edges):
	shapes = []
	testData = [[False,False,False], [False,True,False], [False,True,False], [False,True,False], [False,False,False]]
	for y,row in enumerate(testData):
		for x,pixel in enumerate(row):
			#print(pixel)
			#if you find a white pixel check to see if we already have the shape
			#if we dont already have the shape then add the new shape to the list
			if (edges[y][x]):
				newShape = getShape(x, y, testData)
				if (not containsShape(newShape, shapes)):
					shapes.append(newShape)
	return shapes

