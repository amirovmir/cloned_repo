#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
������� 11
������������� ������� ��� ������ � ������������ � �����.
1. �������� �����������
void createImage(Image* img, int tmx, int tmy)
2. ����������� ����������� �� ����� � pnm �������
void showImage(Image* img)
3. ���������� ����� �� �����������
void setPointImage(Image* img, int x, int y, int color);
4. ��������� ����� �� �����������
int getPointImage(Image* img, int x, int y);
5. ��������� ����������� � pnm �������
void saveToPnmFile(Image* img, string fileName);
*/

class Image {
private:
	int mx;
	int my;
	int* pixels;

public:
	Image()	{
		mx = 0;
		my = 0;
	}

	Image(int tmx, int tmy)	{
		mx = tmx;
		my = tmy;
		pixels = new int[tmx * tmy]{ 1 };
	}

	void setPointImage(int x, int y, int color) {
		pixels[(y * mx + x)] = color;
	}

	int getPointImage(int x, int y) {
		return pixels[y * mx + x];
	}

	void showImage() {
		for (int i = 0; i < my; i++) {
			for (int j = 0; j < mx; j++)
				cout << pixels[i * mx + j] << " ";

			cout << endl;
		}
	}

	void saveImage(const string filename) {
		fstream out;
		out.open(filename, fstream::out);
		out << "P1" << endl;
		out << mx << " " << my << endl;

		for (int i = 0; i < my; i++) {
			for (int j = 0; j < mx; j++)
				out << pixels[i * mx + j] << " ";

			out << endl;
		}

		out.close();
	}
};


int main()
{
	Image img(3, 3);
	img.setPointImage(0, 1, 0);
	img.setPointImage(1, 1, 1);
	img.setPointImage(1, 2, 3);
	img.showImage();
	img.saveImage("test_image.pnm");
}