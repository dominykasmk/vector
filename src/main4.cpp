#include "../headers/Student.hpp"


int main()
{

    Vector<Student> students;
    while(true) {

        unsigned option;
        cout << "\nPasirinkite\n"
            << "0 - baigti programą\n"
            << "1 - Sugeneruoti 5 studentų sąrašus automatiškai\n"
            << "  11 - atlikti testus naudojant std vektorių\n"
            << "  12 - atliiti testus naudojant custom vektorių\n"
            << "2 - Įvesti studentus ranka\n"
            << "3 - Spausdinti įvestus studentus\n"

            << endl;

        while (true) {
            cout << "> ";
            cin >> option;

            if (cin && (option == 0 || option == 1 || option == 11 || option == 12 || option == 2 || option == 3)) {
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

                unsigned student_amount = 100;
                unsigned scores_amount = 5;
                string temp_file_name("./student_files/studentai");
                for (int i{}; i < 5; i++) {
                    
                    student_amount *= 10;
                    const string file_name = temp_file_name + std::to_string(student_amount) + ".txt";

                    auto start = std::chrono::high_resolution_clock::now();

                    // creating
                    try {
                        create_student_file(file_name, student_amount, scores_amount);
                    }
                    catch (string e) {
                        std::cerr << "\nKlaida kuriant failą\n";
                    }

                    auto time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = time - start;

                    cout << endl << student_amount << "ies studentų failo kūrimas užtruko: "<< diff.count() << "s\n";
                }
                break;
            }

            case 11: {
                
                unsigned student_amount = 100;
                string temp_file_name("./student_files/studentai");
                for (int i{}; i < 5; i++) {
                    
                    student_amount *= 10;
                    const string file_name = temp_file_name + std::to_string(student_amount) + ".txt";
                    cout << endl << student_amount << " studentų\n";
                    {
                        vector<Student> students_low;

                        try {
                            read_student_file(students_low, file_name);
                        }
                        catch (string e) {
                            cout << "\nKlaida atidarinėjant failą\n" << endl;
                        }

                        auto start = std::chrono::high_resolution_clock::now();
                        std::sort(students_low.begin(), students_low.end(), compare_by_final_score);
                        vector<Student> students_high;

                        auto it = students_low.begin();
                        auto end = students_low.end() - 1;

                        for (; end != it; end--) {
                            if ((*end).get_final_score() < 5)
                                break;

                            students_high.push_back(*end);
                            //students_high.pop_back();
                        }
                        students_low.resize(students_low.size() - students_high.size());

                        auto time = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> diff = time - start;
                        cout << "rūšiavimas naudojant vieną papildomą konteinerį užtruko: "<< diff.count() << "s\n";

                        //write_student_file( students_high, "kietekai.txt" ) ;
                        //write_student_file( students_low, "vargsiukai.txt" ) ;

                        students_low.clear();
                        students_high.clear();
                    }
                }
                break;
            }

            case 12: {
                
                unsigned student_amount = 100;
                string temp_file_name("./student_files/studentai");
                for (int i{}; i < 5; i++) {
                    
                    student_amount *= 10;
                    const string file_name = temp_file_name + std::to_string(student_amount) + ".txt";
                    cout << endl << student_amount << " studentų\n";
                    {
                        Vector<Student> students_low;

                        try {
                            read_student_file(students_low, file_name);
                        }
                        catch (string e) {
                            cout << "\nKlaida atidarinėjant failą\n" << endl;
                        }

                        auto start = std::chrono::high_resolution_clock::now();
                        std::sort(students_low.begin(), students_low.end(), compare_by_final_score);
                        Vector<Student> students_high;

                        auto it = students_low.begin();
                        auto end = students_low.end() - 1;

                        for (; end != it; end--) {
                            if ((*end).get_final_score() < 5)
                                break;

                            students_high.push_back(*end);
                            //students_high.pop_back();
                        }
                        students_low.resize(students_low.size() - students_high.size());

                        auto time = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> diff = time - start;
                        cout << "rūšiavimas naudojant vieną papildomą konteinerį užtruko: "<< diff.count() << "s\n";

                        write_student_file( students_high, "kietekai.txt" ) ;
                        write_student_file( students_low, "vargsiukai.txt" ) ;
                        
                        students_low.clear();
                        students_high.clear();
                    }
                }
                break;
            }


            case 2: {
                
                bool continue_input;
                do {

                    Student student;
                    cin >> student;
                    student.calculate_averages();
                    students.push_back(student);

                    cout << "\nAr norite testi įvestį? (y/n)";
                    string input;
                    while (true) {
                        cin >> input;
                        if (cin && input == "y") {
                            continue_input = true;
                            break;
                        }
                        else if (cin && input == "n") {
                            continue_input = false;
                            break;
                        }
                        else {
                            cout << "\nPasirinkite 'y' jei norite tęsti ir 'n' jei ne";
                            cin.clear();
                            ignore_line();
                        }
                    }
                } while (continue_input);
                break;
            }

            case 3: {
                for (const auto& student : students) {
                    cout << student;
                }
                break;
            }

            default:
                break;
        }
    }

    return 0;
}
