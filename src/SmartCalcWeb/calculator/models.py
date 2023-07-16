from typing import Any
from django.db import models
# from django.utils import timezone
# import datetime
# from django.contrib import admin

class MainExpression(models.Model):
    Expression_text = models.CharField(max_length=300)
    Answer_text = models.CharField(max_length=300)

    def __str__(self):
        return self.Expression_text + "; " + self.Answer_text


class XValueExpression(models.Model):
    Expression_text = models.CharField(max_length=300)
    Answer_text = models.CharField(max_length=300)

    def __str__(self):
        return self.question_text




