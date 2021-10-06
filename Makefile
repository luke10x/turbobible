clean:
	rm -f bible

indent:
	indent -kr -ts5 -nut -l80 *.cpp

bible:
	g++ -std=c++14 -o bible bible.cpp ../tvision/build/libtvision.a \
		-I../tvision/include  \
		$$(ncursesw5-config --cflags --libs)
		# -lgpm
