from graph import *
import pytest

g = importGraphFile("test.txt")

def test_initial():
    assert g.v() == 6
    assert g.e() == 6

def test_BFS():
    assert g.BFS("a") == ['a', 'b', 'c', 'd', 'e', 'f']

def test_DFS():
    assert g.DFS("a") == ['a', 'd', 'f', 'c', 'e', 'b']

def test_modedge():
    assert g.add_edge(("c","d")) == 1
    assert g.e() == 7
    assert g.del_edge(("c","d")) == 1
    assert g.e() == 6

def test_addnode():
    with pytest.raises(OverflowError):
        g.add_node("g")

def test_delnode():
    assert g.del_node("a") == 1
    assert g.v() == 5

if __name__ == "__main__":
    pytest.main()