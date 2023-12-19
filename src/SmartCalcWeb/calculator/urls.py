from django.urls import path

from . import views

app_name = "polls"
urlpatterns = [
    path("", views.index, name="index"),
    path("config", views.config, name="config"),
    path("calculate", views.calculate, name="calculate"),
    path("graph", views.graph, name="graph"),
    path("loan_calculator", views.loan_calculator, name="loan_calculator"),
    path("deposit_calculator", views.deposit_calculator, name="deposit_calculator"),
]

