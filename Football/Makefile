CXXFLAGSDEBUG =	-g  -fmessage-length=0 -Wall -pedantic
CXXFLAGSFAST =	 -fmessage-length=0 -Wall -pedantic -O4
CXXFLAGS = $(CXXFLAGSDEBUG) -std=c++11
CXXCOMPFLAGS = $(CXXFLAGS) -c

SOURCES =  $(wildcard *.cpp) $(wildcard */*.cpp)
OBJECTS = $(addprefix bin/,$(SOURCES:.cpp=.o))
GBG	 = 		bin/*.csv bin/*.txt bin/*.exe
FILE_2 =	bin/TestingResults
FILE_3 =	bin/UserData

LIBS = 		

TARGET =	bin/Football.exe

$(TARGET):	$(OBJECTS) copyConfigFiles
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LIBS) -o $(TARGET)

all:	$(TARGET)
#		mkdir -p ${FILE_2}
#		mkdir -p ${FILE_3}

copyConfigFiles:
	cp *.conf bin/
	
bin/%.o: %.cpp %.h
	$(CXX) $(CXXCOMPFLAGS) $< -o $@

#bin/Main.o: Main.cpp
#	 $(CXX) $(CXXFLAGS) -c -o bin/Main.o Main.cpp
	
clean:
	rm -f -r $(OBJECTS) $(TARGET) ${GBG} ${FILE_3}
