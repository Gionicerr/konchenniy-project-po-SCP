demo: demo.cpp
	g++ demo.cpp -o demo

mycpp.dll: demo.cpp
	g++ demo.cpp -shared -o demo.dll -static-libgcc -static-libstdc++



