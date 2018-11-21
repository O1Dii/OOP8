#include "Time.h"
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Point<Time<int>> t0 = new Time<int>;
	Point<Time<int>> t = t0;
	Point<Time<double>> t1 = new Time<double>;
	Point<Time<double>> t2;

	t->Set_time(18, 2, 4);
	cin >> *t1;

	t2 = t1;

	t0->Output();
	t->Output();
	t1->Output();
	t2->Output();

	if (t1->Until_noon() == true)
		cout << "Полдень ещё не наступил" << endl;
	else
		cout << "Полдень уже наступил" << endl;

	system("Pause");
}