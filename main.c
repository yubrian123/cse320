#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

typedef struct
 student_records{

 int id;
 char* first_name;
 char* last_name;
 float gpa;
 char* major;

 struct student_records* next;
}student_records;

student_records* create(int id, char* first_name, char* last_name, float gpa, char* major){
        student_records* new_student_records = (student_records*)malloc(sizeof(student_records));
        if(new_student_records == NULL)
        {
                printf("Error creating a new Student Record.\n");
                exit(0);
        }
        new_student_records->id = id;
        new_student_records->first_name = first_name;
        new_student_records->last_name = last_name;
        new_student_records->gpa = gpa;
        new_student_records->major = major;
        new_student_records->next = NULL;
        return new_student_records;
}

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
         char *temp = p;
         while(*temp!= '\0')
         {
                 c++;
                 temp++;
         }
         return c;
 }

 int checkIfAllInts(char *p)
 {
         int c = 0;
         char *temp = p;
         while(*temp != '\0')
         {
                 if((*temp < '0') || (*temp > '9'))
                 {
                         return c;
                 }
                 *temp++;
         }
         return 1;
 }

 int checkIfAllChars(char *p)
 {
         int c = 0;
         char* temp = p;
         while(*temp != '\0')
         {
                 if((*temp >= 'a') && (*temp <= 'z'))
                 {
                         temp++;
                 }
                 else if((*temp >= 'A' ) && (*temp <= 'Z'))
                         temp++;
                 else return c;
         }
         return 1;
 }

 int checkIfValidGPA(char *p)
 {
        int c = 0;
        char* temp = p;
        if((*temp <= '0') || (*temp >= '9'))
        {
                return c;
        }
        temp++;
        if(*temp != '.')
        {
                return c;
        }
        temp++;
        if((*temp <= '0') || (*temp >= '9'))
        {
                return c;
        }
        temp++;
        if((*temp <= '0') || (*temp >= '9'))
        {
                return c;
        }
        return 1;
 }

 int getValueOfId(char *p)
 {
   return atoi(p);
 }
 float getValueOfGPA(char *p)
 {
   return atof(p);
 }

 int compareStrings(char *stringOne, char *stringTwo)
 {
  char *stringOnePointer = stringOne;
  char *stringTwoPointer = stringTwo;
  if(getStringLength(stringOnePointer) == getStringLength(stringTwoPointer))
  {
    while(*stringOnePointer != '\0' && *stringTwoPointer != '\0')
    {
          if(*stringOnePointer != *stringTwoPointer)
          {
                  return 0;
          }
          stringOnePointer++;
          stringTwoPointer++;
   }
   return 1;
  }
  return 0;
}

void printCertainRecord(student_records* cursor)
{
    printf("%d %s %s %.2f %s\n", cursor->id, cursor->first_name, cursor->last_name, cursor->gpa, cursor->major);
}


void add(student_records* head, char* id, char* first_name, char* last_name, char* gpa, char* major)
{
    int valueOfID = getValueOfId(id);
    student_records* pointer = head;
    while(pointer != NULL)
    {
      if(pointer->id == valueOfID)
      {
        printf("ID NOT UNIQUE\n");
        exit(0);
      }
      pointer = pointer->next;
    }
    float valueOfGPA = getValueOfGPA(gpa);
    student_records* newStudentRecord = create(valueOfID, first_name, last_name, valueOfGPA, major);
    student_records* pointer2 = head;
    if(head == NULL)
    {
      head = newStudentRecord;
    }
    else
    {
      while(pointer2->next != NULL)
      {
        if((newStudentRecord->id > pointer2->id) && (newStudentRecord->id < pointer2->next->id))
        {
          newStudentRecord->next = pointer2->next;
          pointer2->next = newStudentRecord;
          return;
        }
        pointer2 = pointer2->next;
      }
      pointer2->next = newStudentRecord;
    }
}
void update(student_records* head, char* id, char* first_name, char* last_name, char* gpa, char* major)
{
    int valueOfID = getValueOfId(id);
    student_records* pointer = head;
    float valueOfGPA = getValueOfGPA(gpa);
    while(pointer != NULL)
    {
      if(pointer->id == valueOfID)
      {
        pointer->first_name = first_name;
        pointer->last_name = last_name;
        pointer->gpa = valueOfGPA;
        pointer->major = major;
        return;
      }
      pointer = pointer->next;
    }
    printf("STUDENT RECORD CANNOT BE DELETED NOR UPDATED\n");
    exit(0);
  }

  student_records* delete(student_records* head, char* id)
  {
    if(id == NULL)
    {
            printf("OTHER ERROR\n");
            exit(0);
    }
    int valueOfID = getValueOfId(id);
    if(valueOfID <= 0)
    {
            printf("OTHER ERROR\n");
            exit(0);
    }
    if(checkIfAllInts(id) == 0)
    {
            printf("OTHER ERROR\n");
            exit(0);
    }
    student_records* pointer2 = head;
    if(pointer2 == NULL)
    {
      printf("STUDENT RECORD CANNOT BE DELETED NOR UPDATED\n");
      exit(0);
    }
    if(pointer2->id == valueOfID)
    {
      if(pointer2->next == NULL)
      {
        head = NULL;
      }
      else
      {
        head = pointer2->next;
      }
      free(pointer2);
      return head;
    }
    while(pointer2->next != NULL)
    {
      if(pointer2->next->id == valueOfID)
      {
        student_records* temp = pointer2->next;
        if(pointer2->next->next != NULL)
        {
          pointer2->next = pointer2->next->next;
        }
        else
        {
          pointer2->next = NULL;
        }
        free(temp);
        return head;
      }
      pointer2 = pointer2->next;
    }
    printf("STUDENT RECORD CANNOT BE DELETED NOR UPDATED\n");
    exit(0);
  }

  void changeToCamelCase(char* string)
  {
    *string = toupper(*string);
    string++;
    while(*string != '\0')
    {
        *string = tolower(*string);
        string++;
    }
  }

  void makeMajorCaps(char* string)
  {
    *string = toupper(*string);
    string++;
    *string = toupper(*string);
    string++;
    *string = toupper(*string);
    string++;
  }
         int main(int argc, char** argv) {
           /*
           * Dummy values
           */
           student_records* head;

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
           int vFlag = 0;
           int iFlag = 0;
           int fFlag = 0;
           int mFlag = 0;
           int oFlag = 0;
           int size = 0;

           char* iArg = malloc(255);
           char* fArg = malloc(255);
           char* mArg = malloc(255);
           char* oArg = malloc(255);

           char* inputFile = *(argv +1);
           FILE *fp;
           fp = fopen(inputFile, "r");
           if(fp == NULL)
           {
              printf("FAILED TO PARSE FILE\n");
              exit(0);
           }

           if(access(inputFile, F_OK) == -1)
           {
             printf("FAILED TO PARSE FILE\n");
             exit(0);
           }

           char* lineByLine = malloc(255);
           char* command = malloc(255);
           char* readId = malloc(255);
           char* readFirst = malloc(255);
           char* readLast = malloc(255);
           char* readGPA = malloc(255);
           char* readMajor = malloc(255);
           char* deleteCommand = "DELETE";
           char* addCommand = "ADD";
           char* updateCommand = "UPDATE";

           while(fgets(lineByLine, 255, fp) != NULL)
           {
             command = malloc(255);
             readId = malloc(255);
             readFirst = malloc(255);
             readLast = malloc(255);
             readGPA = malloc(255);
             readMajor = malloc(255);
             sscanf(lineByLine, "%s %s %s %s %s %s", command, readId, readFirst, readLast, readGPA, readMajor);
             if(compareStrings(addCommand, command) == 1)
             {
                 if(readId == NULL || readFirst == NULL || readLast == NULL || readGPA == NULL || readMajor == NULL)
                 {
                         free(lineByLine);
                         free(command);
                         free(readId);
                         free(readFirst);
                         free(readLast);
                         free(readGPA);
                         free(readMajor);
                         fclose(fp);
                         printf("FAILED TO PARSE FILE\n");
                         exit(0);
                 }
                 //check if valid id
                 int valueOfID = getValueOfId(readId);
                 if(valueOfID <= 0)
                 {
                         free(lineByLine);
                         free(command);
                         free(readId);
                         free(readFirst);
                         free(readLast);
                         free(readGPA);
                         free(readMajor);
                         fclose(fp);
                         printf("FAILED TO PARSE FILE\n");
                         exit(0);
                 }
                 if(checkIfAllInts(readId) == 0)
                 {
                         free(lineByLine);
                         free(command);
                         free(readId);
                         free(readFirst);
                         free(readLast);
                         free(readGPA);
                         free(readMajor);
                         fclose(fp);
                         printf("FAILED TO PARSE FILE\n");
                         exit(0);
                 }
                 //check if valid first name
                 int lengthOfFirstName = getStringLength(readFirst);
                 if(lengthOfFirstName > 10 || lengthOfFirstName < 3)
                 {
                         free(lineByLine);
                         free(command);
                         free(readId);
                         free(readFirst);
                         free(readLast);
                         free(readGPA);
                         free(readMajor);
                         fclose(fp);
                         printf("FAILED TO PARSE FILE\n");
                         exit(0);
                 }
                 if(checkIfAllChars(readFirst) == 0)
                 {
                         free(lineByLine);
                         free(command);
                         free(readId);
                         free(readFirst);
                         free(readLast);
                         free(readGPA);
                         free(readMajor);
                         fclose(fp);
                         printf("FAILED TO PARSE FILE\n");
                         exit(0);
                 }
                 //check if valid last name
                 int lengthOfLastName = getStringLength(readLast);
                 if(lengthOfLastName > 10 || lengthOfLastName < 3)
                 {
                         free(lineByLine);
                         free(command);
                         free(readId);
                         free(readFirst);
                         free(readLast);
                         free(readGPA);
                         free(readMajor);
                         fclose(fp);
                         printf("FAILED TO PARSE FILE\n");
                         exit(0);
                 }
                 if(checkIfAllChars(readLast) == 0)
                 {
                         free(lineByLine);
                         free(command);
                         free(readId);
                         free(readFirst);
                         free(readLast);
                         free(readGPA);
                         free(readMajor);
                         fclose(fp);
                         printf("FAILED TO PARSE FILE\n");
                         exit(0);
                 }
                 //check if gpa is valid
                 int lengthOfGPA = getStringLength(readGPA);
                 if(lengthOfGPA != 4)
                 {
                         free(lineByLine);
                         free(command);
                         free(readId);
                         free(readFirst);
                         free(readLast);
                         free(readGPA);
                         free(readMajor);
                         fclose(fp);
                         printf("FAILED TO PARSE FILE\n");
                         exit(0);
                 }
                 if(checkIfValidGPA(readGPA) == 0)
                 {
                         free(lineByLine);
                         free(command);
                         free(readId);
                         free(readFirst);
                         free(readLast);
                         free(readGPA);
                         free(readMajor);
                         fclose(fp);
                         printf("FAILED TO PARSE FILE\n");
                         exit(0);
                 }
                 //check if valid major
                 int lengthOfMajor = getStringLength(readMajor);
                 if(lengthOfMajor != 3)
                 {
                         free(lineByLine);
                         free(command);
                         free(readId);
                         free(readFirst);
                         free(readLast);
                         free(readGPA);
                         free(readMajor);
                         fclose(fp);
                         printf("FAILED TO PARSE FILE\n");
                         exit(0);
                 }
                 if(checkIfAllChars(readMajor) == 0)
                 {
                         free(lineByLine);
                         free(command);
                         free(readId);
                         free(readFirst);
                         free(readLast);
                         free(readGPA);
                         free(readMajor);
                         fclose(fp);
                         printf("FAILED TO PARSE FILE\n");
                         exit(0);
                 }
                 changeToCamelCase(readFirst);
                 changeToCamelCase(readLast);
                 makeMajorCaps(readMajor);
                 if(size == 0)
                 {
                    float valueOfGPA = getValueOfGPA(readGPA);
                    head = create(valueOfID, readFirst, readLast, valueOfGPA , readMajor);
                    size++;
                 }
                else
                {
                  add(head, readId, readFirst, readLast, readGPA, readMajor);
                  size++;
                }
                 }
                 else if(compareStrings(updateCommand, command) == 1)
                 {
                   if(readId == NULL || readFirst == NULL || readLast == NULL || readGPA == NULL || readMajor == NULL)
                   {
                           free(lineByLine);
                           free(command);
                           free(readId);
                           free(readFirst);
                           free(readLast);
                           free(readGPA);
                           free(readMajor);
                           fclose(fp);
                           printf("FAILED TO PARSE FILE\n");
                           exit(0);
                   }
                   //check if valid id
                   int valueOfID = getValueOfId(readId);
                   if(valueOfID <= 0)
                   {
                           free(lineByLine);
                           free(command);
                           free(readId);
                           free(readFirst);
                           free(readLast);
                           free(readGPA);
                           free(readMajor);
                           fclose(fp);
                           printf("FAILED TO PARSE FILE\n");
                           exit(0);
                   }
                   if(checkIfAllInts(readId) == 0)
                   {
                           free(lineByLine);
                           free(command);
                           free(readId);
                           free(readFirst);
                           free(readLast);
                           free(readGPA);
                           free(readMajor);
                           fclose(fp);
                           printf("FAILED TO PARSE FILE\n");
                           exit(0);
                   }
                   //check if valid first name
                   int lengthOfFirstName = getStringLength(readFirst);
                   if(lengthOfFirstName > 10 || lengthOfFirstName < 3)
                   {
                           free(lineByLine);
                           free(command);
                           free(readId);
                           free(readFirst);
                           free(readLast);
                           free(readGPA);
                           free(readMajor);
                           fclose(fp);
                           printf("FAILED TO PARSE FILE\n");
                           exit(0);
                   }
                   if(checkIfAllChars(readFirst) == 0)
                   {
                           free(lineByLine);
                           free(command);
                           free(readId);
                           free(readFirst);
                           free(readLast);
                           free(readGPA);
                           free(readMajor);
                           fclose(fp);
                           printf("FAILED TO PARSE FILE\n");
                           exit(0);
                   }
                   //check if valid last name
                   int lengthOfLastName = getStringLength(readLast);
                   if(lengthOfLastName > 10 || lengthOfLastName < 3)
                   {
                           free(lineByLine);
                           free(command);
                           free(readId);
                           free(readFirst);
                           free(readLast);
                           free(readGPA);
                           free(readMajor);
                           fclose(fp);
                           printf("FAILED TO PARSE FILE\n");
                           exit(0);
                   }
                   if(checkIfAllChars(readLast) == 0)
                   {
                           free(lineByLine);
                           free(command);
                           free(readId);
                           free(readFirst);
                           free(readLast);
                           free(readGPA);
                           free(readMajor);
                           fclose(fp);
                           printf("FAILED TO PARSE FILE\n");
                           exit(0);
                   }
                   //check if gpa is valid
                   int lengthOfGPA = getStringLength(readGPA);
                   if(lengthOfGPA != 4)
                   {
                           free(lineByLine);
                           free(command);
                           free(readId);
                           free(readFirst);
                           free(readLast);
                           free(readGPA);
                           free(readMajor);
                           fclose(fp);
                           printf("FAILED TO PARSE FILE\n");
                           exit(0);
                   }
                   if(checkIfValidGPA(readGPA) == 0)
                   {
                           free(lineByLine);
                           free(command);
                           free(readId);
                           free(readFirst);
                           free(readLast);
                           free(readGPA);
                           free(readMajor);
                           fclose(fp);
                           printf("FAILED TO PARSE FILE\n");
                           exit(0);
                   }
                   //check if valid major
                   int lengthOfMajor = getStringLength(readMajor);
                   if(lengthOfMajor != 3)
                   {
                           free(lineByLine);
                           free(command);
                           free(readId);
                           free(readFirst);
                           free(readLast);
                           free(readGPA);
                           free(readMajor);
                           fclose(fp);
                           printf("FAILED TO PARSE FILE\n");
                           exit(0);
                   }
                   if(checkIfAllChars(readMajor) == 0)
                   {
                           printf("FAILED TO PARSE FILE\n");
                           exit(0);
                   }
                   changeToCamelCase(readFirst);
                   changeToCamelCase(readLast);
                   makeMajorCaps(readMajor);
                   update(head, readId, readFirst, readLast, readGPA, readMajor);
                 }
                 else if(compareStrings(deleteCommand, command) == 1)
                 {
                   int valueOfID = getValueOfId(readId);
                   if(valueOfID <= 0)
                   {
                           free(lineByLine);
                           free(command);
                           free(readId);
                           free(readFirst);
                           free(readLast);
                           free(readGPA);
                           free(readMajor);
                           fclose(fp);
                           printf("FAILED TO PARSE FILE\n");
                           exit(0);
                   }
                   if(checkIfAllInts(readId) == 0)
                   {
                           free(lineByLine);
                           free(command);
                           free(readId);
                           free(readFirst);
                           free(readLast);
                           free(readGPA);
                           free(readMajor);
                           fclose(fp);
                           printf("FAILED TO PARSE FILE\n");
                           exit(0);
                   }
                   head = delete(head, readId);
                   size++;
                 }
                 else
                {
                  printf("FAILED TO PARSE FILE\n");
                  exit(0);
                }
          }
          free(lineByLine);
          free(command);
          free(readId);
          free(readFirst);
          free(readLast);
          free(readGPA);
          free(readMajor);
          fclose(fp);

           while((c = getopt(argc, argv, "vi:f:m:o:")) != -1)
           {
                 if(c == 'v'){
                        vFlag++;
                 }
                 else if(c == 'i'){
                         iFlag++;
                         iArg = optarg;
                         if(iArg == NULL)
                         {
                                 printf("OTHER ERROR\n");
                                 exit(0);
                         }
                         printId = getValueOfId(iArg);
                         if(printId <= 0)
                         {
                                 printf("OTHER ERROR\n");
                                 exit(0);
                         }
                         else if(checkIfAllInts(iArg) == 0)
                         {
                                 printf("OTHER ERROR\n");
                                 exit(0);
                         }
                 }
                 else if(c == 'f'){
                         fFlag++;
                         fArg = optarg;
                         if(fArg == NULL)
                         {
                                 printf("OTHER ERROR\n");
                                 exit(0);
                         }
                         lengthOfLastName = getStringLength(fArg);
                         if(lengthOfLastName > 10 || lengthOfLastName < 3)
                         {
                                 printf("OTHER ERROR\n");
                                 exit(0);
                         }
                         else if(checkIfAllChars(fArg) == 0)
                         {
                                 printf("OTHER ERROR\n");
                                 exit(0);
                         }
                 }
                 else if(c == 'm'){
                         mArg = optarg;
                         mFlag++;
                         if(mArg == NULL)
                         {
                                 printf("OTHER ERROR\n");
                                 exit(0);
                         }
                         lengthOfMajor = getStringLength(mArg);
                         if(lengthOfMajor != 3)
                         {
                                 printf("OTHER ERROR\n");
                                 exit(0);
                         }
                         else if(checkIfAllChars(mArg) == 0)
                         {
                                 printf("OTHER ERROR\n");
                                 exit(0);
                         }
                  }
                  else if(c == 'o'){
                         oFlag++;
                         oArg = optarg;
                         if(oArg == NULL)
                         {
                           printf("OTHER ERROR\n");
                           exit(0);
                         }
                         if(access(oArg, F_OK) != -1)
                         {
                             char* prompt = malloc(255);
                             FILE *oFile;
                             oFile = fopen(oArg, "r");
                             if(oFile != NULL)
                             {
                               printf ("File Exist, Are You Sure You Want To Overwrite it? (y/n) \n");
                               scanf ("%s", prompt);
                               if(*prompt == 'n')
                               {
                                 printf("FILE EXIST\n");
                                 exit(0);
                               }
                             }
                             fclose(oFile);
                        }

                  }
   }

   if(vFlag == 0 && fFlag == 0 && mFlag == 0 && oFlag == 0 && iFlag == 0)
   {
     printf("NO QUERY PROVIDED\n");
     exit(0);
   }

   if(iFlag == 0 && vFlag == 0 && fFlag == 0 && mFlag == 0 && oFlag ==1)
   {
     printf("OTHER ERROR\n");
     exit(0);
   }

   if(vFlag == 1)
   {
     if(iFlag == 1)
     {
       printf("OTHER ERROR\n");
       exit(0);
     }
     else if(fFlag == 1)
     {
       printf("OTHER ERROR\n");
       exit(0);
     }
     else if(mFlag == 1)
     {
       printf("OTHER ERROR\n");
       exit(0);
     }
     else if(oFlag == 1)
     {
       printAll(head);
       student_records* pointer = head;
       FILE *file_pointer;
       file_pointer = fopen(oArg, "w");
       while(pointer != NULL)
       {
         fprintf(file_pointer, "%d %s %s %.2f %s\n", pointer->id, pointer->first_name, pointer->last_name, pointer->gpa, pointer->major);
         pointer = pointer->next;
       }
       fclose(file_pointer);
     }
     else
        printAll(head);
        exit(0);
    }

    else if(oFlag == 1)
    {
      FILE *file_pointer;
      file_pointer = fopen(oArg, "w");
      student_records* pointer = head;
      if(iFlag == 1 &&fFlag == 1 && mFlag ==1)
      {
        makeMajorCaps(mArg);
        changeToCamelCase(fArg);
        while(pointer != NULL)
        {
          if(pointer->id == getValueOfId(iArg))
          {
            if((compareStrings(pointer->last_name, fArg) == 1) && (compareStrings(pointer->major, mArg) == 1))
            {
                fprintf(file_pointer, "%d %s %s %.2f %s\n", pointer->id, pointer->first_name, pointer->last_name, pointer->gpa, pointer->major);
                fclose(file_pointer);
                printCertainRecord(pointer);
                exit(0);
            }
          }
          pointer = pointer->next;
        }
      }
        else if(iFlag == 1 && fFlag == 1)
        {
          changeToCamelCase(fArg);
          while(pointer != NULL)
          {
            if(pointer->id == getValueOfId(iArg))
            {
              if(compareStrings(pointer->last_name, fArg) == 1)
              {
                  fprintf(file_pointer, "%d %s %s %.2f %s\n", pointer->id, pointer->first_name, pointer->last_name, pointer->gpa, pointer->major);
                  fclose(file_pointer);
                  printCertainRecord(pointer);
                  exit(0);
              }
            }
            pointer = pointer->next;
          }
        }
        else if (iFlag == 1 && mFlag == 1)
        {
          makeMajorCaps(mArg);
          while(pointer != NULL)
          {
            if(pointer->id == getValueOfId(iArg))
            {
              if(compareStrings(pointer->major, mArg) == 1)
              {
                  fprintf(file_pointer, "%d %s %s %.2f %s\n", pointer->id, pointer->first_name, pointer->last_name, pointer->gpa, pointer->major);
                  fclose(file_pointer);
                  printCertainRecord(pointer);
                  exit(0);
              }
            }
            pointer = pointer->next;
          }
        }
        else if(fFlag == 1 && mFlag == 1)
        {
          makeMajorCaps(mArg);
          changeToCamelCase(fArg);
          int printedFM;
          while(pointer != NULL)
          {
            if((compareStrings(pointer->last_name, fArg) == 1) && (compareStrings(pointer->major, mArg) == 1))
            {
                printedFM = 1;
                fprintf(file_pointer, "%d %s %s %.2f %s\n", pointer->id, pointer->first_name, pointer->last_name, pointer->gpa, pointer->major);
                printCertainRecord(pointer);
            }
            pointer = pointer->next;
          }
          if(printedFM != 1)
          {
            printf("STUDENT RECORD NOT FOUND\n");
          }
          fclose(file_pointer);
          exit(0);
        }
        else if(iFlag == 1)
        {
          while(pointer != NULL)
          {
            if(pointer->id = getValueOfId(iArg))
            {
              printCertainRecord(pointer);
              exit(0);
            }
            pointer = pointer->next;
          }
          printf("STUDENT RECORD NOT FOUND\n");
        }
        else if(fFlag == 1)
        {
          changeToCamelCase(fArg);
          int printedFM;
          while(pointer != NULL)
          {
            if(compareStrings(pointer->last_name, fArg) == 1)
            {
                printedFM = 1;
                fprintf(file_pointer, "%d %s %s %.2f %s\n", pointer->id, pointer->first_name, pointer->last_name, pointer->gpa, pointer->major);
                printCertainRecord(pointer);
            }
            pointer = pointer->next;
          }
          if(printedFM != 1)
          {
            printf("STUDENT RECORD NOT FOUND\n");
          }
          fclose(file_pointer);
          exit(0);
        }
        else if(mFlag == 1)
        {
          makeMajorCaps(mArg);
          int printedFM;
          while(pointer != NULL)
          {
            if(compareStrings(pointer->major, mArg) == 1)
            {
                printedFM = 1;
                fprintf(file_pointer, "%d %s %s %.2f %s\n", pointer->id, pointer->first_name, pointer->last_name, pointer->gpa, pointer->major);
                printCertainRecord(pointer);
            }
            pointer = pointer->next;
          }
          if(printedFM != 1)
          {
            printf("STUDENT RECORD NOT FOUND\n");
          }
          fclose(file_pointer);
          exit(0);
        }
      }
    else if(iFlag == 1)
    {
      if(fFlag == 1 && mFlag ==1)
      {
          makeMajorCaps(mArg);
          changeToCamelCase(fArg);
          student_records* pointer = head;
          while(pointer != NULL)
          {
            if(pointer->id == getValueOfId(iArg))
            {
              if((compareStrings(pointer->last_name, fArg) == 1) && (compareStrings(pointer->major, mArg) == 1))
              {
                  printCertainRecord(pointer);
                  exit(0);
              }
            }
            pointer = pointer->next;
          }
          printf("STUDENT RECORD NOT FOUND\n");
      }
      else if(fFlag == 1)
      {
        changeToCamelCase(fArg);
        student_records* pointer = head;
        while(pointer != NULL)
        {
          if(pointer->id == getValueOfId(iArg))
          {
            if(compareStrings(pointer->last_name, fArg) == 1)
            {
                printCertainRecord(pointer);
                exit(0);
            }
          }
          pointer = pointer->next;
        }
        printf("STUDENT RECORD NOT FOUND\n");
        exit(0);
      }
      else if(mFlag == 1)
        {
          student_records* pointer = head;
          makeMajorCaps(mArg);
          while(pointer != NULL)
          {
            if(pointer->id == getValueOfId(iArg))
            {
              if(compareStrings(pointer->major, mArg) == 1)
              {
                  printCertainRecord(pointer);
                  exit(0);
              }
            }
            pointer = pointer->next;
          }
          printf("STUDENT RECORD NOT FOUND\n");
          exit(0);
        }
        else
        {
          student_records* pointer = head;
          while(pointer != NULL)
          {
            if(pointer->id == getValueOfId(iArg))
            {
                printCertainRecord(pointer);
                exit(0);
            }
            pointer = pointer->next;
          }
          printf("STUDENT RECORD NOT FOUND\n");
          exit(0);
        }
      }
      else if(fFlag == 1 && mFlag == 1)
      {
        makeMajorCaps(mArg);
        changeToCamelCase(fArg);
        student_records* pointer = head;
        int printedFM;
        while(pointer != NULL)
        {
            if((compareStrings(pointer->last_name, fArg) == 1) && (compareStrings(pointer->major, mArg) == 1))
            {
                printedFM = 1;
                printCertainRecord(pointer);
            }
            pointer = pointer->next;
        }
        if(printedFM != 1)
        {
          printf("STUDENT RECORD NOT FOUND\n");
        }
        exit(0);
      }
      else if(fFlag == 1)
      {
        student_records* pointer = head;
        changeToCamelCase(fArg);
        int printedF;
        while(pointer != NULL)
        {
          if(compareStrings(pointer->last_name, fArg) == 1)
          {
              printedF = 1;
              printCertainRecord(pointer);
          }
          pointer = pointer->next;
        }
        if(printedF != 1)
        {
          printf("STUDENT RECORD NOT FOUND\n");
        }
        exit(0);
      }
      else if(mFlag == 1)
      {
        student_records* pointer = head;
        makeMajorCaps(mArg);
        int printedM;
        while(pointer != NULL)
        {
          if(compareStrings(pointer->major, mArg) == 1)
          {
              printedM = 1;
              printCertainRecord(pointer);
          }
          pointer = pointer->next;
        }
        if(printedM != 1)
        {
          printf("STUDENT RECORD NOT FOUND\n");
        }
        exit(0);
      }
   return 0;
 }

