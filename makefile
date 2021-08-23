BINARY = OEKOLOGISCHE_ITERATION
CC = gcc
CFLAGS = -Wall -Wpedantic -Ofast -flto
LFLAGS = -lm
OBJECTS = oekologische_iteration.o
HEADER = 
VPATH = src/

all: $(BINARY)

$(BINARY): $(OBJECTS) 
	$(CC) $(OBJECTS) $(CLAGS) $(LFLAGS) -o $(BINARY)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $< -c -o $@

run: $(BINARY)
	./$(BINARY)

plot: clean run
	python plot_iterations.py
	python plot_bifurcation_diagram.py
	python plot_lyapunov_exponent.py
	

clean:
	@rm -rf *.o
	@rm -f $(BINARY)
	@rm -f *.csv
