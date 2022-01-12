#include<stdio.h>
#include<string.h>
struct student{
  char name[50];
  int rollNo;
  float sub[5];
  float total;
  char dep[30];
  int sem;
  char subName[5][30];
  char result[4];
  float average;
  char grade;
};

char calculateGrade(float);
void getstu(struct student *s);
int fileEmpty();
void displayRecord();
void createRecord();
int checkRoll(int);
void deleteRecord();

char calculateGrade(float average){
  if(average>=90)
    return 'A';
  else if(average>=70)
    return 'B';
  else if(average>=50)
    return 'C';
  else
    return 'F';
}


void getstu(struct student *s){
  int total=0,no;
  fflush(stdin);
  printf("ENTER THE STUDENT NAME:");
  scanf("%s",&s->name);
  printf("ENTER THE DEPARTMENT NAME:");
  scanf("%s",&s->dep);
  printf("ENTER THE CURRENT SEM:");
  scanf("%d",&s->sem);
  printf("ENTER THE SUBJECT ENROLLED:\n");
  for(int i=0;i<3;i++){
    printf("SUBJECT %d:",i+1);
    scanf("%s",&s->subName[i]);
  }
  printf("ENTER THE MARKS SUBJECTWISE:\n");
  for(int i=0;i<3;i++){
    printf("%s:",s->subName[i]);
    scanf("%f",&s->sub[i]);
    total+=s->sub[i];
  }
  s->total=total;
  s->average=s->total/3;
  s->grade=calculateGrade(s->average);
  if(s->grade=='F')
    strcpy(s->result,"FAIL");
  else
    strcpy(s->result,"PASS");
}


int fileEmpty(){
  FILE *file;
  int flag=0;
  file=fopen("student.txt","r");
  if(file==NULL)
  {
    printf("ERROR,FILE CANNOT BE OPENED!!!\n");
    return 0;
  }
  struct student stu;
  while(fread(&stu,sizeof(stu),1,file))
    flag=1;
  fclose(file);
  if (flag==0)
    printf("FILE IS EMPTY\n");
  return flag;
}

void display(struct student stu,int j){
  printf("%d\t%d\t\t%s\t%s\t%d\tSUBJECT NAME\tMARKS\t %.1f\t  %.1f\t  %c\t %s\n",j,stu.rollNo,stu.name,stu.dep,stu.sem,stu.total,stu.average,stu.grade,stu.result);
  for(int i=0;i<3;i++)
  {
    printf("\t\t\t\t \t\t%s       \t%.1f\n",stu.subName[i],stu.sub[i]);
  }
  printf("\n=========================================================================================================\n");
}


void displayRecord(){
  struct student stu;
  if(!fileEmpty())
    return;
  FILE *file;
  file=fopen("student.txt","r");
  if(file==NULL)
  {
    printf("ERROR,FILE CANNOT BE OPENED!!!\n");
    return;
  }
  int j=1;
  printf("\n=========================================================================================================\n");
  printf("S.NO\tROLLNUMBER\tNAME\tDEP\tSEM\t\tSUBJECT\t\tTOTAL\tAVERAGE\tGRADE\tRESULT\n");
  printf("\n=========================================================================================================\n");
  while(fread(&stu,sizeof(stu),1,file))
  {
      display(stu,j);
      j++;
  }
  fclose(file);
}


void createRecord(){
  int n,i;
  printf("ENTER THE NUMBER OF STUDENTS:");
  scanf("%d",&n);
  struct student s[n];
  FILE *file;
  file=fopen("student.txt","w");
  for(i=0;i<n;i++)
  {
    int no;
    printf("STUDENT %d:\n",i+1);
    printf("ENTER THE ROLL NUMBER:");
    scanf("%d",&no);
    if(checkRoll(no))
      return;
    s[i].rollNo=no;
    getstu(&s[i]);
    printf("\n");
  }
  if(file==NULL)
  {
    printf("ERROR,FILE CANNOT BE OPENED!!!\n");
    return;
  }
  for(i=0;i<n;i++)
    fwrite(&s[i],sizeof(s[i]),1,file);
    fclose(file);
    printf("STUDENT RECORD CREATED\n");
}


int checkRoll(int rollno){
    struct student stu;
    FILE *file;
    file=fopen("student.txt","a+");
    if(file==NULL)
    {
      printf("ERROR,FILE CANNOT BE OPENED!!!");
      return 1;
    }
    while(fread(&stu,sizeof(stu),1,file))
    {
      if(rollno==stu.rollNo)
      {
        printf("ROLL NUMBER %d IS ALREADY RECORDED, TRY AGAIN!\n",rollno);
        fclose(file);
        return 1;
      }
    }
    fclose(file);
    return 0;
}

void deleteRecord(){
      if(!fileEmpty())
        return;
      struct student stu;
      int no;
      int found=0;
      FILE *file1;
      FILE *file2;
      printf("\nPLEASE ENTER THE ROLLNUMBER WANT TO DELETE: ");
      scanf("%d", &no);
      file1 = fopen("student.txt", "r");
      if(file1==NULL)
      {
        printf("ERROR,FILE CANNOT BE OPENED!!!");
        return;
      }
      file2 = fopen("temp.txt", "w");
      if(file2==NULL)
      {
        printf("ERROR,FILE CANNOT BE OPENED!!!\n");
        return;
      }
      rewind(file1);
      while ((fread(&stu, sizeof(stu), 1,file1)) > 0)
          if (stu.rollNo != no)
              fwrite(&stu, sizeof(stu), 1, file2);
          else
            found=1;
      fclose(file2);
      fclose(file1);
      remove("student.txt");
      rename("temp.txt", "student.txt");
      if(found)
        printf("\nRECORD DELETED\n");
      else
        printf("RECORD NOT FOUND\n");
}

int main()
{
  int ch;
  printf("1.CREATE STUDENT RECORD/NEW RECORD\n2.DISPLAY ALL STUDENT RECORD\n3.DELETE STUDENT RECORD\n4.GO BACK TO MENU\n0.EXIT\n");
  do{
  printf("\nENTER THE OPTION:");
  scanf("%d",&ch);
  switch(ch){
    case 0:
      printf("EXITING.....\n");
      break;
    case 1:
      createRecord();
      break;
    case 2:
      displayRecord();
      break;
    case 3:
      deleteRecord();
      break;
    case 4:
      printf("1.CREATE STUDENT RECORD/NEW RECORD\n2.DISPLAY ALL STUDENT RECORD\n3.DELETE STUDENT RECORD\n4.GO BACK TO MENU\n0.EXIT\n");
      break;
    default:
      printf("INVALID OPTION! TRY AGAIN");
  }

  }while(ch!=0);
  return 0;
}