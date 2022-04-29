#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h> 
#include <windows.h> 
#include <string.h>
#define dis_date 20 // Discount Day
void menu();
void add_c();
void Newadd_i();
void set_zero(char card_id[]);
void view_card();
void view_items();
int check_cus(char c_name[]);
void modify();
void above_60();

void points();
void discount_list();
void card_validity();
int valid_date(int day, int mon, int year);
void stocks(char i_name[]);

static int cus_no = 0;        // initialising maximum customers to zero
static int garment = 100;     // stock of garment
static int grocery = 300;     // stock of grocery
static int electronics = 200; // stock of electronics

struct card // new customer  add
{
    char card_id[30];
    char c_name[30];
    char dob[11], addr[100];
};
struct customer // new items added to existing customer
{
    int points, quantity;
    char item_id[30], card_id[30], i_name[20], ldot[11];
    float price;
};
int main()
{

    printf("\n<--:DETAILS OF SHOPPING CARD:-->\n\n");

    printf("\n\nPress any key to continue.\n");
    getch();
    menu();
    return 0;
}
void menu() // displays the menu
{
    int choice;
    system("cls");
    printf("\n	\n");
    printf("  <----------------:MENU---------------	>");
    printf("\n	\n");
    printf("\nEnter appropriate number to perform following task\n");
    printf("\n\t1 : Add Customer.");
    printf("\n\t2 : Add items to existing customer.");
    printf("\n\t3 : View Card Details.");
    printf("\n\t4 : View Item Details.");
    printf("\n\t5 : Modify Card.");
    printf("\n\t6 : Avail senior citizen discount.");
    printf("\n\t7 : Check points.");

    printf("\n\t8 : Discount list.");
    printf("\n\t9 : Check card validity.");
    printf("\n\t0 : Exit.");
    printf("\nEnter your choice.");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        add_c();
        break;

    case 2:
        Newadd_i();
        break;

    case 3:
        view_card();
        break;

    case 4:
        view_items();
        break;
    case 5:
        modify();
        break;
    case 6:
        above_60();
        break;

    case 7:
        points();
        break;
    case 8:
        discount_list();
        break;

    case 9:
        card_validity();
        break;

    case 0:
        exit(1);
        break;

    default:
        printf("\nInvalid Choice.");
    }
}

void add_c() // adds new customer
{
    FILE *fp, *ft;
    int flag = 0;
    char id[30], card_id[30];
    struct card std;
    system("cls");

    fflush(stdin);

    printf("Enter the Customer Card_id: ");
    gets(id);
    ft = fopen("Card_details.txt", "r");
    while (fgets(card_id, 30, ft))
    {
        // checks whether the particular card id is unique or not
        char *ptr = strstr(card_id, id);
        if (ptr != NULL)
        {
            flag = 1;
            break;
        }
    }
    fclose(ft);

    if (flag == 1)
    {
        printf("Already Exist!!! please Enter correct Card_id\n");
        printf("\n\nPress any key to continue.");
        getch();
        menu();
    }

    fp = fopen("Card_details.txt", "a");
    if (fp == NULL)
    {
        printf("\nError opening file");
        exit(1);
    }

    fflush(stdin);
    printf("\n<------:ADD CUSTOMER	>\n\n");
    printf("Enter details of customer\n");
    fflush(stdin);
    printf("Enter Name : ");
    gets(std.c_name);
    strcpy(std.c_name, strupr(std.c_name));
    fflush(stdin);

    strcpy(std.card_id, id);
    fflush(stdin);
    printf("\nEnter Date of Birth (MM/DD/YYYY): ");
    gets(std.dob);
    fflush(stdin);
    printf("\nEnter Address : ");
    gets(std.addr);
    strcpy(std.addr, strupr(std.addr));
    fflush(stdin);
    system("cls");
    fflush(stdin);
    fprintf(fp, "\n%s\t%s\t%s\t%s", std.c_name, std.card_id, std.dob, std.addr);
    fclose(fp);
    printf("\n\nPress any key to continue.");
    getch();
    menu();
}
void Newadd_i() // adds new items to existing customer
{
    FILE *fp, *ft, *f;
    struct customer std;
    struct card s;
    int flag = 0, sum = 0, flag2 = 0;
    char another = 'y';
    system("cls");
    char id[30], card_id[30], iid[30], item_id[30];
    fflush(stdin);
    printf("Enter the Customer Card_id: ");
    scanf("%[^\n]", id);
    ft = fopen("Card_details.txt", "r");
    while (fgets(card_id, 30, ft)) // Checks  whether  the  customer  exists  or not
    {
        char *ptr = strstr(card_id, id);
        if (ptr != NULL)
        {
            flag = 1;
            break;
        }
    }
    fclose(ft);

    if (flag != 1)
    {
        printf("Error...No such Customer corresponding to Card_id\n");
        exit(1);
    }

    fflush(stdin);
    printf("Enter the Item_id: ");
    scanf("%[^\n]", iid);
    f = fopen("Item_details.txt", "r");
    while (fscanf(f, "%s	%s	%s	%f	%d %d %s", std.card_id, std.i_name, std.item_id, &std.price, &std.quantity, &std.points, std.ldot) != EOF)
    {
        // checks whether the item id is unique or not

        if (strcmp(iid, std.item_id) == 0)
        {
            flag2 = 1;
            break;
        }
    }
    fclose(f);

    if (flag2 == 1)
    {
        printf("Already Exist!!! please Enter correct Item_id\n");
        printf("\nPress any key to continue.");
        getch();
        menu();
    }
    fflush(stdin);

    fp = fopen("Item_details.txt", "a");
    if (fp == NULL)
    {
        printf("\nError opening file");
        exit(1);
    }
    fflush(stdin);
    printf("\n<------:ADD ITEMS TO CUSTOMER	>\n\n");
    printf("Enter details of items\n");
    int choice;
    system("cls");
    printf("\nEnter your choice from ...Grocery,Garments,Electronics	");
    printf("\n \t");
    printf("\n\t * Grocery --> 1 point");
    printf("\n\t * Garments --> 5 point");
    printf("\n\t * Electronics --> 10 point");
    printf("\n \t");
    fflush(stdin);
    strcpy(std.card_id, id);
    printf("\nEnter	Type	of	item	u	want	to buy ...Grocery,Garments,Electronics...? ");

    fflush(stdin);
    gets(std.i_name);
    strcpy(std.i_name, strupr(std.i_name));
    stocks(strupr(std.i_name));
    fflush(stdin);
    strcpy(std.item_id, iid);
    printf("\nEnter Item price: ");
    scanf("%f", &std.price);
    printf("\nEnter Item quantity : ");
    scanf("%d", &std.quantity);
    printf("\nEnter points : ");
    scanf("%d", &std.points);
    fflush(stdin);
    printf("\nEnter Last Date of Transaction (MM/DD/YYYY): ");
    gets(std.ldot);
    fflush(stdin);
    system("cls");
    fflush(stdin);
    fprintf(fp, "\n%s\t%s\t%s\t%f\t%d\t%d\t%s", std.card_id, std.i_name, std.item_id, std.price, std.quantity, std.points, std.ldot);
    fclose(fp);
    printf("\n\nPress any key to continue.");
    getch();
    menu();
}

void modify() // modifies the address only
{
    char CDid[20];
    FILE *fp, *fp1;
    int found = 0;
    struct card std;
    system("cls");
    printf("\n<--:MODIFY RECORD:-->\n\n");
    printf("\nEnter Card_id of customer to modify: ");
    fflush(stdin);
    gets(CDid);
    fp = fopen("Card_details.txt", "rb+");
    fp1 = fopen("temp.txt", "w");
    if (fp == NULL)
    {
        printf("\nError opening file");
        exit(1);
    }
    rewind(fp);
    fflush(stdin);
    while (fscanf(fp, "%s %s %s %s", std.c_name, std.card_id, std.dob, std.addr) != EOF)

    {
        if (strcmp(CDid, std.card_id) == 0)
        {
            found = 1;
            printf("\nEnter address: ");
            gets(std.addr);
            strcpy(std.addr, strupr(std.addr));
            fflush(stdin);
            fprintf(fp1, "\n%s\t%s\t%s\t%s", std.c_name, std.card_id, std.dob, std.addr);
        }
        else
            fprintf(fp1, "\n%s\t%s\t%s\t%s", std.c_name, std.card_id, std.dob, std.addr);
    }
    fclose(fp);
    fclose(fp1);
    if (found)
    {
        fp1 = fopen("temp.txt", "r");
        fp = fopen("Card_details.txt", "w");
        while (fscanf(fp1, "%s %s %s %s", std.c_name, &std.card_id, std.dob, std.addr) != EOF)
        {
            fprintf(fp, "\n%s\t%s\t%s\t%s", std.c_name, std.card_id, std.dob, std.addr);
        }
        fclose(fp);
        fclose(fp1);
    }
    else
        printf("\n\nRecord is not found..\n");

    remove("temp.txt");
    printf("\n\nPress any key to continue.");
    getch();
    menu();
}

void points() // checks points of the customer
{
    char CDid[20];
    FILE *fp, *fp1;
    int found = 0, sum = 0;
    struct customer std;
    system("cls");

    printf("\nEnter name of customer who want to know their points: ");

    fflush(stdin);
    gets(CDid);
    fp = fopen("Item_details.txt", "rb+");
    if (fp == NULL)
    {
        printf("\nError opening file");
        exit(1);
    }
    rewind(fp);
    fflush(stdin);
    while (fscanf(fp, "%s %s %s %f %d %d %s", std.card_id, std.i_name, std.item_id, &std.price, &std.quantity, &std.points, std.ldot) != EOF)
    {
        if (strcmp(CDid, std.card_id) == 0)
        {
            // calculates total points of the customer
            found = 1;
            sum = sum + std.points;
        }
    }

    if (found)
    {
        printf("Total points %d:", sum);

        fclose(fp);
    }
    else
        printf("\nRecord is not found..\n");

    printf("\n\nPress any key to continue.");
    getch();
    menu();
}

void discount_list() // gives  discount  to  customers  having  points  1000 and above
{
    char CDid[20];
    FILE *fp, *fp1;
    int found = 0, sum = 0;
    int opt;
    struct customer std;
    system("cls");
    int ch1;
    printf("\nEnter Card_id of the customer who want to know their points:");
    fflush(stdin);

    gets(CDid);
    fp = fopen("Item_details.txt", "rb+");
    if (fp == NULL)
    {
        printf("\nError opening file");
        exit(1);
    }
    rewind(fp);
    fflush(stdin);
    while (fscanf(fp, "%s %s %s %f %d %d %s", std.card_id, std.i_name, std.item_id, &std.price, &std.quantity, &std.points, std.ldot) != EOF)
    {
        // calculates total points of the customer

        if (strcmp(CDid, std.card_id) == 0)
        {
            found = 1;
            sum = sum + std.points;
        }
    }

    if (cus_no < 10) // gives  discount  to  10  customers  only  those  who  are eligible
    {
        if (sum >= 1000)
        {
            cus_no++;
            FILE *p;
            int found = 0;
            struct customer std;
            system("cls");
            int ch1;
            fflush(stdin);
            p = fopen("Item_details.txt", "rb+");
            if (p == NULL)
            {
                printf("\nError opening file");
                exit(1);
            }
            rewind(p);
            fflush(stdin);
            printf("\n	-: LIST of all last date of transaction:-	");
            printf("\n******************");
            while (fscanf(p, "%s %s %s %f %d %d %s", std.card_id, std.i_name, std.item_id, &std.price, &std.quantity, &std.points, std.ldot) != EOF)
            {
                // Displays list of all transactions of that particular customer

                if (strcmp(CDid, std.card_id) == 0)
                {
                    printf("\n	%s", std.ldot);
                }
            }
            fclose(p);
            int day1, mon1, year1;
            printf("\n\nFrom	list	,Enter	last	date	of	transaction	: (MM/DD/YYYY): ");
            scanf("%d/%d/%d", &mon1, &day1, &year1);
            if (!valid_date(day1, mon1, year1))
            {
                printf("First date is invalid.\n");
            }
            if (day1 == dis_date) // last    day    of    transaction    matches    the discount day
            {
                printf("Your Total points is %d", sum);
                fclose(fp);
                printf("\n\ncongratulations! Your points now above 1000 .You get 10 % Discount.\n");
                printf("\nYou  are  eligible  for  today's  discount..\n\n	Press 1: Avail discount\n	Press 0: Don't want discount : ");
                scanf("\n%d", &opt);
                if (opt == 1)
                {
                    set_zero(CDid);
                    // sets the points to zero again if customer avails it
                    printf("\n\nPress any key to continue.");
                    getch();
                    menu();
                }
            }
            else
            {
                printf("\nThere is no such discount for the entered date.\n");
                printf("\n\nPress any key to continue.");
                getch();
                menu();
            }
        }
        else
            printf("\n till now your points below 1000!..\n");
    }
    else
    {
        printf("\n\nSorry ..Discount is already over !!\n");
    }

    printf("\n\nPress any key to continue.");
    getch();
    menu();
}

void above_60() // gives discount to customers having points 1000 and above, also are senior citizens
{
    char CDid[20];
    FILE *fp, *fp1, *ft;
    int found = 0, sum = 0, opt;
    struct customer std;
    system("cls");
    printf("\nEnter card_id of customer who want to know their age difference: ");
    fflush(stdin);
    gets(CDid);
    struct card s;
    system("cls");

    ft = fopen("Card_details.txt", "rb+");
    if (ft == NULL)
    {
        printf("\nError opening file");
        exit(1);
    }
    rewind(ft);
    fflush(stdin);
    while (fscanf(ft, "%s %s %s %s ", s.c_name, s.card_id, s.dob, s.addr) != EOF)
    { // Displays customer's date of birth

        if (strcmp(CDid, s.card_id) == 0)
        {
            printf("\n	\n");
            printf(" Name is:- %s ;\tDate Of Birth is:- %s\n", s.c_name, s.dob);
        }
    }

    fp = fopen("Item_details.txt", "rb+");
    if (fp == NULL)
    {
        printf("\nError opening file");
        exit(1);
    }

    rewind(fp);
    fflush(stdin);
    printf("\n   -: LIST of all last date of transaction:-	");
    printf("\n******************");
    while (fscanf(fp, "%s %s %s %f %d %d %s", std.card_id, std.i_name, std.item_id, &std.price, &std.quantity, &std.points, std.ldot) != EOF)
    {
        if (strcmp(CDid, std.card_id) == 0)
        { // Displays list of all transactions of that particular customer
            printf("\n	%s", std.ldot);
        }
    }
    printf("\n	\n");
    fclose(fp);

    int day1, mon1, year1, day2, mon2, year2;

    int day_diff, mon_diff, year_diff;

    printf("\n\nFrom list ,Enter your Date Of Birth : (MM/DD/YYYY): ");
    scanf("%d/%d/%d", &mon1, &day1, &year1);

    printf("\nFrom list ,Enter last date of transaction : (MM/DD/YYYY): ");
    scanf("%d/%d/%d", &mon2, &day2, &year2);

    if (!valid_date(day1, mon1, year1))
    {
        printf("First date is invalid.\n");
    }

    if (!valid_date(day2, mon2, year2))
    {
        printf("Second date is invalid.\n");
        exit(0);
    }

    if (day2 < day1)
    {

        if (mon2 == 3)
        {
            // check whether year is a leap year
            if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0))
            {
                day2 += 29;
            }

            else
            {
                day2 += 28;
            }
        }

        else if (mon2 == 5 || mon2 == 7 || mon2 == 10 || mon2 == 12)
        {
            day2 += 30;
        }

        else
        {
            day2 += 31;
        }

        mon2 = mon2 - 1;
    }

    if (mon2 < mon1)
    {
        mon2 += 12;
        year2 -= 1;
    }

    day_diff = day2 - day1;
    mon_diff = mon2 - mon1;
    year_diff = year2 - year1;
    fflush(stdin);
    fclose(ft);

    if (year_diff < 60)
    {
        printf("\nYou are not eligible for this discount as you are not a senior citizen.\n");
        printf("\n\nPress any key to continue.");
        getch();
        menu();
    }
    else if (day2 != dis_date)
    {
        printf("\nThere is no such discount for the entered date.\n");
        printf("\n\nPress any key to continue.");
        getch();
        menu();
    }
    else
    {
        FILE *f;

        system("cls");
        f = fopen("Item_details.txt", "rb+");
        if (f == NULL)
        {
            printf("\nError opening file");
            exit(1);
        }
        rewind(f);
        fflush(stdin);
        system("cls");
        while (fscanf(f, "%s	%s	%s	%f	%d %d %s", std.card_id, std.i_name, std.item_id, &std.price, &std.quantity, &std.points, std.ldot) != EOF)
        {
            // calculates total points of the customer
            if (strcmp(CDid, std.card_id) == 0)
            {
                found = 1;
                sum = sum + std.points;
            }
        }
        if (cus_no < 10) // gives  discount  to  10  customers  only  those  who  are eligible
        {

            if (sum >= 1000 && year_diff >= 60)
            {
                cus_no++;
                int found = 0;
                struct customer std;
                system("cls");
                int ch1;
                fflush(stdin);
                if (day2 == dis_date) // last    day    of    transaction    matches    the discount day
                {
                    printf("\n	Now your age is: %d years.", year_diff);
                    printf("\n	Your Total points is %d", sum);
                    fclose(f);
                    printf("\nCongratulations! Your points now above 1000 .You get 15 % Discount.\n");
                    printf("\nYou  are  eligible  for  today's  discount..\n\n	Press 1: Avail discount\n	Press 0: Don't want discount : ");
                    scanf("\n%d", &opt);
                    if (opt == 1)
                    {
                        set_zero(CDid); // sets the points to zero again if customer avails it
                    }
                }
            }
            else
            {
                printf("\n Your age above 60 But ... !!! Till now your points below 1000!..\n");
                printf("\n\nPress any key to continue.");
                getch();
                menu();
            }
        }
        else
        {
            printf("\n\nSorry ..Discount is already over !!\n");
            printf("\n\nPress any key to continue.");
            getch();
            menu();
        }
    }
    printf("\n\nPress any key to continue.");
    getch();
    menu();
}

void view_card() // shows the customer details
{
    FILE *fp;
    int i = 1;
    struct card std;
    system("cls");
    printf("\n<--------------------:SHOPPING CARD DETAILS:------------------------->\n\n");
    printf("Name  of  Customer     Card  ID         DOB             Address         ");
    printf("\n	\n");
    fp = fopen("Card_details.txt", "r");
    if (fp == NULL)
    {
        printf("\nError opening file.");
        exit(1);
    }
    fflush(stdin);
    while (fscanf(fp, "%s	%s	%s	%s ", std.c_name, std.card_id, std.dob, std.addr) != EOF)
    {
        printf("\n%-22s%-10s%-16s%-26s", std.c_name, std.card_id, std.dob, std.addr);
        i++;
    }
    fclose(fp);
    printf("\n\nPress any key to continue.");
    getch();
    menu();
}
void view_items() // displays	the	items purchased ,price,quantity,points, and last date of transaction
{
    FILE *fp;
    int i = 1;
    struct customer std;
    system("cls");
    printf("\n<-<-<---------------------------------:CUSTOMER ITEM DETAILS:---------------------------------------------------->-->-->\n\n");
    printf("S.No	Card_id	Item  Name	Item  ID	Price Quantity	Points		LDOT ");
    printf("\n------------------------------------------------------------------------------------------------------------------------\n");
    fp = fopen("Item_details.txt", "r");
    if (fp == NULL)
    {
        printf("\nError opening file.");
        exit(1);
    }
    fflush(stdin);
    while (fscanf(fp, "%s %s %s %f %d %d %s", std.card_id, std.i_name, std.item_id, &std.price, &std.quantity, &std.points, std.ldot) != EOF)
    {
        printf("\n%2d. %10s %15s %10s %15f %10d %10d %12s", i, std.card_id, std.i_name, std.item_id, std.price, std.quantity, std.points, std.ldot);
        i++;
    }
    fclose(fp);
    printf("\n\nPress any key to continue.");
    getch();
    menu();
}

void card_validity() // validity of customer card
{
    char CDid[20];
    FILE *fp, *fp1;
    int found = 0, sum = 0;
    struct customer std;
    system("cls");
    int ch1;

    printf("\nEnter Card_id of that customer who want to know their year difference: ");
    fflush(stdin);
    gets(CDid);
    fp = fopen("Item_details.txt", "rb+");
    if (fp == NULL)
    {
        printf("\nError opening file");
        exit(1);
    }
    rewind(fp);
    fflush(stdin);
    while (fscanf(fp, "%s %s %s %f %d %d %s", std.card_id, std.i_name, std.item_id, &std.price, &std.quantity, &std.points, std.ldot) != EOF)
    {
        // Displays list of all transactions of that particular customer
        if (strcmp(CDid, std.card_id) == 0)
        {
            printf("\nLIST of all last date of transaction :%s", std.ldot);
        }
    }

    int day1, mon1, year1, day2, mon2, year2;

    int day_diff, mon_diff, year_diff;

    printf("\n\nFrom list ,Enter second last date : (MM/DD/YYYY): ");
    scanf("%d/%d/%d", &mon1, &day1, &year1);

    printf("\nFrom list ,Enter last date (MM/DD/YYYY): ");
    scanf("%d/%d/%d", &mon2, &day2, &year2);

    if (!valid_date(day1, mon1, year1))
    {
        printf("First date is invalid.\n");
    }

    if (!valid_date(day2, mon2, year2))
    {
        printf("Second date is invalid.\n");
        exit(0);
    }

    if (day2 < day1)
    {

        if (mon2 == 3)

        {
            // check whether year is a leap year
            if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0))
            {
                day2 += 29;
            }

            else
            {
                day2 += 28;
            }
        }
        else if (mon2 == 5 || mon2 == 7 || mon2 == 10 || mon2 == 12)
        {
            day2 += 30;
        }

        else
        {
            day2 += 31;
        }

        mon2 = mon2 - 1;
    }

    if (mon2 < mon1)
    {
        mon2 += 12;
        year2 -= 1;
    }

    day_diff = day2 - day1;
    mon_diff = mon2 - mon1;
    year_diff = year2 - year1;

    printf("Difference: %d years %02d months and %02d days.", year_diff, mon_diff, day_diff);

    fclose(fp);

    FILE *fp4, *fp5;
    struct card std1;
    fflush(stdin);

    fp4 = fopen("Card_details.txt", "rb+");
    fp5 = fopen("temp.txt", "w");
    if (fp4 == NULL)
    {

        printf("\nError opening file");
        exit(1);
    }
    rewind(fp4);
    fflush(stdin);
    if (year_diff >= 1)
    {
        // removes the customer from customer list

        while (fscanf(fp4, "%s %s %s %s", std1.c_name, std1.card_id, std1.dob, std1.addr) != EOF)
        {
            if ((strcmp(CDid, std1.card_id) != 0) && (year_diff >= 1))
            {
                found = 1;
                fprintf(fp5, "\n%s\t%s\t%s\t%s", std1.c_name, std1.card_id, std1.dob, std1.addr);
            }
        }
    }

    fclose(fp4);
    fclose(fp5);

    if (found == 1)
    {
        printf("\nYou card_id get expired .\n");
        remove("Card_details.txt");
        rename("temp.txt", "Card_details.txt");
    }
    else
    {
        remove("temp.txt");
        printf("\n\n Time limit of your card is Not Over..\n");
    }

    printf("\n\nPress any key to continue.");
    getch();
    menu();
}

int valid_date(int day, int mon, int year)
// checks whether the date is valid or not
{
    int is_valid = 1, is_leap = 0;
    if (year >= 1800 && year <= 9999)
    {
        // check whether year is a leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            is_leap = 1;
        } // check whether mon is between 1 and 12
        if (mon >= 1 && mon <= 12)
        { // check for days in feb
            if (mon == 2)
            {
                if (is_leap && day == 29)
                {
                    is_valid = 1;
                }
                else if (day > 28)
                {
                    is_valid = 0;
                }
            } // check for days in April, June, September and November
            else if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
            {
                if (day > 30)
                {
                    is_valid = 0;
                }
            } // check for days in rest of the months // i.e Jan, Mar, May, July, Aug, Oct, Dec
            else if (day > 31)
            {
                is_valid = 0;
            }
        }
        else
        {
            is_valid = 0;
        }
    }
    else
    {
        is_valid = 0;
    }
    return is_valid;
}

void set_zero(char CDid[]) // sets points to zero
{

    FILE *fp, *fp1;
    int found = 0;
    struct customer std;
    fp = fopen("Item_details.txt", "rb+");
    fp1 = fopen("temp.txt", "w");
    if (fp == NULL)
    {
        printf("\nError opening file");
        exit(1);
    }

    fflush(stdin);
    while (fscanf(fp, "%s %s %s %f %d %d %s", std.card_id, std.i_name, std.item_id, &std.price, &std.quantity, &std.points, std.ldot) != EOF)
    { // finds the particular customer and sets the points to zero
        if (strcmp(CDid, std.card_id) == 0)
        {
            found = 1;
            std.points = 0;
            fflush(stdin);
            fprintf(fp1, "\n%s\t%s\t%s\t%f\t%d\t%d\t%s", std.card_id, std.i_name, std.item_id, std.price, std.quantity, std.points, std.ldot);
        }
        else
            fprintf(fp1, "\n%s\t%s\t%s\t%f\t%d\t%d\t%s", std.card_id, std.i_name, std.item_id, std.price, std.quantity, std.points, std.ldot);
    }
    fclose(fp);
    fclose(fp1);
    remove("Item_details.txt");
    rename("temp.txt", "Item_details.txt");
    printf("\nPoints are set to zero again");
}
void stocks(char i_name[]) // to know the availability of stocks
{

    char s1[10] = "GARMENTS";
    char s2[10] = "GROCERY";

    char s3[20] = "ELECTRONICS";
    FILE *fp, *fp1;
    int found = 0, sum = 0, sub1, sub2, sub3;
    struct customer std;
    system("cls");

    fp = fopen("Item_details.txt", "rb+");
    if (fp == NULL)
    {
        printf("\nError opening file");
        exit(1);
    }
    rewind(fp);
    fflush(stdin);
    while (fscanf(fp, "%s %s %s %f %d %d %s", std.card_id, std.i_name, std.item_id, &std.price, &std.quantity, &std.points, std.ldot) != EOF)
    {
        if (strcmp(i_name, std.i_name) == 0)
        {
            found = 1;
            sum = sum + std.quantity;
        }
    }
    fflush(stdin);

    if (strcmp(s1, i_name) == 0)
    {
        sub1 = garment - sum;

        if (sub1 > 0)
        {
            printf("\n	\n");
            printf("\n\nAvailability of Garment : %d", sub1);
            printf("\n	\n\n");
            fclose(fp);
        }
        else if (sub1 == 0)
        {
            printf("\nSorry It's already out of stocks.\n");
            fclose(fp);
            printf("\n\nPress any key to continue.");
            getch();
            menu();
        }
    }

    fflush(stdin);

    if (strcmp(i_name, s2) == 0)
    {
        sub2 = grocery - sum;

        if (sub2 > 0)
        {
            printf("\n	\n");
            printf("\nAvailability of Grocery : %d ", sub2);
            printf("\n	\n\n");
            fclose(fp);
        }
        else if (sub2 == 0)
        {
            printf("\nSorry It's already out of stocks.\n");
            fclose(fp);
            printf("\n\nPress any key to continue.");
            getch();
            menu();
        }
    }
    fflush(stdin);

    if (strcmp(i_name, s3) == 0)
    {
        sub3 = electronics - sum;

        if (sub3 > 0)
        {
            printf("\n	\n");
            printf("Availability of Electronics : %d", sub3);
            printf("\n	\n\n");
            fclose(fp);
        }
        else if (sub3 == 0)
        {
            printf("\nSorry It's already out of stocks.\n");
            fclose(fp);
            printf("\n\nPress any key to continue.");
            getch();
            menu();
        }
    }
}