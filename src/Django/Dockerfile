FROM python:3.11-alpine


WORKDIR /project
COPY ./requirements.txt /project/requirements.txt 

RUN apk add --no-cache g++ make;    \
    pip install --upgrade pip;      \
    pip install -r /project/requirements.txt;

ENTRYPOINT [ "make" ]
