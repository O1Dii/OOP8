#pragma once
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <string>
using namespace std;

template <typename T>
class Time
{
private:
	int seconds;
	int minutes;
	int hours;
public:
	void Set_time(T, T, T);
	void Output();
	bool Until_noon();
	friend istream& operator>> <>(istream &s, Time<T> &time);
	void operator+=(T);
	Time();
};

template <class T>
struct Status // ��������� ���������
{
	T *RealPtr; // ���������
	int Count; // ������� ����� ������ �� ���������
};

template <class T>
class Point // �����-���������
{
	Status<T> *StatPtr;
public:
	Point(T *ptr = 0); // �����������
	Point(const Point &); // ���������� �����������
	~Point();
	Point &operator=(const Point &); // ���������� �������� =
	T *operator->() const;
	T &operator*() const;
};

template <class T>
Point<T>::Point(T *ptr)
{
	if (!ptr) StatPtr = NULL; // ��������� �� ������ ������
	else
	{
		StatPtr = new Status<T>;
		StatPtr->RealPtr = ptr; // �������������� ������ ����������
		StatPtr->Count = 1; // ������� ��������������� ��������
	}
}

template <class T> // �������� ������������ �����������
Point<T>::Point(const Point &p) :StatPtr(p.StatPtr)
{
	cout << "�������� ����������� �����������" << endl;
	if (StatPtr) StatPtr->Count++; // ������ ���������� ����� ������
}

template <class T>
Point<T>::~Point() // �������� �����������
{
	if (StatPtr)
	{
		StatPtr->Count--; // ����������� ����� ������ �� ������
		if (StatPtr->Count <= 0) // ���� ����� ������ �� ������ ������
		{ // ���� ����� ����, �� ������������
			delete StatPtr->RealPtr; // ������
			delete StatPtr;
		}
	}
}

template <class T>
T *Point<T>::operator->() const
{
	if (StatPtr) return StatPtr->RealPtr;
	else return NULL;
}

template <class T>
T &Point<T>::operator*() const {
	return *StatPtr->RealPtr;
}

template <class T>
Point<T> &Point<T>::operator=(const Point &p)
{ // ������������ �������, �������������� �����
	if (StatPtr) // �� ����� �=� �� ���������
	{
		StatPtr->Count--; // ��������� ������� ��������������� ��������
		if (StatPtr->Count <= 0) // ���� �������� ���, �� ��� ��, ��� � �
		{ // ����������� ����������� ������������
			delete StatPtr->RealPtr; // ���������� ��� ������ ������������ ������
			delete StatPtr;
		}
	}
	StatPtr = p.StatPtr; // ������������� � ������ ���������
	if (StatPtr) StatPtr->Count++; // ����������� ������� ���������������
	return *this; // ��������
}


template<typename T>
void Time<T>::Set_time(T hours, T minutes, T seconds)
{
	if (is_same<T, int>::value || is_same<T, double>::value || is_same<T, float>::value) {
		int odd;
		this->seconds = (int)round(seconds);
		this->minutes = (int)round(minutes);
		this->hours = (int)round(hours);
		odd = abs(this->seconds / 60);
		this->seconds -= odd * 60;
		this->minutes += odd;
		odd = abs(this->minutes / 60);
		this->minutes -= odd * 60;
		this->hours += odd;
		while (this->hours >= 24) {
			this->hours -= 24;
		}
	}
}

template<typename T>
void Time<T>::Output()
{
	cout << this->hours << ":" << this->minutes << ":" << this->seconds << endl;
}

template<typename T>
bool Time<T>::Until_noon()
{
	if (this->hours < 12)
		return true;
	else
		return false;
}

template<typename T>
void Time<T>::operator+=(T seconds)
{
	if (is_same<T, int>::value || is_same<T, double>::value || is_same<T, float>::value) {
		this->seconds += (int)seconds;
		this->Set_time(this->hours, this->minutes, this->seconds);
	}
}

template<typename T>
Time<T>::Time()
{
	this->hours = 0;
	this->minutes = 0;
	this->seconds = 0;
}

template<typename T>
istream& operator>>(istream& s, Time<T>& time)
{
	string a;
	char *str, temp[20];
	int len, count, pos[3], hours = 0, minutes = 0, seconds = 0;
	bool flag;
	do {
		count = 0;
		flag = true;
		getline(s, a);
		len = strlen(a.c_str());
		str = new char[len + 1];
		memcpy_s(str, len, a.c_str(), len);
		str[len] = '\0';
		pos[0] = pos[1] = 0;
		pos[2] = len;
		for (int i = 0; i < len; i++)
			if (str[i] == ':' || str[i] == ' ') {
				count++;
				if (count <= 2) pos[count - 1] = i;
			}
		if (count > 2) {
			cout << "����������� ������� �����, ���������� ��� ���" << endl;
			flag = false;
			continue;
		}
		else if (count == 2) {
			if (pos[0] > 2 || (pos[1] - pos[0]) > 3) {
				cout << "����������� ������� �����, ���������� ��� ���" << endl;
				flag = false;
				continue;
			}
			else {
				for (int i = 0; i < count + 1; i++) {
					if (i == 0) {
						for (int j = 0; j < pos[i]; j++)
							temp[j] = str[j];
						hours = atoi(temp);
						if (hours == 0) {
							cout << "����������� ������� �����, ���������� ��� ���" << endl;
							flag = false;
							break;
						}
					}
					else {
						for (int j = pos[i - 1] + 1; j < pos[i]; j++)
							temp[j - pos[i - 1] - 1] = str[j];
						if (i == 1) {
							minutes = atoi(temp);
							if (minutes == 0) {
								cout << "����������� ������� �����, ���������� ��� ���" << endl;
								flag = false;
								break;
							}
						}
						else if (i == 2) {
							seconds = atoi(temp);
							if (seconds == 0) {
								cout << "����������� ������� �����, ���������� ��� ���" << endl;
								flag = false;
								break;
							}
						}
					}
				}
			}
		}
		else if (count == 1) {
			if (pos[0] > 2) {
				cout << "����������� ������� �����, ���������� ��� ���" << endl;
				flag = false;
				continue;
			}
		}
	} while (flag == false);
	delete[] str;
	time.Set_time(hours, minutes, seconds);
	s.clear();
	s.ignore(s.rdbuf()->in_avail());
	return s;
}
