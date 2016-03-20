
COMPILER = g++
OBJS = dataset.o cp_main.o
SOURCE = $(OBJS:.o=.cc)

FLAGS = -g -Wall -std=c++11
# FLAGS = -g -Wall  -I/usr/local/Cellar/gsl/1.16/include -std=c++11

# GSL library
# LIBS = -lgsl -lgslcblas -L/usr/local/Cellar/gsl/1.16/lib

LIBS =

default: cp_main.cc

hdp: $(OBJS) 
	$(COMPILER) $(FLAGS) $(OBJS) -o cp_main  $(LIBS)

%.o: %.cc
	$(COMPILER) -c $(FLAGS) -o $@  $< 

.PHONY: clean
clean: 
	rm -f *.o
