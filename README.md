# TP_EAS

Algorithms Implemented:
  Canny Edge Detection for image preprocessing and initial edge detection
  Sobel Operator for image edge Detection
  Bresenham's line algorithm for plotting which pixels to draw in an X,Y coordinate system to create a smooth line between two points.

### From Devpost:

## Inspiration
A modern, technical twist on one of our favorite childhood games.

## What it does
Using a python image processing library we wrote, we are able to convert png files into a simplified version of the image that our algorithm can then convert into points on an X, Y plane for our stepper motors to turn the Etch a Sketch knobs to draw the line.

We also build in a manual drawing mode that allows a user to operate the Etch a Sketch using a joystick. This was originally a debugging feature but it was a nice touch once all of our systems were working together, giving our project two different operating modes.  

## How I built it
We wrote an algorithm inside of the Image_Detection.py file to read in the png file from the a command line argument and then uses the scikit image library to perform a number of transformations and apply a layer of Gaussian Blur to reduce the image down to more basic lines that will display better on the Etch a Sketch. We then use a Motor Controller script we wrote to run an Edge Detection algorithm to convert the processed image into lines and plot them in an array of X, Y coordinates. We then communicate the points over a serial channel to an Arduino that drives the stepper motors to draw the image.

We also 3D printed pieces to hold our stepper motors onto the knobs of the Etch a Sketch.

## Challenges I ran into

Our edge detection algorithm was one of the hardest software pieces to complete. The problem of attaching the motors to the Etch a Sketch knobs was our biggest hardware problem, which I was able to remedy by using a 3D part library that had pieces for our model of the stepper motors. Printing them took over 3 hours, which was a big time sacrifice, but ended up working in our favor.

## Accomplishments that I'm proud of

Being able to efficiently print all four of our 3D pieces in one print, since I had not used a 3D printer in over four years.
Our Image Processing and Line Detection algorithms were our biggest software accomplishments. We are also very proud of our resourcefulness in using scrap parts to put together the hardware pieces in a way that moves the Etch a Sketch knobs in a controlled manner.  

## What I learned

We all learned a lot about python development and image processing. We also learned how to make sperate systems (python and Arduino) communicate over a serial channel. And lastly, that the power of friendship can allow you to accomplish anything :)

## What's next for Magic Etch a Sketch
Using better hardware would make the knob mechanism smoother, we hope to 3D print gears that would replace the stock knobs to give the motors a more controlled movement. We would also like to revise our image detection algorithms to accept more file types and perform better transformations to provide a higher resolution image on the Etch a Sketch. Also, we would like to change from using stepper motors to standard motors, since the stepper motors run very slowly which causes the picture to take a very long time to finish.
