BINARY = OEKOLOGISCHE_ITERATION
CC = gcc
CFLAGS = -Wall -Wpedantic -Ofast -flto
LFLAGS = -lm
OBJECTS = oekologische_iteration.o functions.o
HEADER = functions.h
VPATH = src/

all: $(BINARY)
	@mkdir -p data img
$(BINARY): $(OBJECTS) 
	$(CC) $(OBJECTS) $(CLAGS) $(LFLAGS) -o $(BINARY)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $< -c -o $@

run: $(BINARY)
	@mkdir -p data img
	./$(BINARY)

plot: clean run
	python plot_bifurcation_diagram.py
	python plot_lyapunov_exponent.py
	python plot_additional_lyapunov.py
	

clean:
	@rm -f -r data img
	@rm -rf *.o
	@rm -f $(BINARY)

