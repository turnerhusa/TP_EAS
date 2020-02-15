
from PIL import Image

width = 550
height = 370

def resize(img_name):
	img = Image.open(img_name)
	img = img.resize((width, height))
	img.save('resized-' + img_name)
