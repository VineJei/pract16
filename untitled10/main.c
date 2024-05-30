#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "queue.h"

int main() {
    Queue* student_queue = create_queue();
    if (!student_queue) {
        fprintf(stderr, "Ошибка: не удалось создать очередь\n");
        return EXIT_FAILURE;
    }

    load_students_from_binary_file("students.dat", student_queue);

    struct Student* student1 = create_student("Ivanov", "Ivan", "Male", 20, "A1", 5, 4, 3);
    if (!student1) {
        fprintf(stderr, "Ошибка: не удалось создать студента Ivanov Ivan\n");
        free_queue(student_queue);
        return EXIT_FAILURE;
    }

    struct Student* student2 = create_student("Petrov", "Petr", "Male", 21, "B1", 4, 5, 4);
    if (!student2) {
        fprintf(stderr, "Ошибка: не удалось создать студента Petrov Petr\n");
        free(student1);
        free_queue(student_queue);
        return EXIT_FAILURE;
    }

    struct Student* student3 = create_student("Galich", "Nasty", "Female", 22, "C1", 3, 5, 5);
    if (!student3) {
        fprintf(stderr, "Ошибка: не удалось создать студента Galich Nasty\n");
        free(student1);
        free(student2);
        free_queue(student_queue);
        return EXIT_FAILURE;
    }

    add_students_to_queue_and_save("students.dat", student_queue, student1);
    add_students_to_queue_and_save("students.dat", student_queue, student2);
    add_students_to_queue_and_save("students.dat", student_queue, student3);

    printf("Студенты в очереди:\n");
    print_queue(student_queue);

    free_queue(student_queue);

    return 0;
}
