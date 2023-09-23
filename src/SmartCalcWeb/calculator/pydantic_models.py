
from pydantic import BaseModel
import json

class PlotData(BaseModel):
    expression: str
    x_from: float
    x_to: float

    def __str__(self):
        return f"expression: {self.expression}, x_from: {self.x_from}, x_to: {self.x_to}"
