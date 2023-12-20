from django.urls import path

from . import views

app_name = "polls"
urlpatterns = [
    path("", views.index, name="index"),
    path("plot", views.index, name="index"),
    path("loan_calculator", views.index, name="index"),
    path("deposit_calculator", views.index, name="index"),
    path("settings", views.index, name="index"),
    path("about", views.index, name="index"),
    
    path("config", views.config, name="config"),
    path("history", views.history, name="history"),
    path("calculate", views.calculate, name="calculate"),
    path("plot_calculate", views.plot_calculate, name="plot_calculate"),
    path("loan_calculate", views.loan_calculate, name="loan_calculate"),
    path("deposit_calculate", views.deposit_calculate, name="deposit_calculate"),
]

