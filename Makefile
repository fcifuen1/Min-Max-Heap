EXE = Project4.out
OFILES = Driver.o MMheap.o
DRIVER = Driver.cpp

$(EXE): $(OFILES)
	g++ -Wall $(OFILES) -o $(EXE)

Driver.o: MyException.h $(DRIVER)
	g++ -Wall -c $(DRIVER)

MMheap.o: MMheap.h MMheap.cpp
	g++ -Wall -c MMheap.cpp

.PHONY: run
run:
	./$(EXE)

.PHONY: clean
clean:
	rm -rf *~ *# *.o *.h.gch

.PHONY: val
val:
	valgrind ./$(EXE)