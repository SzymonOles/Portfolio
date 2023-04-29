# -*- coding: utf-8 -*-
from cmath import sqrt


class Point:
    """Klasa reprezentująca punkty na płaszczyźnie."""

    def __init__(self, x, y):  # konstuktor
        self.x = x
        self.y = y

    def __str__(self):  # zwraca string "(x, y)"
        return "({}, {})".format(self.x, self.y)

    def __repr__(self):  # zwraca string "Point(x, y)"
        return "Point({}, {})".format(self.x, self.y)

    def __eq__(self, other):  # obsługa point1 == point2
        return self.x == other.x and self.y == other.y

    def __ne__(self, other):  # obsługa point1 != point2
        return not self == other

    # Punkty jako wektory 2D.
    def __add__(self, other):  # v1 + v2
        return Point(self.x + other.x, self.y + other.y)

    def __sub__(self, other):  # v1 - v2
        return Point(self.x - other.x, self.y - other.y)

    def __mul__(self, other):  # v1 * v2, iloczyn skalarny, zwraca liczbę
        return self.x * other.x + self.y * other.y

    def cross(self, other):  # v1 x v2, iloczyn wektorowy 2D, zwraca liczbę
        return self.x * other.y - self.y * other.x

    def length(self):  # długość wektora
        return sqrt(self.x * self.x + self.y * self.y)

    def __hash__(self):
        return hash((self.x, self.y))  # bazujemy na tuple, immutable points


# Kod testujący moduł.

import unittest


class TestPoint(unittest.TestCase):
    def test_str(self):
        self.assertEqual(str(Point(2, 3)), "(2, 3)")
        self.assertEqual(str(Point(3, 4)), "(3, 4)")

    def test_repr(self):
        self.assertEqual(repr(Point(2, 3)), "Point(2, 3)")
        self.assertEqual(repr(Point(3, 4)), "Point(3, 4)")

    def test_eq(self):
        self.assertEqual(Point(2, 3) == Point(2, 3), True)
        self.assertEqual(Point(2, 3) == Point(2, 4), False)

    def test_ne(self):
        self.assertEqual(Point(2, 3) != Point(2, 3), False)
        self.assertEqual(Point(2, 3) != Point(2, 4), True)

    def test_add(self):
        self.assertEqual(Point(2, 3) + Point(2, 3), Point(4, 6))
        self.assertEqual(Point(2, 3) + Point(-2, -3), Point(0, 0))

    def test_sub(self):
        self.assertEqual(Point(2, 3) - Point(2, 3), Point(0, 0))
        self.assertEqual(Point(2, 3) - Point(-2, -3), Point(4, 6))

    def test_mul(self):
        self.assertEqual(Point(1, 2) * Point(3, 4), 11)
        self.assertEqual(Point(3, 4) * Point(5, 6), 39)

    def test_cross(self):
        self.assertEqual(Point(1, 2).cross(Point(3, 4)), -2)
        self.assertEqual(Point(3, 4).cross(Point(5, 6)), -2)

    def test_len(self):
        self.assertEqual(Point(2, 2).length(), sqrt(8))
        self.assertEqual(Point(3, 4).length(), 5)

    def test_hash(self):
        self.assertEqual(hash(Point(1, 2)), hash((1, 2)))

    def tearDown(self):
        pass


if __name__ == "__main__":
    unittest.main()
