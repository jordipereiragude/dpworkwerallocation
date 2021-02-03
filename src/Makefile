CCC = g++
CCOPT = -std=c++11 -m64 -O2 -fPIC -fno-strict-aliasing -fexceptions -Wall

OBJS = obj/instance.o obj/wap.o obj/dp.o obj/hs.o

TARGETS = ../wap

all: $(TARGETS) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGETS)

obj/instance.o : instance.cpp
		$(CCC) -c $(CCOPT) instance.cpp -o obj/instance.o

obj/hs.o : hs.cpp
		$(CCC) -c $(CCOPT) hs.cpp -o obj/hs.o

obj/wap.o : wap.cpp
		$(CCC) -c $(CCOPT) wap.cpp -o obj/wap.o

obj/dp.o : dp.cpp
		$(CCC) -c $(CCOPT) dp.cpp -o obj/dp.o

../wap: $(OBJS)
		$(CCC) $(CCOPT) $(OBJS) -o ../wap
