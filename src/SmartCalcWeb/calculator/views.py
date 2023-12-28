import datetime
import concurrent.futures
from django.http import (
    HttpResponse,
    HttpResponseRedirect,
    HttpResponseBadRequest,
    JsonResponse,
    HttpResponseNotAllowed,
)
from django.shortcuts import render
# from rest_framework.response import Response
import json
import logging
import toml
from pathlib import Path
# from rest_framework.decorators import api_view
from django.views.decorators.http import require_http_methods
from .pydantic_serializer import *
from .services import *

def Print(*args):
    print(*args, flush=True)

base_dir = Path(__file__).parent.parent
config_path = base_dir / 'calculator/configs/config.toml'
CONFIG = toml.load(config_path)

def GetQuery(query):
    return {k: v[0] for k, v in dict(query).items()}

@require_http_methods(["GET", "POST"])
def config(request):
    try:
        settings = CONFIG['CalculatorSettings']

        if request.method == 'POST':
            data = json.loads(request.body.decode('utf-8'))

            settings['primaryBtnType'] = data.get('primaryBtnType')
            settings['secondaryBtnType'] = data.get('secondaryBtnType')
            settings['isDarkMode'] = data.get('isDarkMode')

            with open(config_path, "w") as toml_file:
                toml.dump(CONFIG, toml_file)

        return JsonResponse(settings, status=200)

    except Exception as e:
        logger.error(f"{e}")
        return HttpResponseBadRequest(json.dumps({"error": str(e)}), content_type="application/json")


@require_http_methods(["GET", "DELETE"])
def history(request):
    try:
        if request.method == 'DELETE':
            DeleteHistory()

        res = GetHistory()

        return JsonResponse({"history": res}, status=200)

    except Exception as e:
        logger.error(f"{e}")
        return HttpResponseBadRequest(json.dumps({"error": str(e)}), content_type="application/json")


def index(request):
    html = "calculator/index.html"
    logger.info(f'{html} loaded')
    return render(request, html)


@require_http_methods(["GET"])
def calculate(request):
    try:
        query = GetQuery(request.GET)
        res = CalculateData(query['expression'], query['x'])
        return JsonResponse({'result': res}, status=200)

    except Exception as e:
        logger.error(f"{e}")
        return HttpResponseBadRequest(json.dumps({"error": str(e)}), content_type="application/json")


@require_http_methods(["GET"])
def plot_calculate(request):
    try:
        query = GetQuery(request.GET)
        data_input = PlotDataInput.parse_obj(query)
        data_output = CaclculatePlotData(data_input)

        return JsonResponse(data_output.dict(), status=200)

    except Exception as e:
        logger.error(f"{e}")
        return HttpResponseBadRequest(json.dumps({"error": str(e)}), content_type="application/json")


@require_http_methods(["GET"])
def loan_calculate(request):
    try:
        query = GetQuery(request.GET)
        data_input = LoanDataInput.parse_obj(query)
        data_output = CalculateLoan(data_input)

        return JsonResponse(data_output.dict(), status=200)

    except Exception as e:
        logger.error(f"{e}")
        return HttpResponseBadRequest(json.dumps({"error": str(e)}), content_type="application/json")


@require_http_methods(["GET"])
def deposit_calculate(request):
    try:
        query = GetQuery(request.GET)
        data_input = DepositDataInput.parse_obj(query)
        data_output = CalculateDeposit(data_input)

        return JsonResponse(data_output.dict(), status=200)

    except Exception as e:
        logger.error(f"{e}")
        return HttpResponseBadRequest(json.dumps({"error": str(e)}), content_type="application/json")
