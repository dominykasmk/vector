#include "../headers/Student.hpp"

Student::Student(std::string& data)
{
    istringstream iss(data);
    
    iss >> last_name;
    iss >> first_name;

    double score;
    while (iss >> score) {
        scores.push_back(score);
    }

    final_score_avg = scores.back();
    scores.pop_back();
    has_final_score = true;

    test_score = scores.back();
    scores.pop_back();
}

Student::Student(std::string first_name, std::string last_name, unsigned test_score, Vector<unsigned> scores)
    : first_name { first_name }, last_name { last_name }, test_score { test_score }, scores { scores }
{
    calculate_averages();
}

void Student::print_student() const
{
        std::cout << std::setw(15) << std::left << last_name;
        std::cout << std::setw(15) << std::left << first_name;
        std::cout << std::setprecision(2) << final_score_avg << std::endl << std::endl;
        printf("%15s%15s%15.2lf", last_name.c_str(), first_name.c_str(), final_score_avg);
}

unsigned Student::get_score_amount() const
{
    return scores.size();
}

std::string Student::get_first_name() const
{
    return first_name;
}

std::string Student::get_last_name() const
{
    return last_name;
}

double Student::get_final_score() const
{
    return final_score_avg;
}

unsigned Student::get_test_score() const {
    return test_score;
}

const Vector<unsigned>& Student::get_scores() const
{
    return scores;
}

bool Student::get_has_final_score() const {
    return has_final_score;
}


std::ostream& operator<< (std::ostream& out, const Student& student)
{
    out << std::setw(15) << std::left << student.first_name
        << std::setw(15) << std::left << student.last_name;
    
    for (const auto& score: student.scores) {
        out << std::setw(15) << std::left << score;
    }
    out << std::setw(15) << std::left << student.test_score;
    if (student.has_final_score)
        out << std::setw(15) << std::left << student.final_score_avg;
    out << '\n';

    return out;
}

std::istream& operator>> (std::istream& in, Student& student)
{
    //std::string line;
    //getline(in, line);
    //std::istringstream ss( line );

    in >> student.first_name >> student.last_name;

    unsigned score;
    while ( in >> score ) {
        student.scores.push_back( score );
    }
    student.test_score = student.scores.back();
    student.scores.pop_back();

    return in;
}

void ignore_line()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void input_valid_string(std::string &input, const string prompt)
{
    cout << prompt;
    while (true) {

        cout << "> ";
        cin >> input;

        if (!cin) {
            cout << prompt << endl;
            cin.clear();
            ignore_line();
        }
        else {
            ignore_line();
            break; 
        }
    }
}

void Student::calculate_averages()
{
    has_final_score = true;
    if (scores.empty()) {
        score_average = score_median = 0;
        return;
    }

    double average{};
    for (const auto score : scores) {
        average += score;
    }
    score_average = average / scores.size();
    double temp = 0.4 * score_average + 0.6 * test_score;
    final_score_avg = round(temp);

    // Surikiuojam pažymius medianos apskaičiavimui
    std::sort (scores.begin(), scores.begin() + scores.size());

    
    if (scores.size() % 2 == 0) {
        score_median = (scores[(scores.size() - 1) / 2] + 
            scores[scores.size() / 2]) / 2.0;
        temp = 0.4 * score_median + 0.6 * test_score;
        final_score_med = round(temp * 10) / 10;
            return;
    }

    score_median = scores[scores.size() / 2];
    temp = 0.4 * score_median + 0.6 * test_score;
    final_score_med = round(temp);
}


void print_students(const Vector<Student> &students, unsigned option)
{
    printf("\n%-15s%-15s%s", "Pavardė", "Vardas", "(Vid.)");
    cout << endl << endl;

    std::string temp(50, '-');
    cout << temp << endl;

    for (const auto& student : students) {
        student.print_student();
    }
}

unsigned generate_random_score()
{
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(1, 10);
    
    return dist(mt);
}

bool compare(Student a, Student b)
{
    return a.get_last_name() < b.get_last_name();
}

bool compare_by_final_score(Student a, Student b)
{
    return a.get_final_score() < b.get_final_score();
}

void sort_students(Vector<Student> &students)
{
    std::sort(students.begin(), students.end(), compare);
}

void create_student_file(const std::string file_name, const unsigned student_amount, const unsigned scores_amount)
{
    Vector<Student> students;
    students.reserve(student_amount);
    for (unsigned i{}; i < student_amount; i++) {

        string first_name = "Vardas" + std::to_string(i + 1);
        string last_name = "Pavarde" + std::to_string(i + 1);

        Vector<unsigned> temp_scores;
        for (unsigned i{}; i < scores_amount - 1; i++) {
            temp_scores.push_back(generate_random_score());
        }
        unsigned test_score = generate_random_score();
        
        Student student{first_name, last_name, test_score, temp_scores};
        students.push_back(student);
    }

    write_student_file( students, file_name );
}

void create_student_file_myvec(const std::string file_name, const unsigned student_amount, const unsigned scores_amount)
{
    Vector<Student> students;
    students.reserve(student_amount);
    for (unsigned i{}; i < student_amount; i++) {

        string first_name = "Vardas" + std::to_string(i + 1);
        string last_name = "Pavarde" + std::to_string(i + 1);

        Vector<unsigned> temp_scores;
        for (unsigned i{}; i < scores_amount - 1; i++) {
            temp_scores.push_back(generate_random_score());
        }
        unsigned test_score = generate_random_score();
        
        Student student{first_name, last_name, test_score, temp_scores};
        students.push_back(student);
    }

    write_student_file( students, file_name );
}

/*
void read_student_Vector(Vector<Student> &students, const std::string file_name)
{
    ifstream student_file;
    try {
        student_file.open(file_name);

        if (student_file.fail())
            throw file_name;

        else if (student_file.is_open()) {
            string line;

            getline(student_file, line);
            while (getline(student_file, line)) {

                    istringstream iss(line);
                    Student student(line);
                    students.push_back(student);
            }
        }

        student_file.close();
    }
    catch (string e) {
        cout << "\nKlaida atidarinėjant failą\n" << endl;
    }
}

void read_student_list(std::list<Student> &students, const std::string file_name)
{
    ifstream student_file;
    try {
        student_file.open(file_name);

        if (student_file.fail())
            throw file_name;

        else if (student_file.is_open()) {
            string line;

            getline(student_file, line);
            while (getline(student_file, line)) {

                    istringstream iss(line);
                    Student student(line);
                    students.push_back(student);
            }
        }

        student_file.close();
    }
    catch (string e) {
        cout << "\nKlaida atidarinėjant failą\n" << endl;
    }
}

void read_student_deque(std::deque<Student> &students, const std::string file_name)
{
    ifstream student_file;
    try {
        student_file.open(file_name);

        if (student_file.fail())
            throw file_name;

        else if (student_file.is_open()) {
            string line;

            getline(student_file, line);
            while (getline(student_file, line)) {

                    istringstream iss(line);
                    Student student(line);
                    students.push_back(student);
            }
        }

        student_file.close();
    }
    catch (string e) {
        cout << "\nKlaida atidarinėjant failą\n" << endl;
    }
}
*/
