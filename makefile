clean:
	sudo rm -rf /etc/iris/

install:
	sudo mkdir /etc/iris/
	sudo cp ./default_config/* /etc/iris/

cleaninstall:
	make clean
	make install
