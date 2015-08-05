CXXFLAGSDEBUG =	-g  -fmessage-length=0 -Wall -pedantic
CXXFLAGSFAST =	 -fmessage-length=0 -Wall -pedantic -O4
CXXFLAGS = $(CXXFLAGSDEBUG) -std=c++11
CXXCOMPFLAGS = $(CXXFLAGS) -c

SOURCES =  $(wildcard */*.cpp)
OBJECTS = $(addprefix bin/,$(SOURCES:.cpp=.o))
GBG	 = 		bin/*.csv bin/*.txt bin/*.exe
FOOTBALLLIB = bin/libFootball.a

LIBS = -L bin $(FOOTBALLLIB)

TARGET =	bin/Football.exe
TEST = bin/Tests.exe

$(TARGET): bin/Main.o $(FOOTBALLLIB)
	$(CXX) $(CXXFLAGS) bin/Main.o $(LIBS) -o $(TARGET)
	
$(TEST): bin/Tests.o bin/TestsFramework.o $(FOOTBALLLIB)
	$(CXX) $(CXXFLAGS) bin/TestsFramework.o bin/Tests.o $(LIBS) -o $(TEST)

all:	$(TARGET) tests copyConfigFiles
		cd bin; ./Tests.exe
#		mkdir -p ${FILE_2}
#		mkdir -p ${FILE_3}

$(FOOTBALLLIB): $(OBJECTS)
	ar rvs $@  $(OBJECTS)
	

tests: $(TEST)

copyConfigFiles:
	cp *.conf bin/
	
bin/%.o: %.cpp %.h
	$(CXX) $(CXXCOMPFLAGS) $< -o $@
	
bin/TestsFramework.o: TestsFramework.cpp TestsFramework.hpp
	$(CXX) $(CXXCOMPFLAGS) $< -o $@
	
clean:
	rm -f -r $(OBJECTS) $(TARGET)
