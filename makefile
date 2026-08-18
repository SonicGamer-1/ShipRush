CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -I./Src
LDFLAGS = -lenet -lraylib -lws2_32 -lopengl32 -lgdi32 -lwinmm
SRCDIR = Src
OBJDIR = temp
TARGET = Plate_Form.exe

SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	if not exist $(OBJDIR) mkdir $(OBJDIR)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	if exist $(OBJDIR) rmdir /S /Q $(OBJDIR)
	if exist $(TARGET) del $(TARGET)

run: $(TARGET)
	.\$(TARGET)

.PHONY: all clean run