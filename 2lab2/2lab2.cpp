#include <iostream>
#include <windows.h>

using namespace std;

enum choise {
	first = 1, second, third, fourth, fifth
}; // Перечисление вариантов выбранных пунктов меню

const int e = 4; // Выбран выход
const int f = 2; // Для вывода мелкими купюрами
const int CountNam = 6; // Количество вариантов номиналов купюр
const int kratnost = 100; // Кратность купюр в банкомате
const int maxonce = 40000; // Максимально возможная сумма для разовой выдачи
const int MaxTermMin = 20000; // Максимальная сумма для выдачи мелкими купюрами

int intmenu = 0, // Выбранный пункт меню
intmenu2, // Выбор в меню второго уровня
intmenu3; // Выбор в меню 3 уровня

int Naminal[CountNam] = { 100, 200, 500, 1000, 2000, 5000 }; // Номиналы купюр
int CountNote[CountNam] = { 100, 100, 10, 10, 10, 10 }; // Количество купюр каждого номинала, которое есть в банкомате
int CountVivod[CountNam] = { 0,0,0,0,0,0 }; // Количество купюр каждого номинала, которые нужно выдать

int sredstva = 150000, // Баланс пользователя
vivod, // Сумма, которую нужно снять
vvod, // Сумма, которую нужно внести
MaxVTerm = 0, // Количество денег в банкомате
mem; // На случай шутки

void fmenu() { // Функция вывода меню 1 уровня
	cout << "(1) Снять деньги" << endl;
	cout << "(2) Внести деньги" << endl;
	cout << "(3) Запросить информацию о балансе" << endl;
	cout << "(4) Выход" << endl;
}

void smenu() { // Функция вывода меню 2 уровня для снятия средств
	cout << "Максимальная сумма для разовой выдачи " << maxonce << endl;
	cout << "Вы можете снять одну из предложенных сумм или ввести свою" << endl;
	cout << "(1) 100" << endl;
	cout << "(2) 400" << endl;
	cout << "(3) 500" << endl;
	cout << "(4) Ввести свою сумму" << endl;
	cout << "(5) Вернуться в главное меню" << endl;
}

void kmenu() { // Функция вывода меню 3 уровня для снятия средств
	cout << "Вы хотите получить деньги" << endl;
	cout << "(1) мелкими купюрами (преимущественно 500, 200 и 100)" << endl;
	cout << "(2) крупными купюрами (500 и более)" << endl;
	cout << "(3) не имеет значения" << endl;
}

void coutt (int CountVivod[]){ // Функция вывода результата работы программы
	cout << "Результаты работы программы:" << endl; 
	for (int j = CountNam - 1; j >= 0; j--) {
		cout << "Купюр номиналом " << Naminal[j] << ":" << CountVivod[j] << endl;
	}
	cout << endl << "Сейчас вы будете возвращены в главное меню" << endl << endl;
}

bool check(int vivod) {
	if (vivod % 100 != 0) {
		cout << "Сумма, которую вы хотите снять, не кратна 100. Вам будет выдана ближайшая к ней сумма" << endl;
		vivod = (vivod / kratnost) * kratnost;
		cout << "Вам будет выдано " << vivod << endl;
		return true;
	}
	if (sredstva < vivod) { // Проверка возможности снятия
		// Если снятие невозможно - сумма снятия превышает баланс карты или количество средств в банкомате
		cout << endl << "В выводе отказано. Недостаточно средств на карте." << endl; // Вывод сообщения о невозможности снтия средств
		return false;
	}
	else if (MaxVTerm < vivod) {
		cout << "В банкомате недостаточно средств. Адрес ближайшего банкомата - пр. Ленина, 26. Хотите свежую шутку?";
		cout << endl << "(1) Да" << endl << "(2) Нет" << endl;
		cin >> mem;
		if (mem == 1) {
			cout << "Соединение с мемнетом в данный момент отсутствует. Повторите попытку позже." << endl;
		}
		return false;
	}
	else if (vivod > maxonce) { 
		cout << "Слишком большая сумма. Выдача более " << maxonce << " за раз запрещена" << endl;
		return false;
	}
	else return true;
}

int main()
{
	const int lang = 1251; //Код языка
	SetConsoleCP(lang); //Установка языка
	SetConsoleOutputCP(lang); //Для вывода в консоль

	for (int i = 0; i < CountNam; i++) 
	{ // Цикл подсчёта суммы в банкомате
		MaxVTerm += Naminal[i] * CountNote[i];
	}

	cout << "Доброго времени суток! Вас приветствует программа-банкомат." << endl; 
	cout << "Что вы хотите сделать?" << endl; // Запрос выбора пункта меню

	fmenu(); // вызов меню
	cin >> intmenu; // Выбор пункта меню

	while (intmenu != e) {

		switch (intmenu) { // Переход к выбранному пункту меню

		case first: { // Выбрано снятие средств

			smenu(); // Меню второго уровня для снятия средств
			cin >> intmenu2; // Ввод выбранного пункта меню

			switch (intmenu2) // Переход к выбранному пункту меню
			{

			case first: {// Снятие 100 рублей
				vivod = 100;
				intmenu3 = 1;
				break;
			}
			case second: { // Снятие 400 рублей
				vivod = 400;
				intmenu3 = 1;
				break;
			}
			case third: { // Снятие 500 рублей
				vivod = 500;
				intmenu3 = 1;
				break;
			}
			case fourth: { // Снятие другой суммы
				cout << "Введите сумму, которую хотите снять" << endl;
				cin >> vivod; // Ввод суммы, которую нужно снять
				if (check(vivod)) {
					// Если снятие возможно, подбираем необходимые купюры
					if ((vivod<MaxTermMin)&&(vivod >= Naminal[2])) {
						kmenu();
						cin >> intmenu3;
					}
					else {
						intmenu3 = 3;
					}
					}
				}
			}
			switch (intmenu3) {
			case first: {
				for (int i = f; i > -1; i--) { // Проходим по всем нноминалам купюр
					if (vivod / Naminal[i] <= CountNote[i]) { // Если купюр каким-то номиналом целое число,
						CountNote[i] -= vivod / Naminal[i]; // то снимаем это число купюр,уменьшаем их количество в банкомате
						CountVivod[i] = vivod / Naminal[i]; // и увеличиваем в количестве снятых
						vivod -= CountVivod[i] * Naminal[i]; // Уменьшаем сумму снятия
					}
					if ((vivod / Naminal[i] > CountNote[i]) && (CountNote[i] * (vivod / Naminal[i]) != 0)) {
						// Если в банкомате недостаточно купюр нужного номинала, то снимаем все купюры данного номинала
						// и продолжаем искать купюры, чтобы вывести необходимую сумму
						CountVivod[i] = CountNote[i]; // Увеличиваем необходимый счётчик купюр для снятия
						vivod = vivod - Naminal[i] * CountNote[i]; // Уменьшаем сумму, которую осталось снять
						CountNote[i] = 0; // Зануляем счётчик купюр
						vivod -= CountVivod[i] * Naminal[i]; // Уменьшаем сумму снятия
					}
				}
				coutt(CountVivod);
				break;
			}
			case second:  case third: {
				for (int i = CountNam - 1; i >= 0; i--) { // Проходим по всем нноминалам купюр
					if (vivod / Naminal[i] <= CountNote[i]) { // Если купюр каким-то номиналом целое число,
						CountNote[i] -= vivod / Naminal[i]; // то снимаем это число купюр,уменьшаем их количество в банкомате
						CountVivod[i] = vivod / Naminal[i]; // и увеличиваем в количестве снятых
						vivod -= CountVivod[i] * Naminal[i]; // Уменьшаем сумму снятия
					}
					if ((vivod / Naminal[i] > CountNote[i]) && (CountNote[i] * (vivod / Naminal[i]) != 0)) {
						// Если в банкомате недостаточно купюр нужного номинала, то снимаем все купюры данного номинала
						// и продолжаем искать купюры, чтобы вывести необходимую сумму
						CountVivod[i] = CountNote[i]; // Увеличиваем необходимый счётчик купюр для снятия
						vivod = vivod - Naminal[i] * CountNote[i]; // Уменьшаем сумму, которую осталось снять
						CountNote[i] = 0; // Зануляем счётчик купюр
						vivod -= CountVivod[i] * Naminal[i]; // Уменьшаем сумму снятия
					}
				}
				coutt(CountVivod);
				break;
			}
			}
			for (int k = 0; k < CountNam; k++) {
				CountVivod [k] = 0;
			}
			break;
		}
		case second: {
			for (int i = 0; i < CountNam; i++) {
				cout << endl << "Сколько желаете внести купюр номиналом " << Naminal[i] << "?" << endl;
				cin >> vvod;
				sredstva += vvod * Naminal[i];
				CountNote[i] += vvod;
			}
			cout << "Ваш баланс после внесения средств составляет: " << sredstva << endl;
			for (int i = 0; i < CountNam; i++)
			{ // Цикл подсчёта суммы в банкомате
				MaxVTerm += Naminal[i] * CountNote[i];
			}
			cout << endl << "Сейчас вы будете возвращены в главное меню" << endl << endl;
			break; // Выход из конструкции case 
		}
		case third: {
			cout << "Ваш баланс составляет: " << sredstva << endl; // Вывод баланса на экран
			cout << endl << "Сейчас вы будете возвращены в главное меню" << endl << endl;
			break; // Выход из конструкции case
		}
		case fourth: break; // Выход из программы
		default: cout << "Вы выбрали несуществующий пункт меню. Пожалуйста, повторите попытку." << endl;
			// Если пользоатель вводит число, которого нет в списке пунктов меню, просим повторить попытку.
		}
		// Возвращение в меню
		if (intmenu != 4) {
			fmenu(); // вызов меню
			cin >> intmenu; // Выбор пункта меню
		}
	}
}