#include <iostream>
#include <cmath>
#include <fstream>

/* 
Задача 10
Добавить функцию отрисовки траектории в файл формата pnm к задаче моделирования полета шарика в соответвии с вариантом
*/

using namespace std;

const double g = 9.81;

struct Image {
	int mx;
	int my;
	int* points;
};

void CreateImage(Image* img, int tmx, int tmy) {
	img->mx = tmx;
	img->my = tmy;
	img->points = new int[tmx * tmy]{ 1 };
}

void SetPointImage(Image* img, int x, int y, int collor) {
	img->points[(y * img->mx + x)] = collor;
}

int GetPointImage(Image* img, int x, int y) {
	return img->points[(y * img->mx + x)];
}

void ShowImage(Image* img) {
	for (int i = 0; i < img->my; i++) {
		for (int j = 0; j < img->mx; j++) {
			cout << img->points[i * img->mx + j] << " ";
		}
		cout << endl;
	}
}

void SaveToPnmFile(Image* img, string fileName) {
	fstream out;
	out.open(fileName, fstream::out);
	out << "Picture" << endl;
	out << img->mx << " " << img->my << endl;

	for (int i = 0; i < img->my; i++) {
		for (int j = 0; j < img->mx; j++) {
			out << img->points[i * img->mx + j] << " ";
		}
		out << endl;
	}
	out.close();
}

struct Node {
	double h, V, V0, a, t;
	Node* next;
};

void initList(Node* head) {
	head->h = 0;
	head->V = 0;
	head->V0 = 0;
	head->a = 0;
	head->t = 0;
	head->next = NULL;
}

void showList(Node* head, double h, double Vx, double Vy, double a, double t) {
	Node* print = head;
	while (print != 0) {
		cout << "t= " << print->t << ", Vx = " << print->V << ", Vy = " << print->V0 << ", a= " << print->a << ", h= " << print->h << "." << endl;
		print = print->next;
	}
	cout << endl;
}

void pushNode(double h, double a, double V, double V0, double t) {
	Node* nd = new Node();
	while (nd->next != NULL)
		nd = nd->next;
	nd->h = h;
	nd->V = V;
	nd->V0 = V0;
	nd->a = a;
	nd->t = t;

	nd->next = new Node();
	initList(nd->next);
}

Node* simulate(double h, double V, double V0, double dt) {
	Node* out = new Node();

	double V = V0 - g * dt;
	double a = V * V / (dt * dt);
	double max_t, max_h;

	if (V > 0) {
		max_t = V / a;
		max_h = V / (2 * g);

		showList(out, h, V, V0, g, 0);
	}
	else {
		showList(out, h, V, V0, 0, 0);
	}

	double ct = dt;
	while (ct <= max_t)	{
		h += V * ct - a * ct * ct / 2;
		V -= V0 - g * (dt + ct);
		showList(out, h, V, V0, g, ct);
		ct++;
	}

	V = V - g * (ct - max_t);
	V = a * (ct - max_t);
	h = max_h - a * pow(ct - max_t, 2) / 2;
	showList(out, h, V, V0, a, ct);
	while (ct < dt + max_t) {
		h -= V * ct - a * ct * ct / 2;
		V += V0 + g * (dt + ct);
		showList(out, h, V, V0, g, ct);
		ct++;
	}

	showList(out, 0, 0, 0, 0, ct);
	cout << "Stop" << endl;
	return out;
}

void Interpritate(Node* ls, Image* img) {
	const int h_val = 10;
	const double t_val = 0.1;

	Node* cur = ls;
	while (cur->next != NULL) {
		SetPointImage(img, t_val * cur->t, (img->my - 1) - h_val * cur->h, 1);
		cur = cur->next;
	}
	SaveToPnmFile(img, "modelation.pnm");
}

int main() {
	Image* ball = new Image;
	CreateImage(ball, 800, 600);

	Node* list = simulate(100, 10, 2, 0.01);
	Interpritate(list, ball);
}