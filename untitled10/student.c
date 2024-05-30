#include "student.h"
#include "queue.h"

struct Student* create_student(const char* surname, const char* name, const char* gender, int age, const char* group, int math_grade, int physics_grade, int chemistry_grade) {
    struct Student* student = (struct Student*)malloc(sizeof(struct Student));
    if (student) {
        strncpy(student->surname, surname, 50);
        strncpy(student->name, name, 50);
        strncpy(student->gender, gender, 10);
        student->age = age;
        strncpy(student->group, group, 10);
        student->math_grade = math_grade;
        student->physics_grade = physics_grade;
        student->chemistry_grade = chemistry_grade;
        student->next = NULL;
    }
    return student;
}

void print_student(const struct Student* student) {
    printf("Surname: %s\nName: %s\nGender: %s\nAge: %d\nGroup: %s\nMath Grade: %d\nPhysics Grade: %d\nChemistry Grade: %d\n",
           student->surname, student->name, student->gender, student->age, student->group, student->math_grade, student->physics_grade, student->chemistry_grade);
}

void print_students_with_top_grades(const struct Student* students) {
    while (students != NULL) {
        if (strcmp(students->gender, "female") == 1 && students->physics_grade == 5 && students->chemistry_grade == 5) {
            print_student(students);
        }
        students = students->next;
    }
}

void print_all_students(const struct Student* students) {
    while (students != NULL) {
        print_student(students);
        students = students->next;
    }
}

struct Student* add_student(struct Student* students, struct Student* new_student) {
    if (!students) {
        return new_student;
    }
    struct Student* current = students;
    while (current->next) {
        current = current->next;
    }
    current->next = new_student;
    return students;
}

void load_students_from_file(const char* filename, struct Queue* queue) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file for reading");
        return;
    }

    char surname[50], name[50], gender[10], group[10];
    int age, math_grade, physics_grade, chemistry_grade;
    while (fscanf(file, "%49s %49s %9s %d %9s %d %d %d", surname, name, gender, &age, group, &math_grade, &physics_grade, &chemistry_grade) == 8) {
        struct Student* student = create_student(surname, name, gender, age, group, math_grade, physics_grade, chemistry_grade);
        enqueue(queue, student);
    }

    fclose(file);
}

void save_students_to_file(const char* filename, struct Student* students) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Could not open file for writing");
        return;
    }

    struct Student* current = students;
    while (current) {
        fprintf(file, "%s %s %s %d %s %d %d %d\n", current->surname, current->name, current->gender, current->age, current->group, current->math_grade, current->physics_grade, current->chemistry_grade);
        current = current->next;
    }

    fclose(file);
}

void add_students_to_queue_and_save(const char* filename, struct Queue* queue, struct Student* new_students) {
    enqueue(queue, new_students);
    save_students_to_binary_file(filename, queue);
}

void save_students_to_binary_file(const char* filename, struct Queue* queue) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Could not open file for writing");
        return;
    }

    struct QueueNode* current = queue->front;
    while (current != NULL) {
        fwrite(current->student, sizeof(struct Student), 1, file);
        current = current->next;
    }

    fclose(file);
}

void load_students_from_binary_file(const char* filename, struct Queue* queue) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Could not open file for reading");
        return;
    }

    struct Student temp;
    while (fread(&temp, sizeof(struct Student), 1, file)) {
        struct Student* student = create_student(temp.surname, temp.name, temp.gender, temp.age, temp.group, temp.math_grade, temp.physics_grade, temp.chemistry_grade);
        enqueue(queue, student);
    }

    fclose(file);
}
