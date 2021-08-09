# executable filename
BIN=tranhoa1

# compilers
CXX=g++
LD=g++

# flags
CFLAGS=-std=c++17 -Wall -pedantic

# libraries
CLIBS=-lncurses -pthread

# objects
OBJS=main.o CApplication.o CGraphicController.o TStructures.o CCell.o CMap.o CPerson.o CVirus.o CStatHandler.o 
OBJS_SCREENS=CScreen.o CGame.o CIntroScreen.o COutroScreen.o
OBJS_FILES=CFile.o CConfigFile.o CAssetsFile.o CGameFile.o CEventFile.o
OBJS_BUILDINGS=CEmpty.o CResidential.o CBusiness.o CHospital.o CUniversity.o CLaboratory.o

# documentation directory
DOC=./doc

# make all including doc
all: $(BIN)
	make doc

# make only the executable file
compile: $(BIN)

# run the executable file
run:
	./$(BIN)

# make clean
clean:
	rm -rf $(BIN) $(OBJS) $(OBJS_SCREENS) $(OBJS_FILES) $(OBJS_BUILDINGS) $(DOC)

# make doc
doc:
	doxygen ./Doxyfile

# rules for objs
$(BIN): $(OBJS) $(OBJS_SCREENS) $(OBJS_FILES) $(OBJS_BUILDINGS)
	$(LD) $(CFLAGS) -o $@ $^ $(CLIBS)

# generated from g++ -MM
main.o: src/main.cpp src/include/CApplication.hpp \
 src/include/CGraphicController.hpp src/include/TStructures.hpp \
 src/include/CStatHandler.hpp src/include/CPerson.hpp \
 src/include/CMap.hpp src/include/CCell.hpp \
 src/include/buildings/CEmpty.hpp src/include/buildings/CResidential.hpp \
 src/include/buildings/CHospital.hpp src/include/buildings/CBusiness.hpp \
 src/include/buildings/CUniversity.hpp \
 src/include/buildings/CLaboratory.hpp src/include/CConfigFile.hpp \
 src/include/CFile.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)
	
CApplication.o: src/include/CApplication.cpp src/include/CApplication.hpp \
 src/include/CGraphicController.hpp src/include/TStructures.hpp \
 src/include/CStatHandler.hpp src/include/CPerson.hpp \
 src/include/CMap.hpp src/include/CCell.hpp \
 src/include/buildings/CEmpty.hpp src/include/buildings/CResidential.hpp \
 src/include/buildings/CHospital.hpp src/include/buildings/CBusiness.hpp \
 src/include/buildings/CUniversity.hpp \
 src/include/buildings/CLaboratory.hpp src/include/CConfigFile.hpp \
 src/include/CFile.hpp src/include/CAssetsFile.hpp \
 src/include/CEventFile.hpp src/include/CGame.hpp src/include/CScreen.hpp \
 src/include/CVirus.hpp src/include/CIntroScreen.hpp \
 src/include/COutroScreen.hpp src/include/CGameFile.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CAssetsFile.o: src/include/CAssetsFile.cpp src/include/CAssetsFile.hpp \
 src/include/CFile.hpp src/include/TStructures.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CCell.o: src/include/CCell.cpp src/include/CCell.hpp \
 src/include/TStructures.hpp src/include/CStatHandler.hpp \
 src/include/CPerson.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CFile.o: src/include/CFile.cpp src/include/CFile.hpp \
 src/include/TStructures.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CConfigFile.o: src/include/CConfigFile.cpp src/include/CConfigFile.hpp \
 src/include/CFile.hpp src/include/TStructures.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CEventFile.o: src/include/CEventFile.cpp src/include/CEventFile.hpp \
 src/include/CFile.hpp src/include/TStructures.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CGame.o: src/include/CGame.cpp src/include/CGame.hpp \
 src/include/CScreen.hpp src/include/CGraphicController.hpp \
 src/include/TStructures.hpp src/include/CStatHandler.hpp \
 src/include/CPerson.hpp src/include/CMap.hpp src/include/CCell.hpp \
 src/include/buildings/CEmpty.hpp src/include/buildings/CResidential.hpp \
 src/include/buildings/CHospital.hpp src/include/buildings/CBusiness.hpp \
 src/include/buildings/CUniversity.hpp \
 src/include/buildings/CLaboratory.hpp src/include/CVirus.hpp \
 src/include/CGameFile.hpp src/include/CFile.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CGameFile.o: src/include/CGameFile.cpp src/include/CGameFile.hpp \
 src/include/CFile.hpp src/include/TStructures.hpp src/include/CMap.hpp \
 src/include/CCell.hpp src/include/CStatHandler.hpp \
 src/include/CPerson.hpp src/include/buildings/CEmpty.hpp \
 src/include/buildings/CResidential.hpp \
 src/include/buildings/CHospital.hpp src/include/buildings/CBusiness.hpp \
 src/include/buildings/CUniversity.hpp \
 src/include/buildings/CLaboratory.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CGraphicController.o: src/include/CGraphicController.cpp \
 src/include/CGraphicController.hpp src/include/TStructures.hpp \
 src/include/CStatHandler.hpp src/include/CPerson.hpp \
 src/include/CMap.hpp src/include/CCell.hpp \
 src/include/buildings/CEmpty.hpp src/include/buildings/CResidential.hpp \
 src/include/buildings/CHospital.hpp src/include/buildings/CBusiness.hpp \
 src/include/buildings/CUniversity.hpp \
 src/include/buildings/CLaboratory.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CIntroScreen.o: src/include/CIntroScreen.cpp src/include/CIntroScreen.hpp \
 src/include/CScreen.hpp src/include/CGraphicController.hpp \
 src/include/TStructures.hpp src/include/CStatHandler.hpp \
 src/include/CPerson.hpp src/include/CMap.hpp src/include/CCell.hpp \
 src/include/buildings/CEmpty.hpp src/include/buildings/CResidential.hpp \
 src/include/buildings/CHospital.hpp src/include/buildings/CBusiness.hpp \
 src/include/buildings/CUniversity.hpp \
 src/include/buildings/CLaboratory.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CMap.o: src/include/CMap.cpp src/include/CMap.hpp src/include/CCell.hpp \
 src/include/TStructures.hpp src/include/CStatHandler.hpp \
 src/include/CPerson.hpp src/include/buildings/CEmpty.hpp \
 src/include/buildings/CResidential.hpp \
 src/include/buildings/CHospital.hpp src/include/buildings/CBusiness.hpp \
 src/include/buildings/CUniversity.hpp \
 src/include/buildings/CLaboratory.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CMenu.o: src/include/CMenu.cpp src/include/CMenu.hpp \
 src/include/TStructures.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

COutroScreen.o: src/include/COutroScreen.cpp src/include/COutroScreen.hpp \
 src/include/CScreen.hpp src/include/CGraphicController.hpp \
 src/include/TStructures.hpp src/include/CStatHandler.hpp \
 src/include/CPerson.hpp src/include/CMap.hpp src/include/CCell.hpp \
 src/include/buildings/CEmpty.hpp src/include/buildings/CResidential.hpp \
 src/include/buildings/CHospital.hpp src/include/buildings/CBusiness.hpp \
 src/include/buildings/CUniversity.hpp \
 src/include/buildings/CLaboratory.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CPerson.o: src/include/CPerson.cpp src/include/CPerson.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CScreen.o: src/include/CScreen.cpp src/include/CScreen.hpp \
 src/include/CGraphicController.hpp src/include/TStructures.hpp \
 src/include/CStatHandler.hpp src/include/CPerson.hpp \
 src/include/CMap.hpp src/include/CCell.hpp \
 src/include/buildings/CEmpty.hpp src/include/buildings/CResidential.hpp \
 src/include/buildings/CHospital.hpp src/include/buildings/CBusiness.hpp \
 src/include/buildings/CUniversity.hpp \
 src/include/buildings/CLaboratory.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CStatHandler.o: src/include/CStatHandler.cpp src/include/CStatHandler.hpp \
 src/include/CPerson.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CVirus.o: src/include/CVirus.cpp src/include/CVirus.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

TStructures.o: src/include/TStructures.cpp src/include/TStructures.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CBusiness.o: src/include/buildings/CBusiness.cpp \
 src/include/buildings/CBusiness.hpp src/include/buildings/../CCell.hpp \
 src/include/buildings/../TStructures.hpp \
 src/include/buildings/../CStatHandler.hpp \
 src/include/buildings/../CPerson.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CEmpty.o: src/include/buildings/CEmpty.cpp \
 src/include/buildings/CEmpty.hpp src/include/buildings/../CCell.hpp \
 src/include/buildings/../TStructures.hpp \
 src/include/buildings/../CStatHandler.hpp \
 src/include/buildings/../CPerson.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CHospital.o: src/include/buildings/CHospital.cpp \
 src/include/buildings/CHospital.hpp src/include/buildings/../CCell.hpp \
 src/include/buildings/../TStructures.hpp \
 src/include/buildings/../CStatHandler.hpp \
 src/include/buildings/../CPerson.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)
	
CLaboratory.o: src/include/buildings/CLaboratory.cpp \
 src/include/buildings/CLaboratory.hpp src/include/buildings/../CCell.hpp \
 src/include/buildings/../TStructures.hpp \
 src/include/buildings/../CStatHandler.hpp \
 src/include/buildings/../CPerson.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CResidential.o: src/include/buildings/CResidential.cpp \
 src/include/buildings/CResidential.hpp \
 src/include/buildings/../CCell.hpp \
 src/include/buildings/../TStructures.hpp \
 src/include/buildings/../CStatHandler.hpp \
 src/include/buildings/../CPerson.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)

CUniversity.o: src/include/buildings/CUniversity.cpp \
 src/include/buildings/CUniversity.hpp src/include/buildings/../CCell.hpp \
 src/include/buildings/../TStructures.hpp \
 src/include/buildings/../CStatHandler.hpp \
 src/include/buildings/../CPerson.hpp
	$(CXX) $(CFLAGS) -c $< $(CLIBS)
