#include <iostream>
#include <limits>
void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
template <typename T>
T *getInput()
{
    T obj{};
    T *result{nullptr};
    std::cin >> obj;
    if (!std::cin)
    {
        std::cin.clear();
        ignoreLine();
        return result;
    }
    else
    {
        ignoreLine();
        // QUESTION: this is messed up, earlier I just saved address of obj to result 
        // IT WORKED!!! but it shouldn't.  
        result = new T{obj};
        return result;
    }
}

template <>
std::string* getInput()
{
    std::string obj{};
    std::string *result{nullptr};
    std::getline(std::cin >> std::ws, obj); 
    if (!std::cin)
    {
        std::cin.clear();
        return result;
    }
    else
    {
        result = new std::string{obj};
        return result;
    }
}

template <typename T>
T pleaseEnter(std::string_view message)
{
    while (true)
    {
        std::cout << message;
        T* result{getInput<T>()};
    
        if (result != nullptr)
        {
            // convert dynamic to static
            T staticResult{*result};
            // QUESTION: is it like viable solution, or bad practice? 
            delete result;
            return staticResult;
        }
    }
}

#include <vector>
#include <algorithm>
struct Student {
    std::string name{};
    int grade{};
};

Student enterStudent(int n) {
    std::string name{pleaseEnter<std::string>("Please enter name"+ std::to_string(n)+": ")};
    int grade{pleaseEnter<int>("Please enter grade" + std::to_string(n)+": ")};
    return Student{name, grade};
}
void printStudents(std::vector<Student> students) {
    for (const auto& student : students)
    {
        std::cout << student.name << " has grade " << student.grade << std::endl;
    }
}
bool compareStudents(const Student& a, const Student& b) {
    return (a.grade > b.grade);
}
int main() {
    size_t numOfStudents {pleaseEnter<size_t>("How many students do we have?: ")};

    std::vector<Student> students(numOfStudents);
    
    int i{}; // this is bad I know, but I wanted to experiment a little bit
    for (auto& student : students)
    {
        student = enterStudent(i++);
    }
    std::sort(students.begin(), students.end(), compareStudents);
    printStudents(students);   
}