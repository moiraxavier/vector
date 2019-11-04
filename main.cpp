#include <iostream>
#include <vector>
#include <math.h>

#include "Vector.h"
#include "Algorithm.h"

using namespace std;

typedef struct Student
{
    std::string m_name;
    double m_av_mark;
    int m_group;
} Student;

int main()
{
    cout.setf(ios_base::internal, ios_base::adjustfield);

    auto print = [](const Student& student) {  std::cout.width(10);
                                        std::cout << student.m_name << " |";
                                        std::cout.width(3);
                                        std::cout << student.m_group << " |";
                                        std::cout.width(5);
                                        std::cout << student.m_av_mark << std::endl; };

    Vector<Student> vector_students_1({{"Sebastian", 6.7, 1},
                                       {"Ava", 9.9, 1},
                                       {"Tess", 4.1, 2},
                                       {"David", 5.2, 3},
                                       {"Marta", 5.1, 2},
                                       {"Steve", 8.7, 2}});

    Vector<Student> vector_students_2;
    Student student = {"Helen", 7.3, 3};
    vector_students_2.pushBack(student);
    student = {"Olaf", 3.3, 2};
    vector_students_2.pushBack(student);
    student = {"Martin", 6.3, 3};
    vector_students_2.insert(vector_students_2.begin() + 1, student);
    student = {"Jim", 9.2, 1};
    vector_students_2.insert(vector_students_2.begin() + 2, student);
    student = {"Ada", 8.3, 3};
    vector_students_2.pushBack(student);

    std::cout << std::endl << "First group" << std::endl;
    forEach(vector_students_1.begin(), vector_students_1.end(), print);

    std::cout << std::endl <<  "Second group" << std::endl;
    forEach(vector_students_2.begin(), vector_students_2.end(), print);

    vector_students_1.insert(vector_students_1.begin() + round(vector_students_1.size()/2), vector_students_2.begin(), vector_students_2.end());
    std::cout << std::endl <<  "First group with second added in the middle" << std::endl;
    forEach(vector_students_1.begin(), vector_students_1.end(), print);

    // sort(vector_students_1.begin(),vector_students_1.end(),[] (Student st1,Student st2){ return st1.m_av_mark>st2.m_av_mark; });

    findIf(vector_students_1.begin() + 2, vector_students_1.begin() + 9, [](Student student) { return student.m_av_mark < 4.0;}).operator->()->m_av_mark = 0;
    std::cout << std::endl << "First group: one student in [] got 0!" << std::endl;
    forEach(vector_students_1.begin(), vector_students_1.end(), print);

    Vector<Student> vector_students_3;
    auto condition = [](const Student& student) { return student.m_group == 2;};
    size_t n = countIf(vector_students_1.begin(), vector_students_1.end(), condition);
    vector_students_3.resize(n);
    copyIf(vector_students_1.begin(), vector_students_1.end(), vector_students_3.begin(), condition);
    std::cout << std::endl << "Third group: all students from group = 2" << std::endl;
    forEach(vector_students_3.begin(), vector_students_3.end(), print);

    return 0;
}