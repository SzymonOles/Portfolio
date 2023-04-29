import pytest
from rectangle import Rectangle
from points import Point

def test_init():
    with pytest.raises(ValueError):
        Rectangle(2, 2, 1, 1)

def test_str():
    assert str(Rectangle(1, 2, 3, 4))== "[(1, 2), (3, 4)]"

def test_repr():
    assert repr(Rectangle(1, 2, 3, 4))== "Rectangle(1, 2, 3, 4)"

def test_eq():
    assert (Rectangle(1, 2, 3, 4) == Rectangle(1, 2, 3, 4))== True
    assert (Rectangle(1, 2, 3, 5) == Rectangle(1, 2, 3, 4))== False

def test_ne():
    assert (Rectangle(1, 2, 3, 4) != Rectangle(1, 2, 3, 4)) == False
    assert (Rectangle(1, 2, 3, 5) != Rectangle(1, 2, 3, 4)) == True

def test_center():
    assert Rectangle(1, 2, 3, 4).center == Point(2,3)
    assert Rectangle(2, 3, 4, 5).center == Point(3,4)

def test_area():
    assert Rectangle(1, 2, 3, 4).area()== 4
    assert Rectangle(2, 3, 4, 6).area()== 6

def test_move():
    assert Rectangle(1, 2, 3, 4).move(1,1)==Rectangle(2, 3, 4, 5)
    assert Rectangle(2, 3, 4, 5).move(-1,-1)==Rectangle(1, 2, 3, 4)

def test_intersection(): 
    assert Rectangle(1, 1, 4, 4).intersection(Rectangle(2, 2, 5, 5))== Rectangle(2, 2, 4, 4)
    assert Rectangle(2, 2, 5, 5).intersection(Rectangle(1, 1, 4, 4))== Rectangle(2, 2, 4, 4)
    assert Rectangle(1, 1, 4, 4).intersection(Rectangle(2, 2, 3, 3))== Rectangle(2, 2, 3, 3)

def test_cover(): 
    assert Rectangle(1, 1, 4, 4).cover(Rectangle(2, 2, 5, 5))== Rectangle(1, 1, 5, 5)
    assert Rectangle(2, 2, 5, 5).cover(Rectangle(1, 1, 4, 4))== Rectangle(1, 1, 5, 5)
    assert Rectangle(1, 1, 4, 4).cover(Rectangle(2, 2, 3, 3))== Rectangle(1, 1 ,4 ,4)

def test_make4(): 
    assert Rectangle(0, 0, 2, 2).make4()== (Rectangle(0,1,1,2),Rectangle(1,1,2,2),Rectangle(0,0,1,1),Rectangle(1,0,2,1))

def test_frompoints(): 
    assert Rectangle.from_points((Point(1,2),Point(3,4))) == Rectangle(1,2,3,4)

def test_properties(): 
    assert Rectangle(1, 2, 3, 4).left == 1
    assert Rectangle(1, 2, 3, 4).bottom == 2
    assert Rectangle(1, 2, 3, 4).right == 3
    assert Rectangle(1, 2, 3, 4).top == 4
    assert Rectangle(1, 2, 3, 4).topleft == Point(1,4)
    assert Rectangle(1, 2, 3, 4).bottomleft == Point(1,2)
    assert Rectangle(1, 2, 3, 4).topright == Point(3,4)
    assert Rectangle(1, 2, 3, 4).bottomright == Point(3,2)

if __name__ == "__main__":
    pytest.main()