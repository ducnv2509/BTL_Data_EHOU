all: HoaDonApp

HoaDonApp: main.o hoadon.o utils.o
	g++ -std=c++11 main.o hoadon.o utils.o -o HoaDonApp

main.o: main.cpp hoadon.h
	g++ -std=c++11 -c main.cpp

hoadon.o: hoadon.cpp hoadon.h utils.h
	g++ -std=c++11 -c hoadon.cpp

utils.o: utils.cpp utils.h
	g++ -std=c++11 -c utils.cpp

clean:
	rm -f *.o HoaDonApp