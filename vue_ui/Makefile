
PROJECT := SmartCalcWebUi

all: dev

start:  create chart intall dev

up:
	docker-compose build
	docker-compose up

down:
	docker-compose down

create:
	npm create vue@latest

install:
	cd $(PROJECT); npm instal

dev: sass
	cd $(PROJECT); npm run dev

build:
	cd $(PROJECT); npm run build

chart:
	cd $(PROJECT); npm install vue-chartjs chart.js @vuepic/vue-datepicker

nvm:
	nvm install 16
	nvm use 16

sass:
#	cd $(PROJECT); sass scss/custom.scss src/assets/custom.css

nvm_install:
	curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/master/install.sh | bash