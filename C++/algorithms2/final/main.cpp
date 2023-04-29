#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
//sudo apt-get install libsfml-dev
#include <SFML/Graphics.hpp>
//wybrac jakis z fc-list
#define FONT "/usr/share/fonts/truetype/ubuntu/Ubuntu-C.ttf"
#define TOWRITE 10
#define WIDTH 800
#define HEIGHT 500

using namespace std;
using namespace sf;

int getid(char s)
{
    if (s == 'a' || s == 'b' || s == 'c')
        return 0;
    if (s == 'd' || s == 'e' || s == 'f')
        return 1;
    if (s == 'g' || s == 'h' || s == 'i')
        return 2;
    if (s == 'j' || s == 'k' || s == 'l')
        return 3;
    if (s == 'm' || s == 'n' || s == 'o')
        return 4;
    if (s == 'p' || s == 'q' || s == 'r' || s == 's')
        return 5;
    if (s == 't' || s == 'u' || s == 'v')
        return 6;
    if (s == 'w' || s == 'x' || s == 'y' || s == 'z')
        return 7;
    return -1;
}

int getids(char s)
{
    switch(s)
    case 'a':
    case 'b':
    case 'c':
        return 0;
    if (s == 'd' || s == 'e' || s == 'f')
        return 1;
    if (s == 'g' || s == 'h' || s == 'i')
        return 2;
    if (s == 'j' || s == 'k' || s == 'l')
        return 3;
    if (s == 'm' || s == 'n' || s == 'o')
        return 4;
    if (s == 'p' || s == 'q' || s == 'r' || s == 's')
        return 5;
    if (s == 't' || s == 'u' || s == 'v')
        return 6;
    if (s == 'w' || s == 'x' || s == 'y' || s == 'z')
        return 7;
    return -1;
}
class LinkedList
{
public:
    struct Node
    {
        string data;
        Node *next;
    };
    int size = 0;
    Node *head = NULL;
    Node *tail = NULL;

    void add(string p)
    {
        Node *temp = new Node();
        if (size == 0)
        {
            head = temp;
        }
        else
        {
            tail->next = temp;
        }
        temp->data = p;
        temp->next = NULL;
        tail = temp;
        size++;
    }
    string print(int x)
    {
        if (size != 0)
        {
            Node *ptr = head;
            for (int j = 0; j < x; j++)
            {
                if (ptr == NULL)
                {
                    return "-";
                }
                ptr = ptr->next;
            }
            if (ptr == NULL)
            {
                return "-";
            }
            return ptr->data;
        }
        else
        {
            return "-";
        }
    }
};

class ModTree
{
public:
    struct Node
    {
        LinkedList data;
        Node *child[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    };
    Node *root = new Node();
    Node *ptr = root;

    void ptrreset()
    {
        ptr = root;
    }

    bool ptrmove(int i)
    {
        if (ptr->child[i - 1] != NULL)
        {
            ptr = ptr->child[i - 1];
            return true;
        }
        else
        {
            return false;
        }
    }

    string ptrprint(int x)
    {
        return ptr->data.print(x);
    }

    void insert(string s)
    {
        Node *ptr = root;
        char chr;
        int chrid;

        for (int i = 0; i < s.length(); i++)
        {
            chr = s.at(i);
            chrid = getid(chr);

            if (ptr->child[chrid] == NULL)
            {
                ptr->child[chrid] = new Node();
            }
            ptr = ptr->child[chrid];
        }
        ptr->data.add(s);
    }
};

int main(int argc, char const *argv[])
{
    ModTree tree;
    string src = "data.txt";
    string word;
    ifstream reader;
    //insert
    reader.open(src);
    if (!reader)
    {
        std::cout << "open error" << endl;
        return 1;
    }
    reader >> word;
    while (!reader.eof())
    {
        tree.insert(word);
        reader >> word;
    }
    reader.close();

    //===============gui==============
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "T9", Style::Close | Style::Titlebar);
    Text text[9];
    RectangleShape button[9];
    Font font;
    Text out[TOWRITE];
    //font
    if (!font.loadFromFile(FONT))
    {
        std::cout << "font loading error" << endl;
    }
    //buttons & text
    text[0].setString("clear");
    text[1].setString("a,b,c");
    text[2].setString("d,e,f");
    text[3].setString("g,h,i");
    text[4].setString("j,k,l");
    text[5].setString("m,n,o");
    text[6].setString("p,q,r,s");
    text[7].setString("t,u,v");
    text[8].setString("w,x,y,z");

    for (int i = 0; i < 9; i++)
    {
        text[i].setFont(font);
        text[i].setFillColor(Color::White);
        button[i].setFillColor(Color(50, 50, 50));
    }
    for (int i = 0; i < TOWRITE; i++)
    {
        out[i].setFont(font);
        out[i].setFillColor(Color::White);
        out[i].setString("-");
    }

    int winY = window.getSize().y / 3;
    int wY = window.getSize().y;

    //event
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
            {
                window.close();
            }
            break;

            case Event::MouseMoved:
            {
                Vector2i mousePos = Mouse::getPosition(window);
                Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                for (int i = 0; i < 9; i++)
                {
                    if (button[i].getGlobalBounds().contains(mousePosF))
                    {
                        button[i].setFillColor(Color(80, 80, 80));
                    }
                    else
                    {
                        button[i].setFillColor(Color(50, 50, 50));
                    }
                }
            }
            break;
            case Event::KeyReleased:
            {
                for (int y = 0; y < 9; y++)
                {
                    button[y].setFillColor(Color(50, 50, 50));
                }
            }
            break;
            case Event::KeyPressed:
            {
                switch (event.key.code)
                {
                case Keyboard::Numpad7:
                {
                    button[0].setFillColor(Color(80, 80, 80));
                    tree.ptrreset();
                    for (int z = 0; z < TOWRITE; z++)
                    {
                        out[z].setString("-");
                    }
                }
                break;

                case Keyboard::Numpad8:
                {
                    button[1].setFillColor(Color(80, 80, 80));
                    if (!tree.ptrmove(1))
                    {
                        out[0].setString("out of words,");
                        out[1].setString("please clear");
                        for (int z = 2; z < TOWRITE; z++)
                        {
                            out[z].setString("-");
                        }
                    }
                    else
                    {
                        for (int z = 0; z < TOWRITE; z++)
                        {
                            out[z].setString(tree.ptrprint(z));
                        }
                    }
                }
                break;

                case Keyboard::Numpad9:
                {
                    button[2].setFillColor(Color(80, 80, 80));
                    if (!tree.ptrmove(2))
                    {
                        out[0].setString("out of words,");
                        out[1].setString("please clear");
                        for (int z = 2; z < TOWRITE; z++)
                        {
                            out[z].setString("-");
                        }
                    }
                    else
                    {
                        for (int z = 0; z < TOWRITE; z++)
                        {
                            out[z].setString(tree.ptrprint(z));
                        }
                    }
                }
                break;

                case Keyboard::Numpad4:
                {
                    button[3].setFillColor(Color(80, 80, 80));
                    if (!tree.ptrmove(3))
                    {
                        out[0].setString("out of words,");
                        out[1].setString("please clear");
                        for (int z = 2; z < TOWRITE; z++)
                        {
                            out[z].setString("-");
                        }
                    }
                    else
                    {
                        for (int z = 0; z < TOWRITE; z++)
                        {
                            out[z].setString(tree.ptrprint(z));
                        }
                    }
                }
                break;

                case Keyboard::Numpad5:
                {
                    button[4].setFillColor(Color(80, 80, 80));
                    if (!tree.ptrmove(4))
                    {
                        out[0].setString("out of words,");
                        out[1].setString("please clear");
                        for (int z = 2; z < TOWRITE; z++)
                        {
                            out[z].setString("-");
                        }
                    }
                    else
                    {
                        for (int z = 0; z < TOWRITE; z++)
                        {
                            out[z].setString(tree.ptrprint(z));
                        }
                    }
                }
                break;

                case Keyboard::Numpad6:
                {
                    button[5].setFillColor(Color(80, 80, 80));
                    if (!tree.ptrmove(5))
                    {
                        out[0].setString("out of words,");
                        out[1].setString("please clear");
                        for (int z = 2; z < TOWRITE; z++)
                        {
                            out[z].setString("-");
                        }
                    }
                    else
                    {
                        for (int z = 0; z < TOWRITE; z++)
                        {
                            out[z].setString(tree.ptrprint(z));
                        }
                    }
                }
                break;

                case Keyboard::Numpad1:
                {
                    button[6].setFillColor(Color(80, 80, 80));
                    if (!tree.ptrmove(6))
                    {
                        out[0].setString("out of words,");
                        out[1].setString("please clear");
                        for (int z = 2; z < TOWRITE; z++)
                        {
                            out[z].setString("-");
                        }
                    }
                    else
                    {
                        for (int z = 0; z < TOWRITE; z++)
                        {
                            out[z].setString(tree.ptrprint(z));
                        }
                    }
                }
                break;

                case Keyboard::Numpad2:
                {
                    button[7].setFillColor(Color(80, 80, 80));
                    if (!tree.ptrmove(7))
                    {
                        out[0].setString("out of words,");
                        out[1].setString("please clear");
                        for (int z = 2; z < TOWRITE; z++)
                        {
                            out[z].setString("-");
                        }
                    }
                    else
                    {
                        for (int z = 0; z < TOWRITE; z++)
                        {
                            out[z].setString(tree.ptrprint(z));
                        }
                    }
                }
                break;

                case Keyboard::Numpad3:
                {
                    button[8].setFillColor(Color(80, 80, 80));
                    if (!tree.ptrmove(8))
                    {
                        out[0].setString("out of words,");
                        out[1].setString("please clear");
                        for (int z = 2; z < TOWRITE; z++)
                        {
                            out[z].setString("-");
                        }
                    }
                    else
                    {
                        for (int z = 0; z < TOWRITE; z++)
                        {
                            out[z].setString(tree.ptrprint(z));
                        }
                    }
                }
                break;

                default:
                    break;
                }
            }
            break;

            case Event::MouseButtonPressed:
            {
                Vector2i mousePos = Mouse::getPosition(window);
                Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                //button actions
                int chr;
                for (int i = 0; i < 9; i++)
                {
                    if (button[i].getGlobalBounds().contains(mousePosF))
                    {
                        chr = i;
                    }
                }
                if (chr == 0)
                {
                    tree.ptrreset();
                    for (int z = 0; z < TOWRITE; z++)
                    {
                        out[z].setString("-");
                    }
                }
                else if (chr == 1 || chr == 2 || chr == 3 || chr == 4 || chr == 5 || chr == 6 || chr == 7 || chr == 8)
                {
                    if (!tree.ptrmove(chr))
                    {
                        out[0].setString("out of words,");
                        out[1].setString("please clear");
                        for (int z = 2; z < TOWRITE; z++)
                        {
                            out[z].setString("-");
                        }
                    }
                    else
                    {
                        for (int z = 0; z < TOWRITE; z++)
                        {
                            out[z].setString(tree.ptrprint(z));
                        }
                    }
                }
            }
            break;
            }
        }

        //drawing
        int iter = 0;

        int textsize = winY / 3;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                text[iter].setCharacterSize(textsize);
                button[iter].setSize(Vector2f(winY, winY));

                text[iter].setOrigin(Vector2f(j * (-winY), i * (-winY) - ((winY - textsize) / 3)));
                button[iter].setOrigin(Vector2f(j * (-winY), i * (-winY)));
                iter++;
            }
        }

        window.clear();

        for (int i = 0; i < 9; i++)
        {
            window.draw(button[i]);
            window.draw(text[i]);
        }
        for (int i = 0; i < TOWRITE; i++)
        {
            out[i].setCharacterSize(wY / (TOWRITE + 1));
            out[i].setOrigin(-(3 * winY), -(i * (wY / (TOWRITE + 1))));
            window.draw(out[i]);
        }

        window.display();
    }

    return 0;
}
