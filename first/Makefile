#used for building the GBA game!

# Add the devkitarm binaries to the path
# Expects the DEVKITARM env var to already be set
PATH := $(DEVKITARM)/bin:$(PATH)

# Name of the project
PROJ := first
# Unclear why tonc includes this variable? Feels redundant?
TARGET := $(PROJ)

# Will later be a list of object files
OBJS := $(PROJ).o

# Temporary fix for updating with headers
# correct way to do it is with -MMD .d files
# will explore later!
HEADERS := toolbox.h

# all devkit arm tools we'll use start with this prefix
PREFIX := arm-none-eabi-
#use gcc for both compiling and linking
CC      := $(PREFIX)gcc
LD      := $(PREFIX)gcc
# used for copying from one object file to another (maybe will be used to convert .o to .gba?)
OBJCOPY := $(PREFIX)objcopy

# mthumb-interwork is needed so ARM and THUMB code can be used together
ARCH  := -mthumb-interwork -mthumb

#gba.specs is for cart, gba_mb.specs is for multiboot. We're doing cart
#used during linking
SPECS := -specs=gba.specs


# Flags for compiling
# O2 - moderate optimization tradeoff between speed and size
# Wall - all warnings on
# fno-strict-aliasing allows for pointers of different types to point to the same data (used for our pointer tricks like writing multiple 16 bits with a single 32 bit write)
CFLAGS := $(ARCH) -O2 -Wall -fno-strict-aliasing

# Flags for linking
LDFLAGS := $(ARCH) $(SPECS)

#indicates that build and clean are just target names, not filenames
#.PHONY is a special built in target name!
.PHONY : build clean

# for the build to be finished, the gba file must be created
build: $(TARGET).gba

# Our overall plan:
# 1. compile
# 2. link
# 3. strip header
# 4. fix header

# COMPILE
# % is wildcard
# The multiple colons is for a static pattern rule
# Every .o needs a .c
$(OBJS) : %.o : %.c $(HEADERS)
# -c compiles without linking
# Maybe we do this in separate steps to better recognize where changes are needed?
# gcc gets called once per file out of date
# $< is the first prereq (the c file name)
# $@ is the target name (the object file name)
# -o is for specifying the name of the object file to create
	$(CC) -c $< $(CFLAGS) -o $@

# LINK
# used for making the elf file (executable linkable file)
$(TARGET).elf : $(OBJS)
# $^ ALL the prereqs
# $@ target name (the elf name)
	$(LD) $^ $(LDFLAGS) -o $@


# STRIP/FIX HEADER
# for the gba file to be made, we need the elf
$(TARGET).gba : $(TARGET).elf
# $< is first prereq
# $@ is target name
# -v   verbose
# -O binary  means the output format is binary
# Strips the header
	$(OBJCOPY) -v -O binary $< $@
#- ignore exit status. Continue even if failed. Not sure why we would want this here?
#@ do not echo. Also not 100% sure why we don't want this?
#gbafix will fix the ROM header to make it GBA compatible
	-@gbafix $@

# clean up
# no prereqs
clean : 
# @ do not echo the rm command itself
# f force
# v verbose - list all files being deleted
	@rm -fv *.gba
	@rm -fv *.elf
	@rm -fv *.o
