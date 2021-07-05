#include <iostream>

using namespace std;

/*
Вариант 2

Разработать программу для моделирования полета брошенного с высоты h  со скоростью v шарика массой m. При соударении с землей шарик прилипает к поверхности.
Программа должна иметь функции:
- Вычисления положения (h) и параметров движения шарика (v, a) через заданный промежуток времени
- Позволять записывать параметы движения шарика и метку времении в односвязный списко
- Печатать на экран информацию о траектории движения шарика за заданный промежуток времени
*/

const float g = 9.81;

struct Ball {
    float h;
    float v;
    float m;
    float t;
    float a;
	Ball* next;
};

void init(Ball* a) {
	a->h = 0;
	a->v = 0;
	a->m = 0;
	a->t = 0;
	a->a = -g;
	a->next = NULL;
};

// Напечатать на экран параметры полета шарика
void show(Ball* ball) {
	while (ball->next != NULL) {
		cout << "h= " << ball->h << endl;
		cout << "v= " << ball->v << endl;
		cout << "t= " << ball->t << endl;
		cout << "a= " << ball->a << endl;

		ball = ball->next;
	}
	cout << endl;
};

// Моделирование изменения положения шарика за время dt в секундах
void move(Ball* ball, float dt) {
	float t1, t2, max_h;
	if (ball->v > 0) {
		ball->t = t1 = ball->v / ball->a;
		float dh = ball->v * ball->v / (2 * ball->a);
		max_h = ball->h + dh;
		t2 = sqrt(2 * max_h / ball->a);
		ball->t += t2;
		show(ball);
	}
	else {
		t1 = 0;
		max_h = ball->h;
		t2 = (-abs(ball->v) + sqrt(ball->v * ball->v + 2 * ball->a * ball->h)) / ball->a;
		show(ball);
	}
	float ct = dt;
	while (ct <= t1) {
		ball->h += ball->v * dt - ball->a * dt * dt / 2;
		ball->v -= ball->a * dt;
		show(ball);
		ct += dt;
	}
	ball->v = ball->a * (ct - t1);
	ball->h = max_h - ball->a * (ct - t1) * (ct - t1) / 2;
	show(ball);
	ct += dt;
	while (ct < t1 + t2) {
		ball->h -= ball->v * dt + ball->a * dt * dt / 2;
		ball->v += ball->a * dt;
		show(ball);
		ct += dt;
	}
	show(ball);
	cout << "\nSimulation finished" << endl;
};

int main() {
	float t = 0;
	Ball* a = new Ball;
	init(a);

	float v0 = a->v = 10;
	float m = a->m = 1;
	float h0 = a->h = 100;
	float dt = 0.01;

	move(a, dt);

	return 0;
};