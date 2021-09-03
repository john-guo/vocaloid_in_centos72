.PHONY: all clean

DEBUG = 1
CXXFLAGS = -Wall -std=c++11 -pthread
SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include
LIBDIR = ./lib
PROTODIR = ./protos
PROTOSRCDIR = ./include/protos

# Target Name
myvocaloid = myvocaloid
server = server
TARGET = $(myvocaloid) $(server)

# Library Name
LIBBASE = VocSDKLinux avcodec avformat avutil

# Sorce
INC_FILES := $(wildcard $(INCDIR)/*.h)
CPP_FILES := $(wildcard $(SRCDIR)/*.cpp)
OBJ_FILES := $(addprefix $(OBJDIR)/,$(notdir $(CPP_FILES:.cpp=.o)))
PROTO_FILES := $(wildcard $(PROTODIR)/*.proto)
PB_OBJ_FILES := $(addprefix $(OBJDIR)/,$(notdir $(PROTO_FILES:.proto=.pb.o)))

OBJ_MAIN = $(OBJDIR)/main.o
OBJ_SERVER = $(OBJDIR)/server.o

# Debug or Release
ifeq ($(DEBUG),1)
  CXXFLAGS += -g -O0
  LIBNAME = $(LIBBASE)
else
  CXXFLAGS += -O2
  LIBNAME = $(LIBBASE)
endif

VOCALOID_CXXFLAGS = $(CXXFLAGS) -D_GLIBCXX_USE_CXX11_ABI=0

GRPCLIB = -lprotobuf -lgrpc++ -lgrpc
 
# Library Name Option
LIBS = $(addprefix -l,$(LIBNAME))

# Library Path Option
LIBDIRS = $(addprefix -L,$(LIBDIR))

all : $(myvocaloid) $(server)

$(myvocaloid) : $(OBJ_MAIN) $(LIBTARGET)
	g++ -o $@ $(OBJ_MAIN) $(LIBDIRS) $(LIBS) -lpthread -Wl,--no-as-needed -ldl -Wl,-rpath=. -Wl,-rpath-link=$(LIBS)

$(server) : $(OBJ_SERVER) $(LIBTARGET) $(PB_OBJ_FILES)
	g++ -o $@ $(OBJ_SERVER) $(PB_OBJ_FILES) $(LIBDIRS) $(LIBS) $(GRPCLIB) -lpthread -Wl,--no-as-needed -ldl -Wl,-rpath=. -Wl,-rpath-link=$(LIBS)
 
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INC_FILES)
	@mkdir -p $(dir $@)
	g++ $(VOCALOID_CXXFLAGS) -c -o $@ $< -I$(INCDIR) -lpthread

$(OBJDIR)/%.pb.o: $(PROTODIR)/%.proto
	@mkdir -p $(dir $@)
	protoc --cpp_out=$(INCDIR) $<
	g++ $(CXXFLAGS) -c -o $@ $(PROTOSRCDIR)/$*.pb.cc -I$(INCDIR) -lpthread

clean:
	@rm -rf $(TARGET) $(OBJDIR)
