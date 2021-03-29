#
# this makefile will compile and and all source
# found in the "DataReader" directory.
# 
# 

# =======================================================
#                  DataReader
# =======================================================
# FINAL BINARY Target
./bin/DataCreator : ./obj/main.o ./obj/functions.o
	cc ./obj/main.o ./obj/functions.o -o ./bin/DataCreator
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/main.o : ./src/main.c ./inc/dataCreator.h
	cc -c ./src/main.c -o ./obj/main.o

./obj/functions.o : ./src/functions.c ./inc/dataCreator.h
	cc -c ./src/functions.c -o ./obj/functions.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/DataCreator

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
