clean:
	rm -f bible

indent:
	indent -kr -ts4 -nut -l80 *.c

bible:
	g++ -std=c++14 -o bible bible.cpp ../tvision/build/libtvision.a \
		-I../tvision/include  \
		$$(ncursesw5-config --cflags --libs)
		# -lgpm
