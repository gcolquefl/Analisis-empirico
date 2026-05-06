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
	set title 'Strassen vs Estandar'; \
	set xlabel 'n (Tamaño de la Matriz)'; \
	set ylabel 'Tiempo (microsegundos)'; \
	set grid; \
	set key top left; \
	plot '$(DATA)' using 1:2 with linespoints title 'Estandard', \
			 '$(DATA)' using 1:3 with linespoints title 'Strassen'; \
	set terminal wxt; \
	set output; \
	replot"
	
# Limpiar archivos generados
clean:
	rm -f $(TARGET) 
