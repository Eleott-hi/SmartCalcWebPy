from cmath import isnan
from SmartCalc import RPN
from .pydantic_models import PlotData
from numpy import arange

def ExludeNanFromArray(x: list, y: list):
    x_res, y_res = [], []
    for i in range(len(x)):
        if  not isnan(y[i]):
            x_res.append(x[i])
            y_res.append(y[i])
    return x_res, y_res

def CalculatePlotData(plot_data: PlotData):
    x,y = [], []
    rpn = RPN()

    for i in arange(plot_data.x_from, plot_data.x_to, 0.01):
        x.append(i)
        answer = 0.0
        answer = rpn.calc(plot_data.expression, i)
        y.append(answer)
    return x, y
