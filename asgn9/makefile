# builds hello program from multiple source files  
   
PROG = namelist 
CC = gcc  
FLAGS = -Wall -g -m32
OBJS = stringlist.o namelist.o  
   
namelist: $(OBJS)  
	$(CC) $(FLAGS) -o $(PROG) $(OBJS)
   
namelist.o: namelist.c stringlist.h  
	$(CC) $(FLAGS) -c namelist.c  
   
stringlist.o: stringlist.c stringlist.h  
	$(CC) $(FLAGS)  -c stringlist.c  
   
clean:  
	rm $(PROG) $(OBJS)
