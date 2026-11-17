/*
 * Project 6: Online Examination Grading System
 * Topics: Arrays, Loops, Conditional Structures, Structures
 *
 * Compile: gcc exam_grading.c -o exam_grading
 * Run    : ./exam_grading
 */

#include <stdio.h>
#include <ctype.h>

#define NUM_QUESTIONS 10
#define MAX_STUDENTS  50
#define NAME_LEN      50

/* Structure to store one student's data */
struct Student {
    char  name[NAME_LEN];
    int   rollNo;
    char  answers[NUM_QUESTIONS];   /* student's responses */
    int   score;
    float percentage;
    char  grade[3];                 /* "A+", "A", "B", "C", "D", "F" */
};

/* Stored answer key (array) */
const char answerKey[NUM_QUESTIONS] = {
    'A', 'C', 'B', 'D', 'A', 'B', 'C', 'D', 'A', 'B'
};

/* Sample questions so the exam feels real */
const char *questions[NUM_QUESTIONS] = {
    "Which of these is a valid C data type?  (A) int (B) integer (C) number (D) real",
    "Which header file is needed for printf()?  (A) conio.h (B) math.h (C) stdio.h (D) string.h",
    "Array index in C starts from?  (A) 1 (B) 0 (C) -1 (D) Any value",
    "Which loop checks its condition after executing the body?  (A) for (B) while (C) if (D) do-while",
    "Which operator gives the remainder?  (A) % (B) / (C) * (D) &",
    "Which keyword is used to define a structure?  (A) union (B) struct (C) class (D) record",
    "Format specifier for float is?  (A) %d (B) %c (C) %f (D) %s",
    "Which statement exits a loop immediately?  (A) skip (B) exit (C) stop (D) break",
    "Size of char in C is typically?  (A) 1 byte (B) 2 bytes (C) 4 bytes (D) 8 bytes",
    "Which symbol accesses a structure member?  (A) -> only (B) . (dot) (C) :: (D) #"
};

/* Function prototypes */
void  takeExam(struct Student *s);
void  evaluate(struct Student *s);
void  assignGrade(struct Student *s);
void  displayResult(const struct Student *s);
void  displaySummary(const struct Student list[], int count);

int main(void)
{
    struct Student students[MAX_STUDENTS];
    int  count = 0;
    char again = 'y';

    printf("=====================================\n");
    printf("   ONLINE EXAMINATION GRADING SYSTEM\n");
    printf("=====================================\n");

    while ((again == 'y' || again == 'Y') && count < MAX_STUDENTS) {
        takeExam(&students[count]);
        evaluate(&students[count]);
        assignGrade(&students[count]);
        displayResult(&students[count]);
        count++;

        if (count < MAX_STUDENTS) {
            printf("\nEvaluate another student? (y/n): ");
            scanf(" %c", &again);
        }
    }

    displaySummary(students, count);
    return 0;
}

/* Accepts student details and MCQ responses */
void takeExam(struct Student *s)
{
    int  i;
    char ch;

    printf("\nEnter student name : ");
    scanf(" %49[^\n]", s->name);
    printf("Enter roll number  : ");
    scanf("%d", &s->rollNo);

    printf("\nAnswer each question with A, B, C or D.\n");
    printf("-------------------------------------\n");

    for (i = 0; i < NUM_QUESTIONS; i++) {
        printf("\nQ%d. %s\n", i + 1, questions[i]);

        /* Input validation loop */
        while (1) {
            printf("Your answer: ");
            scanf(" %c", &ch);
            ch = toupper((unsigned char)ch);

            if (ch >= 'A' && ch <= 'D') {
                s->answers[i] = ch;
                break;
            }
            printf("Invalid option! Please enter A, B, C or D.\n");
        }
    }
}

/* Compares responses with the answer key and computes score/percentage */
void evaluate(struct Student *s)
{
    int i;
    s->score = 0;

    for (i = 0; i < NUM_QUESTIONS; i++) {
        if (s->answers[i] == answerKey[i]) {
            s->score++;
        }
    }
    s->percentage = ((float)s->score / NUM_QUESTIONS) * 100;
}

/* Uses conditional structure to assign grade from percentage */
void assignGrade(struct Student *s)
{
    float p = s->percentage;

    if (p >= 90)      { s->grade[0] = 'A'; s->grade[1] = '+'; s->grade[2] = '\0'; }
    else if (p >= 80) { s->grade[0] = 'A'; s->grade[1] = '\0'; }
    else if (p >= 70) { s->grade[0] = 'B'; s->grade[1] = '\0'; }
    else if (p >= 60) { s->grade[0] = 'C'; s->grade[1] = '\0'; }
    else if (p >= 50) { s->grade[0] = 'D'; s->grade[1] = '\0'; }
    else              { s->grade[0] = 'F'; s->grade[1] = '\0'; }
}

/* Prints a detailed result card */
void displayResult(const struct Student *s)
{
    int i;

    printf("\n=========== RESULT CARD ===========\n");
    printf("Name        : %s\n", s->name);
    printf("Roll No     : %d\n", s->rollNo);
    printf("-----------------------------------\n");
    printf("Q.No  Your Ans  Correct  Status\n");

    for (i = 0; i < NUM_QUESTIONS; i++) {
        printf("%-5d %-9c %-8c %s\n",
               i + 1, s->answers[i], answerKey[i],
               (s->answers[i] == answerKey[i]) ? "Correct" : "Wrong");
    }

    printf("-----------------------------------\n");
    printf("Score       : %d / %d\n", s->score, NUM_QUESTIONS);
    printf("Percentage  : %.2f%%\n", s->percentage);
    printf("Grade       : %s\n", s->grade);
    printf("Result      : %s\n", (s->percentage >= 50) ? "PASS" : "FAIL");
    printf("===================================\n");
}

/* Shows a class summary table for all students evaluated */
void displaySummary(const struct Student list[], int count)
{
    int   i, passed = 0, topIndex = 0;
    float total = 0;

    if (count == 0) return;

    printf("\n\n============ CLASS SUMMARY ============\n");
    printf("%-6s %-20s %-6s %-8s %-5s\n", "Roll", "Name", "Score", "Percent", "Grade");
    printf("---------------------------------------------\n");

    for (i = 0; i < count; i++) {
        printf("%-6d %-20s %-6d %-8.2f %-5s\n",
               list[i].rollNo, list[i].name, list[i].score,
               list[i].percentage, list[i].grade);

        total += list[i].percentage;
        if (list[i].percentage >= 50) passed++;
        if (list[i].score > list[topIndex].score) topIndex = i;
    }

    printf("---------------------------------------------\n");
    printf("Students evaluated : %d\n", count);
    printf("Students passed    : %d\n", passed);
    printf("Class average      : %.2f%%\n", total / count);
    printf("Topper             : %s (%.2f%%)\n",
           list[topIndex].name, list[topIndex].percentage);
}