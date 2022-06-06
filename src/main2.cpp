#include "../headers/Student.hpp"


int main()
{

    Vector<Student> students;
    while(true) {

        unsigned option;
        cout << "\nPasirinkite\n"
            << "0 - baigti programą\n"
            << "1 - Sugeneruoti 5 std vector'is\n"
            << "2 - Sugeneruoti 5 custom vector'ius\n"

            << endl;

        while (true) {
            cout << "> ";
            cin >> option;

            if (cin && (option == 0 || option == 1 || option == 2)) {
                break;         
            }
            else {
                cout << "Pasirinkite ką nors iš meniu\n";
                cin.clear();
                ignore_line();
            }
        } 

        switch (option) {

            case 0:
                return 0;

            case 1: {

                unsigned sz = 1000;
                for (int i{}; i < 5; i++) {
                    
                    sz *= 10;
                    auto start = std::chrono::high_resolution_clock::now();

                    vector<int> v;
                    for (int i{}; i < sz; i++) {
                        v.push_back(sz);
                    }
                    auto time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = time - start;

                    cout << sz << " dydžio std vektorių užpildyti užtruko: "<< diff.count() << "s\n";
                }
                break;
            }

            case 2: {

                unsigned sz = 1000;
                for (int i{}; i < 5; i++) {
                    
                    sz *= 10;
                    auto start = std::chrono::high_resolution_clock::now();

                    Vector<int> v;
                    for (int i{}; i < sz; i++) {
                        v.push_back(sz);
                    }
                    auto time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = time - start;

                    cout << sz << " dydžio custom vektorių užpildyti užtruko: "<< diff.count() << "s\n";
                }
                break;
            }

            default:
                break;
        }
    }

}
