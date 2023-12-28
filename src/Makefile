all: build run

init:
	cd Desktop; make

build:
	cd Vue; make build;
	cd Django; make copy_ui; make install;
	cd Desktop; make

clean:
	cd Desktop; rm -rf manage dist build
	cd Django; rm -rf  dist build