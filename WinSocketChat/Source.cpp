//Main.cpp
#include <iostream>
#include "Socket.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int nChoice;
	int port = 24242; //выбираем порт
	string ipAddress = "127.0.0.1"; //Адрес сервера

	char receiveMessage[MAXSTRLEN];
	char sendMessage[MAXSTRLEN];

	cout << "1) Start server" << endl;
	cout << "2) Connect to server" << endl;
	cout << "3) Exit" << endl;
	cin >> nChoice;
	if (nChoice == 1)
	{
		ServerSocket server;
		cout << "Starting server..." << endl;
		//Запускаем сервер
		server.StartHosting(port);
		while (true)
		{
			cout << "\tWaiting..." << endl;
			//Получаем данные от клиента
			//и сохраняем в переменной receiveMessage
			server.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;
			//// !!!! 
			string Menu = "1. кола(30грн)\n2. картошка фри(40грн)\n3. мороженное(25грн)\n";
			if (strcmp(receiveMessage, "Menu") == 0)
			{
				server.SendDataMessage(Menu.c_str());
			}
			//Отправляем данные клиенту
			cout << "Введите строку для отправки ";
			char buff[100];
			cin.ignore();
			cin.get(buff, 100);

			server.SendDataMessage(buff); // server.SendDataMessage(string str); переделать !!!

			//Если есть сообщение "end", завершаем работу

			if (strcmp(receiveMessage, "end") == 0 ||
				strcmp(sendMessage, "end") == 0)
				break;
		}
	}
	else if (nChoice == 2)
	{
		cout << "IP address = 127.0.0.1 " << endl;
			
		ClientSocket client;
		//подключаемся к серверу
		client.ConnectToServer(ipAddress.c_str(), port);
		while (true)
		{
			//отправляем сообщение
		//Отправляем данные клиенту
			cout << "Введите строку для отправки ";
			char buff[100];
			cin.ignore();
			cin.get(buff,100);
		
			client.SendDataMessage(buff);

			cout << "\tWaiting" << endl;

			//получаем ответ
			client.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;
			if (strcmp(receiveMessage, "end") == 0 ||
				strcmp(sendMessage, "end") == 0)
				break;
		}
		//Закрываем соединение
		client.CloseConnection();
	}
	else if (nChoice == 3)
		return 0;
}










