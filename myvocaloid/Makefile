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
#CPP_FILES := $(wildcard $(SRCDIR)/*.cpp)
#OBJ_FILES := $(addprefix $(OBJDIR)/,$(notdir $(CPP_FILES:.cpp=.o)))
PROTO_FILES := $(wildcard $(PROTODIR)/*.proto)
PB_OBJ_FILES := $(addprefix $(OBJDIR)/,$(notdir $(PROTO_FILES:.proto=.pb.o)))
GRPC_OBJ_FILES := $(addprefix $(OBJDIR)/,$(notdir $(PROTO_FILES:.proto=.grpc.pb.o)))

OBJ_MAIN = $(OBJDIR)/main.o
OBJ_SERVER = $(OBJDIR)/server.o
OBJ_WRAPPER = $(OBJDIR)/VLS_wrapper.o

CPP_FILES = $(SRCDIR)/server.cpp

OBJ_CXX11ABI = $(OBJ_MAIN) $(OBJ_WRAPPER)
OBJ_FILES = $(OBJ_SERVER)

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

$(OBJDIR)/%.pb.o: $(PROTODIR)/%.proto
	@mkdir -p $(dir $@)
	protoc --cpp_out=$(INCDIR) $<
	g++ $(CXXFLAGS) -c -o $@ $(PROTOSRCDIR)/$*.pb.cc -I$(INCDIR) -lpthread

$(OBJDIR)/%.grpc.pb.o: $(PROTODIR)/%.proto
	@mkdir -p $(dir $@)
	protoc --grpc_out=$(INCDIR) --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` $<
	g++ $(CXXFLAGS) -c -o $@ $(PROTOSRCDIR)/$*.grpc.pb.cc -I$(INCDIR) -lpthread

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(INC_FILES)
	@mkdir -p $(dir $@)
	g++ $(VOCALOID_CXXFLAGS) -c -o $@ $< -I$(INCDIR) -lpthread

$(OBJDIR)/VLS_wrapper.o: $(SRCDIR)/VLS_wrapper.cc $(INC_FILES)
	@mkdir -p $(dir $@)
	g++ $(VOCALOID_CXXFLAGS) -c -o $@ $< -I$(INCDIR) -lpthread

$(OBJ_FILES): $(CPP_FILES) $(INC_FILES)
	@mkdir -p $(dir $@)
	g++ $(CXXFLAGS) -c -o $@ $< -I$(INCDIR) -lpthread

$(myvocaloid) : $(OBJ_MAIN) $(LIBTARGET)
	g++ -o $@ $(OBJ_MAIN) $(LIBDIRS) $(LIBS) -lpthread -Wl,--no-as-needed -ldl -Wl,-rpath=. -Wl,-rpath-link=$(LIBS)

$(server) : $(PB_OBJ_FILES) $(GRPC_OBJ_FILES) $(OBJ_WRAPPER) $(OBJ_SERVER) $(LIBTARGET)
	g++ -o $@ $(PB_OBJ_FILES) $(GRPC_OBJ_FILES) $(OBJ_WRAPPER) $(OBJ_SERVER) $(LIBDIRS) $(LIBS) $(GRPCLIB) -lpthread -Wl,--no-as-needed -ldl -Wl,-rpath=. -Wl,-rpath-link=$(LIBS)



clean:
	@rm -rf $(TARGET) $(OBJDIR)
