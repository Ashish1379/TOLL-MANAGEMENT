#include <stdio.h>
#include <time.h>
#include <string.h>

typedef struct Toll_Managment
{
  char time[40];
  char name[30];          // name of owner
  char vehiclenumber[15]; // number plate data of vehicle
  char dateofreg[20];     // date of registration
  char vehmodel[20];      // vehicle model
  char toll[20];
} T_Managment;
T_Managment size[15];

void display_a_record() // this module will display record of that person whose vehicles vehicle number will be enterd.
{
  FILE *ptr;
  ptr = fopen("toll data.txt", "r");

  char search[10];
  printf("Enter vehicle number to search: ");
  scanf("%s", &search);
  int flag = 0;

  while (fread(&size, sizeof(T_Managment), 1, ptr))
  {

    if (strcmp(search, size->vehiclenumber) == 0)
    {

      flag = 1;
      printf("%-20s%-20s%-30s%-20s%-20s%s", "owner name", "Vehicle number", "Date of registration", "Vehicle model", "Amount paid", "Timing", "\n");
      printf("\n%-20s%-20s%-30s%-20s%-20s%s", size->name, size->vehiclenumber, size->dateofreg, size->vehmodel, size->toll, size->time, "\n\n");
      return;
    }
  }
  if (flag == 0)
  {
    printf("_____________________________\n");
    printf("   Enter Valid Credentials\n");
    printf("_____________________________\n\n");
  }

  fclose(ptr);
}

void addnew() // this module will add new record to database
{
  int stat;
  time_t ltime;
  time(&ltime);
  FILE *ptr;
  ptr = fopen("toll data.txt", "a");

  printf("\n\n===========WELCOME TO ADDING SECTION===========\n\n");
  printf("Enter name of owner : ");
  scanf("%s", size[0].name);

  printf("Enter vehicle number(number plate) : ");
  scanf("%s", size[0].vehiclenumber);

  printf("Enter date of registration (dd/mm/yyyy) : ");
  scanf("%s", size[0].dateofreg);

  printf("Enter model of vehicle : ");
  scanf("%s", size[0].vehmodel);

  printf("Enter amount to be paid : ");
  scanf("%s", size[0].toll);

  strcpy(size[0].time, ctime(&ltime));
  fwrite(&size[0], sizeof(T_Managment), 1, ptr);
  fclose(ptr);

  printf("\n-------!!!!!ADDED SUCCESSFULLY!!!!!-------\n");
  printf("\nFor adding more press 1 or Press 0 for exit\n");
  scanf("%d", &stat);
  if (stat == 0)
  {
    printf("\n");
  }
  else
    addnew();
}

void display_all_record() // this module will display all the records present in database
{
  FILE *ptr;
  ptr = fopen("toll data.txt", "r");
  if (fread(&size, sizeof(T_Managment), 1, ptr) == NULL)
  {
    printf("\n----------------NO RECORDS TO DISPLAY----------------\n");
  }
  else
  {
    printf("========================= ALL RECORDS =========================\n\n");
    printf("%-20s%-20s%-30s%-20s%-20s%s", "owner name", "Vehicle number", "Date of registration", "Vehicle model", "Amount paid", "Timing", "\n\n");
    while (fread(&size, sizeof(T_Managment), 1, ptr))
    {
      printf("\n%-20s%-20s%-30s%-20s%-20s%s", size->name, size->vehiclenumber, size->dateofreg, size->vehmodel, size->toll, size->time, "\n\n");
    }
  }
}

void erase() // this module will clear whole data in database
{
  FILE *ptr;
  ptr = fopen("toll data.txt", "w+");
  fprintf(ptr, "%s", "");
  printf("\n----------CLEANED SUCCESSFULLY-----------\n");
}

void delete_a_record() // this module will delete record of particular vehicle number entered
{
  FILE *ptr;
  ptr = fopen("toll data.txt", "r");
  FILE *ptr2;
  ptr2 = fopen("toll data1.txt", "w");

  char search[100];
  printf("Enter vehicle number to delete : ");
  scanf("%s", &search);
  int flag = 0;

  while (fread(&size, sizeof(T_Managment), 1, ptr))
  {
    if (strcmp(search, size->vehiclenumber) == 0)
    {
      flag = 1;
    }
    else
    {
      fwrite(&size, sizeof(T_Managment), 1, ptr2);
    }
  }

  fclose(ptr);
  fclose(ptr2);
  if (flag == 1)
  {
    ptr2 = fopen("toll data1.txt", "r");
    ptr = fopen("toll data.txt", "w");
    while (fread(&size, sizeof(T_Managment), 1, ptr2))
    {
      fwrite(&size, sizeof(T_Managment), 1, ptr);
    }
    fclose(ptr);
    fclose(ptr2);
    printf("\n________________________\n");
    printf("  DELETED SUCCESSFULLY\n");
    printf("________________________\n");
  }
  else
  {
    printf("NOT FOUND\n");
  }
}

void update() // this module will update record of the enterd vehicle number
{
  time_t ltime;
  time(&ltime);

  FILE *ptr;
  ptr = fopen("toll data.txt", "r");
  FILE *ptr2;
  ptr2 = fopen("toll data1.txt", "w");

  char search[100];
  printf("Enter vehicle number to update : ");
  scanf("%s", &search);
  int flag = 0;

  while (fread(&size, sizeof(T_Managment), 1, ptr))
  {
    if (strcmp(search, size->vehiclenumber) == 0)
    {
      flag = 1;
      printf("\n\n===========WELCOME TO UPDATE SECTION===========\n\n");
      printf("Enter name of owner : ");
      scanf("%s", size[0].name);

      printf("Enter updated vehicle number(number plate) : ");
      scanf("%s", size[0].vehiclenumber);

      printf("Enter new date of registration (dd/mm/yyyy) : ");
      scanf("%s", size[0].dateofreg);

      printf("Enter new model of vehicle : ");
      scanf("%s", size[0].vehmodel);

      strcpy(size[0].time, ctime(&ltime));
    }
    fwrite(&size, sizeof(T_Managment), 1, ptr2);
  }
  fclose(ptr);
  fclose(ptr2);
  if (flag == 0)
  {
    printf("__________________________");
    printf("\nNOT FOUND\n");
  }
  else
  {
    ptr2 = fopen("toll data1.txt", "r");
    ptr = fopen("toll data.txt", "w");
    while (fread(&size, sizeof(T_Managment), 1, ptr2))
    {
      fwrite(&size, sizeof(T_Managment), 1, ptr);
    }
    fclose(ptr);
    fclose(ptr2);
    printf("__________________________\n");
    printf("   UPDATED SUCCESSFULLY\n");
    printf("__________________________\n");
  }
}

int main()
{
  int run, who;
  printf("______________________________________________________________________________________________________\n\n");
  printf("----------------------------------WELCOME TO TOLL MANAGMENT SYSTEM------------------------------------\n");
  printf("______________________________________________________________________________________________________\n\n");
  do
  {
    printf("\n=======================================================================================================");
    printf("\n_____________________________\n");
    printf("  ^_^ PERFORMABLE TASKS ^_^\n");
    printf("_____________________________\n");
    printf("\n1.ADD NEW RECORD\n2.DISPLAY ALL RECORD\n3.ERASE ALL RECORD\n4.UPDATE RECORD\n5.DELETE AN EXISTING RECORD\n6.SEARCH A RECORD\n7.EXIT FROM SYSTEM\n\n");

    printf("<----excecution code---->\nENTER HERE : ");
    scanf("%d", &run);
    printf("\n");
    if (run >= 7)
    {
      printf("THANK YOU VISIT AGAIN!!!");
      break;
    }
    switch (run)
    {
    case 1:
      addnew();
      break;
    case 2:
      display_all_record();
      break;
    case 3:
      erase();
      break;
    case 4:
      update();
      break;
    case 5:
      delete_a_record();
      break;
    case 6:
      display_a_record();
      break;
    }
  } while (run != 7);

}