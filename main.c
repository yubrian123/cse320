#include <stdio.h>

typedef struct
 student_records{

 int id;
 char[10] first_name;
 char[10} last_name;
 float gpa;
 char[3} major;

 struct student_records* next;
}

int main(int argc, char** argv) {
  /*
  * Dummy values
  */

  student_record* head;
  int id = 1;
  char* first_name = "Sergey";
  char* last_name = "Madaminov";
  float gpa = 3.41;
  char* major = "CSE";
  /*
  * This formatting for the string
  * that you are expected to follow
  */
  printf("%d %s %s %.2f %s\n", id, first_name, last_name, gpa, major);
  return 0;
}
