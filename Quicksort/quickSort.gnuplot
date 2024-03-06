

set terminal png
set output "quickSort.png"

set xlabel "Array size"
set ylabel "CPU time (ms)"

set title  "Quicker Sort: Empirical Analysis of Exact Time Complexity"

plot "quickSort.CPUtimes" using 1:2 with lines title "CPU Times of sample"


##########################################################################
#Testing different analytical functions to determine which best fits:

set output "quicksortSort_and_Fit-Function.png"
set title "Quick Sort: Exact time complexity and Fit function"


#------------------------------------------------------------------------

# Testing 3 different functions:
#Uncomment the function to be tested and comment the rest:


##Fit to (n log n) function:
y(x)=a*x*log(x)
fitFunction="Fitting quicksort time values to f(n) = n log(n)"
fit y(x) "quickSort.CPUtimes" using 1:2 via a

##Fit to (n log n + n) function:
#y(x)=a*x*log(x) + b*x
#fitFunction="Fitting quicksort time values to f(n) = n log(n)+n"
#fit y(x) "quickSort.CPUtimes" using 1:2 via a,b

##Fit to a cuadratic function:

#y(x)=a*x*x + b*x + c
#fitFunction="Fitting Quicksort time values to f(n) = n²+n+k"
#fit y(x) "quickSort.CPUtimes" using 1:2 via a,b,c

#------------------------------------------------------------------------


#Finally draw both functions (CPU times of sample and the one that best fits) on one graph
plot "quickSort.CPUtimes" using 1:2 with lines title "CPU times of sample", y(x) title fitFunction


