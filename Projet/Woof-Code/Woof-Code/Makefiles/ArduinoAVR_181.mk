#
# embedXcode
# ----------------------------------
# Embedded Computing on Xcode
#
# Copyright © Rei Vilo, 2010-2020
# https://embedXcode.weebly.com
# All rights reserved
#
#
# Last update: 06 Nov 2019 release 11.3.2
#


ifeq ($(MAKEFILE_NAME),)

ARDUINO_AVR_1 = $(ARDUINO_180_PACKAGES_PATH)/arduino

ifneq ($(wildcard $(ARDUINO_AVR_1)/hardware/avr),)
    ARDUINO_AVR_APP     = $(ARDUINO_AVR_1)
    ARDUINO_AVR_PATH    = $(ARDUINO_AVR_APP)
    ARDUINO_181_AVR_BOARDS  = $(ARDUINO_AVR_APP)/hardware/avr/$(ARDUINO_AVR_RELEASE)/boards.txt
endif

BOARD_CHECK   := 0
ifneq ($(call PARSE_FILE,$(BOARD_TAG),name,$(ARDUINO_181_AVR_BOARDS)),)
    BOARD_CHECK   := 1
endif
ifneq ($(call PARSE_FILE,$(BOARD_TAG1),name,$(ARDUINO_181_AVR_BOARDS)),)
    BOARD_CHECK   := 1
endif

ifeq ($(BOARD_CHECK),1)
MAKEFILE_NAME = ArduinoAVR_181


# Adafruit 1.6.1 AVR specifics
# Arduino 1.6.1 AVR specifics
# LittleRobotFriends 1.6.1 specifics
# ----------------------------------
#
#ifneq ($(findstring LITTLEROBOTFRIENDS,$(GCC_PREPROCESSOR_DEFINITIONS)),)
#    PLATFORM         := LittleRobotFriends
#    PLATFORM_TAG      = ARDUINO=$(LITTLEROBOTFRIENDS_RELEASE) EMBEDXCODE=$(RELEASE_NOW) $(GCC_PREPROCESSOR_DEFINITIONS)
#    APPLICATION_PATH := $(LITTLEROBOTFRIENDS_PATH)
#    BOARDS_TXT       := $(LITTLEROBOTFRIENDS_BOARDS)
#    USER_LIBS_LIST   := $(filter-out 0,$(USER_LIBS_LIST)) LittleRobotFriends
#
#else ifneq ($(findstring ADAFRUIT,$(GCC_PREPROCESSOR_DEFINITIONS)),)
#    PLATFORM         := Adafruit
#    PLATFORM_TAG      = ARDUINO=$(ARDUINO_RELEASE) ADAFRUIT EMBEDXCODE=$(RELEASE_NOW)
#    APPLICATION_PATH := $(ARDUINO_PATH)
#    BOARDS_TXT       := $(APPLICATION_PATH)/hardware/adafruit/avr/boards.txt
#
#else
#    PLATFORM         := Arduino
#    PLATFORM_TAG      = ARDUINO=$(ARDUINO_RELEASE) ARDUINO_ARCH_AVR EMBEDXCODE=$(RELEASE_NOW) ARDUINO_$(ARDUINO_TAG)
#    APPLICATION_PATH := $(ARDUINO_PATH)
#    BOARDS_TXT       := $(HARDWARE_PATH)/boards.txt
#endif

PLATFORM         := Arduino
BUILD_CORE       := avr
SUB_PLATFORM     := avr
PLATFORM_TAG      = ARDUINO=10812 ARDUINO_ARCH_AVR ARDUINO_$(BUILD_BOARD) EMBEDXCODE=$(RELEASE_NOW) $(filter __%__ ,$(GCC_PREPROCESSOR_DEFINITIONS))
APPLICATION_PATH := $(ARDUINO_PATH)
PLATFORM_VERSION := AVR $(ARDUINO_AVR_RELEASE) for Arduino $(ARDUINO_IDE_RELEASE)

HARDWARE_PATH     = $(ARDUINO_AVR_PATH)/hardware/avr/$(ARDUINO_AVR_RELEASE)

# With ArduinoCC 1.6.6, AVR 1.6.9 used to be under ~/Library
TOOL_CHAIN_PATH   = $(ARDUINO_AVR_PATH)/tools/avr-gcc/$(ARDUINO_GCC_AVR_RELEASE)
OTHER_TOOLS_PATH  = $(ARDUINO_AVR_PATH)/tools/avrdude/$(ARDUINO_AVRDUDE_RELEASE)

# With ArduinoCC 1.6.7, AVR 1.6.9 is back under Arduino.app
ifeq ($(wildcard $(TOOL_CHAIN_PATH)),)
    TOOL_CHAIN_PATH   = $(ARDUINO_PATH)/hardware/tools/avr
endif
ifeq ($(wildcard $(OTHER_TOOLS_PATH)),)
    OTHER_TOOLS_PATH  = $(ARDUINO_PATH)/hardware/tools/avr
endif

# Complicated menu system for Arduino 1.5
# Another example of Arduino's quick and dirty job
#
BOARD_TAGS_LIST   = $(BOARD_TAG) $(BOARD_TAG1) $(BOARD_TAG2)
SEARCH_FOR        = $(strip $(foreach t,$(1),$(call PARSE_BOARD,$(t),$(2))))

APP_TOOLS_PATH   := $(TOOL_CHAIN_PATH)/bin
CORE_LIB_PATH    := $(HARDWARE_PATH)/cores/arduino
APP_LIB_PATH     := $(HARDWARE_PATH)/libraries
BOARDS_TXT       := $(HARDWARE_PATH)/boards.txt
#BUILD_BOARD       = $(call PARSE_BOARD,$(BOARD_TAG),build.board)
BUILD_BOARD       = $(firstword $(call SEARCH_FOR,$(BOARD_TAGS_LIST),build.board))

ARDUINO_NAME      =  $(call PARSE_BOARD,$(BOARD_TAG),build.board)


# Sketchbook/Libraries path
# wildcard required for ~ management
# ?ibraries required for libraries and Libraries
#
ifeq ($(USER_LIBRARY_DIR)/Arduino15/preferences.txt,)
    $(error Error: run Arduino once and define the sketchbook path)
endif

ifeq ($(shell if [ -d '$(SKETCHBOOK_DIR)' ]; then echo 1 ; fi ),)
    SKETCHBOOK_DIR = $(shell grep sketchbook.path $(USER_LIBRARY_DIR)/Arduino15/preferences.txt | cut -d = -f 2)
endif
ifeq ($(shell if [ -d '$(SKETCHBOOK_DIR)' ]; then echo 1 ; fi ),)
   $(error Error: sketchbook path not found)
endif
USER_LIB_PATH  = $(wildcard $(SKETCHBOOK_DIR)/?ibraries)


# Tool-chain names
#
CC      = $(APP_TOOLS_PATH)/avr-gcc
CXX     = $(APP_TOOLS_PATH)/avr-g++
# LTO requires avr-gcc-ar
AR      = $(APP_TOOLS_PATH)/avr-gcc-ar
OBJDUMP = $(APP_TOOLS_PATH)/avr-objdump
OBJCOPY = $(APP_TOOLS_PATH)/avr-objcopy
SIZE    = $(APP_TOOLS_PATH)/avr-size
NM      = $(APP_TOOLS_PATH)/avr-nm

ifeq ($(BOARD_NAME),)
    BOARD_NAME          := $(call SEARCH_FOR,$(BOARD_TAGS_LIST),name)
endif

# MCU options
#
MCU_FLAG_NAME           := mmcu
ifeq ($(MCU),)
    MCU                 := $(call SEARCH_FOR,$(BOARD_TAGS_LIST),build.mcu)
endif

ifeq ($(F_CPU),)
    F_CPU               := $(call SEARCH_FOR,$(BOARD_TAGS_LIST),build.f_cpu)
endif

ifeq ($(MAX_FLASH_SIZE),)
    MAX_FLASH_SIZE      := $(call SEARCH_FOR,$(BOARD_TAGS_LIST),upload.maximum_size)
endif

ifeq ($(AVRDUDE_BAUDRATE),)
    AVRDUDE_BAUDRATE    := $(call SEARCH_FOR,$(BOARD_TAGS_LIST),upload.speed)
endif

ifeq ($(AVRDUDE_PROGRAMMER),)
    AVRDUDE_PROGRAMMER  := $(call SEARCH_FOR,$(BOARD_TAGS_LIST),upload.protocol)
endif


# Specific AVRDUDE location and options
#
AVRDUDE_COM_OPTS  = -D -p$(MCU) -C$(AVRDUDE_CONF)

ifneq ($(BOARD_TAG1),)
# Adafruit Pro Trinket uses arduino:eightanaloginputs
    avr166_10        = $(call PARSE_BOARD,$(BOARD_TAG1),build.variant)
    VARIANT      = $(patsubst arduino:%,%,$(avr166_10))
    VARIANT_PATH = $(HARDWARE_PATH)/variants/$(VARIANT)
else
# Adafruit Pro Trinket uses arduino:eightanaloginputs
    avr166_10        = $(call PARSE_BOARD,$(BOARD_TAG),build.variant)
    VARIANT      = $(patsubst arduino:%,%,$(avr166_10))
    VARIANT_PATH = $(HARDWARE_PATH)/variants/$(VARIANT)
endif


# Two locations for Arduino libraries
#
APP_LIB_PATH    = $(HARDWARE_PATH)/libraries

avr166_20    = $(foreach dir,$(APP_LIB_PATH),$(patsubst %,$(dir)/%,$(APP_LIBS_LIST)))
avr166_20   += $(foreach dir,$(APP_LIB_PATH),$(patsubst %,$(dir)/%/utility,$(APP_LIBS_LIST)))
avr166_20   += $(foreach dir,$(APP_LIB_PATH),$(patsubst %,$(dir)/%/src,$(APP_LIBS_LIST)))
avr166_20   += $(foreach dir,$(APP_LIB_PATH),$(patsubst %,$(dir)/%/src/utility,$(APP_LIBS_LIST)))
avr166_20   += $(foreach dir,$(APP_LIB_PATH),$(patsubst %,$(dir)/%/src/arch/$(BUILD_CORE),$(APP_LIBS_LIST)))
avr166_20   += $(foreach dir,$(APP_LIB_PATH),$(patsubst %,$(dir)/%/src/$(BUILD_CORE),$(APP_LIBS_LIST)))

APP_LIB_CPP_SRC = $(foreach dir,$(avr166_20),$(wildcard $(dir)/*.cpp)) # */
APP_LIB_C_SRC   = $(foreach dir,$(avr166_20),$(wildcard $(dir)/*.c)) # */
APP_LIB_H_SRC   = $(foreach dir,$(avr166_20),$(wildcard $(dir)/*.h)) # */
APP_LIB_H_SRC  += $(foreach dir,$(avr166_20),$(wildcard $(dir)/*.hpp)) # */

APP_LIB_OBJS     = $(patsubst $(HARDWARE_PATH)/%.cpp,$(OBJDIR)/%.cpp.o,$(APP_LIB_CPP_SRC))
APP_LIB_OBJS    += $(patsubst $(HARDWARE_PATH)/%.c,$(OBJDIR)/%.c.o,$(APP_LIB_C_SRC))

#BUILD_APP_LIBS_LIST = $(subst $(BUILD_APP_LIB_PATH)/, ,$(APP_LIB_CPP_SRC))
BUILD_APP_LIB_PATH     = $(APPLICATION_PATH)/libraries

avr166_30    = $(foreach dir,$(BUILD_APP_LIB_PATH),$(patsubst %,$(dir)/%,$(APP_LIBS_LIST)))
avr166_30   += $(foreach dir,$(BUILD_APP_LIB_PATH),$(patsubst %,$(dir)/%/utility,$(APP_LIBS_LIST)))
avr166_30   += $(foreach dir,$(BUILD_APP_LIB_PATH),$(patsubst %,$(dir)/%/src,$(APP_LIBS_LIST)))
avr166_30   += $(foreach dir,$(BUILD_APP_LIB_PATH),$(patsubst %,$(dir)/%/src/utility,$(APP_LIBS_LIST)))
avr166_30   += $(foreach dir,$(BUILD_APP_LIB_PATH),$(patsubst %,$(dir)/%/src/arch/$(BUILD_CORE),$(APP_LIBS_LIST)))
avr166_30   += $(foreach dir,$(BUILD_APP_LIB_PATH),$(patsubst %,$(dir)/%/src/$(BUILD_CORE),$(APP_LIBS_LIST)))

BUILD_APP_LIB_CPP_SRC = $(foreach dir,$(avr166_30),$(wildcard $(dir)/*.cpp)) # */
BUILD_APP_LIB_C_SRC   = $(foreach dir,$(avr166_30),$(wildcard $(dir)/*.c)) # */
BUILD_APP_LIB_H_SRC   = $(foreach dir,$(avr166_30),$(wildcard $(dir)/*.h)) # */
BUILD_APP_LIB_H_SRC  += $(foreach dir,$(avr166_30),$(wildcard $(dir)/*.hpp)) # */

BUILD_APP_LIB_OBJS     = $(patsubst $(APPLICATION_PATH)/%.cpp,$(OBJDIR)/%.cpp.o,$(BUILD_APP_LIB_CPP_SRC))
BUILD_APP_LIB_OBJS    += $(patsubst $(APPLICATION_PATH)/%.c,$(OBJDIR)/%.c.o,$(BUILD_APP_LIB_C_SRC))

APP_LIBS_LOCK = 1

CORE_C_SRCS     = $(wildcard $(CORE_LIB_PATH)/*.c $(CORE_LIB_PATH)/*/*.c) # */

###avr166_40              = $(filter-out %main.cpp, $(wildcard $(CORE_LIB_PATH)/*.cpp $(CORE_LIB_PATH)/*/*.cpp $(CORE_LIB_PATH)/*/*/*.cpp $(CORE_LIB_PATH)/*/*/*/*.cpp)) # */
avr166_40              = $(filter-out %main.cpp, $(shell find $(CORE_LIB_PATH) -name \*.cpp))

CORE_CPP_SRCS     = $(filter-out %/$(EXCLUDE_LIST),$(avr166_40))
CORE_AS1_SRCS        = $(shell find $(CORE_LIB_PATH) -name \*.S)
CORE_AS1_SRCS_OBJ = $(patsubst %.S,%.S.o,$(filter %S, $(CORE_AS1_SRCS)))
CORE_AS2_SRCS        = $(shell find $(CORE_LIB_PATH) -name \*.s)
CORE_AS2_SRCS_OBJ = $(patsubst %.s,%.s.o,$(filter %s, $(CORE_AS2_SRCS)))

CORE_OBJ_FILES  += $(CORE_C_SRCS:.c=.c.o) $(CORE_CPP_SRCS:.cpp=.cpp.o) $(CORE_AS1_SRCS_OBJ) $(CORE_AS2_SRCS_OBJ)
#    CORE_OBJS       += $(patsubst $(CORE_LIB_PATH)/%,$(OBJDIR)/%,$(CORE_OBJ_FILES))
#CORE_OBJS       += $(patsubst $(APPLICATION_PATH)/%,$(OBJDIR)/%,$(CORE_OBJ_FILES))
CORE_OBJS       += $(patsubst $(HARDWARE_PATH)/%,$(OBJDIR)/%,$(CORE_OBJ_FILES))

CORE_LIBS_LOCK = 1


# Arduino Leonardo USB PID VID
#
USB_VID     := $(call PARSE_BOARD,$(BOARD_TAG),build.vid)
USB_PID     := $(call PARSE_BOARD,$(BOARD_TAG),build.pid)
USB_VENDOR  := $(call PARSE_BOARD,$(BOARD_TAG),build.usb_manufacturer)
USB_PRODUCT := $(call PARSE_BOARD,$(BOARD_TAG),build.usb_product)

ifneq ($(USB_VID),)
    USB_FLAGS    = -DUSB_VID=$(USB_VID)
    USB_FLAGS   += -DUSB_PID=$(USB_PID)
    USB_FLAGS   += -DUSBCON
    USB_FLAGS   += -DUSB_MANUFACTURER='$(USB_VENDOR)'
    USB_FLAGS   += -DUSB_PRODUCT='$(USB_PRODUCT)'
endif

# Arduino Leonardo serial 1200 reset
#
USB_TOUCH := $(call PARSE_BOARD,$(BOARD_TAG),upload.protocol)

ifeq ($(USB_TOUCH),avr109)
    USB_RESET  = python $(UTILITIES_PATH)/reset_1200.py
endif


INCLUDE_PATH    = $(CORE_LIB_PATH) $(APP_LIB_PATH) $(VARIANT_PATH)
INCLUDE_PATH   += $(sort $(dir $(APP_LIB_CPP_SRC) $(APP_LIB_C_SRC) $(APP_LIB_H_SRC)))
INCLUDE_PATH   += $(sort $(dir $(BUILD_APP_LIB_CPP_SRC) $(BUILD_APP_LIB_C_SRC) $(BUILD_APP_LIB_H_SRC)))

#FIRST_O_IN_A     = $$(find $(BUILDS_PATH) -name wiring_pulse.S.o)


# Flags for gcc, g++ and linker
# ----------------------------------
#
# Common CPPFLAGS for gcc, g++, assembler and linker
#
CPPFLAGS     = $(OPTIMISATION) $(WARNING_FLAGS)
CPPFLAGS    += -$(MCU_FLAG_NAME)=$(MCU) -DF_CPU=$(F_CPU)
CPPFLAGS    += -ffunction-sections -fdata-sections -MMD -flto
CPPFLAGS    += -Wno-error=narrowing
CPPFLAGS    += $(addprefix -D, printf=iprintf $(PLATFORM_TAG))
CPPFLAGS    += $(addprefix -I, $(INCLUDE_PATH))

# Specific CFLAGS for gcc only
# gcc uses CPPFLAGS and CFLAGS
#
CFLAGS       = -std=gnu11 -fno-fat-lto-objects

# Specific CXXFLAGS for g++ only
# g++ uses CPPFLAGS and CXXFLAGS
#
CXXFLAGS     = -fdata-sections -fno-threadsafe-statics -std=gnu++11 -fpermissive -fno-exceptions

# Specific ASFLAGS for gcc assembler only
# gcc assembler uses CPPFLAGS and ASFLAGS
#
ASFLAGS      = -x assembler-with-cpp

# Specific LDFLAGS for linker only
# linker uses CPPFLAGS and LDFLAGS
#
LDFLAGS      = $(OPTIMISATION) $(WARNING_FLAGS)
LDFLAGS     += -$(MCU_FLAG_NAME)=$(MCU)
LDFLAGS     += -flto -fuse-linker-plugin -Wl,--gc-sections,--relax

# Specific OBJCOPYFLAGS for objcopy only
# objcopy uses OBJCOPYFLAGS only
#
#OBJCOPYFLAGS  = -v -Oihex

# Target
#
TARGET_HEXBIN    = $(TARGET_HEX)
TARGET_EEP       = $(OBJDIR)/$(TARGET_NAME).eep


# Commands
# ----------------------------------
# Link command
#
REMOTE_OBJS = $(sort $(CORE_OBJS) $(BUILD_CORE_OBJS) $(APP_LIB_OBJS) $(BUILD_APP_LIB_OBJS) $(VARIANT_OBJS))
REMOTE_NON_A_OBJS = $(USER_OBJS)

COMMAND_LINK    = $(CC) $(LDFLAGS) $(OUT_PREPOSITION)$@ $(LOCAL_OBJS) $(REMOTE_NON_A_OBJS) $(TARGET_A) -LBuilds -lm

# Horrible patch for Leonardo upload command
# Even worse patch for HID-configured Leonardo upload
# ----------------------------------
# Upload port /dev/tty.usbmodem14101
# HID port: /dev/tty.usbmodemHIDPC1
#
ifeq ($(BOARD_TAG),leonardo)
#    USB_RESET := -stty -f $(AVRDUDE_PORT) 1200
#    $(undefine USB_RESET)

ifeq ($(SERIAL_SELECTION_FLAG),1)
    COMMAND_UPLOAD   = PORT=$$(ls -1 $(BOARD_PORT)) ; echo $$PORT ; $(AVRDUDE_EXEC) -C$(AVRDUDE_CONF) -p$(AVRDUDE_MCU) $(AVRDUDE_OPTS) -P$$PORT -Uflash:w:$(TARGET_HEX):i
endif

#    COMMAND_UPLOAD   = -stty -f $(AVRDUDE_PORT) 1200 ; sleep 2 ; $(AVRDUDE_EXEC) $(AVRDUDE_COM_OPTS) $(AVRDUDE_OPTS) -P$(USED_SERIAL_PORT) -Uflash:w:$(TARGET_HEX):i
#    DELAY_BEFORE_UPLOAD = 2
    DELAY_AFTER_UPLOAD = 2
endif # leonardo

endif

endif
