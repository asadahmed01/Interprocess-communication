#
# this makefile will compile and and all source
# found in the "DataCorruptor" directory.
# 
# 

# =======================================================
#                  DataCorruptor
# =======================================================
# FINAL BINARY Target
./bin/DataCorruptor : ./obj/main.o ./obj/functions.o
	cc ./obj/main.o ./obj/functions.o -o ./bin/DataCorruptor
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/main.o : ./src/main.c ./inc/dataCorruptor.h
	cc -c ./src/main.c -o ./obj/main.o

./obj/functions.o : ./src/functions.c ./inc/dataCorruptor.h
	cc -c ./src/functions.c -o ./obj/functions.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/DataCorruptor

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
