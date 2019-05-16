/*
Создать текстовый файл с произвольной информацией. Организовать просмотр содержимого файла.
Организовать чтение и обработку данных из файла.Сохранить результаты в новый текстовый файл.

"Здание" :
	адрес;тип здания;количество этажей;количество квартир;срок эксплуатации;
	срок до капитального ремонта;
	Вывести данные про здания срок эксплуатации, которых больше 50 лет.

*/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.H>



using namespace std;

struct building {
	string adress;
	string typeOfBuilding;
	unsigned short numberOfFloors;
	unsigned short numberOfFlats;
	unsigned short lifetime;
	unsigned short termToOverhaul;
};

//Метод  ввода с проверкой вводимого 
int readInt() {
	unsigned short N;
	while (!(cin >> N) || (cin.peek() != '\n')) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка!Введите число - " << endl;
	}
	return N;
}

//Метод ввода с проверкой ,что вводимое число позитивное 
int readPositiveInt() {
	unsigned short N;
	bool check = false;
	unsigned short temp;
	while (check == false) {
		temp = readInt();
		if (temp & (1U << (sizeof(temp) * 8 - 1))) {
			cout << "Ошибка! Введите положительное число - ";
		}
		else {
			N = temp;
			check = true;
		}
	}
	return N;
}

//Метод заполнения массива структур
void fillArray(building* Array, int N) {
	cin.ignore();
	for (int i = 0; i < N; i++)
	{
		cout << endl << "Адресс - ";
		getline(cin, Array[i].adress);
		cout << "Тип здания - ";
		getline(cin, Array[i].typeOfBuilding);
		cout << "Количество этажей - ";
		Array[i].numberOfFloors = readPositiveInt();
		cout << "Количество квартир - ";
		Array[i].numberOfFlats = readPositiveInt();
		cout << "Срок эксплуатации - ";
		Array[i].lifetime = readPositiveInt();
		cout << "Срок до ремонта - ";
		Array[i].termToOverhaul = readPositiveInt();
		cin.ignore();
		cout << endl;
	}
}

//Функция чтения содержимого из текстового файла
void readFromTextFile(string path) {
	cout << "\t\tСодержимое файла" << endl;
	string line;
	ifstream fin(path); // окрываем файл для чтения
	if (fin.is_open())
		while (getline(fin, line))
			cout << line << endl;
	else
		cout << "Ошибка открытия файла!" << endl;
	fin.close();     // закрываем файл
}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//строка хранит путь к текстовому файлу
	string inputPath = "C:\\Users\\user\\Desktop\\input.txt";
	string outputPath = "C:\\Users\\user\\Desktop\\output.txt";

	//открытие текстового файла с произвольной информацией и вывод на консоль
	readFromTextFile(inputPath);

	//Создание дин. массива структур
	unsigned short N;
	cout << "Введите кол-во зданий - ";
	N = readPositiveInt();
	building* BUILDINGS = new building[N];
	
	//заполнение массива структур
	fillArray(BUILDINGS, N);

	//запись в текстовый файл
	ofstream fout;          // поток для записи
	fout.open(outputPath); // окрываем файл для записи
	fout << "\t\tДома, срок эксплуатации которых превышает 50 лет." << endl << endl; 
	for (size_t i = 0; i < N; i++)
	{
		if (BUILDINGS[i].lifetime > 50) {
			if (fout.is_open())
			{
				fout << "Адресс - " << BUILDINGS[i].adress << endl;
				fout << "Тип здания - " << BUILDINGS[i].typeOfBuilding << endl;
				fout << "Количество этажей - " << BUILDINGS[i].numberOfFloors << endl;
				fout << "Количество квартир - " << BUILDINGS[i].numberOfFlats << endl;
				fout << "Срок эксплуатации - " << BUILDINGS[i].lifetime << " лет."  << endl;
				fout << "Срок до ремонта - " << BUILDINGS[i].termToOverhaul << " лет." << endl;
				fout << endl;
			}
			else
				cout << "Ошибка открытия файла!" << endl;
			
		}
	}
	fout.close();
	
	
}

