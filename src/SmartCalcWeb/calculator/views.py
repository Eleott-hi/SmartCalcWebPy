import concurrent.futures
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
import json
from django.http import HttpResponseNotAllowed
from SmartCalc import RPN
from math import isnan
from .models import MainExpression
import logging
import toml

CONFIG = toml.load('config.toml')

logger = logging.getLogger(__name__)


def Print(*args):
    print(*args, flush=True)


def index(request):
    logger.info('common/index.html loaded')
    return render(request, "common/index.html", {'CONFIG': CONFIG})


def calculate(request):
    context = {"result": "Invalid Expression"}
    status = 404

    if request.method != "POST":
        return HttpResponseNotAllowed(['POST'])
    try:
        expression = json.loads(request.body)["expression"]
        rpn = RPN()
        result = rpn.calc(expression)
        Print("result", result)
        if (result):
            context["result"] = str(result)
            status = 200
            model = MainExpression()
            model.Expression_text = expression
            model.Answer_text = str(result)
            model.save()

            Print(MainExpression.objects.all())
    except:
        pass

    return HttpResponse(json.dumps(context), status=status, content_type="application/json")


def graph(request):
    data = json.loads(request.body)

    Print(data)

    expression = data["expression"]
    x_from = float(data["x_from"])
    x_to = float(data["x_to"])
    step = float(0.01)
    
    results, values = [], []
    rpn = RPN()

    i = x_from
    while i <= x_to:
        values.append(i)
        answer = 0.0
        try:
            answer = rpn.calc(expression, i)
        except:
            logger.warning("C++ EXEPTION")

        results.append(answer)
        i += step

    # Print("values", values)
    logger.info("/graph send values array")

    return HttpResponse(json.dumps({
        "x": values,
        "y": results,
        "label": expression,
    }), status=200, content_type="application/json")
