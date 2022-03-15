# ----------------------------
# Makefile Options
# ----------------------------

NAME = PERIODIC
ICON = icon.png
DESCRIPTION = "Periodic Table CE"
COMPRESSED = YES
ARCHIVED = NO
HAS_PRINTF := NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
