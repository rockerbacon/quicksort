CC = g++ -std=c++11
OBJS = main.o
DEPS = quicksort.h Lab309_ADT_Container.h Lab309_ADT_StaticContainer.h Lab309_ADT_StaticList.h

%.o : %.cpp $(DEPS)
	$(CC) -c $<

main: $(OBJS)
	$(CC) -o quicksort $(OBJS)
