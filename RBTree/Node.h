#pragma once
#ifndef NODE_H
#define NODE_H
#include <string>
#include "NodeColor.h"
#include <iostream>
using namespace std;
typedef struct node *link;
struct node { // Red-Black Tree
	int v;
	link izq, der;
	NodeColor nColor;

	node(int v) : v{ v }, izq{ nullptr },
		der{ nullptr }, nColor{ rojo } {}
	node(int v, NodeColor nColor, link izq, link der)
		: v{ v }, izq{ izq }, der{ der },
		nColor{ nColor } {}

	void show(int nivel);

	string scolor() {
		if (this->nColor == rojo)
			return "rojo";
		else
			return "negro";
	}

	bool igual(link h);
};
#endif // !NODE_H

bool node::igual(link h) {
	if (h == nullptr) return false;
	if ((this->v != h->v) || (this->nColor != h->nColor)) return false;
	bool izqOk = ((this->izq == nullptr) ? (h->izq == nullptr) : this->izq->igual(h->izq));
	bool derOk = ((this->der == nullptr) ? (h->der == nullptr) : this->der->igual(h->der));
	return izqOk && derOk;
}

void node::show(int nivel) {
	for (int i = 0; i < 3 * nivel; i++) cout << " ";

	if (this->izq == nullptr && this->der == nullptr) {
		cout << "[" << this->v << " <" << this->scolor() << ">" << "]";
	}
	else {
		cout << "[" << this->v << " <" << this->scolor() << ">" << endl;
		if (this->izq)
			this->izq->show(nivel + 1);
		else {
			for (int i = 0; i < 3 * (nivel + 1); i++) cout << " ";
			cout << "[ ]";
		}
		cout << "\n";
		if (this->der)
			this->der->show(nivel + 1);
		else {
			for (int i = 0; i < 3 * (nivel + 1); i++) cout << " ";
			cout << "[ ]";
		}
		cout << "\n";
		for (int i = 0; i < 3 * nivel; i++) cout << " ";
		cout << "]";
	}
}


ostream& operator <<(ostream& os, link h) {
	h->show(0);
	cout << "\n";
	return os;
}

void rotateR(link &h) {
	link p = h->izq;    // (1)
	h->izq = p->der;    // (2)
	p->der = h;         // (3)
	h = p;              // (4)
}

void rotateL(link &h) {
	link p = h->der;    // (1)
	h->der = p->izq;    // (2)
	p->izq = h;         // (3)
	h = p;              // (4)
}

bool esRojo(link x) {
	if (x == nullptr) return false;
	return x->nColor == rojo;
}

void RBinsertR(link& h, int x, int sw) {
	if (h == nullptr) { h = new node(x); return; }
	if (esRojo(h->izq) && esRojo(h->der)) {
		h->nColor = rojo;
		h->izq->nColor = negro;
		h->der->nColor = negro;
	}
	if (x < h->v) {
		RBinsertR(h->izq, x, 0);
		if (esRojo(h) && esRojo(h->izq) && sw)
			rotateR(h);
		if (esRojo(h->izq) && esRojo(h->izq->izq)) {
			rotateR(h);
			h->nColor = negro;
			h->der->nColor = rojo;
		}
	}
	else {
		RBinsertR(h->der, x, 1);
		if (esRojo(h) && esRojo(h->der) && !sw)
			rotateL(h);
		if (esRojo(h->der) && esRojo(h->der->der)) {
			rotateL(h);
			h->nColor = negro;
			h->izq->nColor = rojo;
		}
	}
}

void RBinsert(link& h, int x) {
	RBinsertR(h, x, 0);
	h->nColor = negro;
}
