
This Matlab package is developed by Zhonggang Zeng (zzeng@neiu.edu)
dated March 15, 2003

References:
[1] ZHONGGANG ZENG, "COMPUTING MULTIPLE ROOTS OF INEXACT POLYNOMIALS",
MATHEMATICS OF COMPUTATION,
Volume 74, Number 250, Pages 869–903
S 0025-5718(04)01692-8
Article electronically published on July 22, 2004

[2] ZHONGGANG ZENG, "MultRoot - A Matlab package computing polynomial roots and multiplicities"
Journal ACM Transactions on Mathematical Software (TOMS), Volume 30 Issue 2, June 2004 , Pages 218-236 



Unpack and save all the files, then set proper path. 

To find roots and multiplicities of a polynomial p in Matlab format,
simply call

>> z = multroot(p)

The first column of z lists distinct roots, the 2nd column shows
the corresponding multiplicities.

At the current version, the code works for polynomials with 
moderate root multiplicities (such as 30).

Example:

>> f = poly([ones(1,20),2*ones(1,20),3*ones(1,10),4*ones(1,5)]);

>> z = multroot(f)

    !!!THE COMPUTATION IS SUCCESSFUL!!!

THE PEJORATIVE CONDITION NUMBER:     		73.6821 
THE BACKWARD ERROR:                    		8.63e-016 
THE ESTIMATED FORWARD ROOT ERROR:      	1.27e-013 

        computed roots         			multiplicities

        4.000000000000002 	 	 	   5 
        2.999999999999999 	 	 	  10 
        2.000000000000000 	 	 	  20 
        1.000000000000000 	 	 	  20 


--------------------------------------------------------------------
For expert users:

There are three main programs:

1. MultRoot:	calculates roots and corresponding multiplicities,
		by calling the next two expert programs.


2. GcdRoot:   	calculates the multiplicity structure and initial 
               		estimates of the roots. In many cases, the estimates
               		are accurate enough.

		The minimum input is the polynomial coefficient vector

2. PejRoot:  	from given multiplicity structure and initial root estimates,
              		Pejroot calculate the root accurately.

	    	The minimum input is the polyn. coef. vector, initial 
            		iterate and multiplicity structure.


At current version, both programs could fail if the polynomial is 
too crazy. 


****************************************************************
******************* Example ************************************
****************************************************************




>> f = poly([ones(1,20),2*ones(1,15),3*ones(1,10),4*ones(1,5)]); ...
         %%%% construct a test polynomial with roots 1, 2, 3, 4 and ...
         %%%% multiplicities 20, 15, 10, 5 respectively




>> z = gcdroot(f)            %%%% running GcdRoot

(... intermediate print out, please ignor, results are below ...)

z =

   4.00000000011502   5.00000000000000
   3.00000000017309  10.00000000000000
   2.00000000002700  15.00000000000000
   1.00000000000023  20.00000000000000



>> y = z(:,1).', m = z(:,2)'  %%%% prepare input for PejRoot using the result

y =

   4.00000000011502   3.00000000017309   2.00000000002700   1.00000000000023


m =

     5    10    15    20




>> pejroot(f,y,m)           %%%% running PejRoot, get results

    !!!THE COMPUTATION IS SUCCESSFUL!!!

THE PEJORATIVE CONDITION NUMBER:     			76.7706 
THE BACKWARD ERROR:                    		1.99e-015 
THE ESTIMATED FORWARD ROOT ERROR:      	3.06e-013 

        computed roots         			multiplicities

        3.999999999999985 	 	 	   5 
        3.000000000000010 	 	 	  10 
        1.999999999999999 	 	 	  15 
        1.000000000000000 	 	 	  20 

