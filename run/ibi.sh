#!/bin/bash

#############################################
# Script to run Iterative Boltzman Inverion #
# To run: ./ibi.sh -t rdf.dat               #
# For help ./ibi.sh -h                      #
#############################################

MC_SIM_PATH=../../code/mc/source
RDF_PATH=../../code/rdf/source

POSITIONAL_ARGS=()

while [[ $# -gt 0 ]]; do
  case $1 in
    -t|--temp)
      TEMP="$2"
      shift # past argument
      shift # past value
      ;;
    -d|--data)
      TARGETFNAME="$2"
      shift 
      shift
      ;;
    -n|--num)
      ITERATIONS="$2"
      shift
      shift
      ;;
    -c|--cutoff)
      CUTOFF="$2"
      shift 
      shift
      ;;
    -r|--rho)
      DENSITY="$2"
      shift 
      shift
      ;;
    -p|--particles)
      NPART="$2"
      shift 
      shift
      ;;
    -h|--help)
      echo "Help: "
      echo "options:"
      echo "--data/-d: trajectory file"
      echo "--temp/-t: temperature"
      echo "--cutoff/-c: cutoff for comparison of g(r)"
      echo "--num/-n: number of iterations to perform"
      echo "--rho/-r: density for MC simulations"
      echo "--particles/-p: number of particles for MC simulations"
      exit 0 # past argument
      ;;
    -*|--*)
      echo "Unknown option $1"
      exit 1
      ;;
    *)
      POSITIONAL_ARGS+=("$1") # save positional arg
      shift # past argument
      ;;
  esac
done

set -- "${POSITIONAL_ARGS[@]}" # restore positional parameters

# CHECK ALL OPTIONS HAVE BEEN ASSIGNED
if [ -z ${TARGETFNAME+z} ]; then echo "ERROR: Trajectory filename has not been set"; exit 1; fi
if [ -z ${TEMP+z} ]; then echo "ERROR: Temperature has not been set"; exit 1; fi
if [ -z ${CUTOFF+z} ]; then echo "ERROR: Cutoff has not been set"; exit 1; fi
if [ -z ${ITERATIONS+z} ]; then echo "ERROR: Number of iterations has not been set"; exit 1; fi
if [ -z ${DENSITY+z} ]; then echo "ERROR: Density has not been set"; exit 1; fi
if [ -z ${NPART+z} ]; then echo "ERROR: Number of particles has not been set"; exit 1; fi

if [ ! -f ${TARGETFNAME} ]; then echo "ERROR: Could not find ${TARGETFNAME}"; exit 1; fi

# PRINT OPTIONS
echo
echo
echo "Iterative Boltzman Inversion"
echo
echo "Target g(r) filename                      = ${TARGETFNAME}"
echo "Temperature                               = ${TEMP}"
echo "Cutoff in r for RDF comparison            = ${CUTOFF}"
echo "Number of iterations                      = ${ITERATIONS}"
echo "Density                                   = ${DENSITY}"
echo "Number of particles for MC simulations    = ${NPART}"

# EXIT IF ANY PROCESS FAILS
set -e

# CALCULATE TARGET RDF
echo "Calculating target g(r) from trajectory file"
mkdir rdf && cd rdf
cp ../defaults/options .
mv ../${TARGETFNAME} .
echo filename ${TARGETFNAME} >> options
numframes=$(../scripts/numframes.sh ${TARGETFNAME})
echo sweeps ${numframes} >> options
${RDF_PATH}/rdf >> rdf.out
cp rdf.dat ../rdf-target.dat
TARGETFNAME="rdf-target.dat"
cd ../
echo "Target g(r) calculated and in rdf-target.dat"


# GENERATE INITIAL POTENTIAL
echo

# IF INITIAL POTENTIAL FILE EXISTS, USE THAT
if [ ! -f "initial-potential.dat" ]; then

	echo "Generating initial potential as potential of mean force"
	python3 scripts/initial.py ${TARGETFNAME} ${TEMP} ${CUTOFF} > initial-potential.dat
fi

cp initial-potential.dat potential-0.dat
echo "Initial potential in: initial-potential.dat"
echo
echo "Processing target g(r) for cutoff"
awk -v cutoff="${CUTOFF}" '{if($1<cutoff) print $0}' ${TARGETFNAME} > truncated-${TARGETFNAME}
echo "Processed"
echo
echo

echo "Calculating box size to use for MC simulations"
BOXSIZE=$(awk -v rho=${DENSITY} -v n=${NPART} 'BEGIN{printf("%lf",sqrt(n/rho))}')
echo "Calculated box size = " ${BOXSIZE}


# ITERATIVE PROCESS
# Keep track of number of iterations
count=$((0))

while [ $count -lt ${ITERATIONS} ]
do

# Make directory for this iteration
if [[ ! -d iteration-${count} ]];
then
	mkdir iteration-${count} && cd iteration-${count}
	echo
	echo "Performing iteration ${count}"
	cp ../defaults/options-mc .
	cp ../potential-${count}.dat potential.dat

	# Add boxsize and npart to default options-mc file
	echo box ${BOXSIZE} ${BOXSIZE} >> options-mc
	echo discs ${NPART} 0 >> options-mc

	NL=$(wc -l potential.dat)
	echo kt ${TEMP} >> options-mc
 
	# RUN MC SIM
	now=$(date +"%T")
	echo "Starting MC simulation at ${now}"
	${MC_SIM_PATH}/mc >> iteration-${count}.log
	now=$(date +"%T")
	
	echo "End of simulation at ${now}"

	# CALCULATE G(R) FROM NEW DATA
	echo
	echo "Calculating RDF from simulation"
	cp ../defaults/options .
	nsweeps=$(../scripts/numframes.sh configs-*)
	echo sweeps $nsweeps >> options
	echo filename configs-* >> options
	${RDF_PATH}/rdf > rdf.log	
	awk -v cutoff="${CUTOFF}" '{if($1<cutoff) print $0}' rdf.dat  > rdf-truncated.dat
	echo "RDF calculated"

	# COMPARE G(R) TO GIVEN PRECISION
	# TEST FOR CONVERGENCE BY CALCULATING CHI SQUARED
	cp ../scripts/chi-squared.py .
	python3 chi-squared.py ../truncated-${TARGETFNAME} rdf-truncated.dat >> ../chi-squared.dat
	# IF NOT CLOSE ENOUGH, CHANGE POTENTIAL
	python3 ../scripts/invert.py potential.dat rdf-truncated.dat ../truncated-${TARGETFNAME} ${TEMP} > invert.log

	((count+=1))
	
	# Get potential and ratios from outfile
	awk '{print $1,$2}' invert.log > potential-${count}.dat
	cp potential-${count}.dat ../

	echo
	cd ../
else 
	echo "Directory iteration-${count} already exists..."
	echo "Skipping"
	((count+=1))
	echo
	echo

fi
done
# END OF ITERATION
echo "Done"
echo
echo
