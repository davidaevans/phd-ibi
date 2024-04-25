import sys
import numpy as np

filename = str(sys.argv[1])
start = float(sys.argv[2])
window_size = int(sys.argv[3])
loaded = np.loadtxt(filename, delimiter=" ")
#arr = loaded[:,0]
#print(arr)
#window_size = 9
adj = int((window_size-1)/2)
averaged = np.copy(loaded)


for i in range(np.size(loaded,0)):
    #print(i)
    if loaded[i][0] <= start:
        continue     
    
    sum = 0
    count = 0
    for j in range(0,window_size):
        k = j + i - adj
        try:
            # if loaded[k][0] <= start: continue
            sum += loaded[k][1]
            #print(loaded[k][1])
            count += 1
        except IndexError:
            continue
    average = float(sum/count)
    #print("ave:", average)
    averaged[i][1] = average

outname = "smoothed-" + filename
np.savetxt(outname,averaged, delimiter=" ")
