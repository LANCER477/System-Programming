#include "Socket.h"
#include <cstring>

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int nChoice;
    int port = 24242; 
    string ipAddress = "127.0.0.1"; 

    char receiveMessage[MAXSTRLEN];
    char sendMessage[MAXSTRLEN];

    int order[4] = { 0 }; 
    int prices[4] = { 0, 30, 40, 25 }; 

    cout << "Выберите действие:" << endl;
    cout << "1) Запустить сервер" << endl;
    cout << "2) Подключиться к серверу" << endl;
    cout << "3) Выйти" << endl;
    cin >> nChoice;
    cin.ignore(); 

    if (nChoice == 1)
    {
        ServerSocket server;
        cout << "Сервер запущен и подключаем..." << endl;
        server.StartHosting(port);

        while (true)
        {
            cout << "Ожидание..." << endl;
            server.ReceiveData(receiveMessage, MAXSTRLEN);
            cout << "Получено: " << receiveMessage << endl;

            if (strcmp(receiveMessage, "Menu") == 0)
            {
                string menu = "\n--- МЕНЮ ---\n1. Кола (30 грн)\n2. Картошка фри (40 грн)\n3. Мороженое (25 грн)\n4. Чек\n";
                server.SendDataMessage(menu.c_str());
                continue;
            }

            if (strcmp(receiveMessage, "Чек") == 0)
            {
                int total = 0;
                string receipt = "\n--- ВАШ ЗАКАЗ ---\n";
                for (int i = 1; i <= 3; i++)
                {
                    if (order[i] > 0)
                    {
                        receipt += "Позиция " + to_string(i) + ": " + to_string(order[i]) + " шт. | " + to_string(order[i] * prices[i]) + " грн\n";
                        total += order[i] * prices[i];
                    }
                }
                receipt += "ИТОГО: " + to_string(total) + " грн\n";
                server.SendDataMessage(receipt.c_str());
                continue;
            }

            
            string msg(receiveMessage);
            size_t spacePos = msg.find(' ');
            if (spacePos != string::npos)
            {
                string posStr = msg.substr(0, spacePos);
                string qtyStr = msg.substr(spacePos + 1);

                int position = stoi(posStr);
                int quantity = stoi(qtyStr);

                if (position >= 1 && position <= 3 && quantity > 0)
                {
                    order[position] += quantity;
                    string response = "Заказ принят: " + to_string(quantity) + " в количестве " + to_string(position);
                    server.SendDataMessage(response.c_str());
                }
                else
                {
                    server.SendDataMessage("Ошибка формат заказа");
                }
            }
            else
            {
                server.SendDataMessage("Ошибка формат ввода");
            }

            if (strcmp(receiveMessage, "end") == 0)
                break;
        }
    }
    else if (nChoice == 2)
    {
        cout << "Подключение к серверу: " << ipAddress << "..." << endl;
        ClientSocket client;
        client.ConnectToServer(ipAddress.c_str(), port);

        while (true)
        {
            cout << "Введите заказ (номер количество) или 'Чек': ";
            string input;
            getline(cin, input);
            client.SendDataMessage(input.c_str());

            cout << "Ожидание..." << endl;
            client.ReceiveData(receiveMessage, MAXSTRLEN);
            cout << "Ответ сервера: " << receiveMessage << endl;

            if (input == "end" || strcmp(receiveMessage, "end") == 0)
                break;
        }
        client.CloseConnection();
    }
    else if (nChoice == 3)
    {
        cout << "Выход" << endl;
        return 0;
    }
}
