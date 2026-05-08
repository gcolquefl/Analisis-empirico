# Compilador
CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall -Wextra

# Nombre del ejecutable
TARGET = experimento

# Archivo fuente
SRC = main.cpp

# Archivo de salida de datos
DATA = resultados.dat

# Regla principal
all: $(TARGET)

# Compilar
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Ejecutar y generar datos
run: $(TARGET)
	./$(TARGET) > $(DATA)

# Graficar con gnuplot
plot: run
	gnuplot -persist -e "\
	set terminal pngcairo size 800, 600; \
	set output 'grafico.png'; \
	set title 'Strassen vs Estandar (THRESHOLD = 64)'; \
	set xlabel 'n (Tamaño de la Matriz)'; \
	set ylabel 'Tiempo (microsegundos)'; \
	set grid; \
	set key top left; \
	n0 = system('cat n0.dat') + 0.0; \
	set arrow from n0, graph 0 to n0, graph 1 nohead lc rgb 'red' lw 2 dt 2;\
	set label sprintf('N0 = %.1f', n0) at n0*1.02, graph 0.5 tc rgb 'red' font ',11'; \
	plot '$(DATA)' using 1:2 with linespoints lw 2 pt 4 title 'Estandard', \
	'$(DATA)' using 1:3 with linespoints lw 2 pt 6 title 'Strassen'; \
	set terminal wxt; \
	set output; \
	replot"
	
# Limpiar archivos generados
clean:
	rm -f $(TARGET) 
