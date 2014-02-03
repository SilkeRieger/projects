# define project name
export PROJECT = rpl_bloom

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
	export BOARD = native
endif

# the absolute path of the RIOT-base dir
export RIOTBASE = $(CURDIR)/../../RIOT

# modules to include
USEMODULE += hashes
USEMODULE += bloom
USEMODULE += random

export INCLUDES = -I$(CURDIR)/include -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/cpu/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/

include $(RIOTBASE)/Makefile.include

all: CFLAGS+= -g
debug: CFLAGS+= -g