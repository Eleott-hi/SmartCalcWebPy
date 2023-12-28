UNAME := $(shell uname)
OPEN :=
APP := "SmartCalcDescktop-1.0.0.AppImage"

ifeq ($(UNAME), Darwin)
	OPEN := open
	APP := mac/SmartCalcDescktop.app
endif

all: copy build open

clean:
	rm -rf ./manage
	rm -rf ./dist

copy:
	cp -r ../Django/dist/manage .

build:
	npm run build

start:
	npm run start
	
open:
	$(OPEN) ./dist/$(APP); 
