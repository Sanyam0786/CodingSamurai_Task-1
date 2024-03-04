#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <iomanip> /*For std::setprecision*/

using namespace std;

/*Define a struct to store student details*/
struct Student {
    string name;
    string id;
    double assignmentScore;
    double quizScore;
    double examScore;
    double finalGrade;
    char letterGrade;
    string feedback;
};

/*Function prototypes*/
void inputStudentDetails(Student &student);
void calculateFinalGrade(Student &student, double assignmentWeight, double quizWeight, double examWeight);
char calculateLetterGrade(double finalGrade);
void provideFeedback(Student &student);
void displayStudentDetails(const Student &student);
bool validateScore(double score);
bool validateWeights(double assignmentWeight, double quizWeight, double examWeight);

int main() {
    int numStudents;
    double assignmentWeight, quizWeight, examWeight;

    /*Welcome message and instructions*/
    cout << "Welcome to the Student Grade Calculator!" << endl;
    cout << "Please enter the following details:" << endl;

    /*Prompt user for the number of students*/
    cout << "Enter the number of students: ";
    cin >> numStudents;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    /*Prompt user for weights until valid weights are entered*/
    do {
        cout << "Enter weight for assignments (in %): ";
        cin >> assignmentWeight;
        cout << "Enter weight for quizzes (in %): ";
        cin >> quizWeight;
        cout << "Enter weight for exams (in %): ";
        cin >> examWeight;
        if (!validateWeights(assignmentWeight, quizWeight, examWeight)) {
            cout << "Invalid weights. Weights should sum up to 100%. Please try again." << endl;
        }
    } while (!validateWeights(assignmentWeight, quizWeight, examWeight));

    /*Create a vector to store student objects*/
    vector<Student> students(numStudents);

    /*Input student details, calculate grades, and provide feedback for each student*/
    for (int i = 0; i < numStudents; ++i) {
        cout << "\nStudent " << i + 1 << ":" << endl;
        inputStudentDetails(students[i]);
        calculateFinalGrade(students[i], assignmentWeight, quizWeight, examWeight);
        provideFeedback(students[i]);
    }

    /*Display student details and grades*/
    cout << "\nStudent Details and Grades:" << endl;
    for (const auto &student : students) {
        displayStudentDetails(student);
    }

    return 0;
}

/*Function to input student details*/
void inputStudentDetails(Student &student) {
    cout << "\nEnter student name: ";
    cin.ignore();
    getline(cin, student.name);
    cout << "Enter student ID: ";
    getline(cin, student.id);

    /*Validate and input assignment score*/
    do {
        cout << "Enter assignment score (0-100): ";
        cin >> student.assignmentScore;
    } while (!validateScore(student.assignmentScore));

    /*Validate and input quiz score*/
    do {
        cout << "Enter quiz score (0-100): ";
        cin >> student.quizScore;
    } while (!validateScore(student.quizScore));

    /*Validate and input exam score*/
    do {
        cout << "Enter exam score (0-100): ";
        cin >> student.examScore;
    } while (!validateScore(student.examScore));
}

/*Function to validate score (should be between 0 and 100)*/
bool validateScore(double score) {
    if (score < 0 || score > 100) {
        cout << "Invalid score! Please enter a score between 0 and 100." << endl;
        return false;
    }
    return true;
}

/*Function to validate weights (sum should be 100%)*/
bool validateWeights(double assignmentWeight, double quizWeight, double examWeight) {
    double totalWeight = assignmentWeight + quizWeight + examWeight;
    return totalWeight == 100;
}

/*Function to calculate final grade based on weights*/
void calculateFinalGrade(Student &student, double assignmentWeight, double quizWeight, double examWeight) {
    student.finalGrade = (student.assignmentScore * assignmentWeight / 100) +
                         (student.quizScore * quizWeight / 100) +
                         (student.examScore * examWeight / 100);
    student.letterGrade = calculateLetterGrade(student.finalGrade); /*Calculate letter grade*/
}

/*Function to calculate letter grade based on final grade*/
char calculateLetterGrade(double finalGrade) {
    if (finalGrade >= 90)
        return 'A';
    else if (finalGrade >= 80)
        return 'B';
    else if (finalGrade >= 70)
        return 'C';
    else if (finalGrade >= 60)
        return 'D';
    else
        return 'F';
}

/*Function to provide feedback based on final grade*/
void provideFeedback(Student &student) {
    if (student.finalGrade >= 90)
        student.feedback = "Congratulations on your excellent performance!";
    else if (student.finalGrade >= 80)
        student.feedback = "Good job!";
    else if (student.finalGrade >= 70)
        student.feedback = "You're doing well, keep it up!";
    else if (student.finalGrade >= 60)
        student.feedback = "You passed, but there's room for improvement.";
    else
        student.feedback = "You need to work harder to improve your grades.";
}

/*Function to display student details and grades*/
void displayStudentDetails(const Student &student) {
    cout << "\nName: " << student.name << endl;
    cout << "ID: " << student.id << endl;
    cout << "Final Grade: " << fixed << setprecision(2) << student.finalGrade << endl; /*Set precision to 2 decimal places*/
    cout << "Letter Grade: " << student.letterGrade << endl;
    cout << "Feedback: " << student.feedback << endl;
}
