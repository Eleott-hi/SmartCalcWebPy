
from pydantic import BaseModel, validator
import json
from PybindLoanCalculator import LoanInfo, LoanResult
from PybindDepositCalculator import DepositInput, DepositOutput, Period
import datetime


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


class DepositDataInput (BaseModel):
    date_start: datetime.datetime
    term: int
    percent: float
    percent_max_without_bill: float
    percent_bill: float
    sum_in: float
    sum_add: float
    sum_sub: float
    cop_period: Period
    add_period: Period
    sub_period: Period

    class Config:
        arbitrary_types_allowed = True

    @validator("cop_period", "add_period", "sub_period", pre=True, always=True)
    def validate_period(cls, value):
        values = {
            "NONE": Period.NONE,
            "DAY": Period.DAY,
            "WEEK": Period.WEEK,
            "MONTH": Period.MONTH,
            "QUARTER": Period.QUARTER,
            "HALF_YEAR": Period.HALF_YEAR,
            "YEAR": Period.YEAR,
        }

        try:
            return values[value]
        except:
            raise ValueError("Invalid Period value: " + value)

    def __str__(self):
        return f"\tsum: {self.amount},\t\nterm: {self.period},\t\nrate: {self.rate},\t\nannuity: {self.paymentsType}"

    def getCPPObject(self):
        deposit_input = DepositInput()

        deposit_input.date_start = self.date_start
        deposit_input.term = self.term
        deposit_input.percent = self.percent
        deposit_input.percent_max_without_bill = self.percent_max_without_bill
        deposit_input.percent_bill = self.percent_bill
        deposit_input.sum_in = self.sum_in
        deposit_input.sum_add = self.sum_add
        deposit_input.sum_sub = self.sum_sub
        deposit_input.cop_period = self.cop_period
        deposit_input.add_period = self.add_period
        deposit_input.sub_period = self.sub_period

        return deposit_input


class DepositDataOutput(BaseModel):
    profite: float
    bills: float
    profit_wb: float
    summary: float

    @classmethod
    def from_cpp_object(cls, cpp_object: DepositOutput):
        return cls(
            profite=cpp_object.profite,
            bills=cpp_object.bills,
            profit_wb=cpp_object.profit_wb,
            summary=cpp_object.summary,
        )

    def __str__(self):
        return f"month: {self.month}, payment: {self.payment}, debth: {self.debth}, percent: {self.percent}, remain: {self.remain}, overpay: {self.overpay}, all_sum: {self.all_sum}"
