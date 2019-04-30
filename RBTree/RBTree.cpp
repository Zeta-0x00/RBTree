#include <iostream>
#include "Node.h"
#include"Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
using namespace std;
int main()
{
	cout << "Prueba de el arbol rojo negro" << endl << endl;
	link p = nullptr;
	RBinsert(p, 6);
	RBinsert(p, 10);
	RBinsert(p, 18);
	RBinsert(p, 25);
	RBinsert(p, 30);
	RBinsert(p, 35);
	cout << p;
	Simple_window win(Point(122, 200), 400, 500, "Red Black Tree");
	win.wait_for_button();



	return 0;
}