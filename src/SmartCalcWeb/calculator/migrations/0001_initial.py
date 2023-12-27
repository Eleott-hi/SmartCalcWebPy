# Generated by Django 4.2.2 on 2023-09-25 18:06

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='MainExpression',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('Expression', models.CharField(max_length=300)),
                ('Answer', models.FloatField(null=True)),
            ],
        ),
        migrations.CreateModel(
            name='XValueExpression',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('Expression', models.CharField(max_length=300)),
                ('Answer', models.FloatField(null=True)),
            ],
        ),
    ]
