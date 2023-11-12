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

        # query = {
        #     "cop_period": "NONE",
        #     "add_period": "YEAR",
        #     "sub_period": "YEAR",
        #     "date_start": "2022-01-01 00:00:00",
        #     "term": 100,
        #     "percent": 100,
        #     "percent_max_without_bill": 100,
        #     "percent_bill": 100,
        #     "sum_in": 100,
        #     "sum_add": 100,
        #     "sum_sub": 100,
        # }
        
        logger.info(type(query["date_start"]))

        data_input = DepositDataInput.parse_obj(query)
        data_output = CalculateDeposit(data_input)

        return JsonResponse(data_output.dict(), status=200)

    except Exception as e:
        logger.error(f"{e}")
        return HttpResponseBadRequest(json.dumps({"error": str(e)}), content_type="application/json")
