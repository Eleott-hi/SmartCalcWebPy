import logging
from cmath import isnan
from PybindRPN import RPN
from PybindLoanCalculator import LoanCalculator
from PybindDepositCalculator import DepositCalculator
from .pydantic_serializer import *
from numpy import arange
from .models import MainExpression, XValueExpression
from typing import Tuple


logger = logging.getLogger(__name__)

rpn = RPN()


def CalculateRPN(expression: str, x_value: float = 0) -> float | None:
    y = rpn.Calculate("0" if len(expression) == 0 else expression, x_value)
    return None if isnan(y) else y


def Calculate(expression: str, x_value: float = 0) -> float:
    logger.info(f"Expression: '{expression}', x: {x_value}")
    res = CalculateRPN(expression, x_value)
    logger.info(f"Result: {res}")

    return res


def CaclculatePlotData(plot_data: PlotDataInput) -> PlotDataOutput:
    logger.info(f"Calculating plot data...")

    x = arange(plot_data.xMin, plot_data.xMax, 0.01)
    y = [CalculateRPN(plot_data.expression, i) for i in x]

    logger.info(f"Success!")

    return PlotDataOutput(
        label=plot_data.expression,
        x=list(x),
        y=list(y),
    )


def CalculateData(main_exp: str, x_exp: str) -> str:
    logger.info(f"Main_exp: '{main_exp}', x_exp: '{x_exp}'")

    x = Calculate(x_exp)
    res = Calculate(main_exp, x)

    logger.info(f"Saving to database...")

    XValueExpression.objects.create(Expression=x_exp, Answer=x)
    MainExpression.objects.create(Expression=main_exp, Answer=res)

    logger.info(f"Success!")

    return "nan" if res == None else str(res)


def DeleteHistory():
    logger.info(f"Deleting history...")

    MainExpression.objects.all().delete()
    XValueExpression.objects.all().delete()

    logger.info(f"Success!")


def GetHistory():
    logger.info(f"Getting history...")

    main_expressions = MainExpression.objects.all()
    x_value_expressions = XValueExpression.objects.all()

    history_data = [
        {
            'expression_main': main_expression.expression,
            'expression_x': x_value_expression.expression,
        }
        for main_expression, x_value_expression in zip(main_expressions, x_value_expressions)
    ]

    logger.info(f"Success!")

    return history_data


def CalculateLoan(data_input: LoanDataInput) -> LoanDataOutput:
    logger.info(f"Calculating loan...")

    cpp_data_output = LoanCalculator.Calculate(data_input.getCPPObject())
    python_data_output = LoanDataOutput.from_cpp_object(cpp_data_output)

    logger.info(f"Success!")

    return python_data_output


def CalculateDeposit(data_input: DepositDataInput) -> DepositDataOutput:
    logger.info(f"Calculating deposit...")

    cpp_data_output = DepositCalculator.Calculate(data_input.getCPPObject())
    python_data_output = DepositDataOutput.from_cpp_object(cpp_data_output)

    logger.info(f"Success!")

    return python_data_output
