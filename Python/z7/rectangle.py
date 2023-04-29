# -*- coding: utf-8 -*-
from points import Point

class Rectangle:
    """Klasa reprezentująca prostokąt na płaszczyźnie."""

    def __init__(self, x1, y1, x2, y2):
        if(x1 > x2 or y1 > y2):
            raise ValueError("nieodpowiednie ulozenie punktow")
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

    def intersection(self, other):  # część wspólna prostokątów
        pt1x = max(self.pt1.x,other.pt1.x)
        pt1y = max(self.pt1.y,other.pt1.y)
        pt2x = min(self.pt2.x,other.pt2.x)
        pt2y = min(self.pt2.y,other.pt2.y)
        return Rectangle(pt1x,pt1y,pt2x,pt2y)

    def cover(self, other):     # prostąkąt nakrywający oba
        pt1x = min(self.pt1.x,other.pt1.x)
        pt1y = min(self.pt1.y,other.pt1.y)
        pt2x = max(self.pt2.x,other.pt2.x)
        pt2y = max(self.pt2.y,other.pt2.y)
        return Rectangle(pt1x,pt1y,pt2x,pt2y)

    def make4(self):            # zwraca krotkę czterech mniejszych
        cent = self.center()
        R1 = Rectangle(self.pt1.x,cent.y,cent.x,self.pt2.y)
        R2 = Rectangle(cent.x,cent.y,self.pt2.x,self.pt2.y)
        R3 = Rectangle(self.pt1.x,self.pt1.y,cent.x,cent.y)
        R4 = Rectangle(cent.x,self.pt1.y,self.pt2.x,cent.y)
        return (R1,R2,R3,R4)
# A-------B   po podziale  A---+---B
# |       |                |   |   |
# |       |                +---+---+
# |       |                |   |   |
# D-------C                D---+---C    


# Kod testujący moduł.

import unittest

class TestRectangle(unittest.TestCase):
    def setUp(self):
        self.zero = [0, 1]

    def test_init(self):
        with self.assertRaises(ValueError):
            Rectangle(2, 2, 1, 1)

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

    def test_intersection(self): 
        self.assertEqual(Rectangle(1, 1, 4, 4).intersection(Rectangle(2, 2, 5, 5)), Rectangle(2, 2, 4, 4))
        self.assertEqual(Rectangle(2, 2, 5, 5).intersection(Rectangle(1, 1, 4, 4)), Rectangle(2, 2, 4, 4))
        self.assertEqual(Rectangle(1, 1, 4, 4).intersection(Rectangle(2, 2, 3, 3)), Rectangle(2, 2, 3, 3))
        with self.assertRaises(ValueError):
            Rectangle(1, 1, 4, 4).intersection(Rectangle(3, 3, 2, 2))

    def test_cover(self): 
        self.assertEqual(Rectangle(1, 1, 4, 4).cover(Rectangle(2, 2, 5, 5)), Rectangle(1, 1, 5, 5))
        self.assertEqual(Rectangle(2, 2, 5, 5).cover(Rectangle(1, 1, 4, 4)), Rectangle(1, 1, 5, 5))
        self.assertEqual(Rectangle(1, 1, 4, 4).cover(Rectangle(2, 2, 3, 3)), Rectangle(1, 1 ,4 ,4))

    def test_make4(self): 
        self.assertEqual(Rectangle(0, 0, 2, 2).make4(), (Rectangle(0,1,1,2),Rectangle(1,1,2,2),Rectangle(0,0,1,1),Rectangle(1,0,2,1)))

    def tearDown(self):
        pass

if __name__ == "__main__":
    unittest.main()



