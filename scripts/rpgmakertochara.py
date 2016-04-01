import Image
import sys, os

im = Image.open(sys.argv[1])
(width, height) = im.size
wx = width / 96
hx = width / 128
n = 0
for ww in range(wx - 1):
	for hh in range(hx - 1):
		x = ww * 96
		y = hh * 128
		call = ("convert %s -crop 96x128+%d+%d %s.png" % \
			(sys.argv[1], x, y, "chara" + str(n)))
		print call
		os.system(call)
		n += 1
