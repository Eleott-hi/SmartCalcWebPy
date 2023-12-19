import concurrent.futures
from django.http import (HttpResponse,
                         HttpResponseRedirect,
                         HttpResponseBadRequest,
                         JsonResponse,
                         HttpResponseNotAllowed,)
from django.shortcuts import render
from rest_framework.response import Response
import json
import logging
import toml
from rest_framework.decorators import api_view
from django.views.decorators.http import require_http_methods
from .pydantic_serializer import *
from .services import *

CONFIG = toml.load('config.toml')

logger = logging.getLogger(__name__)


def Print(*args):
    print(*args, flush=True)


def GetQuery(query):
    return {k: v[0] for k, v in dict(query).items()}

@require_http_methods(["POST"])
def config(request):
    try:
        data = json.loads(request.body.decode('utf-8'))

        primary_btn_type = data.get('primaryBtnType')
        secondary_btn_type = data.get('secondaryBtnType')
        is_dark_mode = data.get('isDarkMode')
    

        return JsonResponse({
            'primaryBtnType': primary_btn_type,
            'secondaryBtnType': secondary_btn_type,
            'isDarkMode': is_dark_mode
        }, status=200)


    except Exception as e:
        logger.error(f"{e}")
        return HttpResponseBadRequest(json.dumps({"error": str(e)}), content_type="application/json")

def index(request):
    html = "common/index.html"
    logger.info(f'{html} loaded')
    return render(request, html, {'CONFIG': CONFIG})


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
def graph(request):
    try:
        query = GetQuery(request.GET)
        data_input = PlotDataInput.parse_obj(query)
        data_output = CaclculatePlotData(data_input)

        return JsonResponse(data_output.dict(), status=200)

    except Exception as e:
        logger.error(f"{e}")
        return HttpResponseBadRequest(json.dumps({"error": str(e)}), content_type="application/json")


@require_http_methods(["GET"])
def loan_calculator(request):
    try:
        query = GetQuery(request.GET)
        data_input = LoanDataInput.parse_obj(query)
        data_output = CalculateLoan(data_input)

        return JsonResponse(data_output.dict(), status=200)

    except Exception as e:
        logger.error(f"{e}")
        return HttpResponseBadRequest(json.dumps({"error": str(e)}), content_type="application/json")

import datetime
@require_http_methods(["GET"])
def deposit_calculator(request):
    try:
        query = GetQuery(request.GET)
        data_input = DepositDataInput.parse_obj(query)
        data_output = CalculateDeposit(data_input)

        return JsonResponse(data_output.dict(), status=200)

    except Exception as e:
        logger.error(f"{e}")
        return HttpResponseBadRequest(json.dumps({"error": str(e)}), content_type="application/json")
