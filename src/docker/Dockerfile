FROM python:3.11-alpine

WORKDIR /project
RUN apk add --no-cache g++ make 
# ENV FLASK_APP=app.py
# ENV FLASK_RUN_HOST=0.0.0.0
# VOLUME  ../:/usr/src/app
# COPY . /project

EXPOSE 8000

ENTRYPOINT [ "make" ]