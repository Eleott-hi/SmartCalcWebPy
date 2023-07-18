from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
import json
from django.http import HttpResponseNotAllowed
from SmartCalc import RPN
from math import isnan
from .models import MainExpression
import logging

logger = logging.getLogger(__name__)

def Print(*args):
    print(*args, flush=True)


def index(request):
    logger.info('This is an information message')
    logger.warning('This is a warning message')
    logger.error('This is an error message')
    return render(request, "calculator/index.html", {})


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

