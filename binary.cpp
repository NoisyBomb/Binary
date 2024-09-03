#include <iostream>
#include <algorithm>


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

void DoubleFunction(union Binary number,double num){
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
                cout<<"Yeah"<<endl;
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
}


int main() {
    size_t mode;
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
            DoubleFunction(number, num);
            break;
        }
        default:{
            cout<<"Unknown mistake"<<endl;
        }
    }
    cout<< "Print any key";
    int a;
    cin>>a;
    return 0;
}
