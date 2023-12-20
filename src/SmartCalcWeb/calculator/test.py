"""Тесты модели"""

from PybindRPN import RPN


def test_get_error():
    """Test that it can sum a list of integers"""
    strs = ['34-', '99(', 'cos(8+9)cos', '/67', 'df', 'c', 'c(', '78+lna(5)']
    model = RPN()
    for s in strs:
        answer = model.Calculate(s, 0)
        answer_original = 'error in the formula'
        assert answer == answer_original, s


def test_get_right():
    str_f = ['cos(0)', '1 / 10', '1/(-30)', '1 / 0.3', '1/0.03',
             '1/(-11)', 'ln(3)', 'atan(sqrt(78)) - 45/sin(8)',
             'atan(sqrt(78))', '45/sin(8)', '-(2*3)', '-4-3', '(-10*16)',
             '23+(-sin(12) + 66)', '-9-0',
             '- cos(10) + tan(2) - acos(0.5) - asin(0.5) + log(6.9)',
             '2^6 - 4.5mod0.2 ', '2--4+5', '+--+-4--++7', '1.5']
    str_original = ['1', '0.1', '-0.03333333',  '3.33333333', '33.33333333',
                    '-0.09090909', '1.09861229', '-44.02598101', '1.45804881',
                    '45.48402983', '-6', '-7', '-160', '89.53657292', '-9',
                    '-2.07791557', '63.9', '11', '3', '1.5']
    model = RPN()
    for s, answer_original in zip(str_f, str_original):
        answer = model.Calculate(s, 0)
        assert round(float(answer), 7) == round(float(answer_original), 7), s


def test_notition():
    str_f = ['1.e+1', '1.e+2', '2.e-2', '2.3e-2']
    str_original = ['10', '100', '0.02', '0.023']
    model = RPN()
    for s, answer_original in zip(str_f, str_original):
        answer = model.Calculate(s, 0)
        assert answer == answer_original, s
