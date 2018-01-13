APPNAME=gdktest

CFLAGS = -Wall -O0 -g  $(shell pkg-config gdk-3.0 --cflags)
CXXFLAGS = $(CFLAGS)

LFLAGS = $(shell pkg-config gdk-3.0 --libs)

.PHONY: clean run

default: $(APPNAME)

$(APPNAME): gdktest.o
	$(CXX) -o $@ $(CFLAGS) $^ $(LFLAGS)

run: $(APPNAME)
	./$^

clean:
	-rm gdktest.o $(APPNAME)
