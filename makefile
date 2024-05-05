install:
	sudo mkdir /usr/local/etc/iris;
	sudo cp ./config/* /usr/local/etc/iris/;
	sudo cp ./out/Debug/src/iris /usr/local/bin/;

remove:
	sudo rm -rf /usr/local/etc/iris/;
	sudo rm -rf /usr/local/bin/iris;

cleaninstall:
	make remove 
	make install
