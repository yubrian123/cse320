#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
 student_records{

 int id;
 char* first_name;
 char* last_name;
 float gpa;
 char* major;

 struct student_records* next;
}student_records;

student_records* create(student_records* next, int id,
char* first_name, char* last_name, float gpa, char* major){
        student_records* new_student_records = (student_records*)malloc(sizeof(student_records));
        new_student_records->id = id;
        new_student_records->first_name = first_name;
        new_student_records->last_name = last_name;
        new_student_records->gpa = gpa;
        new_student_records->major = major;
        if(next == NULL)
        {
                new_student_records->next = NULL;
        }
        else
        {
                new_student_records->next = NULL;
        }
        return new_student_records;
}

/*student_records* add(student_records* head, int id,
char* first_name, char* last_name, float gpa, char* major){
        if(id < 0)
                return

        student_records* cursor = head;
        while(cursor != null)
        {
                if(cursor->id = id){
                        printf("ID NOT UNIQUE");
                        return
                }

        }
        student_records* new_student_records = create(id, first_name, last_name, gpa, major);

}*/
void printAll(student_records* head)
{
        student_records* cursor = head;
        while(cursor != NULL)
        {
                 printf("%d %s %s %.2f %s\n", cursor->id, cursor->first_name, cursor->last_name, cursor->gpa, cursor->major);
                cursor = cursor->next;
        }
}

int getStringLength(char *p)
{
        int c=0;
        while(*p!= '\0')
        {
                c++;
                *p++;
        }
        return c;
}

int getValueOfId(char *p)
{
	int i = 0, len, j;
	len = getStringLength(p);
	if(*p == '-')
	{
		return -1;
	}
	if(*p == '0')
	{
		return 0;
	}
	while(*p!= '\0')
	{
		j = j * 10 +(*p - '0');
		*p++;
	}
	return j;
}

void printByID(student_records* head, int id)
{
        student_records* cursor = head;
	int ifprinted = 0;
        while(cursor != NULL)
        {
                if(cursor->id == id){
                	 printf("%d %s %s %.2f %s\n", cursor->id, cursor->first_name, cursor->last_name, cursor->gpa, cursor->major);
			ifprinted++;
                }
                cursor = cursor->next;
        }
	if(ifprinted == 0){
		printf("STUDENT RECORDS NOT FOUND \n");
	}
}

void printByLastName(student_records* head, char *p)
{
	printf("print by last name");
}

void printByMajor(student_records* head, char *p)
{
        printf("print by major");
}

int main(int argc, char** argv) {
  /*
  * Dummy values
  */

  student_records* next = NULL;
  int id = 1;
  char* first_name = "Sergey";
  char* last_name = "Madaminov";
  float gpa = 3.41;
  char* major = "CSE";
  student_records* head = create(next, id, first_name, last_name, gpa, major);

  student_records* next1 = NULL;
  int id1 = 2;
  char* first_name1 = "Se2rgey";
  char* last_name1 = "Mada2minov";
  float gpa1 = 3.411;
  char* major1 = "C1SE";
  student_records* head1 = create(next1, id1, first_name1, last_name1, gpa1, major1);
  head->next = head1;

  /*
  * This formatting for the string
  * that you are expected to follow
  */

  int c;
  char *cvalue = NULL;
  int valueOfID;
  int printId;
  int lengthOfLastName;
  int lengthOfMajor;

  while((c = getopt(argc, argv, "vi:f:m:o:")) != -1)
  {
        if(c == 'v'){
                printAll(head);
        }
        else if(c == 'i'){
                cvalue = optarg;
                printId = getValueOfId(cvalue);
		if(printId <= 0)
			printf("OTHER ERROR");
		else
                	printByID(head, printId);
        }
        else if(c == 'f'){
		cvalue = optarg;
		lengthOfLastName = getStringLength(cvalue);
		if(lengthOfLastName > 10 || lengthOfLastName < 3)
			printf("OTHER ERROR");
		else
                	printByLastName(head, cvalue);
        }
        else if(c == 'm'){
                cvalue = optarg;
		lengthOfMajor = getStringLength(cvalue);
                if(lengthOfMajor != 3)
                        printf("OTHER ERROR");
                else
                	printByMajor(head, cvalue);
        }
        else if(c == 'o'){
                printf("WE GOT A O");
        }
	else
		printf("NO QUERY PROVIDED \n");
  }
  return 0;
}

