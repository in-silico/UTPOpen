set grid xtics ytics
set nokey
set size square
set style line 1 lw 3
set style line 2 pt 7 lc rgb "black" ps 2
set term pngcairo size 400,300 enhanced font 'Verdana,10'
set output "case01.png"
plot "poly01.dat" with lines ls 1
set output "case02.png"
plot "poly02.dat" with lines ls 1
