all: pipeline

pipeline: consumer generator dispacher
    
clean:
	rm dispacher generator consumer consumer.o generator.o dispacher.o
    
consumer: consumer.o
	g++ -Wall -g -o consumer consumer.o

generator: generator.o
	g++ -Wall -g -o generator generator.o
	
dispacher: dispacher.o
	g++ -Wall -g -o dispacher dispacher.o
	
consumer.o: consumer.cpp
	g++ -c consumer.cpp
    
generator.o: generator.cpp
	g++ -c generator.cpp
	
dispacher.o: dispacher.cpp
	g++ -c dispacher.cpp
    


