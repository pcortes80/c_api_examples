CC=gcc
LDFLAGS=-ldl
OBJECTS=Example.o NiFpga.o
EXECUTABLE=Example

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)

Example.o: NiFpga_ExampleRSeries.h NiFpga.h

NiFpga.o: NiFpga.h

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
