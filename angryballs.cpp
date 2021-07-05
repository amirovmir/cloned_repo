#include <iostream>
#include <iomanip>
using namespace std;

/*
Вариант 2
Разработать программу для моделирования полета брошенного с высоты h  со скоростью v шарика массой m.
При соударении с землей шарик прилипает к поверхности.
Программа должна иметь функции:
- Вычисления положения (h) и параметров движения шарика (v, a) через заданный промежуток времени
- Позволять записывать параметы движения шарика и метку времении в односвязный список
- Печатать на экран информацию о траектории движения шарика за заданный промежуток времени
- Тесты
*/

const float g = 9.81;

struct Ball {
	float h;
	float v;
	float a;
	float t;
	Ball* next;
};

void init(Ball* ball) {
	ball->t = 0;
	ball->h = 0;
	ball->v = 0;
	ball->a = 0;
	ball->next = NULL;
};

void pushData(Ball* ls, float h, float v, float a, float t) {
	Ball* p = ls;
	while (p->next != NULL)
		p = p->next;

	p->t = t;
	p->h = h;
	p->v = v;
	p->a = a;
	p->next = new Ball;
	init(p->next);
};

Ball* move(float h, float v, float dt) {
	Ball* output = new Ball;
	init(output);

	double a = g;
	double rise_t, fall_t, max_h;
	if (v > 0) { //движение вверх
		rise_t = v / a;
		float dh = v * v / (2 * a);
		max_h = h + dh;
		fall_t = sqrt(2 * max_h / a);

		pushData(output, h, v, -g, 0);
	}
	else { //движение вниз
		rise_t = 0;
		max_h = h;
		fall_t = (-abs(v) + sqrt(v * v + 2 * a * h)) / a;
		pushData(output, h, v, g, 0);
	}

	double ct = dt; //записываем данные о полете вверх за такт
	while (ct <= rise_t) {
		h += v * dt - a * dt * dt / 2;
		v -= a * dt;
		pushData(output, h, v, -g, ct);
		ct += dt;
	} 
	v = a * (ct - rise_t);
	h = max_h - a * (ct - rise_t) * (ct - rise_t) / 2;
	pushData(output, h, -v, -g, ct);
	ct += dt;
	//записываем данные о полете вниз за такт
	while (ct < rise_t + fall_t) {
		h -= v * dt + a * dt * dt / 2;
		v += a * dt;
		pushData(output, h, -v, -g, ct);
		ct += dt;
	}
	pushData(output, 0, 0, 0, ct);
	cout << "Simulation finished!" << endl;
	return output;
};

void print(Ball* ball, float t) {
	cout << "t =  |  h =  |  v =  | a =" << endl;

	Ball* cur = ball;
	while (cur->next != NULL && cur->t <= t) {
		cout << fixed << showpoint;
		cout << setprecision(2);
		cout << (float)cur->t << "\t" << cur->h << "\t" << cur->v << "\t" << cur->a << endl;
		cur = cur->next;
	}
};

bool testInit() {
	Ball* tmp = new Ball;
	init(tmp);
	tmp->next = new Ball;
	init(tmp->next);
	if (tmp->a == 0 && tmp->next != NULL)
		if (tmp->next->a == 0 && tmp->next->next == NULL)
			return true;
	return false;
};

bool testPushData() {
	Ball* tmp = new Ball;
	init(tmp);

	pushData(tmp, 1.2345, 1, 1, 0.000001);
	pushData(tmp->next, -1, 1000, -1.09876, 1);

	if (tmp->h == 1.2345 && tmp->t == 0.000001)
		if (tmp->next->a == -1.09876 && tmp->next->v == 1000)
			return true;

	return false;
};

bool testMove() {
	Ball* out = move(g, 2*g, 1.0);

	if (out->h - g < 0.001 && out->a == -g && out->v == 2 * g && out->t == 0) {
		out = out->next;
		if (out->h - 2.5 * g < 0.001 && out->a == -g && out->v == g && out->t == 1) {
			out = out->next;
			if (out->h - 3.0 * g < 0.001 && out->a == -g && out->v == 0 && out->t == 2) {
				out = out->next;
				if (out->h - 2.5 * g < 0.001 && out->a == -g && out->v == -g && out->t == 3) {
					out = out->next;
					if (out->h - g < 0.001 && out->a == -g && out->v == -2 * g && out->t == 4) {
						out = out->next;
						if (out->h == 0 && out->a == 0 && out->v == 0 && out->t == 5) {
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

void runTest(bool (*testFunction)(), const string& testName) {
	if (testFunction() == true)
		std::cout << "Test " << testName << " - OK" << std::endl;
	else
		std::cout << "Test " << testName << " - FAIL" << std::endl;
}

int main() {
	runTest(testInit, "testInit");
	runTest(testPushData, "testPushData");
	runTest(testMove, "testMove");
}
