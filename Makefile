#Be careful with trailing spaces in project name
PROJECT = main
DEVICE = rf2500
GCC_BIN = msp430
CPU = -mmcu=msp430g2553
TARGET = TARGET_TI

LIB = libmbed
BUILDDIR = build
APIDIR = libraries/mbed/api
HALDIR = libraries/mbed/hal
SRCDIR = libraries/mbed/common
TDIR = libraries/mbed/targets/hal/$(TARGET)
SOURCES = $(shell find $(TDIR) -name '*.c' -exec basename {} \;) 
SOURCES1 = $(shell find $(SRCDIR) -name '*.cpp' -exec basename {} \;) 
OBJECTS = $(patsubst %.c, %.o, $(SOURCES)) 
OBJECTS += $(patsubst %.cpp, %.o, $(SOURCES1)) 
#Archive members
OUTPUT = $(addprefix $(BUILDDIR)/, $(OBJECTS))
INCLUDE_PATHS = -I $(APIDIR) -I $(HALDIR) -I $(TDIR) -I libraries/mbed/targets/cmsis/$(TARGET) 
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
CC_SYMBOLS = -D$(TARGET) -D__MBED__=1 -DTARGET_MSP430 -DTOOLCHAIN_GCC

LD_FLAGS = $(CPU) -Wl,--gc-sections -u _printf_float -u _scanf_float
#LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys

ifeq ($(DEBUG), 1)
	CC_FLAGS += -DDEBUG -O0
else
	CC_FLAGS += -DNDEBUG -Os
endif

.PHONY: clean

all: $(BUILDDIR)/$(LIB).a

clean:
	rm -rf $(PROJECT).bin $(PROJECT).elf $(BUILDDIR) $(DEPS)
prog:
	mspdebug $(DEVICE) "prog $(PROJECT).elf"

$(BUILDDIR)/%.o: $(TDIR)/%.c | $(BUILDDIR)
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++98 $(INCLUDE_PATHS) -o $@ $<

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++98 $(INCLUDE_PATHS) -o $@ $<

%.o: %.c 
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++98 $(INCLUDE_PATHS) -o $@ $<

%.o: %.cpp 
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++98 $(INCLUDE_PATHS) -o $@ $<

$(BUILDDIR)/$(LIB).a: $(OUTPUT)
	$(AR) rcs $@ $? 

%.elf: %.o 
	$(LD) $(LD_FLAGS) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

$(BUILDDIR):
	mkdir $(BUILDDIR)

DEPS = $(OUTPUT:.o=.d)
-include $(DEPS)

