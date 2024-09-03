#include <conio.h>
#include "iostream"
#include <algorithm>
#include <windows.h>       // Изменить программу, полученную на предыдущей работе таким образом, чтобы в окно с координатами (x1,у1,х2,у2) с шагами Т (секунд) и S (строк)
                            // выводилась надпись при всех возможных комбинациях цвета фона и цвета символов. Для каждой комбинации цветов в окне должны выводиться номера
                            // или символьные обозначения цветов фона и символов (варианты приведены в табл. 2.4).

                            // Координаты окна (15, 5, 65, 15)
                            // Обозначение фона: номер
                            // Обозначение символа: русский
                            // Шаг T (секунд): 0.4
                            // Шаг S (строк): 2
                            // Направление: вниз

using namespace std;

union Binary{
    double double_number;
    char bytes[sizeof(double)];
};

void CharFunction (char number) {
    for (int i = sizeof(char) * 8 - 1; i >= 0; i--) {
        cout << ((number >> i) & 1);
    }
    cout<<endl;
}

void SetCursor(int x, int y){
    HANDLE  hOut;
    COORD position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(hOut, position);
}

string DoubleFunction(union Binary number,double num){
    char checkpoint=1;
    string double_string="";
    for (int i = 0; i < sizeof(num); i++) {
        for (size_t j = 0; j < 8; j++) {
            if ((number.bytes[i] & checkpoint) != 0) {
                double_string += '1';
            }
            else double_string += '0';
            checkpoint *= 2;
        }
        checkpoint = 1;
    }
    reverse(double_string.begin(), double_string.end());
    cout<<"Binary of double number is: ";
    cout<<double_string<<endl;
    reverse(double_string.begin(), double_string.end());
    cout<<"Do you need inversion of number (1 - Yeah, 2 - No)"<<endl;
    int mode;
    do{
        cout<<">";
        cin>>mode;
    }
    while((mode != 1) && (mode != 2));
    switch(mode){
        case 1:{
            int size_of_string;
            size_of_string = double_string.length();
            cout << "Actual size is: "<< size_of_string<<endl;
            cout << "Input count of bytes you need to reverse (1 - 64)" << endl;
            int num_bytes_inverted;
            do{
                cout << ">";
                cin >> num_bytes_inverted;
            }
            while ((num_bytes_inverted < 0) || (num_bytes_inverted > 64));
            if (num_bytes_inverted != 0) {
                int *Bytes_Number = new int[num_bytes_inverted];
                int Min_Byte = 0, Max_Byte = 63;
                cout<<"Input positions of byte from "<< Min_Byte<< " to "<< Max_Byte << endl;
                for (int i=0; i<num_bytes_inverted; i++){
                    cout << ">";
                    cin >> Bytes_Number[i];
                    while ((Bytes_Number[i] < Min_Byte) || (Bytes_Number[i] > Max_Byte)){
                        cout << "Invalid number, retry" << endl;
                        cin >> Bytes_Number[i];
                    }
                }
                for (int i = 0; i < 64; i++){
                    for (int j = 0; j < num_bytes_inverted; j++){
                        if (i == Bytes_Number[j]){
                            if (double_string[i] == '1'){
                                double_string[i] = '0';
                            }
                            else if (double_string[i] == '0'){
                                double_string[i] = '1';
                            }
                        }
                    }
                }
                reverse(double_string.begin(), double_string.end());
                cout << "Binary double number with inverted bytes is: "  << double_string << endl;
                int k = 0;
                for (int i = 0; i < 8; i++){
                    number.bytes[i] = 0x0;
                }
                for (int i = 7; i >= 0; i--){
                    for (int j = 0; j < 8; j++){
                        if (double_string[k] == '1'){
                            number.bytes[i] |= 1;
                        }
                        k++;
                        if (j != 7){
                            number.bytes[i] = number.bytes[i] << 1;
                        }
                    }
                }
                cout << "Decimal double number is: "<< number.double_number << endl;
            }
            break;
        }
        case 2:{
            cout<<"Finishing..."<<endl;
            break;
        }
        default:{
            break;
        }
    }
    return double_string;
}



int main() {
    size_t mode;
    short ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    short ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string Actual_Colour_English[16] = {"BLACK","BLUE","GREEN","CYAN","RED","MAGENTA","BROWN","LIGHTGRAY","DARKGRAY","LIGHTBLUE","LIGHTGREEN","LIGHTCYAN","LIGHTRED","LIGHTMAGENTA","YELLOW","WHITE"};
    string Actual_Colour_Russian[16] = {"ЧЁРНЫЙ","ГОЛУБОЙ","ЗЕЛЁНЫЙ","ЦИАНОВЫЙ","КРАСНЫЙ","ПУРПУРНЫЙ","КОРИЧНЕВЫЙ","СВЕТЛО-СЕРЫЙ","ТЁМНО-СЕРЫЙ","СВЕТЛО-ГОЛУБОЙ","СВЕТЛО-ЗЕЛЁНЫЙ","СВЕТЛО-ЦИАНОВЫЙ","СВЕТЛО-КРАСНЫЙ","СВЕТЛО-ПУРПУРНЫЙ","ЖЁЛТЫЙ","БЕЛЫЙ"};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT Window = {0,0,ScreenWidth,ScreenHeight};
    COORD position;
    position.X = 15;
    position.Y = 5;
    bool Counter = FALSE;
    cout<<"Welcome to binary convertor\nChose type of number (1 - char, 2 - double)"<<endl;
    do{
        cout<<">";
        cin>>mode;
    }
    while((mode != 1)&&(mode != 2));
    switch(mode){
        case 1:{
            cout<<"Chosen type is char"<<endl;
            cout<<"Input number according to char type (from -128 to 127)"<<endl;
            char number;
            do {
                cout<<">";
                cin>>number;
            } while ((number > 127) || (number < -128));
            CharFunction(number);
            break;
        }
        case 2:{
            cout<<"Chosen type is double"<<endl;
            cout<<"Input number according to double type"<<endl;
            double num;
            cout<<">";
            cin>>num;
            union Binary number;
            number.double_number=num;
            string double_number_from_function = DoubleFunction(number, num);
            system("cls");
            int numb;
            for (int i = 0; i < 16; i++){
                for (int j = 0; j < 16; j++){
                    numb = i*16+j;
                    int minus_num = 0;
                    if (numb%3==0){
                        minus_num +=2;
                    }
                    if(numb>=4) {
                        SetConsoleWindowInfo(hConsole, TRUE, &Window);
                        SetCursor(position.X, position.Y);
                        SetConsoleTextAttribute(hConsole, i * 16 + j-minus_num);
                        for (int k = 0; k < 65 - position.X; k++) {
                            cout << double_number_from_function[k];
                        }
                        position.Y++;
                        if (position.Y > 15) {
                            Sleep(400);
                            position.Y = 5;
                        }
                        position.X = 15;
                        SetCursor(position.X, position.Y);
                        for (int k = 65 - position.X; k < double_number_from_function.length(); k++) {
                            cout << double_number_from_function[k];
                        }
                        position.Y++;
                        if (position.Y > 15) {
                            Sleep(400);
                            position.Y = 5;
                        }
                        position.X = 15;
                        SetCursor(position.X, position.Y);
                        SetConsoleTextAttribute(hConsole, 0);
                        cout << Actual_Colour_English[0] << "                       " << Actual_Colour_Russian[0];
                        SetConsoleTextAttribute(hConsole, i * 16 + j-minus_num);
                        SetCursor(position.X, position.Y);
                        cout << Actual_Colour_Russian[j - 2] << " " << Actual_Colour_English[i];
                        Counter = TRUE;
                        if (Counter == TRUE) {
                            Counter = FALSE;
                            Sleep(400);
                        }
                        position.X = 15;
                        SetCursor(position.X, position.Y);
                        position.Y += 2;
                        if (position.Y > 15) {
                            position.Y = 5;
                        }
                    }
                    if(numb<4){
                        SetConsoleWindowInfo(hConsole, TRUE, &Window);
                        SetCursor(position.X, position.Y);
                        SetConsoleTextAttribute(hConsole, i * 16 + j);
                        for (int k = 0; k < 65 - position.X; k++) {
                            cout << double_number_from_function[k];
                        }
                        position.Y++;
                        if (position.Y > 15) {
                            Sleep(400);
                            position.Y = 5;
                        }
                        position.X = 15;
                        SetCursor(position.X, position.Y);
                        for (int k = 65 - position.X; k < double_number_from_function.length(); k++) {
                            cout << double_number_from_function[k];
                        }
                        position.Y++;
                        if (position.Y > 15) {
                            Sleep(400);
                            position.Y = 5;
                        }
                        position.X = 15;
                        SetCursor(position.X, position.Y);
                        SetConsoleTextAttribute(hConsole, 0);
                        cout << Actual_Colour_English[0] << "                       " << Actual_Colour_Russian[0];
                        SetConsoleTextAttribute(hConsole, i * 16 + j);
                        SetCursor(position.X, position.Y);
                        cout << Actual_Colour_Russian[j] << " " << Actual_Colour_English[i];
                        Counter = TRUE;
                        if (Counter == TRUE) {
                            Counter = FALSE;
                            Sleep(400);
                        }
                        position.X = 15;
                        SetCursor(position.X, position.Y);
                        position.Y += 2;
                        if (position.Y > 15) {
                            position.Y = 5;
                        }
                    }
                }
            }
            break;
        }
        default:{
            cout<<"Unknown mistake"<<endl;
        }
    }
    getch();
    return 0;
}