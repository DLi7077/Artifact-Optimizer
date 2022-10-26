########################################
##
## Makefile
## LINUX compilation
##
##############################################

# Flags
C++FLAG = -g -std=c++17 -Wall

# Math library

MATH_LIBS = -lm
EXEC_DIR=.

# Rule for .cpp files
# .SUFFIXES : .cc.o

.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@

# Includes.
INCLUDES=  -I.
LIBS_ALL = -L/usr/lib -L/usr/local/lib $(MATH_LIBS)

# ZEROTH PROGRAM
ALL_OBJ0=optimize.o
PROGRAM_0=optimize
$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

# ONETH PROGRAM
ALL_OBJ1=Game/DamageCalculator.o
PROGRAM_1=dmgcalc
$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

# Compile and run optimize
run_optimize :
	make $(PROGRAM_0)
	./$(PROGRAM_0)
	make clean

run_dmgcalc :
	make $(PROGRAM_1)
	./$(PROGRAM_1)
	make clean
all:
		make $(PROGRAM_0)

# Clean obj files
clean:
	(rm -f *.o; rm -f optimize)

(:
