# if (`uname` == "Darwin")
# OPEN := open
# else
# OPEN := 
# endif

all: copy build open

clean:
	rm -rf ./manage
	rm -rf ./dist

copy:
	cd ../src; make install
	cp -r ../src/dist/manage .

build:
	npm run build

start:
	npm run start

open:
	open ./dist/mac/my-electron-app.app
