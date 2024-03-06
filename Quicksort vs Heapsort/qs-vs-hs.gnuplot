
set terminal png

set xtics("2¹⁵" 32768, "2²⁰" 1048576, "2²¹" 2097152, "2²²" 4194304)
set xlabel "size of arrays"
set ylabel "Millions of program steps"
set yrange[0:]

set output "quickSort.png"
set title "Quicksort"
plot "qs-vs-hs.Msteps" using 1:2 w l title "random arrays",\
	 "qs-vs-hs.Msteps" using 1:4 w l title "sorted arrays",\
	 "qs-vs-hs.Msteps" using 1:6 w l title "reverse-sorted arrays"

set output "heapSort.png"
set title "Heapsort"
plot "qs-vs-hs.Msteps" using 1:3 w l title "random arrays",\
	 "qs-vs-hs.Msteps" using 1:5 w l title "sorted arrays",\
	 "qs-vs-hs.Msteps" using 1:7 w l title "reverse-sorted arrays"

y(x)=a1*x*log(x)+b1*x+c1
z(x)=a2*x*log(x)+b2*x+c2

set output "qs-vs-hs-SA.png"
set title "Quicksort versus Heapsort (sorted arrays)"

fit y(x) "qs-vs-hs.Msteps" using 1:4 via a1, b1, c1
fit z(x) "qs-vs-hs.Msteps" using 1:5 via a2, b2, c2

plot "qs-vs-hs.Msteps" using 1:4 w l title "Quicksort",\
 "qs-vs-hs.Msteps" using 1:5 w l title "Heapsort",\
  y(x) w l title "fitting Quicksort time values to n*log(n)+n",\
  z(x) w l title "fitting Heapsort time values to n*log(n)+n"

set output "qs-vs-hs-RA.png"
set title "Quicksort versus Heapsort (random arrays)"

fit y(x) "qs-vs-hs.Msteps" using 1:2 via a1, b1, c1
fit z(x) "qs-vs-hs.Msteps" using 1:3 via a2, b2, c2

plot "qs-vs-hs.Msteps" using 1:2 w l title "Quicksort",\
 "qs-vs-hs.Msteps" using 1:3 w l title "Heapsort",\
  y(x) w l title "fitting Quicksort time values to n*log(n)+n",\
  z(x) w l title "fitting Heapsort time values to n*log(n)+n"

set output "qs-vs-hs-RSA.png"
set title "Quicksort versus Heapsort (reverse-sorted arrays)"

fit y(x) "qs-vs-hs.Msteps" using 1:4 via a1, b1, c1
fit z(x) "qs-vs-hs.Msteps" using 1:5 via a2, b2, c2

plot "qs-vs-hs.Msteps" using 1:6 w l title "Quicksort",\
 "qs-vs-hs.Msteps" using 1:7 w l title "Heapsort",\
  y(x) w l title "fitting Quicksort time values to n*log(n)+n",\
  z(x) w l title "fitting Heapsort time values to n*log(n)+n"
