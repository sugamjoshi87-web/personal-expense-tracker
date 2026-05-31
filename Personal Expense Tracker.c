#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float salary;

void addExpense();
void viewExpenses();
void deleteExpense();
void categorySummary();
void monthlyReport();
void budgetStatus();

int main()
{
    int choice;

    printf("====================================\n");
    printf("     PERSONAL EXPENSE TRACKER\n");
    printf("====================================\n");

    printf("Enter Monthly Salary: ");
    scanf("%f", &salary);

    do
    {
        printf("\n\n===== MENU =====\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Delete Expense\n");
        printf("4. Category Summary\n");
        printf("5. Monthly Report\n");
        printf("6. Budget Status\n");
        printf("7. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addExpense();
                break;

            case 2:
                viewExpenses();
                break;

            case 3:
                deleteExpense();
                break;

            case 4:
                categorySummary();
                break;

            case 5:
                monthlyReport();
                break;

            case 6:
                budgetStatus();
                break;

            case 7:
                printf("Thank You!\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 7);

    return 0;
}

void addExpense()
{
    FILE *fp;
    int id;
    char date[15];
    char category[30];
    float amount;

    fp = fopen("expenses.txt", "a+");

    if(fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    id = 1;

    int tempId;
    char tempDate[15], tempCategory[30];
    float tempAmount;

    rewind(fp);

    while(fscanf(fp,"%d %s %s %f",
                 &tempId,
                 tempDate,
                 tempCategory,
                 &tempAmount) != EOF)
    {
        id = tempId + 1;
    }

    printf("Enter Date (DD/MM/YYYY): ");
    scanf("%s", date);

    printf("Enter Category: ");
    scanf("%s", category);

    printf("Enter Amount: ");
    scanf("%f", &amount);

    fprintf(fp,"%d %s %s %.2f\n",
            id,date,category,amount);

    fclose(fp);

    printf("Expense Added Successfully!\n");
}

void viewExpenses()
{
    FILE *fp;
    int id;
    char date[15];
    char category[30];
    float amount;

    fp = fopen("expenses.txt","r");

    if(fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("\nID\tDate\t\tCategory\tAmount\n");
    printf("-------------------------------------------------\n");

    while(fscanf(fp,"%d %s %s %f",
                 &id,date,category,&amount)!=EOF)
    {
        printf("%d\t%s\t%s\t\t%.2f\n",
               id,date,category,amount);
    }

    fclose(fp);
}

void deleteExpense()
{
    FILE *fp,*temp;

    int deleteId;
    int id;
    char date[15];
    char category[30];
    float amount;
    int found = 0;

    printf("Enter Expense ID to Delete: ");
    scanf("%d",&deleteId);

    fp = fopen("expenses.txt","r");

    if(fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    temp = fopen("temp.txt","w");

    while(fscanf(fp,"%d %s %s %f",
                 &id,date,category,&amount)!=EOF)
    {
        if(id == deleteId)
        {
            found = 1;
        }
        else
        {
            fprintf(temp,"%d %s %s %.2f\n",
                    id,date,category,amount);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("expenses.txt");
    rename("temp.txt","expenses.txt");

    if(found)
        printf("Expense Deleted Successfully!\n");
    else
        printf("Expense ID Not Found!\n");
}

void categorySummary()
{
    FILE *fp;

    int id;
    char date[15];
    char category[30];
    float amount;

    float food=0;
    float transport=0;
    float shopping=0;
    float education=0;
    float other=0;

    fp = fopen("expenses.txt","r");

    if(fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    while(fscanf(fp,"%d %s %s %f",
                 &id,date,category,&amount)!=EOF)
    {
        if(strcmp(category,"Food")==0)
            food += amount;

        else if(strcmp(category,"Transport")==0)
            transport += amount;

        else if(strcmp(category,"Shopping")==0)
            shopping += amount;

        else if(strcmp(category,"Education")==0)
            education += amount;

        else
            other += amount;
    }

    fclose(fp);

    printf("\n===== CATEGORY SUMMARY =====\n");
    printf("Food       : %.2f\n",food);
    printf("Transport  : %.2f\n",transport);
    printf("Shopping   : %.2f\n",shopping);
    printf("Education  : %.2f\n",education);
    printf("Other      : %.2f\n",other);
}

void monthlyReport()
{
    FILE *fp;

    int id;
    char date[15];
    char category[30];
    float amount;

    char monthYear[8];
    float total = 0;

    printf("Enter Month (MM/YYYY): ");
    scanf("%s",monthYear);

    fp = fopen("expenses.txt","r");

    if(fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("\n===== MONTHLY REPORT =====\n");
    printf("ID\tDate\t\tCategory\tAmount\n");
    printf("-------------------------------------------------\n");

    while(fscanf(fp,"%d %s %s %f",
                 &id,date,category,&amount)!=EOF)
    {
        if(strstr(date + 3, monthYear) != NULL)
        {
            printf("%d\t%s\t%s\t\t%.2f\n",
                   id,date,category,amount);

            total += amount;
        }
    }

    printf("-------------------------------------------------\n");
    printf("Total Monthly Expense: %.2f\n",total);

    fclose(fp);
}

void budgetStatus()
{
    FILE *fp;

    int id;
    char date[15];
    char category[30];
    float amount;

    float totalExpense = 0;

    fp = fopen("expenses.txt","r");

    if(fp != NULL)
    {
        while(fscanf(fp,"%d %s %s %f",
                     &id,date,category,&amount)!=EOF)
        {
            totalExpense += amount;
        }

        fclose(fp);
    }

    printf("\n===== BUDGET STATUS =====\n");
    printf("Monthly Salary : %.2f\n",salary);
    printf("Total Expense  : %.2f\n",totalExpense);
    printf("Remaining      : %.2f\n",
           salary-totalExpense);

    if(totalExpense > salary)
    {
        printf("WARNING: Budget Exceeded!\n");
    }
    else if(totalExpense >= salary*0.8)
    {
        printf("WARNING: More than 80%% of salary spent!\n");
    }
    else
    {
        printf("Budget is under control.\n");
    }
}