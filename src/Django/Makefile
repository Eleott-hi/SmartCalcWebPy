PROJECT := SmartCalcWeb

IP := 0.0.0.0
PORT := 8000
PACKAGE := $(PROJECT)
APP_PACKAGE := django-polls
APP := calculator

all: pip_update pip_install lib migrate test run_server

copy_ui:
	rm -rf $(PROJECT)/assets
	cp -r ../Vue/SmartCalcWebUi/dist/assets $(PROJECT)
	cp ../Vue/SmartCalcWebUi/dist/index.html $(PROJECT)/calculator/templates/calculator/index.html

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

freeze:
	pip freeze > requirements.txt

pip_update:
	pip install --upgrade pip

pip_install:
	pip install -r requirements.txt
