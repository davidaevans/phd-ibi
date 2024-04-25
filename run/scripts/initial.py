import sys
import numpy as np
import math

filename = str(sys.argv[1])
temp = float(sys.argv[2])
cutoff = float(sys.argv[3])

data = np.loadtxt(filename, delimiter=" ")

potential = np.zeros((np.size(data,0),2))

for i in range(np.size(data,0)):
	potential[i][0] = data[i][0]
	if (data[i][1] == 0.0):
		potential[i][1] = 1000000
	else:
		potential[i][1] = - temp * math.log(data[i][1])	
	if (potential[i][0] <= cutoff):
		print(potential[i][0], potential[i][1])
	
