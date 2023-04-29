import pytest
from slist import Node
from slist import SingleList


def test_remove_tail():
    l = SingleList()
    l.insert_head(Node(11))
    l.insert_head(Node(22))
    l.insert_tail(Node(33))
    assert l.remove_tail().data == 33
    assert l.remove_tail().data == 11
    assert l.remove_tail().data == 22
    with pytest.raises(ValueError):
        l.remove_tail()


def test_join():
    l = SingleList()
    l.insert_head(Node(11))
    l.insert_tail(Node(22))
    l.insert_tail(Node(33))
    l2 = SingleList()
    l2.insert_head(Node(44))
    l2.insert_tail(Node(55))
    l2.insert_tail(Node(66))
    l.join(l2)
    assert l.length == 6
    assert l2.length == 0
    assert l2.head is None
    assert l2.tail is None
    assert l.remove_tail().data == 66
    assert l.remove_tail().data == 55
    assert l.remove_tail().data == 44
    assert l.remove_tail().data == 33
    assert l.remove_tail().data == 22
    assert l.remove_tail().data == 11
    with pytest.raises(ValueError):
        l.remove_tail()


def test_clear():
    l = SingleList()
    l.insert_head(Node(11))
    l.insert_head(Node(22))
    l.insert_tail(Node(33))
    l.clear()
    assert l.head is None
    assert l.tail is None
    assert l.length == 0


if __name__ == "__main__":
    pytest.main()
