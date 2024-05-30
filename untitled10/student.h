#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Queue Queue;

#define CALCULATE_AVERAGE(student) (((student)->math_grade + (student)->physics_grade + (student)->chemistry_grade) / 3.0)

struct Student {
    char surname[50];
    char name[50];
    char gender[10];
    int age;
    char group[10];
    int math_grade;
    int physics_grade;
    int chemistry_grade;
    struct Student* next;
};

struct Student* create_student(const char* surname, const char* name, const char* gender, int age, const char* group, int math_grade, int physics_grade, int chemistry_grade);
void print_student(const struct Student* student);
void print_students_with_top_grades(const struct Student* students);
void print_all_students(const struct Student* students);
struct Student* add_student(struct Student* students, struct Student* new_student);
void load_students_from_file(const char* filename, Queue* queue);
void save_students_to_file(const char* filename, struct Student* students);
void add_students_to_queue_and_save(const char* filename, Queue* queue, struct Student* new_students);
void save_students_to_binary_file(const char* filename, Queue* queue);
void load_students_from_binary_file(const char* filename,Queue* queue);

#endif