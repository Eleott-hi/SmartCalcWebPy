from rest_framework import serializers




# class PlotDataInput:
#     def __init__(self, expression: str, x_from: float, x_to: float):
#         self.expression = expression
#         self.x_from = x_from
#         self.x_to = x_to


# class PlotDataOutput:
#     def __init__(self, label: str, x: list, y: list):
#         self.label = label
#         self.x = x
#         self.y = y


# class PlotDataInputSerializer(serializers.Serializer):
#     expression = serializers.CharField(max_length=256)
#     x_from = serializers.FloatField()
#     x_to = serializers.FloatField()

#     def create(self, validated_data):
#         return PlotDataInput(**validated_data)

#     def update(self, instance, validated_data):
#         instance.expression = validated_data.get(
#             'expression', instance.expression)
#         instance.x_from = validated_data.get('x_from', instance.x_from)
#         instance.x_to = validated_data.get('x_to', instance.x_to)
#         return instance


# class PlotDataOutputSerializer(serializers.Serializer):
#     label = serializers.CharField(max_length=256)
#     x = serializers.ListField(child=serializers.FloatField())
#     y = serializers.ListField(child=serializers.FloatField())

#     def create(self, validated_data):
#         return PlotDataOutput(**validated_data)

#     def update(self, instance, validated_data):
#         instance.label = validated_data.get('label', instance.label)
#         instance.x = validated_data.get('x', instance.x)
#         instance.y = validated_data.get('y', instance.y)
#         return instance
