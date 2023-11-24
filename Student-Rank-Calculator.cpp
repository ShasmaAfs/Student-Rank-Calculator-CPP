#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// Define a Student class
class Student {
public:
    std::string name;
    int marksBiology;
    int marksPhysics;
    int marksChemistry;
    int totalMarks;
    int schoolRank;  // Add schoolRank member variable

    // Constructor
    Student(const std::string& n, int bio, int phy, int chem)
        : name(n), marksBiology(bio), marksPhysics(phy), marksChemistry(chem) {
        // Calculate total marks
        totalMarks = marksBiology + marksPhysics + marksChemistry;
    }

    // Overload the comparison operator for sorting
    bool operator<(const Student& other) const {
        return totalMarks > other.totalMarks; // Sort in descending order
    }
};

// Define a ClassRank class to store class-specific information
class ClassRank {
public:
    std::string className;
    std::vector<Student> students;

    // Constructor
    ClassRank(const std::string& name) : className(name) {}

    // Function to calculate ranks within the class
    void calculateClassRank() {
        std::sort(students.begin(), students.end());
    }
};

// Function to calculate school rank
void calculateSchoolRank(std::vector<ClassRank>& classes) {
    std::vector<Student> allStudents;

    // Merge all students from different classes into one vector
    for (const auto& classRank : classes) {
        allStudents.insert(allStudents.end(), classRank.students.begin(), classRank.students.end());
    }

    // Sort all students to calculate school rank
    std::sort(allStudents.begin(), allStudents.end());

    // Assign school ranks
    for (size_t i = 0; i < allStudents.size(); ++i) {
        allStudents[i].schoolRank = i + 1;
    }
}

// Function to print and write ranks to a file
void printAndWriteRanks(const std::vector<ClassRank>& classes) {
    std::ofstream outFile("ranks.txt");

    for (const auto& classRank : classes) {
        std::cout << "Class: " << classRank.className << std::endl;
        outFile << "Class: " << classRank.className << std::endl;

        for (size_t i = 0; i < classRank.students.size(); ++i) {
            const auto& student = classRank.students[i];
            std::cout << "Student: " << student.name << ", Total Marks: " << student.totalMarks
                      << ", Class Rank: " << i + 1 << ", School Rank: " << student.schoolRank << std::endl;

            outFile << "Student: " << student.name << ", Total Marks: " << student.totalMarks
                    << ", Class Rank: " << i + 1 << ", School Rank: " << student.schoolRank << std::endl;
        }

        std::cout << std::endl;
        outFile << std::endl;
    }

    outFile.close();
}

int main() {
    // ... (rest of the code remains unchanged)
}
