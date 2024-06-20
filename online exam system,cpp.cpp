#include <iostream>
#include <string>
#include <fstream>
#include <vector>

const std::string STUDENT_DATA_FILE = "students.dat";
const std::string TEACHER_DATA_FILE = "teachers.dat";
const std::string QUESTIONS_FILE = "questions.dat";
const std::string RESULTS_FILE = "results.dat";

// Node structure for a user (student or teacher)
struct UserNode {
    std::string username;
    std::string password;
    std::string name;   // Student's name
    std::string studentID; // Student's ID
    int marks;          // Student's marks
    UserNode* next;

    // Constructor
    UserNode(const std::string& uname, const std::string& pwd, const std::string& n, const std::string& id, int m)
        : username(uname), password(pwd), name(n), studentID(id), marks(m), next(nullptr) {}
};

// Linked list structure for users
class UserList {
private:
    UserNode* head;

public:
    // Constructor
    UserList() : head(nullptr) {}

    // Destructor to free memory
    ~UserList() {
        UserNode* current = head;
        while (current) {
            UserNode* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    // Function to add a new user to the list
    void addUser(const std::string& uname, const std::string& pwd, const std::string& name, const std::string& id, int marks) {
        UserNode* newNode = new UserNode(uname, pwd, name, id, marks);
        if (!head) {
            head = newNode;
        } else {
            UserNode* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Function to check if a user exists
    bool userExists(const std::string& uname) {
        UserNode* current = head;
        while (current) {
            if (current->username == uname) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Function to validate user login
    bool validateUser(const std::string& uname, const std::string& pwd) {
        UserNode* current = head;
        while (current) {
            if (current->username == uname && current->password == pwd) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Function to find user by username
    UserNode* findUser(const std::string& uname) {
        UserNode* current = head;
        while (current) {
            if (current->username == uname) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Function to get all student names
    std::vector<std::string> getAllStudentNames() {
        std::vector<std::string> studentNames;
        UserNode* current = head;
        while (current) {
            // Check if the user is a student (You can add more checks if needed)
            if (!current->studentID.empty()) {
                studentNames.push_back(current->name);
            }
            current = current->next;
        }
        return studentNames;
    }
};

// Function prototypes
void studentPanel(UserList& students);
void teacherPanel(UserList& teachers, UserList& students);
void registerUser(UserList& users, const std::string& userType);
void loginUser(UserList& users, const std::string& userType);
void createStudentProfile(UserList& students);
void questionPanel();
void addQuestion();
void viewQuestions();
void removeQuestion();
void takeExam(UserList& students);
void viewExamResults(UserList& students);

// Function prototypes
void studentPanel(UserList& students);
void displayStudents(UserList& students);
void updateStudentProfile(UserList& students);

// Updated student panel function
void studentPanel(UserList& students) {
    int choice;

    while (true) {
        std::cout << "\nStudent Panel:\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Display Students\n";
        std::cout << "4. Update Student Profile\n";
        std::cout << "5. Create Student Profile\n";
        std::cout << "6. Take Exam\n";
        std::cout << "7. Back to Main Menu\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                registerUser(students, "student");
                break;
            case 2:
                loginUser(students, "student");
                break;
            case 3:
                displayStudents(students);
                break;
            case 4:
                updateStudentProfile(students);
                break;
            case 5:
                createStudentProfile(students);
                break;
            case 6:
                takeExam(students);
                break;
            case 7:
                return;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
}

// Function to display all registered students
void displayStudents(UserList& students) {
    std::vector<std::string> studentNames = students.getAllStudentNames();

    if (studentNames.empty()) {
        std::cout << "No students registered yet.\n";
    } else {
        std::cout << "\nList of Students:\n";
        for (const auto& name : studentNames) {
            std::cout << "- " << name << "\n";
        }
    }
}

// Function to update student profile
void updateStudentProfile(UserList& students) {
    std::string username, name, studentID;

    std::cout << "Enter your username: ";
    std::cin >> username;

    if (!students.userExists(username)) {
        std::cerr << "Error: User not found.\n";
        return;
    }

    std::cout << "Enter your name: ";
    std::cin.ignore(); // Clear the input buffer
    std::getline(std::cin, name);

    std::cout << "Enter your student ID: ";
    std::cin >> studentID;

    UserNode* student = students.findUser(username);
    if (student) {
        student->name = name;
        student->studentID = studentID;
        std::cout << "Student profile updated successfully.\n";
    } else {
        std::cerr << "Error: User not found.\n";
    }
}



int main() {
    UserList students;
    UserList teachers;

    int choice;

    while (true) {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Student Panel\n";
        std::cout << "2. Teacher Panel\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                studentPanel(students);
                break;
            case 2:
                teacherPanel(teachers, students); // Pass both teachers and students lists
                break;
            case 3:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
}


// Student panel
//void studentPanel(UserList& students) {
//    int choice;
//
//    while (true) {
//        std::cout << "\nStudent Panel:\n";
//        std::cout << "1. Register\n";
//        std::cout << "2. Login\n";
//        std::cout << "3. Create Student Profile\n";
//        std::cout << "4. Take Exam\n";
//        std::cout << "5. Back to Main Menu\n";
//        std::cout << "Choose an option: ";
//        std::cin >> choice;
//
//        switch (choice) {
//            case 1:
//                registerUser(students, "student");
//                break;
//            case 2:
//                loginUser(students, "student");
//                break;
//            case 3:
//                createStudentProfile(students);
//                break;
//            case 4:
//                takeExam(students);
//                break;
//            case 5:
//                return;
//            default:
//                std::cout << "Invalid choice, please try again.\n";
//        }
//    }
//}

// Teacher panel
void teacherPanel(UserList& teachers, UserList& students) {
    int choice;

    while (true) {
        std::cout << "\nTeacher Panel:\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Question Panel\n";
        std::cout << "4. View Exam Results\n";
        std::cout << "5. Back to Main Menu\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                registerUser(teachers, "teacher");
                break;
            case 2:
                loginUser(teachers, "teacher");
                break;
            case 3:
                questionPanel();
                break;
            case 4:
                viewExamResults(students); // Pass students list here
                break;
            case 5:
                return;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
}



// Register a new user (student or teacher)
void registerUser(UserList& users, const std::string& userType) {
    std::string username, password, name, studentID;
    int marks = 0;

    std::cout << "Enter username: ";
    std::cin >> username;
    if (users.userExists(username)) {
        std::cout << "Username already exists. Try a different one.\n";
        return;
    }

    std::cout << "Enter password: ";
    std::cin >> password;

    if (userType == "student") {

        // Additional fields can be added here
    } else if (userType == "teacher") {
        // Additional information for teacher registration can be added here
    }

    users.addUser(username, password, name, studentID, marks);
    std::cout << "Registration successful.\n";
}

// Log in an existing user (student or teacher)
void loginUser(UserList& users, const std::string& userType) {
    std::string username, password;

    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter password: ";
    std::cin >> password;

    if (users.validateUser(username, password)) {
        std::cout << "Login successful.\n";
    } else {
        std::cout << "Invalid username or password.\n";
    }
}

// Create a student profile
void createStudentProfile(UserList& students) {
    std::string username, name, studentID;
    int marks = 0;

    std::cout << "Enter your username: ";
    std::cin >> username;

    if (!students.userExists(username)) {
        std::cerr << "Error: User not found.\n";
        return;
    }

    std::cout << "Enter your name: ";
    std::cin.ignore(); // Clear the input buffer
    std::getline(std::cin, name);

    std::cout << "Enter your student ID: ";
    std::cin >> studentID;

    // Additional fields can be added here if needed

    UserNode* student = students.findUser(username);
    if (student) {
        student->name = name;
        student->studentID = studentID;
        // Assign other fields as necessary
        std::cout << "Student profile updated successfully.\n";
    } else {
        std::cerr << "Error: User not found.\n";
    }
}

// Question panel for teachers
void questionPanel() {
    int choice;

    while (true) {
        std::cout << "\nQuestion Panel:\n";
        std::cout << "1. Add Question\n";
        std::cout << "2. View Questions\n";
        std::cout << "3. Remove Question\n";
        std::cout << "4. Back to Teacher Panel\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addQuestion();
                break;
            case 2:
                viewQuestions();
                break;
            case 3:
                removeQuestion();
                break;
            case 4:
                return;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
}

// Add a question to the questions file
void addQuestion() {
    std::string question;

    std::cin.ignore(); // Clear the input buffer
    std::cout << "Enter the question: ";
    std::getline(std::cin, question);

    std::ofstream outFile(QUESTIONS_FILE, std::ios::app);
    if (outFile.is_open()) {
        outFile << question << "\n";
        std::cout << "Question added successfully.\n";
        outFile.close();
    } else {
        std::cerr << "Error: Unable to open file for writing.\n";
    }
}

// View all questions
void viewQuestions() {
    std::ifstream inFile(QUESTIONS_FILE);
    std::string question;

    if (inFile.is_open()) {
        std::cout << "\nList of Questions:\n";
        while (std::getline(inFile, question)) {
            std::cout << "- " << question << "\n";
        }
        inFile.close();
    } else {
        std::cerr << "Error: Unable to open file for reading.\n";
    }
}

// Remove a question from the questions file
void removeQuestion() {
    std::ifstream inFile(QUESTIONS_FILE);
    std::vector<std::string> questions;
    std::string question;
    int questionIndex;

    if (inFile.is_open()) {
        while (std::getline(inFile, question)) {
            questions.push_back(question);
        }
        inFile.close();
    } else {
        std::cerr << "Error: Unable to open file for reading.\n";
        return;
    }

    std::cout << "\nList of Questions:\n";
    for (size_t i = 0; i < questions.size(); ++i) {
        std::cout << i + 1 << ". " << questions[i] << "\n";
    }

    std::cout << "Enter the number of the question to remove: ";
    std::cin >> questionIndex;

    if (questionIndex < 1 || questionIndex > static_cast<int>(questions.size())) {
        std::cerr << "Error: Invalid question number.\n";
        return;
    }

    questions.erase(questions.begin() + questionIndex - 1);

    std::ofstream outFile(QUESTIONS_FILE);
    if (outFile.is_open()) {
        for (const auto& q : questions) {
            outFile << q << "\n";
        }
        std::cout << "Question removed successfully.\n";
        outFile.close();
    } else {
        std::cerr << "Error: Unable to open file for writing.\n";
    }
}

// Take an exam by answering the questions added by teachers
void takeExam(UserList& students) {
    std::string username;
    std::cout << "Enter your username: ";
    std::cin >> username;

    UserNode* student = students.findUser(username);
    if (student == nullptr) {
        std::cerr << "Error: Student not found.\n";
        return;
    }

    std::ifstream inFile(QUESTIONS_FILE);
    std::string question;
    std::vector<std::string> questions;
    std::vector<std::string> answers;
    std::string answer;

    if (inFile.is_open()) {
        while (std::getline(inFile, question)) {
            questions.push_back(question);
        }
        inFile.close();
    } else {
        std::cerr << "Error: Unable to open file for reading.\n";
        return;
    }

    std::cout << "\nExam:\n";
    for (size_t i = 0; i < questions.size(); ++i) {
        std::cout << i + 1 << ". " << questions[i] << "\n";
        std::cout << "Your answer: ";
        std::cin.ignore(); // Clear the input buffer
        std::getline(std::cin, answer);
        answers.push_back(answer);
    }

    std::ofstream outFile(RESULTS_FILE, std::ios::app);
    if (outFile.is_open()) {
        outFile << "Student Name: " << student->name << "\n";
        for (size_t i = 0; i < questions.size(); ++i) {
            outFile << "Q: " << questions[i] << "\nA: " << answers[i] << "\n";
        }
        outFile << "-----\n"; // Separator for different exams
        std::cout << "\nExam completed. Your answers have been saved.\n";
        outFile.close();
    } else {
        std::cerr << "Error: Unable to open file for writing.\n";
    }
}

// View exam results in the teacher panel
void viewExamResults(UserList& students) {
    std::ifstream inFile(RESULTS_FILE);
    std::string line;
    bool foundResult = false;

    if (inFile.is_open()) {
        std::cout << "\nExam Results:\n";
        while (std::getline(inFile, line)) {
            if (line.find("Student Name:") != std::string::npos) {
                std::cout << line << "\n";
                foundResult = true;
            } else if (foundResult) {
                std::cout << line << "\n"; // Display the student's answers
                foundResult = false;
            }
        }
        inFile.close();
    } else {
        std::cerr << "Error: Unable to open file for reading.\n";
    }
}

