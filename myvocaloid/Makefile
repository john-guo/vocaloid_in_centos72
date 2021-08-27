.PHONY: all clean
 
CXXFLAGS = -Wall -std=c++11 -pthread -D_GLIBCXX_USE_CXX11_ABI=0
SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include
LIBDIR = ./lib

# Target Name
TARGET = myvocaloid

# Library Name
LIBBASE = VocSDKLinux

# Sorce
INC_FILES := $(wildcard include/*.h)
CPP_FILES := $(wildcard $(SRCDIR)/*.cpp)
OBJ_FILES := $(addprefix $(OBJDIR)/,$(notdir $(CPP_FILES:.cpp=.o)))

# Debug or Release
ifeq ($(DEBUG),1)
  CXXFLAGS += -g -O0
  LIBNAME = $(LIBBASE)
else
  CXXFLAGS += -O2
  LIBNAME = $(LIBBASE)
endif

 
# Library Name Option
LIBS = $(addprefix -l,$(LIBNAME))

# Library Path Option
LIBDIRS = $(addprefix -L,$(LIBDIR))

all : $(TARGET)

$(TARGET) : $(OBJ_FILES) $(LIBTARGET)
	g++ -o $@ $(OBJ_FILES) $(LIBDIRS) $(LIBS) -lpthread -Wl,--no-as-needed -ldl -Wl,-rpath=. -Wl,-rpath-link=$(LIBDIR)
 
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INC_FILES)
	@mkdir -p $(dir $@)
	g++ $(CXXFLAGS) -c -o $@ $< -I$(INCDIR) -lpthread

clean:
	@rm -rf $(TARGET) $(OBJDIR)
