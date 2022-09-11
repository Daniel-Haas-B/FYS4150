# Project1


## Reproducing results

### Problem 7
For compiling, run the following command in terminal

```
g++ P7.cpp -o P7
```

Then run the following command for producing the data files with 10, 100 and 1000 steps 

```
for nsteps in 10 100 1000 ; do ./P7 $nsteps; done
```

and finally for plotting the results run 

```
python3 Plot_P7.py 10 100 1000
```

### Problem 9

For compiling, run the following command in terminal

```
g++ P9.cpp -o P9
```

Then run the following command for producing the data file with whatever nsteps desired. The example for P9 only contains nsteps = 1000, but multiple can be used similarly to what was done in P7

```
for nsteps in 1000; do ./P9 $nsteps; done
```

