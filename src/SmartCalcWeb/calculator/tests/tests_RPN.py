from django.test import TestCase
from calculator.services import Calculate
import math


class RPNTests(TestCase):
    def test_cos(self):
        ans = Calculate('cos(0)')
        self.assertEqual(ans, 1)

    def test_add(self):
        ans = Calculate('1 + 2')
        self.assertEqual(ans, 3)

    def test_x(self):
        ans = Calculate('cos(x)', 0)
        self.assertEqual(ans, 1)

    def test_sin(self):
        ans = Calculate('sin(0)')
        self.assertEqual(ans, 0)

    def test_complex_expression(self):
        ans = Calculate('2 * (3 + 4) / 2')
        self.assertEqual(ans, 7)

    def test_negative_number(self):
        ans = Calculate('-5 + 3')
        self.assertEqual(ans, -2)

    def test_exponential_notation(self):
        ans = Calculate('2e2')
        self.assertEqual(ans, 200)

    def test_invalid_expression(self):
        with self.assertRaises(ValueError):
            Calculate('invalid expression')

    def test_variable_substitution(self):
        ans = Calculate('x + 5', 10)
        self.assertEqual(ans, 15)

    def test_division_by_zero(self):
        ans = Calculate('1 / 0')
        self.assertEqual(ans, float('inf'))

    def test_multiple_operations(self):
        ans = Calculate('2 * 3 + 4 / 2 - 1')
        self.assertEqual(ans, 7)

    def test_exponentiation(self):
        ans = Calculate('2 ^ 3')
        self.assertEqual(ans, 8)

    def test_exponentiation(self):
        ans = Calculate('2 ^ 3 ^ 2')
        self.assertEqual(ans, 512)

    def test_modulus(self):
        ans = Calculate('10 % 3')
        self.assertEqual(ans, 1)

    def test_atan(self):
        ans = Calculate('atan(1)')
        self.assertEqual(ans, math.atan(1))

    def test_sqrt(self):
        ans = Calculate('sqrt(9)')
        self.assertEqual(ans, 3)

    def test_logarithm(self):
        ans = Calculate('log(100)')
        self.assertEqual(ans, 2)
