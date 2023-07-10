from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
import json
from django.http import HttpResponseNotAllowed
from SmartCalc import RPN
from math import isnan

# Create your views here.


def index(request):
    context = {}
    return render(request, "calculator/index.html", context)


def calculate(request):
    context = {"result": "Invalid Expression"}
    status = 404

    if request.method != "POST":
        return HttpResponseNotAllowed(['POST'])

    try:
        expression = json.loads(request.body)["expression"]
        rpn = RPN()
        result = rpn.calc(expression)
        print("result", result)
        if (result):
            context["result"] = str(result)
            status = 200
    except:
        pass

    return HttpResponse(json.dumps(context), status=status, content_type="application/json")
