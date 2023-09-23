import concurrent.futures
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
import json
from django.http import HttpResponseNotAllowed
from SmartCalc import RPN
from .models import MainExpression, XValueExpression
import logging
import toml
from django.views.decorators.http import require_http_methods
from .utils import ExludeNanFromArray, CalculatePlotData
from .pydantic_models import PlotData

CONFIG = toml.load('config.toml')

logger = logging.getLogger(__name__)
rpn = RPN()


def Print(*args):
    print(*args, flush=True)

def CheckExpression(expression):
    result = RPN.check_expression(expression)
    logger.info(f'Static CheckExpression: [expression: \"{expression}\" ,result - {result}]')
    return RPN.check_expression(expression)

def index(request):
    html = "common/index.html"
    logger.info(f'{html} loaded')
    return render(request, html, {'CONFIG': CONFIG})


@require_http_methods(["POST"])
def check_expression(request):
    status = 500
    context = {}

    try:
        expression = json.loads(request.body)["expression"]
        result = CheckExpression(expression)
        context = {'result': result}
        status = 200

    except:
        pass

    logger.info(f"/check_expression: [context: {context}, status: {status}]")
    return HttpResponse(json.dumps(context), status=status, content_type="application/json")


@require_http_methods(["POST"])
def calculate(request):
    context = {"result": ""}
    status = 500

    try:
        body: dict = json.loads(request.body)
        x_expression: str = RPN.form_final_expression(body["xValue"])
        main_expression: str = RPN.form_final_expression(body["expression"])

        logger.info(f"/calculate: [x_expression: \"{x_expression}\", main_expression: \"{main_expression}\"]")

        if CheckExpression(x_expression) and CheckExpression(main_expression):
            xValue = 0.0 if (x_expression == "") else rpn.calc(x_expression)
            result = rpn.calc(main_expression, xValue)

            logger.info(f"/calculate: [xValue: \"{xValue}\", result: \"{result}\"]")

            MainExpression.objects.create(Expression=main_expression, Answer=result)
            XValueExpression.objects.create(Expression=x_expression, Answer=xValue)

            context["result"] = str(result)
            status = 200
    except:
        pass

    logger.info(f"/calculate [context: {context}, status: {status}]")
    return HttpResponse(json.dumps(context), status=status, content_type="application/json")


@require_http_methods(["POST"])
def graph(request):
    try:
        plot_data = PlotData(**json.loads(request.body))
        logger.info(f"/graph: [plot_data: {plot_data}]")

        x,y = CalculatePlotData(plot_data)
        logger.info(f"/graph: [ x, y: calulated]")

        x,y = ExludeNanFromArray(x, y)
        status = 200

    except:
        logger.warning("/graph: [plot_data: {plot_data}]")
        status = 500
        x,y = [], []

    data = {
        "x": x,
        "y": y,
        "label": plot_data.expression,
    }

    logger.info("/graph [send data, status: {status}]")
    return HttpResponse(json.dumps(data), status=status, content_type="application/json")
