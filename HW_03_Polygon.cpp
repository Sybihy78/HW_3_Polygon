#include <iostream>
#include <vector>
#include <cmath>

#define PI 3.14159265


struct Point {
	float x;
	float y;
};


class Polygon {
	std::vector<Point> polygon_;
public:
	Polygon() {};
	Polygon(std::vector<Point> polygon):
		polygon_(polygon)
	{};
	Polygon(const Polygon& obj):
		polygon_(obj.polygon_)
	{};
	Polygon(Polygon&& obj):
		polygon_(std::move(obj.polygon_))
	{
		obj.polygon_.clear();
	};
	~Polygon() {};

	int getSize() const {
		return polygon_.size();
	}
	void printPolygon() const {
		for (int i = 0; i < polygon_.size(); ++i) {
			std::cout << "( " << polygon_[i].x << "; " << polygon_[i].y << " ) \t";
		}
	}
	void addPoint_toEnd(const Point obj) {
		polygon_.push_back(obj);
	}
	void addPoint_toEnd(const float a, const float b) {
		Point user;
		user.x = a;
		user.y = b;
		polygon_.push_back(user);
	}
	void deletePoint_fromCoordinates(const Point obj) {
		for (int i = 0; i < polygon_.size(); ++i) {
			if (polygon_[i].x == obj.x && polygon_[i].y == obj.y) {
				polygon_.erase(polygon_.begin() + i);
			}
		}
	}
	void deletePoint_fromNumber(const int number) {
		polygon_.erase(polygon_.begin() + number);
	}
	void deletePoint_fromEnd() {
		polygon_.pop_back();
	}

	Polygon& operator=(const Polygon& obj) {
		polygon_ = obj.polygon_;
		return *this;
	}

	void movePolygon(const Point obj) {
		for (int i = 0; i < polygon_.size(); ++i) {
			polygon_[i].x += obj.x;
			polygon_[i].y += obj.y;
		}
	}
	
	std::vector<float> getSideLength() const {
		std::vector<float> tmp;
		for (int i = 0; i < polygon_.size() - 1; ++i) {
			tmp.push_back(sqrt(pow((polygon_[i + 1].y - polygon_[i].y), 2)
				+ pow((polygon_[i + 1].x - polygon_[i].x), 2)));
		}
		tmp.push_back(sqrt(pow((polygon_[0].y - polygon_[polygon_.size() - 1].y), 2)
				+ pow((polygon_[0].x - polygon_[polygon_.size() - 1].x), 2)));
		return tmp;
	}
	float getAverageSideLength() const{
		float sum = 0;
		for (int i = 0; i < getSideLength().size(); ++i) {
			sum += getSideLength()[i];
		}
		return sum / getSideLength().size();
	}

	bool emptyPolygon() {
		return polygon_.size() >= 3 ? true : false;
	}
	
	bool equalitySides() const{
		int count = 0;
		for (int i = 0; i < getSideLength().size() - 1; ++i) {
			if (getSideLength()[i] == getSideLength()[i + 1]) {
				++count;
			}
		}
		return (count == getSideLength().size() - 1) ? true : false;
	}

	bool regularPolygon() const{

		float r1 = 0;
		float r2 = 0;
		if (equalitySides() == true) {
			double angle = 360 / polygon_.size();
			r1 = (2 * getSquare()) / (polygon_.size() * getSideLength()[0]);
			r2 = getSideLength()[0] / (2 * tan((angle * PI / 180) / 2));

			return (r1 == r2) ? true : false;
		}
	}

	float getSquare() const {
		float sum1 = 0;
		for (int i = 0; i < polygon_.size() - 1; ++i) {
			sum1 += polygon_[i].x * polygon_[i + 1].y;
		}
		float sum2 = polygon_[polygon_.size() - 1].x * polygon_[0].y;
		float sum3 = 0;
		for (int i = 0; i < polygon_.size() - 1; ++i) {
			sum3 += polygon_[i].y * polygon_[i + 1].x;
		}
		float sum4 = polygon_[0].x * polygon_[polygon_.size() - 1].y;
		float sum = abs(sum1 + sum2 - sum3 - sum4);
		return sum / 2;
	}
	
	bool operator==(const Polygon& obj) {
		if (polygon_.size() == obj.getSize()) {
			for (int i = 0; i < polygon_.size(); ++i) {
				if (polygon_[i].x == obj.polygon_[i].x && polygon_[i].y == obj.polygon_[i].y) {
					return true;
				}
			}
		}
		return false;
	}
	
	bool operator!=(const Polygon& obj) {
		for (int i = 0; i < polygon_.size(); ++i) {
			if (polygon_[i].x != obj.polygon_[i].x || polygon_[i].y != obj.polygon_[i].y) {
				return true;
			}
		}
		return false;
	}
};


std::ostream& operator<<(std::ostream& os, const Polygon& obj)
{
	os << "Count of angles \t" << obj.getSize() << '\n'
		<< "Regular polygon or not \t" << obj.regularPolygon() << '\n'
		<< "Average side length \t" << obj.getAverageSideLength() << '\n'
		<< "Square of polygon \t" << obj.getSquare() << '\n';
	return os;
}


template<typename T>
void printVector(std::vector<T> v) {
	for (int i = 0; i < v.size(); ++i) {
		std::cout << v[i] << ' ';
	}
	std::cout << std::endl;
}


int main() {

	std::cout << "Test of constructors:" << std::endl;
	Polygon p1;
	Point point1 = { 0, 0 };
	p1.addPoint_toEnd(point1);
	p1.addPoint_toEnd(3.0, 3.0);
	p1.addPoint_toEnd(6, 0);
	std::cout << "p1 size \t" << p1.getSize() << std::endl; // 3
	std::vector<Point> vec2 = { point1, {-2, 1}, {-4, -1} };
	Polygon p2(vec2);
	std::cout << "p2 size \t" << p2.getSize() << std::endl; // 3
	
	Polygon p3(p1);
	p3.addPoint_toEnd(3, -3);
	std::cout << "p3 size \t" << p3.getSize() << std::endl; //4
	Polygon p4;
	p4 = p2;
	std::cout << "p4 size \t" << p4.getSize() << std::endl; //4
	
	Polygon p5 = std::move(p4);
	std::cout << "p5 size \t" << p5.getSize() << std::endl; // 3
	std::cout << "p4 size \t" << p4.getSize() << std::endl; // 0
	
	std::cout << "Test of methods:" << std::endl;
	
	std::cout << "p5 getPolygon \t";
	p5.printPolygon(); // { {0, 0}, {-2, 1}, {-4, -1} }
	std::cout << std::endl;
	
	std::cout << "p2 getPolygon \t";
	p2.printPolygon(); // { {0, 0}, {-2, 1}, {-4, -1} }
	std::cout << std::endl;
	p2.deletePoint_fromCoordinates({ -2, 1 });
	std::cout << "p2 getPolygon \t";
	p2.printPolygon(); // { {0, 0}, {-4, -1} }
	std::cout << std::endl;

	p5.deletePoint_fromNumber(1);
	std::cout << "p5 getPolygon \t";
	p5.printPolygon(); //{ {0, 0}, { -4, -1 } }
	std::cout << std::endl;
	std::cout << "p5 size \t" << p5.getSize() << std::endl; // 2
	
	p5.deletePoint_fromEnd();
	std::cout << "p5 getPolygon \t";
	p5.printPolygon(); // { {0, 0} }
	std::cout << std::endl;
	std::cout << "p5 size \t" << p5.getSize() << std::endl; // 1

	p1.movePolygon({ 2, -2 });
	std::cout << "p1 getPolygon \t";
	p1.printPolygon(); // { {2, -2}, { 5, 1 }, {8, -2} }
	std::cout << std::endl;
	std::cout << "p1 size \t" << p1.getSize() << std::endl; // 3

	std::cout << "p1 getSideLength \t";
	printVector(p1.getSideLength()); // равнобедренный треугольник

	std::cout << "p3 getSideLength \t";
	printVector(p3.getSideLength()); // ромб
		
	std::cout << "p1 AverageSideLength \t" << p1.getAverageSideLength() << std::endl;

	std::cout << "p1 empty \t" << p1.emptyPolygon() << std::endl; // 1
	std::cout << "p4 empty \t" << p4.emptyPolygon() << std::endl; // 0

	std::cout << "p1 equality \t" << p1.equalitySides() << std::endl; // 0 
	std::cout << "p3 equality \t" << p3.equalitySides() << std::endl; // 1  равенство всех сторон

	std::cout << "p1 regular \t" << p1.regularPolygon() << std::endl; // 0
	std::cout << "p3 regular \t" << p3.regularPolygon() << std::endl; // 0
	
	std::cout << "p1 square \t" << p1.getSquare() << std::endl;
	std::cout << "p3 square \t" << p3.getSquare() << std::endl;

	std::cout << p1 << std::endl; // вывод информации в консоль
	std::cout << p2 << std::endl;

	std::vector<Point> vec6 = { { 0, 0 },{ 6, 2 },{ 12, 0 },{ 6, -2 } };
	Polygon p6(vec6);
	std::cout << "p6 square \t" << p6.getSquare() << std::endl; // ромб
	std::cout << "p6 getSideLength \t";
	printVector(p6.getSideLength());
	std::cout << "p6 equaleSides \t" << p6.equalitySides() << std::endl;
	std::cout << "p6 regular \t" << p6.regularPolygon() << std::endl;

	std::vector<Point> vec7 = { { 0, 0 },{ 0, 4 },{ 4, 4 },{ 4, 0 } };
	Polygon p7(vec7);
	std::cout << "p7 square \t" << p7.getSquare() << std::endl; // квадрат
	std::cout << "p7 getSideLength \t";
	printVector(p7.getSideLength());
	std::cout << "p7 equaleSides \t" << p7.equalitySides() << std::endl;
	std::cout << "p7 regular \t" << p7.regularPolygon() << std::endl;

	std::vector<Point> vec8 = { { 0, 0 },{ 0, -4 },{ -4, -4 },{ -4, 0 } };
	Polygon p8(vec8);
	std::cout << (p8 == p7) << std::endl; // 1
	std::vector<Point> vec9 = { { 0, 0 },{ 0, -3 },{ -3, -3 },{ -3, 0 } };
	Polygon p9(vec9);
	std::cout << (p9 != p7) << std::endl; // 1

	std::vector<Point> vec10 = { { 0, 0 },{ 0, 4 },{ 4, 4 },{ 4, 0 } };
	Polygon p10(vec10);
	std::cout << (p10 == p7) << std::endl;// 1

	std::vector<Point> vec12 = { { 0, 0 },{ 0, 4 },{ 4, 4 } };
	Polygon p12(vec12);
	std::cout << (p12 == p7) << std::endl; // 0

	std::vector<Point> vec11 = { { 8, 8 },{ 8, 12 },{ 12, 12 },{ 12, 8 } };
	Polygon p11(vec11);
	std::cout << (p11 == p7) << std::endl; // 0
	
	
	system("pause");
	return 0;
};

