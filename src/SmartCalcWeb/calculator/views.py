import concurrent.futures
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
import json
from django.http import HttpResponseNotAllowed
from SmartCalc import RPN
from math import isnan
from .models import MainExpression, XValueExpression
import logging
import toml
from numpy import arange
from django.views.decorators.http import require_http_methods

CONFIG = toml.load('config.toml')

logger = logging.getLogger(__name__)
rpn = RPN()


def Print(*args):
    print(*args, flush=True)


def index(request):
    logger.info('common/index.html loaded')
    return render(request, "common/index.html", {'CONFIG': CONFIG})


@require_http_methods(["POST"])
def check_expression(request):
    status = 500
    context = {}

    try:
        expression = json.loads(request.body)["expression"]
        result = RPN.check_expression(str(expression))

        context = {'result': result}
        status = 200
    except:
        pass

    return HttpResponse(json.dumps(context), status=status, content_type="application/json")


@require_http_methods(["POST"])
def calculate(request):
    context = {"result": ""}
    status = 500

    try:
        body: dict = json.loads(request.body)
        x_expression: str = RPN.form_final_expression(body["xValue"])
        main_expression: str = RPN.form_final_expression(body["expression"])

        if RPN.check_expression(x_expression) and RPN.check_expression(main_expression):
            xValue = rpn.calc(x_expression)
            result = rpn.calc(main_expression, xValue)

            MainExpression.objects.create(
                Expression=main_expression, Answer=result)
            XValueExpression.objects.create(
                Expression=x_expression, Answer=xValue)

            context["result"] = str(result)
            status = 200
    except:
        pass

    return HttpResponse(json.dumps(context), status=status, content_type="application/json")


@require_http_methods(["POST"])
def graph(request):
    body = json.loads(request.body)

    Print(body)

    expression = body["expression"]
    x_from = float(body["x_from"])
    x_to = float(body["x_to"])
    step = 0.01

    results, values = [], []
    
    for i in arange(x_from, x_to, step):
        values.append(i)
        answer = 0.0
        try:
            answer = rpn.calc(expression, i)
        except:
            logger.warning("C++ EXEPTION")

        results.append(answer)

    logger.info("/graph send values array")

    data = {
        "x": values,
        "y": results,
        "label": expression,
    }

    return HttpResponse(json.dumps(data), status=200, content_type="application/json")
