from typing import Any
from django.db import models
# from django.utils import timezone
# import datetime
# from django.contrib import admin


class MainExpression(models.Model):
    Expression = models.CharField(max_length=300)
    Answer = models.FloatField(null=True)

    def __str__(self):
        return self.Expression + "; " + self.Answer


class XValueExpression(models.Model):
    Expression = models.CharField(max_length=300)
    Answer = models.FloatField(null=True)

    def __str__(self):
        return self.Expression + "; " + self.Answer
