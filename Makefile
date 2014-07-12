PROJECT = libmbed
GCC_BIN = msp430
CPU = -mmcu=msp430g2553
TARGET = TARGET_TI

SOURCES = BusIn.cpp
BUILDDIR = build
APIDIR = libraries/mbed/api
HALDIR = libraries/mbed/hal
SRCDIR = libraries/mbed/common
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES)) 
INCLUDE_PATHS = -I $(APIDIR) -I $(HALDIR) -I libraries/mbed/targets/hal/$(TARGET)  -I libraries/mbed/targets/cmsis/$(TARGET) 
LIBRARY_PATHS = -L $(BUILDDIR) 
LIBRARIES = -lmbed 

############################################################################### 
AS      = $(GCC_BIN)-as
AR      = $(GCC_BIN)-ar
CC      = $(GCC_BIN)-gcc
CPP     = $(GCC_BIN)-g++
LD      = $(GCC_BIN)-gcc
OBJCOPY = $(GCC_BIN)-objcopy

CC_FLAGS = $(CPU) -c -g -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections 
CC_FLAGS += -MMD -MP
CC_SYMBOLS = -D$(TARGET) -D__MBED__=1 

LD_FLAGS = $(CPU) -Wl,--gc-sections -u _printf_float -u _scanf_float
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys

ifeq ($(DEBUG), 1)
	CC_FLAGS += -DDEBUG -O0
else
	CC_FLAGS += -DNDEBUG -Os
endif

all: $(PROJECT).a

clean:
	rm -f $(PROJECT).bin $(PROJECT).elf $(OBJECTS) $(DEPS)

%.o: $(SRCDIR)/%.cpp 
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++98 $(INCLUDE_PATHS) -o $(BUILDDIR)/$@ $<

$(PROJECT).a: $(OBJECTS)
	$(AR) rcs $(BUILDDIR)/$@ $(BUILDDIR)/$^

$(PROJECT).elf: $(OBJECTS)
	$(LD) $(LD_FLAGS) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

DEPS = $(OBJECTS:.o=.d)
-include $(DEPS)

