LLVM_PREFIX ?= /opt/llvm-riscv
RISCV_TOOLCHAIN_PATH ?= /opt/riscv-gnu-toolchain
SYSROOT ?= $(RISCV_TOOLCHAIN_PATH)/riscv32-unknown-elf
POCL_CC_PATH ?= /opt/pocl/compiler
POCL_RT_PATH ?= /opt/pocl/runtime

VORTEX_DRV_PATH ?= $(realpath ../../../driver)
VORTEX_RT_PATH ?= $(realpath ../../../runtime)

K_LLCFLAGS += "-O3 -march=riscv32 -target-abi=ilp32f -mcpu=generic-rv32 -mattr=+m,+f -float-abi=hard -code-model=small"
K_CFLAGS   += "-v -O3 --sysroot=$(SYSROOT) --gcc-toolchain=$(RISCV_TOOLCHAIN_PATH) -march=rv32imf -mabi=ilp32f -I$(VORTEX_RT_PATH)/include -fno-rtti -fno-exceptions -ffreestanding -nostartfiles -Wl,--gc-sections -Wl,-Bstatic,-T$(VORTEX_RT_PATH)/linker/vx_link.ld"
K_LDFLAGS  += "$(VORTEX_RT_PATH)/libvortexrt.a -lm"

CXXFLAGS += -std=c++11 -O0 -g -Wall -fpermissive -Wextra -pedantic -Wfatal-errors

CXXFLAGS += -I$(POCL_RT_PATH)/include

LDFLAGS += -L$(POCL_RT_PATH)/lib -L$(VORTEX_PATH) -lOpenCL -lvortex

PROJECT=vecadd

SRCS = main.cc

all: $(PROJECT) kernel.pocl

kernel.pocl: kernel.cl
	LLVM_PREFIX=$(LLVM_PREFIX) POCL_DEBUG=all LD_LIBRARY_PATH=$(LLVM_PREFIX)/lib:$(POCL_CC_PATH)/lib $(POCL_CC_PATH)/bin/poclcc -LLCFLAGS $(K_LLCFLAGS) -CFLAGS $(K_CFLAGS) -LDFLAGS $(K_LDFLAGS) -o kernel.pocl kernel.cl
 
$(PROJECT): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

run: $(PROJECT) kernel.pocl   
	LD_LIBRARY_PATH=$(POCL_RT_PATH)/lib:$(VORTEX_PATH):$(LD_LIBRARY_PATH) ./$(PROJECT) -k kernel.pocl

.depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend;

clean:
	rm -rf $(PROJECT) *.o *.pocl *.dump .depend 

ifneq ($(MAKECMDGOALS),clean)
    -include .depend
endif