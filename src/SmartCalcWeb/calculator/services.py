from .pydantic_models import PlotData
import logging
from cmath import isnan
from PybindRPN import RPN
from PybindLoanCalculator import LoanCalculator, LoanInfo, LoanResult
from .pydantic_models import PlotData
from numpy import arange
from .models import MainExpression, XValueExpression
from typing import Tuple

logger = logging.getLogger(__name__)

rpn = RPN()


def ExludeNanFromArray(x_src: list, y_src: list):
    logger.info(f"Exclude nan from x and y")
    x, y = zip(*[(x_val, y_val)
               for x_val, y_val in zip(x_src, y_src) if not isnan(y_val)])
    return list(x), list(y)


def CaclculatePlotData(plot_data: PlotData) -> Tuple[list, list]:
    logger.info(f"Calculating...")

    x = arange(plot_data.x_from, plot_data.x_to, 0.01)
    y = [rpn.Calculate(plot_data.expression, i) for i in x]
    x, y = ExludeNanFromArray(x, y)

    return x, y


def Calculate(expression: str, x_value: float = 0) -> float:
    logger.info(f"Expression: '{expression}', x: '{x_value}'")

    if len(expression) == 0:
        expression = "0"

    res = rpn.Calculate(expression, x_value)

    logger.info(f"Result: {res}")

    return res #TODO: return float(nan)


def CalculateData(main_exp: str, x_exp: str) -> float:
    logger.info(f"Main_exp: '{main_exp}', x_exp: '{x_exp}'")

    x = Calculate(x_exp)
    res = Calculate(main_exp, x)

    logger.info(f"Saving to database...")

    XValueExpression.objects.create(Expression=x_exp, Answer=x)
    MainExpression.objects.create(Expression=main_exp, Answer=res)

    logger.info(f"Success!")

    return res


def CalculateLoan():
    loan_info = LoanInfo()
    loan_info.sum = 100000
    loan_info.term = 3
    loan_info.rate = 3

    res = LoanCalculator.Calculate(loan_info)

    logger.info(f"LOAN RES: {res.overpay}, {res.all_sum}")
    logger.info(f"LOAN vec: {res.payment}")
    pass