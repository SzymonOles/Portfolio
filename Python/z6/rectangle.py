# -*- coding: utf-8 -*-
from points import Point

class Rectangle:
    """Klasa reprezentująca prostokąt na płaszczyźnie."""

    def __init__(self, x1, y1, x2, y2):
        self.pt1 = Point(x1, y1)
        self.pt2 = Point(x2, y2)

    def __str__(self):  # "[(x1, y1), (x2, y2)]"
        return "[({}, {}), ({}, {})]".format(self.pt1.x, self.pt1.y, self.pt2.x, self.pt2.y)

    def __repr__(self):  # "Rectangle(x1, y1, x2, y2)"
        return "Rectangle({}, {}, {}, {})".format(self.pt1.x, self.pt1.y, self.pt2.x, self.pt2.y)

    def __eq__(self, other):  # obsługa rect1 == rect2
        return (
            self.pt1.x == other.pt1.x
            and self.pt2.x == other.pt2.x
            and self.pt1.y == other.pt1.y
            and self.pt2.y == other.pt2.y
        )

    def __ne__(self, other):  # obsługa rect1 != rect2
        return not self == other

    def center(self):  # zwraca środek prostokąta
        return Point((self.pt1.x + self.pt2.x) / 2.0, (self.pt1.y + self.pt2.y) / 2.0)

    def area(self):  # pole powierzchni
        return (abs(self.pt2.x - self.pt1.x) * abs(self.pt2.y - self.pt1.y))

    def move(self, x, y):  # przesunięcie o (x, y)
        return Rectangle(self.pt1.x+x, self.pt1.y+y, self.pt2.x+x, self.pt2.y+y)


import unittest


class TestRectangle(unittest.TestCase):
    def setUp(self):
        self.zero = [0, 1]

    def test_str(self):
        self.assertEqual(str(Rectangle(1, 2, 3, 4)), "[(1, 2), (3, 4)]")

    def test_repr(self):
        self.assertEqual(repr(Rectangle(1, 2, 3, 4)), "Rectangle(1, 2, 3, 4)")

    def test_eq(self):
        self.assertEqual(Rectangle(1, 2, 3, 4) == Rectangle(1, 2, 3, 4), True)
        self.assertEqual(Rectangle(1, 2, 3, 5) == Rectangle(1, 2, 3, 4), False)

    def test_ne(self):
        self.assertEqual(Rectangle(1, 2, 3, 4) != Rectangle(1, 2, 3, 4), False)
        self.assertEqual(Rectangle(1, 2, 3, 5) != Rectangle(1, 2, 3, 4), True)

    def test_center(self):
        self.assertEqual(Rectangle(1, 2, 3, 4).center(), Point(2,3))
        self.assertEqual(Rectangle(2, 3, 4, 5).center(), Point(3,4))

    def test_area(self):
        self.assertEqual(Rectangle(1, 2, 3, 4).area(), 4)
        self.assertEqual(Rectangle(2, 3, 4, 6).area(), 6)

    def test_move(self):
        self.assertEqual(Rectangle(1, 2, 3, 4).move(1,1),Rectangle(2, 3, 4, 5))
        self.assertEqual(Rectangle(2, 3, 4, 5).move(-1,-1),Rectangle(1, 2, 3, 4))


    def tearDown(self):
        pass

if __name__ == "__main__":
    unittest.main()
