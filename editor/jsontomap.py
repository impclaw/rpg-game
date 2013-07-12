import json
import sys
import pprint
import struct

def guard(n):
	if n < 0:
		return 0
	return n

jsonfile = sys.argv[1]
mapfile = sys.argv[2]

jsonf = open(jsonfile, 'r')
jdata = json.load(jsonf)

data = {}
height = jdata["height"]
width = jdata["width"]
mapname = mapfile.split('.')[0]

for l in jdata["layers"]:
	name = l["name"]
	data[name] = l["data"]

if not ('1' in data and '2' in data and '3' in data and 'block' in data):
	print "Invalid map, lacking layer 1, 2, 3 or block"
	sys.exit(0)

if len(mapname) > 8:
	print "Map name too long, max 8 characters"
	sys.exit(0)

print "Map '%s' loaded and validated. " % (mapname)
print "Height:", height, "Width:", width

mapf = open(mapfile, 'wb')
print "Writing Header"
mapf.write("??RPGMAP")
mapf.write(mapname)
mapf.write('\0' * (8 - len(mapname)))
mapf.write(struct.pack('>H', width))
mapf.write(struct.pack('>H', height))
for l in ('1', '2', '3'):
	print "Writing Layer", l
	for b in data[l]:
		mapf.write(struct.pack('>H', guard(b-1)))
		mapf.write(struct.pack('>H', 0))
	
mapf.close()
jsonf.close()


