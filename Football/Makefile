CXXFLAGSDEBUG =	-g  -fmessage-length=0 -Wall -pedantic
CXXFLAGSFAST =	 -fmessage-length=0 -Wall -pedantic -O4
CXXFLAGS = $(CXXFLAGSDEBUG) -std=c++11
CXXCOMPFLAGS = $(CXXFLAGS) -c

SOURCES =  $(wildcard */*.cpp)
OBJECTS = $(addprefix bin/,$(SOURCES:.cpp=.o))
GBG	 = 		bin/*.csv bin/*.txt bin/*.exe

LIBS = 		

TARGET =	bin/Football.exe
TEST = bin/Tests.exe

$(TARGET):	$(OBJECTS) bin/Main.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) bin/Main.o $(LIBS) -o $(TARGET)
	
$(TEST): $(OBJECTS) bin/Tests.o 
	$(CXX) $(CXXFLAGS) $(OBJECTS) bin/Tests.o $(LIBS) -o $(TEST)

all:	$(TARGET) tests copyConfigFiles
		cd bin; ./Tests.exe
#		mkdir -p ${FILE_2}
#		mkdir -p ${FILE_3}

tests: $(TEST)

copyConfigFiles:
	cp *.conf bin/
	
bin/%.o: %.cpp %.h
	$(CXX) $(CXXCOMPFLAGS) $< -o $@
	
bin/Tests.o: Tests.cpp Tests.hpp
	$(CXX) $(CXXCOMPFLAGS) $< -o $@
	

	
clean:
	rm -f -r $(OBJECTS) $(TARGET)
