CXX = g++
#O3 for max optimization (go to 0 for debug)
CXXFLAGS = -Wall -Werror -O3 -Wextra -Wno-unused-local-typedefs -Wno-deprecated-declarations -std=c++11 -g
ifeq "$(GCCVERSION)" "1"
  CXXFLAGS += -Wno-error=misleading-indentation
endif

INCLUDE=-I$(PWD)
LIB=-L$(PWD)/lib
ROOT=`root-config --cflags --glibs`

MKDIR_BIN=mkdir -p $(PWD)/bin
MKDIR_LIB=mkdir -p $(PWD)/lib
MKDIR_OBJ=mkdir -p $(PWD)/obj
MKDIR_OUTPUT=mkdir -p $(PWD)/output
MKDIR_LOGS=mkdir -p $(PWD)/logs
MKDIR_PDF=mkdir -p $(PWD)/pdfDir

all: mkdirBin mkdirLib mkdirLogs mkdirObj mkdirOutput mkdirPdf obj/checkMakeDir.o obj/configParser.o obj/reader.o lib/libMixer.so bin/runMixer.exe bin/testReader.exe bin/mixToSnippet.exe

mkdirBin:
	$(MKDIR_BIN)

mkdirLib:
	$(MKDIR_LIB)

mkdirLogs:
	$(MKDIR_LOGS)

mkdirObj:
	$(MKDIR_OBJ)

mkdirOutput:
	$(MKDIR_OUTPUT)

mkdirPdf:
	$(MKDIR_PDF)

obj/checkMakeDir.o: src/checkMakeDir.C
	$(CXX) $(CXXFLAGS) -fPIC -c src/checkMakeDir.C -o obj/checkMakeDir.o $(INCLUDE)

obj/configParser.o: src/configParser.C
	$(CXX) $(CXXFLAGS) -fPIC -c src/configParser.C -o obj/configParser.o $(INCLUDE)

obj/reader.o: src/reader.C
	$(CXX) $(CXXFLAGS) -fPIC -c src/reader.C -o obj/reader.o $(INCLUDE)

lib/libMixer.so:
	$(CXX) $(CXXFLAGS) -fPIC -shared -o lib/libMixer.so obj/checkMakeDir.o obj/configParser.o obj/reader.o $(ROOT) $(INCLUDE)

bin/runMixer.exe: src/runMixer.C
	$(CXX) $(CXXFLAGS) src/runMixer.C -o bin/runMixer.exe $(ROOT) $(INCLUDE) $(LIB) -lMixer

bin/testReader.exe: src/testReader.C
	$(CXX) $(CXXFLAGS) src/testReader.C -o bin/testReader.exe $(ROOT) $(INCLUDE) $(LIB) -lMixer

bin/mixToSnippet.exe: src/mixToSnippet.C
	$(CXX) $(CXXFLAGS) src/mixToSnippet.C -o bin/mixToSnippet.exe $(ROOT) $(INCLUDE) $(LIB) -lMixer


clean:
	rm -f ./*~
	rm -f ./#*#
	rm -f bash/*~
	rm -f bash/#*#
	rm -f bin/*.exe
	rm -rf bin
	rm -f include/*~
	rm -f include/#*#
	rm -f input/*~
	rm -f input/#*#
	rm -f input/samples/*~
	rm -f input/config/*~
	rm -f lib/*.so
	rm -rf lib
	rm -f obj/*.o
	rm -rf obj
	rm -f src/*~
	rm -f src/#*#
