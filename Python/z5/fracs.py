import fractions

def skroc(frac1):
    skroc = fractions.gcd(frac1[0], frac1[1])
    frac1[0] /= skroc
    frac1[1] /= skroc
    if (frac1[0] > 0 and frac1[1] < 0) or (frac1[0] < 0 and frac1[1] < 0):
        frac1[0] = -frac1[0]
        frac1[1] = -frac1[1]
    return frac1

def unify(frac1, frac2):
    frac1 = skroc(frac1)
    frac2 = skroc(frac2)
    temp = frac1[1]
    frac1[0] *= frac2[1]
    frac1[1] *= frac2[1]
    frac2[0] *= temp
    frac2[1] *= temp
    return frac1, frac2


def add_frac(frac1, frac2):  # frac1 + frac2
    frac1, frac2 = unify(frac1, frac2)
    frac1[0] += frac2[0]
    return skroc(frac1)


def sub_frac(frac1, frac2):  # frac1 - frac2
    frac1, frac2 = unify(frac1, frac2)
    frac1[0] -= frac2[0]
    return skroc(frac1)


def mul_frac(frac1, frac2):  # frac1 * frac2
    frac1[0] *= frac2[0]
    frac1[1] *= frac2[1]
    return skroc(frac1)


def div_frac(frac1, frac2):  # frac1 / frac2
    frac1[0] *= frac2[1]
    frac1[1] *= frac2[0]
    return skroc(frac1)


def is_positive(frac):  # bool, czy dodatni
    frac = skroc(frac)
    if frac[0] < 0:         # robie tak bo transformuje wczesniej do postaci kanonicznej
        return False
    else:
        return True


def is_zero(frac):  # bool, typu [0, x]
    if frac[0] == 0:
        return True
    else:
        return False


def cmp_frac(frac1, frac2):  # -1 | 0 | +1
    frac1, frac2 = unify(frac1, frac2)
    if frac1[0] > frac2[0]:
        return 1
    elif frac1[0] == frac2[0]:
        return 0
    else:
        return -1

def frac2float(frac):  # konwersja do float
    return frac[0]/float(frac[1])


# f1 = [-1, 2]      # -1/2
# f2 = [1, -2]      # -1/2 (niejednoznacznosc)
# f3 = [0, 1]       # zero
# f4 = [0, 2]       # zero (niejednoznacznosc)
# f5 = [3, 1]       # 3
# f6 = [6, 2]       # 3 (niejednoznacznosc)

import unittest


class TestFractions(unittest.TestCase):
    def setUp(self):
        self.zero = [0, 1]

    def test_add_frac(self):
        self.assertEqual(add_frac([1, 2], [1, 3]), [5, 6])
        self.assertEqual(add_frac([-1, 2], [1, 2]), [0, 1])

    def test_sub_frac(self):
        self.assertEqual(sub_frac([1, 2], [1, 3]), [1, 6])
        self.assertEqual(sub_frac([-1, 2], [1, 2]), [-1, 1])

    def test_mul_frac(self):
        self.assertEqual(mul_frac([2, 3], [3, 4]), [1, 2])
        self.assertEqual(mul_frac([-1, 2], [1, 4]), [-1, 8])

    def test_div_frac(self):
        self.assertEqual(div_frac([2, 3], [3, 4]), [8, 9])
        self.assertEqual(div_frac([-3, 2], [1, 4]), [-6, 1])

    def test_is_positive(self):
        self.assertEqual(is_positive([-3, 2]), False)
        self.assertEqual(is_positive([3, 2]), True)
        self.assertEqual(is_positive([-0, 1]), True)
        self.assertEqual(is_positive([0, 1]), True)

    def test_is_zero(self):
        self.assertEqual(is_zero([-3, 2]), False)
        self.assertEqual(is_zero([3, 2]), False)
        self.assertEqual(is_zero([0, 2]), True)
        self.assertEqual(is_zero([0, 1]), True)
        self.assertEqual(is_zero([-0, 1]), True)

    def test_cmp_frac(self):
        self.assertEqual(cmp_frac([1, 3], [1, 4]), 1)
        self.assertEqual(cmp_frac([1, 4], [1, 3]), -1)
        self.assertEqual(cmp_frac([-1, 3], [-1, 4]), -1)
        self.assertEqual(cmp_frac([2, 3], [4, 6]), 0)

    def test_frac2float(self):
        self.assertEqual(frac2float([1, 3]), 1/3.0)
        self.assertEqual(frac2float([-2, 3]), -2/3.0)

    def tearDown(self):
        pass

if __name__ == '__main__':
    unittest.main()     # uruchamia wszystkie testy
