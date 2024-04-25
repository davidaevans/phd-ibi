import sys
import math
import numpy as np

def main():
    pot_fname = str(sys.argv[1])
    gr_fname = str(sys.argv[2])
    gr_target_fname = str(sys.argv[3])
    temp = float(sys.argv[4])
    
    pot = np.loadtxt(pot_fname, delimiter=" ")
    gr = np.loadtxt(gr_fname, delimiter=" ")
    gr_target = np.loadtxt(gr_target_fname, delimiter=" ")
	#print("pot: ", np.size(pot, 0),np.size(pot,1))
	#print("gr : ", np.size(gr, 0), np.size(gr,1))
	#print("grt: ", np.size(gr_target,0), np.size(gr_target, 1))

    newpot = np.copy(pot)	
    for i in range(np.size(pot,0)):
		#if (gr_target[i][1] == 0.0):
		#	newpot[i][1] = 1000000.0
		#	ratio = 0
		#elif (gr[i][1] == 0.0):
		#	newpot[i][1] = pot[i][1]
		#else:
			#print("pot:",pot[i][1])
			#print("gr:", gr[i][1])
			#print("grt:", gr_target[i][1])
        if gr_target[i][1] < 0.01 or gr[i][1] < 0.01:
            newpot[i][1] = pot[i][1]
            ratio = 0.0
        else:
            ratio = gr[i][1]/gr_target[i][1]
            try:
                newpot[i][1] = pot[i][1] + temp * math.log(ratio) 
                #print(newpot[i][1])
            except ValueError:
                newpot[i][1] = pot[i][1]
		        #print(ratio)
		        #exit()
        print(newpot[i][0], newpot[i][1], ratio)
if __name__ == "__main__":
    main()
