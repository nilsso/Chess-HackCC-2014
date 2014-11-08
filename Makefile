CC = g++
CFLAGS = -std=c++11 `pkg-config --cflags sdl2 SDL2_image SDL2_ttf`

LD = g++
LIBS = -std=c++11 `pkg-config --libs sdl2 SDL2_image SDL2_ttf`

MKDIR_P = mkdir -p
RM = -rm -f
RM_R = -rm -rf

SDIR = src
ODIR = out

FILES = main PrisonChess

SRCS = $(SDIR)/$(FILES).cpp
OBJS = $(FILES).o

TARGET = PrisonChess.out

all: directories $(TARGET)

$(TARGET): $(FILES)
	$(LD) $(LIBS) -o $@ $(FILES:%=$(ODIR)/%.o)

$(FILES): $(FILES:%=$(ODIR)/%.o)

$(ODIR)/%.o:
	$(CC) $(CFLAGS) -c $(@:$(ODIR)/%.o=$(SDIR)/%.cpp) -o $@

.PHONY: directories clean remove

# Make directories if needed
directories: $(ODIR)

$(ODIR):
	$(MKDIR_P) $(ODIR)

# Remove output files
clean:
	$(RM_R) $(ODIR)

# Clean and remove target
remove: clean
	$(RM) $(TARGET)

