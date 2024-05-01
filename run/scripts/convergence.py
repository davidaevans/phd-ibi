import sys
import os
import numpy as np
import math


def main():
    target = str(sys.argv[1])
    iteration = str(sys.argv[2])

    data_targ = np.loadtxt(target)
    data_iter = np.loadtxt(iteration, delimiter=" ")

    #print(data_targ)
    #print(data_iter)

    sum = 0
    for i in range(np.size(data_targ,0)):
        #print(data_targ[i][1])
        if (data_targ[i][1] != 0.0):
            sum += (data_iter[i][1]-data_targ[i][1])**2

    rms = math.sqrt(sum/np.size(data_targ,0))
    
    print(sum, rms)

if __name__ == "__main__":

    main()
