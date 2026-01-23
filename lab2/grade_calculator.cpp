// These headers define some of the classes and functions we need
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <sstream>

// ONLY MAKE CHANGES WHERE THERE IS A TODO(student)

// These using declarations let us refer to things more simply
// e.g. instead of "std::cout" we can just write "cout"
using std::cout, std::endl, std::cin, std::string, std::getline;

// Some methods are already implemented for you
// You should not modify them
// Even minor changes might cause you to fail test cases for the wrong reasons

void println(const string& str, double value) {
    cout << str << std::setw(6) << value << endl;
}
void println(const string& str, char value) {
    cout << str << value << endl;
}
void println(const string& str) {
    cout << str << endl;
}

// pretty-print a summary of the grades
void print_results(double homework,
                   double labwork,
                   double midterm_exams,
                   double final_exam,
                   double reading,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade) {
    cout << std::fixed << std::setprecision(2);
    println("summary:");
    println("      homework: ", homework);
    println("       labwork: ", labwork);
    println(" midterm exams: ", midterm_exams);
    println("    final exam: ", final_exam);
    println("      readings: ", reading);
    println("    engagement: ", engagement);
    println("----------------------");
    println("weighted total: ", weighted_total);
    println("final letter grade: ", final_letter_grade);
}

// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
void get_category_and_score(const string& line,
                            string* category,
                            double* score) {
    // turn the string into an input stream
    std::istringstream sin(line); // Putting in the steam "hw 2"

    // read the category (as string) and score (as double) from the stream
    sin >> *category >> *score; // idk why yall didnt pass the double as a copy

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

int main() {
    double homework_score = 0;
    double labwork_score = 0;
    double midterm_exams_score = 0;
    double lowest_midterm_exam_score = 0;
    double final_exam_score = 0;
    double reading_score = 0;
    double engagement_score = 0;

    int homework_amount = 0;
    int labwork_amount = 0;
    int reading_amount = 0;
    int engagement_amount = 0;
    int midterm_amount = 0;

    double homework_percent = .2;
    double labwork_percent = .1;
    double midterm_percent = .36;
    double final_percent = .24;
    double reading_percent = .05;
    double engagement_percent = .05;

    string line;
    getline(cin, line);

    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        if (category == "hw") {
            homework_score += score;
            homework_amount += 1;
        } else if (category == "lw") {
            if (score >= 50) {
                labwork_score += score;
            }
            labwork_amount += 1;
        } else if (category == "exam") {
            midterm_exams_score += score;
            midterm_amount += 1;
            if (score == 0 || score < lowest_midterm_exam_score) {
                lowest_midterm_exam_score = score;
            }
        } else if (category == "final-exam") {
            final_exam_score = score;
        } else if (category == "reading") {
            reading_score += score;
            reading_amount += 1;
        } else if (category == "engagement") {
            engagement_score += score;
            engagement_amount += 1;
        } else {
            println("ignored invalid input");
        }

        getline(cin, line);
    }

    if (midterm_amount > 1) {
        midterm_exams_score -= lowest_midterm_exam_score;
        midterm_amount -= 1;
    } 

    cout << homework_score << endl;
    homework_score = homework_amount > 0 ? (homework_score / static_cast<double>(homework_amount)) : 0;
    cout << homework_score << endl;
    labwork_score = labwork_amount > 0 ? (labwork_score / static_cast<double>(labwork_amount)) : 0;
    reading_score = reading_amount > 0 ? (reading_score / static_cast<double>(reading_amount)) : 0;
    engagement_score = engagement_amount > 0 ? (engagement_score / static_cast<double>(engagement_amount)) : 0;
    midterm_exams_score = midterm_amount > 0 ? (midterm_exams_score / static_cast<double>(midterm_amount)) : 0;
    
    
    double weighted_total = homework_score * homework_percent
        + labwork_score * labwork_percent + reading_score * reading_percent
        + engagement_score * engagement_percent + midterm_exams_score * midterm_percent
        + midterm_exams_score * midterm_percent + final_exam_score * final_percent;

    char final_letter_grade = 'X';

    if (weighted_total < 60) {
        final_letter_grade = 'F';
    } else if (weighted_total < 70 && weighted_total >= 60) {
        final_letter_grade = 'D';
    } else if (weighted_total < 80 && weighted_total >= 70) {
        final_letter_grade = 'C';
    } else if (weighted_total < 90 && weighted_total >= 80) {
        final_letter_grade = 'B';
    } else if (weighted_total >= 90) {
        final_letter_grade = 'A';
    }

    print_results(
        homework_score,
        labwork_score,
        midterm_exams_score,
        final_exam_score,
        reading_score,
        engagement_score,
        weighted_total,
        final_letter_grade);
}
