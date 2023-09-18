all:compile_client link_client open_client compile_server link_server open_server

compile_client:
	g++ -Isrc/include -c client.cpp -o client.o -DSFML_STATIC

link_client:
	g++ client.o -o client -Lsrc/lib -lsfml-network-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lws2_32  -lopengl32 -lwinmm -lgdi32 -lfreetype

open_client:
	./client.exe 

compile_server:
	g++ -Isrc/include -c server.cpp -o server.o -DSFML_STATIC

link_server:
	g++ server.o -o server -Lsrc/lib -lsfml-network-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lws2_32  -lopengl32 -lwinmm -lgdi32 -lfreetype 

open_server:
	./server.exe 

clean:
	rm -f client.o server.o client.exe server.exe
