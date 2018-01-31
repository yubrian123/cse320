#include <stdio.h>

int main(int argc, char** argv) {
  /*
  * Dummy values
  */
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
