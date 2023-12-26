PROJECT := SmartCalcWeb

IP := 0.0.0.0
PORT := 8000
PACKAGE := $(PROJECT)
APP_PACKAGE := django-polls
APP := calculator

start: pip_update pip_install lib migrate test run_server

copy_ui:
	cd ../vue_ui; make build;
	rm -rf $(PROJECT)/assets
	cp -r ../vue_ui/SmartCalcWebUi/dist/assets $(PROJECT)
	cp ../vue_ui/SmartCalcWebUi/dist/index.html $(PROJECT)/calculator/templates/calculator/index.html


install: 
	pyinstaller manage.spec -y

docker:
	-@docker compose up

start_project:
	django-admin startproject $(PACKAGE)

start_app:
	cd $(PACKAGE); python3 manage.py startapp $(APP)

sqlmigrate:
	cd $(PACKAGE); python3 manage.py sqlmigrate $(APP) 0001

run_server:
	cd $(PACKAGE); python3 manage.py runserver $(IP):$(PORT)

admin:
	cd $(PACKAGE); python3 manage.py createsuperuser

test:
	cd $(PACKAGE); python3 manage.py test $(APP)

lib:
	cd libs/RPN; make
	cd libs/Loan; make
	cd libs/Deposit; make

$(PACKAGE): pip_install
	django-admin startproject $(PACKAGE)

migrate: make_migration
	cd $(PACKAGE); python3 manage.py migrate

test:
	cd $(PACKAGE); python3 manage.py test $(APP)

shell:
	cd $(PACKAGE); python3 manage.py shell

make_migration:
	cd $(PACKAGE); python3 manage.py makemigrations $(APP)

env:
	python3 -m venv env
	@echo
	@echo "source env/bin/activate"
	@echo

	exit 1;

freeze:
	pip freeze > requirements.txt

build_package:
	cd $(APP_PACKAGE); python3 setup.py sdist

install_packege:
	python3 -m pip install $(APP_PACKAGE)/dist/*.tar.gz

pip_update:
	pip install --upgrade pip

pip_install:
	pip install -r requirements.txt

.PHONY: docker

pyinstaller:
	./dist/manage/manage runserver --noreload