OutputPath = compiledFiles
BaseClassPath = class/baseClasses
LinkedListPath = class/linkedListClasses

# Edit this for .h file depedences that a cpp files need to recompile
ValidateInputPath = class/validateInputClasses
ReturnTypeClassesInputPath = class/returnTypeClasses
LoggerInputPath = class/loggerClasses

.PHONY : clean rebuild runAndClean

output : $(OutputPath)/main.o $(OutputPath)/company.o $(OutputPath)/branch.o $(OutputPath)/vehicle.o $(OutputPath)/branchLinkedList.o $(OutputPath)/vehicleLinkedList.o
	g++ $(OutputPath)/main.o $(OutputPath)/company.o $(OutputPath)/branch.o $(OutputPath)/vehicle.o $(OutputPath)/branchLinkedList.o $(OutputPath)/vehicleLinkedList.o -o output

$(OutputPath)/main.o : main.cpp | $(OutputPath)
	g++ -c main.cpp -o $@

$(OutputPath)/company.o : $(BaseClassPath)/company.cpp $(BaseClassPath)/company.h | $(OutputPath)
	g++ -c $(BaseClassPath)/company.cpp -o $@

$(OutputPath)/branch.o : $(BaseClassPath)/branch.cpp $(BaseClassPath)/branch.h | $(OutputPath)
	g++ -c $(BaseClassPath)/branch.cpp -o $@

$(OutputPath)/vehicle.o : $(BaseClassPath)/vehicle.cpp $(BaseClassPath)/vehicle.h | $(OutputPath)
	g++ -c $(BaseClassPath)/vehicle.cpp -o $@

$(OutputPath)/branchLinkedList.o : $(LinkedListPath)/branchLinkedList.cpp $(LinkedListPath)/branchLinkedList.h | $(OutputPath)
	g++ -c $(LinkedListPath)/branchLinkedList.cpp -o $@

$(OutputPath)/vehicleLinkedList.o : $(LinkedListPath)/vehicleLinkedList.cpp $(LinkedListPath)/vehicleLinkedList.h | $(OutputPath)
	g++ -c $(LinkedListPath)/vehicleLinkedList.cpp -o $@

$(OutputPath):
	mkdir -p $(OutputPath)

clean:
	rm -rf $(OutputPath) output

rebuild: clean output

run : output
	./output

runAndClean:
	 $(MAKE) run 
	 $(MAKE) clean