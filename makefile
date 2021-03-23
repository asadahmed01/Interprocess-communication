#
# this makefile will compile and and all source
# found in the "DataReader" directory.
# 
# 

# =======================================================
#                  DataReader
# =======================================================
# FINAL BINARY Target
./bin/DataReader : ./obj/main.o ./obj/methods.o
	cc ./obj/main.o ./obj/methods.o -o ./bin/DataReader
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/main.o : ./src/main.c ./inc/header.h
	cc -c ./src/main.c -o ./obj/main.o

./obj/methods.o : ./src/methods.c ./inc/header.h
	cc -c ./src/methods.c -o ./obj/methods.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/DataReader

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
