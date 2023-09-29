all:compile_client compile_server

compile_client:
	cp -R ../../src/client/assets ./ && g++ ../../src/client/index.cpp -o client.exe -l sfml-network -l sfml-graphics -l sfml-window -l sfml-system -l freetype

compile_server:
	g++ ../../src/server/index.cpp -o server.exe -l sfml-network -l sfml-system
