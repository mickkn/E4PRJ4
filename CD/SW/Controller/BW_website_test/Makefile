SOURCES=main.cpp Website.cpp
OBJECTS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))
DEPS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.d))
EXE=$(addprefix $(EXE_DIR)/,WebsiteProg)
CXX=g++
CXXFLAGS= -I.
LIBS= 
BUILD_DIR=build
EXE_DIR=bin

# Making for host
# > make ARCH = host
ifeq (${ARCH},host)
CXX=g++
BUILD_DIR=build/host
EXE_DIR=bin/host
endif

# Making for target
# > make ARCH = target
ifeq (${ARCH},target)
CXX=arm-angstrom-linux-gnueabi-g++
BUILD_DIR=build/target
EXE_DIR=bin/target
endif

# Code below this point is not to be edited. This can be looked at as a template!

.PHONY: all
all: $(EXE)

$(EXE): $(DEPS) $(OBJECTS) $(EXE_DIR)# << Check the $(DEPS) new dependency
	$(CXX) $(CXXFLAGS) -o $@ ${OBJECTS} $(LIBS)

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c -o $@ $^ 

# Rule that describes how a .d ( dependency ) file is created from a .cpp file

# Similar to the assigment that you just completed %. cpp -> %.o
${BUILD_DIR}/%.d: %.cpp $(BUILD_DIR)
	$(CXX) -MT ${BUILD_DIR}/$(@:.d=.o) -MM $(CXXFLAGS) $< > $@

-include $(DEPS)

# Build directories
$(BUILD_DIR):
	mkdir -p $@

$(EXE_DIR):
	mkdir -p $@

.PHONY: help
help:

	@echo " "
	@echo "make help		-This info"
	@echo "make clean		-clean all objects, executables and directories"	
	@echo "make ARCH=host		-build on host"
	@echo "make ARCH=target	-build on target"
	@echo " "

.PHONY: clean
clean:
	rm -f $(EXE) $(OBJECTS)
	rm -rf build
	rm -rf bin
	@echo "Cleaning completed" 
