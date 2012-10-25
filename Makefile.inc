NAME = GLCD

#########################################
#				Doxygen 				#
#########################################

# doxygen executable
DOXYGEN = doxygen

# doxygen flags
DOXYGENFLAGS = ./doxygen.conf

#########################################
#				msp430-gcc				#
#		libs in /usr/msp430/lib/		#
#########################################
DRIVER = sed1335
DEVICE=MSP430
COMPILER = msp430
TARGET = teste
MMCU = -mmcu=msp430g2553 -lfp
LIB_LOCAL = -L/usr/msp430/lib/

#########################################
#				arm-elf-gcc				#
#	libs in /usr/lib/gcc/arm-elf/4.0.2/	#
#########################################
#DRIVER = sed1335
#DEVICE=LPC2100
#COMPILER = arm-elf
#TARGET = teste
#MMCU =  -mcpu=arm7tdmi
#LIB_LOCAL = -L/usr/lib/gcc/arm-elf/4.0.2/

#########################################
#				avr-gcc					#
#		libs in /usr/lib/avr/lib/		#
#########################################
#DRIVER = sed1335
#DEVICE = avr
#COMPILER = avr
#TARGET = teste
#MMCU =  -mmcu=atmega8
#LIB_LOCAL = -L/usr/lib/avr/lib/

#---------------------------------------

GRLIB_DIR = grlib
DRIVER_DIR = driver
SRC_DIR = OLED
OBJ_DIR = obj
LIB_DIR = lib
TEST_DIR = src
ROOT_DIR =.

CC = $(COMPILER)-gcc
AR = $(COMPILER)-ar
LD = $(COMPILER)-ld -v 
AS = $(COMPILER)-as
CP = $(COMPILER)-objcopy
OD = $(COMPILER)-objdump

CC_FLAGS = -c -fno-common -O0 -g3 $(MMCU)
AR_FLAGS = rcs
LD_FLAGS = $(LIB_LOCAL) -lm -L$(ROOT_DIR)/$(LIB_DIR)/ -l$(NAME)-$(DEVICE) -lc $(MMCU)
CP_FLAGS = -O ihex
OD_FLAGS = -x --syms

INCLUDES = -I$(ROOT_DIR)/include

.SILENT:
