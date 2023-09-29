all:compile_client link_client open_client compile_server link_server open_server

compile_client:
	cp -R ../../src/assets ./ && g++ -c ../../src/client/index.cpp -o client.o -DSFML_STATIC

link_client:
	g++ client.o -o client -L lib -lsfml-network-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lws2_32 -lopengl32 -lwinmm -lgdi32 -lfreetype

open_client:
	./client.exe 

compile_server:
	g++ -c ../../src/server/index.cpp -o server.o -DSFML_STATIC

link_server:
	g++ server.o -o server -L lib -lsfml-network-s -lsfml-system-s -lws2_32 -lwinmm -lgdi32 

open_server:
	./server.exe 

clean:
	rm -f client.o server.o client.exe server.exe
