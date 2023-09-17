from django.urls import path

from . import views

app_name = "polls"
urlpatterns = [
    path("", views.index, name="index"),
    path("calculate", views.calculate, name="calculate"),
    path("check_expression", views.check_expression, name="check_expression"),
    path("graph", views.graph, name="graph"),
]