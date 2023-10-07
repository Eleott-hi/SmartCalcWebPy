
PROJECT := SmartCalcWebUi

all: dev

up:
	docker-compose build
	docker-compose up

down:
	docker-compose down

create:
	npm create vue@latest

install:
	cd $(PROJECT); npm instal

dev:
	cd $(PROJECT); npm run dev


build:
	cd $(PROJECT); npm run build

chart:
	npm install vue-chartjs chart.js

nvm:
	nvm use 18

nvm_install:
	curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/master/install.sh | bash