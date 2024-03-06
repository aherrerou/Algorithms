
set terminal png

set title "Grafica practica 5"
set xlabel "n"
set ylabel "STEPS"

set output "pow2.png"
plot [0:30] [0:2000] "pow2.steps" using 1:2 w l t "pow2-1",\
	"" using 1:3 w l t "pow2-2",\
	"" using 1:4 w l t "pow2-3"
