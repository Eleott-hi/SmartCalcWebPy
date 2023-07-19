from django.urls import path

from . import views

app_name = "polls"
urlpatterns = [
    path("", views.index, name="index"),
    path("calculate", views.calculate, name="calculate"),
    path("graph", views.graph, name="graph"),
]