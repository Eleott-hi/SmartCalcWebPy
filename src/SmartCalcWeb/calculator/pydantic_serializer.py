
from pydantic import BaseModel
import json
from PybindLoanCalculator import LoanInfo, LoanResult


class PlotDataInput(BaseModel):
    expression: str
    xMin: float
    xMax: float

    def __str__(self):
        return f"expression: {self.expression}, xMin: {self.xMin}, xMax: {self.xMax}"


class PlotDataOutput(BaseModel):
    label: str
    x: list[float]
    y: list[float | None]

    def __str__(self):
        return f"expression: {self.expression}, xMin: {self.xMin}, xMax: {self.xMax}"


class CalculatorData(BaseModel):
    main_expression: str
    x_expression: str

    def __str__(self):
        return f"main_expression: {self.main_expression}, x_expression: {self.x_expression}"


class LoanDataInput (BaseModel):
    amount: float
    period: int
    rate: float
    paymentsType: str

    def __str__(self):
        return f"sum: {self.amount}, term: {self.period}, rate: {self.rate}, annuity: {self.paymentsType}"

    def getCPPObject(self):
        loan_info = LoanInfo()
        loan_info.amount = self.amount
        loan_info.period = self.period
        loan_info.rate = self.rate
        loan_info.annuity = self.paymentsType == "annuity"
        return loan_info


class LoanDataOutput(BaseModel):
    payment: list[float]
    debth: list[float]
    percent: list[float]
    remain: list[float]
    overpay: float
    all_sum: float

    @classmethod
    def from_cpp_object(cls, cpp_object: LoanResult):
        return cls(
            payment=cpp_object.payment,
            debth=cpp_object.debth,
            percent=cpp_object.percent,
            remain=cpp_object.remain,
            overpay=cpp_object.overpay,
            all_sum=cpp_object.all_sum
        )

    def __str__(self):
        return f"month: {self.month}, payment: {self.payment}, debth: {self.debth}, percent: {self.percent}, remain: {self.remain}, overpay: {self.overpay}, all_sum: {self.all_sum}"
