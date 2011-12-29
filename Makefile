SUBDIRS= UI

DIRS= $(wildcard *)
DIRS= $(patsubst .%,,$(DIRS))
DIRS= $(patsubst %.cpp,,$(DIRS))

ALL_OBJECTS= $(patsubst %.cpp,%.o,$(ALL_FILES))

a.out: $(ALL_OBJECTS)
	ls $(DIRS)
	gcc $(ALL_OBJECTS)

%.o: %.cpp
	gcc -c $? -o $@ -I . -std=c++0x