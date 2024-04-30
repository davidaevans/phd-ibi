# Iterative Boltzmann Inversion

Code and scripts to perform iterative Boltzmann inversion

---

## Compiling
There are two separate codes that need compiling. These are located in `code/mc/source` and `code/rdf/source`. To compile:

```
make clean
clean
```

This produces execuitables `mc` and `rdf` respectively. These do not need to be run manually. The script `run/ibi.sh` runs the iterative procedure using these two execuitables.

## Options

The full range of options can be seen by running `./ibi.sh -h`. They include:

  -  `-d/--data`: the name of the trajectory file where the target data is held.
  -  `-t/--temp`: the temperature at which the simulations are run.
  -  `-n/--num`: the number of iterations that are performed.
  -  `-c/--cutoff`: the cutoff in the potential that is produced.
  -  `-r/--rho`: the density at which to run the simulations.
  -  `-p/--particles`: the number of particles used in the simulations.

The number of iterations that are performed in each simulation is set in `run/defaults/options-mc`. The options required in this file are:

  -  `pbc`: 1 if periodic boundary conditions are required, 0 if not.
  -  `equilibrate`: number of equilibration sweeps.
  -  `sweeps`: number of sweeps in main run.
  -  `dump`: number of sweeps between saving frames.
  -  `diameter`: diameter of particle.
  -  `seed`: random number seed, which must be a negative integer.

The total number of frames saved is then the number of sweeps given divided by `dump`.

## Output

First, the script calculates the target radial distribution function from the given trajectory file in the directory `run/rdf`. It produces a file called `rdf-target.dat` which is produced in `run/`.

For each iteration, a new directory is created `run/iteration-X` where X is the iteration number. The trajectories from the Monte Carlo simulations are saved in a file that starts with `configs-`. The radial distribution is then calculated from this file and output in `run/iteration-X/rdf.dat`. This file and the target file are used to calculate the next potential which is saved as `run/potential-Y.dat` where `Y = X + 1`.

The file `run/chi-squared.dat` saves the sum of the square of the differences between the target radial distribution function and the current iteration. This is used to test for convergence to the 'true' potential.
