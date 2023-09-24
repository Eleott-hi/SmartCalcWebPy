
from pydantic import BaseModel
import json


class PlotData(BaseModel):
    expression: str
    x_from: float
    x_to: float

    def __str__(self):
        return f"expression: {self.expression}, x_from: {self.x_from}, x_to: {self.x_to}"


class CalculatorData(BaseModel):
    main_expression: str
    x_expression: str

    def __str__(self):
        return f"main_expression: {self.main_expression}, x_expression: {self.x_expression}"

    