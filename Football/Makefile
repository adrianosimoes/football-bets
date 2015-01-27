CXXFLAGSDEBUG =	-g  -fmessage-length=0 -Wall -pedantic
CXXFLAGSFAST =	 -fmessage-length=0 -Wall -pedantic -O4
CXXFLAGS = $(CXXFLAGSDEBUG) -std=c++11
CXXCOMPFLAGS = $(CXXFLAGS) -c

SOURCES =  $(wildcard */*.cpp)
OBJECTS = $(addprefix bin/,$(SOURCES:.cpp=.o))
GBG	 = 		bin/*.csv bin/*.txt bin/*.exe
FILE_2 =	bin/TestingResults
FILE_3 =	bin/UserData

LIBS = 		

TARGET =	bin/Football.exe

$(TARGET):	$(OBJECTS) Main.o copyConfigFiles
	$(CXX) $(CXXFLAGS) $(OBJECTS) Main.o $(LIBS) -o $(TARGET)
	
bin/Tests.exe: $(OBJECTS) bin/Tests.o 
	$(CXX) $(CXXFLAGS) $(OBJECTS) bin/Tests.o $(LIBS) -o bin/Tests.exe

all:	$(TARGET) tests
		bin/Tests.exe
#		mkdir -p ${FILE_2}
#		mkdir -p ${FILE_3}

tests: bin/Tests.exe

copyConfigFiles:
	cp *.conf bin/
	
bin/%.o: %.cpp %.h
	$(CXX) $(CXXCOMPFLAGS) $< -o $@

#bin/Tests.o: Tests.cpp
#	 $(CXX) $(CXXCOMPFLAGS) -c -o bin/Tests/Tests.o Utils/Tests/Tests.cpp


	
clean:
	rm -f -r $(OBJECTS) $(TARGET) ${GBG} ${FILE_3}
