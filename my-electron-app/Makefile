UNAME := $(shell uname)
OPEN :=
APP := "my-electron-app Setup 1.0.0.exe"

ifeq ($(UNAME), Darwin)
	OPEN := open
	APP := mac/my-electron-app.app
endif

all: copy build open

clean:
	rm -rf ./manage
	rm -rf ./dist

copy:
	cd ../src; make 
	cp -r ../src/dist/manage .

build:
	npm run build

start:
	npm run start

open:
	$(OPEN) ./dist/$(APP); 
