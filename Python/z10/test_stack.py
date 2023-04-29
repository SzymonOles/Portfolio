import pytest
from stack import Stack


def test_empty():
    s = Stack()
    assert s.is_empty() == True
    s.push(1)
    assert s.is_empty() == False

def test_full():
    s = Stack()
    for i in range(9):
        s.push(i)
    assert s.is_full() == False
    s.push(1)
    assert s.is_full() == True

def test_push():
    s = Stack()
    for i in range(9):
        s.push(i)
    assert s.items[8] == 8
    s.push(9)
    assert s.items[9] == 9

    with pytest.raises(ValueError):
        s.push(1) 

def test_pop():
    s = Stack()
    for i in range(10):
        s.push(i)
    assert s.pop() == 9
    assert s.pop() == 8
    for i in range(8):
        s.pop()
    with pytest.raises(ValueError):
        s.pop() 

if __name__ == "__main__":
    pytest.main()