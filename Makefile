TARGET := test

CXX := g++ 
CUDA_DIR = /opt/cuda
NVCC := $(CUDA_DIR)/bin/nvcc

CFLAGS := -std=c++11 -Iinc
LDFLAGS := 

CU_CFLAGS := -std=c++11 -Iinc -DUSING_CUDA -Wno-deprecated-gpu-targets
CU_LDFLAGS := -L$(CUDA_DIR)/lib64 -lcuda -lcudart -lcublas

SRCS := $(wildcard src/*.cpp) 
OBJS := $(patsubst %cpp,%o,$(SRCS))

CU_SRCS := $(patsubst %cpp,%cu,$(SRCS))
CU_OBJS := $(patsubst %cu,%cu.o,$(CU_SRCS))

all: $(OBJS) 
	$(CXX) $^ $(LDFLAGS) -o $(TARGET)
cuda: $(CU_OBJS)
	$(NVCC) $^ $(CU_LDFLAGS) -o $(TARGET)
clean:
	rm $(TARGET) $(CU_SRCS) src/*.o
clean_all:  
	rm $(TARGET) $(CU_SRCS) $(OBJS) $(CU_OBJS)
%.o:%.cpp  
	$(CXX) $< $(CFLAGS) -c -o $@ 
%.cu.o:%.cu
	$(NVCC) $< $(CU_CFLAGS) -c -o $@ 
%.cu:%.cpp
	ln $< $@
