import concurrent.futures
from django.http import HttpResponse, HttpResponseRedirect, HttpResponseBadRequest, JsonResponse, HttpResponseNotAllowed
from django.shortcuts import render
import json
import logging
import toml
from django.views.decorators.http import require_http_methods
from .pydantic_models import PlotData
from .services import CalculateData, CaclculatePlotData

CONFIG = toml.load('config.toml')

logger = logging.getLogger(__name__)


def Print(*args):
    print(*args, flush=True)


def index(request):
    html = "common/index.html"
    logger.info(f'{html} loaded')
    return render(request, html, {'CONFIG': CONFIG})


@require_http_methods(["POST"])
def calculate(request):
    try:
        body: dict = json.loads(request.body)
        res = CalculateData(body["expression"], body["xValue"])
        context = {'result': res}

        logger.info(f"Context: {context}, Status: 200")
        return JsonResponse(context, status=200)

    except Exception as e:
        logger.error(f"{e}")
        return HttpResponseBadRequest(json.dumps({"error": str(e)}), content_type="application/json")


@require_http_methods(["POST"])
def graph(request):
    try:
        plot_data = PlotData.parse_raw(request.body)
        x, y = CaclculatePlotData(plot_data)
        context = {
            "x": x,
            "y": y,
            "label": plot_data.expression,
        }
        return JsonResponse(context, status=200)

    except Exception as e:
        logger.error(f"/graph: {e}")
        return HttpResponseBadRequest(json.dumps({"error": str(e)}), content_type="application/json")
