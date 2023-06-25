IP := 127.0.0.1
PORT := 8000
PACKAGE := mysite
APP := polls


start: env pip_update pip_install

server_run:
	cd $(PACKAGE); python manage.py runserver $(IP):$(PORT)

app:
	cd $(PACKAGE); python manage.py startapp $(APP)

$(PACKAGE): pip_install
	django-admin startproject $(PACKAGE)

migrate:
	cd $(PACKAGE); python manage.py migrate

make_migration:
	cd $(PACKAGE); python manage.py makemigrations $(APP)

env:
	python3 -m venv env
	@echo
	@echo "source env/bin/activate"
	@echo

	exit 1;

pip_update:
	pip install --upgrade pip

pip_install:
	pip install -r requirements.txt