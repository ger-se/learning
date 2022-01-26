#include <string>

using namespace std;

struct Specialization
{
    string value;

    explicit Specialization(const string& p_value){
        value = p_value;
    }
};

struct Course
{
    string value;

    explicit Course(const string& p_value){
        value = p_value;
    }
};

struct Week
{
    string value;

    explicit Week(const string& p_value){
        value = p_value;
    }
};

struct LectureTitle
{
    string specialization;
    string course;
    string week;

     explicit LectureTitle(const Specialization& p_specialization, const Course& p_course, const Week& p_week)
    {
        specialization = p_specialization.value;
        course = p_course.value;
        week = p_week.value;
    }
};
