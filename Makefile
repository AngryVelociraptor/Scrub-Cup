SCRUBCUP := Scrub\ Cup\ Work

CFLAGS := "-std=c++11"

all: scrubcup

scrubcup: $(SCRUBCUP).o Data.o Division.o ODivision.o Parse.o PrintToFile.o Team.o TeamSort.o
	g++ "Scrub Cup Work.o" Data.o Division.o ODivision.o Parse.o PrintToFile.o Team.o TeamSort.o -o scrubcup


$(SCRUBCUP).o: $(SCRUBCUP).cpp
	g++ -c $(SCRUBCUP).cpp $(CFLAGS)

Data.o: Data.cpp
	g++ -c Data.cpp $(CFLAGS)

Division.o: Division.cpp
	g++ -c Division.cpp $(CFLAGS)

ODivision.o: ODivision.cpp
	g++ -c ODivision.cpp $(CFLAGS)

Parse.o: Parse.cpp
	g++ -c Parse.cpp $(CFLAGS)

PrintToFile.o: PrintToFile.cpp
	g++ -c PrintToFile.cpp $(CFLAGS)

Team.o: Team.cpp
	g++ -c Team.cpp $(CFLAGS)

TeamSort.o: TeamSort.cpp
	g++ -c TeamSort.cpp $(CFLAGS)

clean:
	rm -rf *.o scrubcup
