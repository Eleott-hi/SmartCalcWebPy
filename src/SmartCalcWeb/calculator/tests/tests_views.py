from django.test import TestCase
import json
from numpy import arange


class ViewsTests(TestCase):
    def test_index(self):
        for url in ['/', '/plot', '/loan_calculator', '/deposit_calculator', '/settings', '/about']:
            response = self.client.get(url)
            self.assertEqual(response.status_code, 200)

    def test_calculate(self):
        response = self.client.get(
            '/calculate', {'expression': '1 + 2 + x', 'x': '3'})

        self.assertEqual(response.status_code, 200)

        json_response = json.loads(response.content)

        self.assertEqual(float(json_response['result']), 6)

    def test_plot_calculate(self):
        data = {'expression': 'x^2', 'xMin': 0, 'xMax': 0.1}
        response = self.client.get(
            '/plot_calculate', data)

        self.assertEqual(response.status_code, 200)

        json_response = json.loads(response.content)
        x = arange(data['xMin'], data['xMax'], 0.01) 

        self.assertEqual(json_response['label'], data['expression'])
        self.assertEqual(json_response['x'], list(x))
        self.assertEqual(json_response['y'], [i**2 for i in x])
