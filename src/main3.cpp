#include "../headers/Student.hpp"


int main()
{

    vector<Student> students;
    while(true) {

        unsigned option;
        cout << "\nPasirinkite\n"
            << "0 - baigti programą\n"
            << "1 - atlikti testus naudojant vektorių\n"
            << "2 - atliiti testus naudojant custom vektori'ų\n"

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

                unsigned student_amount = 10000000;
                unsigned scores_amount = 5;
                    
                auto start = std::chrono::high_resolution_clock::now();

                int count = 0;
                    
                vector<Student> students;
                for (unsigned i{}; i < student_amount; i++) {

                    string first_name = "Vardas" + std::to_string(i + 1);
                    string last_name = "Pavarde" + std::to_string(i + 1);

                    Vector<unsigned> temp_scores;
                    for (unsigned i{}; i < scores_amount - 1; i++) {
                        temp_scores.push_back(generate_random_score());
                    }
                    unsigned test_score = generate_random_score();
                    
                    Student student{first_name, last_name, test_score, temp_scores};

                    if (students.size() == students.capacity()) {
                        count++;
                        cout << "atmintis perskirtyta kai vektoriaus dydis: " << students.size() << '\n';
                    }
                    students.push_back(student);
                }

                students.clear();
                auto time = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> diff = time - start;

                cout << endl << "pildant " << student_amount << " dydžio studentų std vektorių atmintis perskirstyta " << count << " kartų\n";

                break;
            }

            case 2: {

                unsigned student_amount = 10000000;
                unsigned scores_amount = 5;
                    
                auto start = std::chrono::high_resolution_clock::now();

                int count = 0;
                    
                Vector<Student> students;
                for (unsigned i{}; i < student_amount; i++) {

                    string first_name = "Vardas" + std::to_string(i + 1);
                    string last_name = "Pavarde" + std::to_string(i + 1);

                    Vector<unsigned> temp_scores;
                    for (unsigned i{}; i < scores_amount - 1; i++) {
                        temp_scores.push_back(generate_random_score());
                    }
                    unsigned test_score = generate_random_score();
                    
                    Student student{first_name, last_name, test_score, temp_scores};

                    if (students.size() == students.capacity()) {
                        count++;
                        cout << "atmintis perskirtyta kai vektoriaus dydis: " << students.size() << '\n';
                    }
                    students.push_back(student);
                }

                students.clear();

                auto time = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> diff = time - start;

                cout << endl << "pildant " << student_amount << " dydžio studentų custom vektorių atmintis perskirstyta " << count << " kartų\n";

                break;
            }

            default:
                break;
        }
    }

    return 0;
}
