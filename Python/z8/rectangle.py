# -*- coding: utf-8 -*-
from points import Point

class Rectangle:
    """Klasa reprezentująca prostokąt na płaszczyźnie."""

    def __init__(self, x1=0, y1=0, x2=1, y2=1):
        if(x1 > x2 or y1 > y2):
            raise ValueError("nieodpowiednie ulozenie punktow")
        self.pt1 = Point(x1, y1)
        self.pt2 = Point(x2, y2)

    @classmethod
    def from_points(cls,PTS):
        return cls(PTS[0].x,PTS[0].y,PTS[1].x,PTS[1].y)

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

    @property
    def center(self):
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
        cent = self.center
        R1 = Rectangle(self.pt1.x,cent.y,cent.x,self.pt2.y)
        R2 = Rectangle(cent.x,cent.y,self.pt2.x,self.pt2.y)
        R3 = Rectangle(self.pt1.x,self.pt1.y,cent.x,cent.y)
        R4 = Rectangle(cent.x,self.pt1.y,self.pt2.x,cent.y)
        return (R1,R2,R3,R4)

    @property
    def top(self):
        return self.pt2.y
    @property
    def bottom(self):
        return self.pt1.y
    @property
    def left(self):
        return self.pt1.x
    @property
    def right(self):
        return self.pt2.x
    @property
    def width(self):
        return self.right() - self.left()
    @property
    def height(self):
        return self.top() - self.bottom()

    @property
    def topleft(self):
        return Point(self.left,self.top)
    @property
    def bottomleft(self):
        return Point(self.left,self.bottom)
    @property
    def topright(self):
        return Point(self.right,self.top)
    @property
    def bottomright(self):
        return Point(self.right,self.bottom)
