SUBDIRS= UI

ALL_SOURCES= main.cpp Game.cpp
ALL_OBJECTS= $(patsubst %.cpp,.obj/%.o,$(ALL_SOURCES))
ALL_DEPS= $(patsubst %.cpp,.dep/%.cpp,$(ALL_SOURCES))

a.out: .obj .dep $(ALL_OBJECTS)
	gcc $(ALL_OBJECTS) -std=c++0x

.obj:
	mkdir .obj
.dep:
	mkdir .dep
.obj/%.o: %.cpp
	gcc -c $*.cpp -o $@ -I . -std=c++0x
	gcc -MM $*.cpp -I . -std=c++0x -MT '.obj/$*.o' -MF .dep/$*.cpp

clean:
	rm -r -f .dep .obj a.out
-include $(ALL_DEPS)
