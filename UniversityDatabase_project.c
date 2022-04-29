#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{ // student database
    int roll;
    char name[30], branch_id[10], university_id[15];
    float cgpa;
    struct student *next;
};

struct university
{ // university database
    char name[70], location[30], university_id[15];
    int yos;

    struct university *next;
};

struct branch
{ // branch database
    char branch_id[10], university_id[15];
    char branch[20];
    struct branch *next;
};

struct student *headst1 = NULL, *lstst1 = NULL;
// student head node for >=6.0 cgpa
struct student *headst2 = NULL, *lstst2 = NULL;
// student head node for <6.0 cgpa
struct university *headuni = NULL, *lstuni = NULL;
// university head node
struct branch *headbr = NULL, *lstbr = NULL;
// branch head node

void adduni();
void displayuni();

void addbr();
void displaybr();
int checkuni(char[]);
int checkbr(char[], char[]);

void addstu();
int checkroll(int, char[], struct student *);

void displayallst();
void displayst_less();
void displayst_uni();

void del_uni();
void del_br();
void del_stu(struct student **, char[], char[], int);
void UniUpdate();
void BrUpdate();
void stUpdate();
void dis_uni_ascending();
void substring();

int main()
{

    int ch, ch1, ch2, ch3, roll;

    char brid[15], unid[20];
    do
    {
        system("cls");
        printf("\n	\n");
        printf("\n\tDatabase Menu\n");
        printf("\n	\n");
        printf("1.	University	Database\n2.	Branch	Database\n3.	Student Database\n4. Search on substring\n0. Exit\n");
        printf("\nEnter the choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            do
            {
                system("cls");
                printf("\n	\n");
                printf("\n\tUniversity Database\n");
                printf("\n	\n");
                printf("1. Add University\n2. List of all Universities\n3. Delete a University\n4. Update of University Database\n5. Display the University details in ASCENDING_ORDER of their year of starting\n0. Back\n");
                printf("\nEnter the choice: ");
                scanf("%d", &ch1);
                switch (ch1)
                {
                case 1:
                    adduni();
                    system("pause");
                    break;
                case 2:
                    displayuni();
                    system("pause");
                    break;
                case 3:
                    del_uni();
                    system("pause");
                    break;
                case 4:
                    UniUpdate();
                    system("pause");
                    break;

                    break;
                }

            case 5:
                dis_uni_ascending();
                system("pause");

            } while (ch1 != 0);
            break;
        case 2:
            do
            {
                system("cls");
                printf("\n	\n");
                printf("\n\tBranch Database\n");
                printf("\n	\n");

                printf("1. Add a branch to a University\n2. List of all the branches in University\n3. Delete Branch\n4. Update of Branch Database\n0. Back\n");
                printf("\nEnter the choice: ");
                scanf("%d", &ch2);
                switch (ch2)
                {
                case 1:
                    addbr();
                    system("pause");
                    break;
                case 2:
                    displaybr();
                    system("pause");
                    break;
                case 3:
                    del_br();
                    system("pause");
                    break;
                case 4:
                    BrUpdate();
                    system("pause");
                    break;
                }
            } while (ch2 != 0);
            break;
        case 3:
            do
            {
                system("cls");
                printf("\n	\n");
                printf("\n\tStudent Database\n");
                printf("\n	\n");
                printf("1. Add a student\n2. List of all the students in database\n");
                printf("3. List of students of a University\n4. List of student with <6.0 CGPA\n5. Update of Student Database\n6. Delete a Student\n0. Back\n");
                printf("\nEnter the choice: ");
                scanf("%d", &ch3);
                switch (ch3)
                {
                case 1:
                    addstu();
                    system("pause");
                    break;
                case 2:
                    displayallst();
                    system("pause");
                    break;
                case 3:
                    displayst_uni();
                    system("pause");
                    break;
                case 4:
                    displayst_less();
                    system("pause");
                    break;
                case 5:
                    stUpdate();
                    system("pause");
                    break;

                case 6:
                {
                    system("cls");
                    printf("\nEnter	university	id: ");
                    fflush(stdin);
                    scanf("%[^\n]", unid);
                    if (!checkuni(unid))
                    {
                        printf("Error...No such University corresponding to University Id\n");
                        break;
                    }

                    printf("\nEnter branch id: ");
                    fflush(stdin);
                    scanf("%[^\n]", brid);
                    if (checkbr(brid, unid))
                    {
                        printf("Error...No such branch in this University\n");
                        break;
                    }

                    printf("\nEnter the roll no.: ");
                    fflush(stdin);
                    scanf("%d", &roll);
                    if (!checkroll(roll, brid, headst1))
                    {
                        del_stu(&headst1, unid, brid, roll);
                    }
                    else if (!checkroll(roll, brid, headst2))
                    {
                        del_stu(&headst2, unid, brid, roll);
                    }
                    else
                    {
                        printf("No such student in the database\n");
                        system("pause");
                        break;
                    }
                    system("pause");
                }
                }
            } while (ch3 != 0);
            break;
        case 4:
            substring();
            system("pause");
            break;
        }
    } while (ch != 0);
    return 0;
}

void adduni()
{ // add new university to database
    system("cls");
    struct university *new;
    char unid[15];

    fflush(stdin);
    printf("Enter the University Id: ");
    scanf("%[^\n]", unid);
    struct university *temp = headuni;
    while (temp != NULL)
    { // checks whether university id is unique or not
        if (strcmp(temp->university_id, strupr(unid)) == 0)
        {
            printf("Error...The University id already exits\n");
            return;
        }
        temp = temp->next;
    }
    new = (struct university *)malloc(sizeof(struct university));
    strcpy(new->university_id, strupr(unid));
    fflush(stdin);
    printf("University Name: ");
    scanf("%[^\n]", new->name);
    strcpy(new->name, strupr(new->name));
    fflush(stdin);
    printf("Enter the location: ");
    scanf("%[^\n]", new->location);
    strcpy(new->location, strupr(new->location));
    fflush(stdin);
    printf("Enter the year of start: ");
    scanf("%d", &new->yos);
    printf("\nUniversity was added to the database\n");

    if (headuni == NULL)
    {
        headuni = lstuni = new;
        new->next = NULL;
    }
    else
    {
        lstuni->next = new;
        new->next = NULL;
        lstuni = new;
    }
}

void displayuni()
{ // displays university list
    system("cls");
    if (headuni == NULL)
        printf("University Database is empty\n");
    else
    {
        struct university *temp = headuni;
        printf("\n	\n");
        printf("\n\tList of Universities\n");
        printf("\n	\n");
        printf("University	ID\t\tName\t\t\t\t\t\t\tLocation\t\tYear	of Start\n");

        while (temp != NULL)
        {
            printf("%-20s\t%-40s\t\t%-20s\t%d\n", temp->university_id, temp->name, temp->location, temp->yos);
            temp = temp->next;
        }
    }
}

void addbr() // add new branch to database
{
    system("cls");
    struct branch new;
    char ch;
    fflush(stdin);
    printf("Enter the University Id: ");
    scanf("%[^\n]", new.university_id);
    if (!checkuni(new.university_id))
    { // checks   whether   university   id   exist or not
        printf("Error...No such University corresponding to University Id\n");
        return;
    }
    while (1)
    {
        fflush(stdin);
        printf("Enter the Branch Id: ");
        scanf("%[^\n]", new.branch_id);
        if (!checkbr(new.branch_id, new.university_id))
        { // checks	whether branch id is unique or not
            printf("The Branch id already exits\n");
            return;
        }
        struct branch *temp;
        temp = (struct branch *)malloc(sizeof(struct branch));
        strcpy(temp->university_id, strupr(new.university_id));
        strcpy(temp->branch_id, strupr(new.branch_id));
        fflush(stdin);
        printf("Enter the Branch name: ");
        scanf("%[^\n]", temp->branch);
        strcpy(temp->branch, strupr(temp->branch));
        fflush(stdin);
        printf("\nBranch was added to the database\n");

        if (headbr == NULL)
        {
            headbr = lstbr = temp;
            temp->next = NULL;
        }

        else
        {
            lstbr->next = temp;
            temp->next = NULL;
            lstbr = temp;
        }
        printf("Want to add another branch(y/n): ");
        scanf("%c", &ch);
        if (ch == 'n')
            break;
    }
}

int checkbr(char brid[], char unid[])
{ // checks    the    uniqueness    and existence of branch
    struct branch *br = headbr;
    while (br != NULL)
    {
        if (strcmp(br->university_id, strupr(unid)) == 0 && strcmp(br->branch_id, strupr(brid)) == 0)
            return 0;
        br = br->next;
    }
    return 1;
}

int checkuni(char unid[])
{ // checks   the   uniqueness   and   existence   of university
    struct university *temp = headuni;
    while (temp != NULL)
    {
        if (strcmp(temp->university_id, strupr(unid)) == 0)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void displaybr()
{ // displays branch details of a particular university
    system("cls");
    char unid[20];
    fflush(stdin);
    printf("Enter the University Id: ");
    scanf("%[^\n]", unid);
    if (!checkuni(unid))
    {
        printf("Error...No such University corresponding to University Id\n");
        return;
    }
    struct branch *temp = headbr;

    printf("\n	\n");
    printf("\n\tList of Branches\n");
    printf("\n	\n");
    printf("Branch name\t\t\t\tBranch ID\n");
    while (temp != NULL)
    {
        if (strcmp(temp->university_id, strupr(unid)) == 0)
        {
            printf("%-30s\t\t%s\n", temp->branch, temp->branch_id);
        }
        temp = temp->next;
    }
}

void addstu()
{ // add student to a particular branch of an university
    system("cls");
    struct student new;
    int flag = 0;
    fflush(stdin);
    printf("Enter the University Id: ");
    scanf("%[^\n]", new.university_id);
    if (!checkuni(new.university_id))
    {
        printf("Error...No such University corresponding to University Id\n");
        return;
    }
    fflush(stdin);
    printf("Enter the Branch Id: ");
    scanf("%[^\n]", new.branch_id);
    if (checkbr(new.branch_id, new.university_id))
    {
        printf("The branch you entered is not provided by the University\n");
        printf("Please enter a different Branch Id or search the 'BranchDatabase' ");
        printf("for the list of branches provided by a particular University\n");
        return;
    }
    struct student *st;
    st = (struct student *)malloc(sizeof(struct student));
    strcpy(st->university_id, strupr(new.university_id));
    strcpy(st->branch_id, strupr(new.branch_id));
    fflush(stdin);
    while (1)
    { // checks uniqueness of roll number printf("Enter the roll: "); scanf("%d",&new.roll);
        struct student *temp = headst1;
        while (temp != NULL)
        {

            if (strcmp(temp->university_id, strupr(new.university_id)) == 0 && temp->roll == new.roll)
                flag = 1;
            temp = temp->next;
        }
        struct student *temp1 = headst2;
        while (temp1 != NULL)
        {
            if (strcmp(temp1->university_id, strupr(new.university_id)) == 0 && temp1->roll == new.roll)
                flag = 1;
            temp1 = temp1->next;
        }
        if (flag == 1)
        {
            printf("The Roll number is already in use.\n");
            flag = 0;
            printf("Provide another roll number.\n");
            system("pause");
            system("cls");
            continue;
        }
        st->roll = new.roll;
        break;
    }
    fflush(stdin);
    printf("Enter the Name of the student: ");
    scanf("%[^\n]", st->name);
    strcpy(st->name, strupr(st->name));
    fflush(stdin);
    printf("Enter the cgpa: ");
    scanf("%f", &st->cgpa);
    printf("\nStudent's details were added to the database\n");
    if (st->cgpa >= 6.00)
    {
        if (headst1 == NULL)
        {
            headst1 = lstst1 = st;
            st->next = NULL;
        }
        else
        {
            lstst1->next = st;
            st->next = NULL;
            lstst1 = st;
        }
    }
    else
    {
        if (headst2 == NULL)
        {
            headst2 = lstst2 = st;
            st->next = NULL;
        }
        else
        {

            lstst2->next = st;
            st->next = NULL;
            lstst2 = st;
        }
    }
}

int checkroll(int roll, char brid[], struct student *st)
{ // checks	the uniqueness and existence of student
    struct student *temp = st;
    while (temp != NULL)
    {
        if (strcmp(temp->branch_id, strupr(brid)) == 0 && temp->roll == roll)
            return 0;
        temp = temp->next;
    }
    return 1;
}

void displayallst()
{ // displays all students of all university
    system("cls");
    struct student *tempa = headst1;
    struct student *tempb = headst2;
    struct university *temp1;
    struct branch *temp2;
    printf("\n	\n");
    printf("\n\tList of Students\n");
    printf("\n	\n");
    printf("Roll No.\t\tName\t\t\t\tBranch\t\t\t\tUniversity\n");
    while (tempa != NULL)
    {
        temp1 = headuni;
        temp2 = headbr;
        printf("%d\t\t\t%-20s\t\t", tempa->roll, tempa->name);
        while (temp1 != NULL && strcmp(temp1->university_id, tempa->university_id) != 0)
            temp1 = temp1->next;
        while (temp2 != NULL && strcmp(temp2->branch_id, tempa->branch_id) != 0)
            temp2 = temp2->next;
        printf("%-20s\t\t%s\n", temp2->branch, temp1->name);
        tempa = tempa->next;
    }
    while (tempb != NULL)
    {
        temp1 = headuni;
        temp2 = headbr;
        printf("%d\t\t\t%-20s\t\t", tempb->roll, tempb->name);
        while (temp1 != NULL && strcmp(temp1->university_id, tempb->university_id) != 0)
            temp1 = temp1->next;

        while (temp2 != NULL && strcmp(temp2->branch_id, tempb->branch_id) != 0)
            temp2 = temp2->next;
        printf("%-20s\t\t%s\n", temp2->branch, temp1->name);
        tempb = tempb->next;
    }
}

void displayst_less()
{ // displays students having less than 6.0 cgpa
    system("cls");
    char unid[20], brid[10], name[30];
    float cgpa;
    long int roll_no;
    fflush(stdin);
    printf("Enter the University Id: ");
    scanf("%[^\n]", unid);
    if (!checkuni(unid))
    {
        printf("Error...No such University corresponding to University Id\n");
        return;
    }

    struct student *temp = headst2;
    printf("\n	\n");
    printf("\n\t\tList of Students\n");
    printf("\n	\n");
    printf("University	ID\t\tBranch	ID\t\tRoll No.\t\t\tName\t\t\tCGPA\n");
    while (temp != NULL)
    {
        if (strcmp(temp->university_id, strupr(unid)) == 0)
        {
            printf("%-20s\t%-20s\t%-25d\t%-20s\t%f\n", temp->university_id, temp->branch_id, temp->roll, temp->name, temp->cgpa);
        }
        temp = temp->next;
    }
}

void displayst_uni()
{ // displays all students of an university
    system("cls");
    char unid[20], brid[10], name[30];
    float cgpa;
    long int roll_no;
    fflush(stdin);
    printf("Enter the University Id: ");
    scanf("%[^\n]", unid);
    if (!checkuni(unid))
    {
        printf("Error...No such University corresponding to University Id\n");
        return;
    }

    struct student *temp1 = headst1;
    struct student *temp2 = headst2;
    printf("\n	\n");
    printf("\n\t\tList of Students\n");
    printf("\n	\n");
    printf("University	ID\t\tBranch	ID\t\tRoll No.\t\t\tName\t\t\tCGPA\n");
    while (temp1 != NULL)
    {
        if (strcmp(temp1->university_id, strupr(unid)) == 0)
        {
            printf("%-20s\t%-20s\t%-25d\t%-20s\t%f\n", temp1->university_id, temp1->branch_id, temp1->roll, temp1->name, temp1->cgpa);
        }
        temp1 = temp1->next;
    }
    while (temp2 != NULL)
    {
        if (strcmp(temp2->university_id, strupr(unid)) == 0)
        {
            printf("%-20s\t%-20s\t%-25d\t%-20s\t%f\n", temp2->university_id, temp2->branch_id, temp2->roll, temp2->name, temp2->cgpa);
        }
        temp2 = temp2->next;
    }
}

void del_uni()
{ // deletes university
    char unid[15];
    system("cls");
    fflush(stdin);
    printf("Enter the University Id: ");
    scanf("%[^\n]", unid);
    if (!checkuni(unid))
    {
        printf("Error...No such University corresponding to University Id\n");
        return;
    }
    fflush(stdin);
    struct university *temp = headuni, *temp1 = headuni, *temp2;
    if (strcmp(headuni->university_id, strupr(unid)) == 0)
    {
        headuni = headuni->next;
        free(temp);
        printf("University deleted\n");
    }
    else
    {
        while (temp1->next != NULL)
        {
            if (strcmp(temp1->next->university_id, strupr(unid)) == 0)
            {
                temp2 = temp1->next;
                temp1->next = temp1->next->next;

                free(temp2);
                printf("University deleted\n");
                break;
            }
            else
                temp1 = temp1->next;
        }
    }
}

void del_br()
{ // deletes branch
    char unid[15];
    char brid[15];
    int c;
    system("cls");
    fflush(stdin);
    printf("Enter the University Id: ");
    scanf("%[^\n]", unid);
    fflush(stdin);
    printf("Enter the Branch Id: ");
    scanf("%[^\n]", brid);
    c = checkbr(brid, unid);
    if (c == 1)
    {
        printf("Error...No such Branch corresponding to Branch Id\n");
        return;
    }
    fflush(stdin);
    struct branch *temp = headbr, *temp1 = headbr, *temp2;
    if (strcmp(headbr->university_id, strupr(unid)) == 0 && strcmp(headbr->branch_id,
                                                                   strupr(brid)) == 0)
    {
        headbr = headbr->next;
        free(temp);
        printf("Branch deleted\n");
    }
    else
    {
        while (temp1->next != NULL)
        {
            if (strcmp(temp1->next->university_id, strupr(unid)) == 0 && strcmp(temp1->next->branch_id, strupr(brid)) == 0)
            {
                temp2 = temp1->next;
                temp1->next = temp1->next->next;
                free(temp2);
                printf("Branch deleted\n");
                break;
            }
            else
                temp1 = temp1->next;
        }
    }
}

void del_stu(struct student **head, char unid[], char brid[], int roll)
{ // deletes student
    int flag;
    system("cls");
    struct student *temp = (*head);
    while (temp != NULL)
    {
        if (strcmp(temp->university_id, strupr(unid)) == 0 && strcmp(temp->branch_id, strupr(brid)) == 0 && temp->roll == roll)
        {
            flag++;
            break;
        }
        temp = temp->next;
    }
    if (flag == 0)
        return;
    if (temp == (*head))
    {
        (*head) = (*head)->next;
        free(temp);
        printf("Student deleted\n");
    }
    else
    {
        struct student *temp2 = (*head);
        while (temp2->next != temp)
            temp2 = temp2->next;
        temp2->next = temp->next;
        free(temp);
        printf("Student deleted\n");
    }
}

void UniUpdate()
{ // updates details of university
    system("cls");
    char ch1;
    int flag = 0;
    struct university new;
    fflush(stdin);
    printf("For Updating information Enter that University Id: ");
    scanf("%[^\n]", new.university_id);
    struct university *temp = headuni;
    while (temp != NULL)
    {
        if (strcmp(temp->university_id, strupr(new.university_id)) == 0)
        {
            flag++;
            break;
        }

        temp = temp->next;
    }
    if (flag == 0)
    {
        printf("University_id Is Not Present In The University Database.\n");
        return;
    }
    system("cls");
    printf("If You want to Update Press 'Y' If Not Press 'N'	>>>\n");
    fflush(stdin);
    printf("\nDo you want to change University_id?: ");
    scanf("%c", &ch1);
    if (ch1 == 'Y')
    {
        fflush(stdin);
        printf("\nPlease Enter New University_id: ");
        scanf("%[^\n]", new.university_id);
        if (checkuni(new.university_id))
        {
            printf("The University Id already exist. Please enter another Id\n");
            return;
        }
        strcpy(temp->university_id, strupr(new.university_id));
    }
    fflush(stdin);
    printf("\nDo you want to change University_Name?: ");
    scanf("%c", &ch1);
    if (ch1 == 'Y')
    {
        fflush(stdin);
        printf("\nPlease Enter New University_Name: ");
        scanf("%[^\n]", new.name);
        strcpy(temp->name, strupr(new.name));
    }
    fflush(stdin);
    printf("\nDo you want to change University_location?: ");
    scanf("%c", &ch1);
    if (ch1 == 'Y')
    {
        fflush(stdin);
        printf("\nPlease Enter New University_location: ");
        scanf("%[^\n]", new.location);
        strcpy(temp->location, strupr(new.location));
    }
    fflush(stdin);
    printf("\nDo you want to change University_Year Of Start?: ");
    scanf("%c", &ch1);
    if (ch1 == 'Y')
    {
        fflush(stdin);
        printf("\nPlease Enter New University_year of start: ");
        scanf("%d", &new.yos);
        temp->yos = new.yos;
    }

    fflush(stdin);
    printf("\nUniversity was added to the database\n");
}

void BrUpdate()
{ // updates details of branch
    system("cls");
    struct branch new;
    char ch1;
    int flag = 0;
    fflush(stdin);
    printf("Enter the University Id: ");
    scanf("%[^\n]", new.university_id);
    if (!checkuni(new.university_id))
    {
        printf("Error...No such University corresponding to University Id\n");
        return;
    }
    fflush(stdin);
    printf("Enter the Branch Id: ");
    scanf("%[^\n]", new.branch_id);
    struct branch *br = headbr;
    while (br != NULL)
    {
        if (strcmp(br->university_id, strupr(new.university_id)) == 0 && strcmp(br->branch_id, strupr(new.branch_id)) == 0)
        {
            flag++;
            break;
        }
        br = br->next;
    }
    if (flag == 0)
    {
        printf("\nNo such branch-id present in the database.\n");
        return;
    }
    system("cls");
    printf("\nYou Want to change press ('Y') if not press('N')");
    fflush(stdin);
    printf("\nDo you want to change Branch-id?: ");
    scanf("%c", &ch1);
    if (ch1 == 'Y')
    {
        fflush(stdin);
        printf("\nPlease Enter Your new branch-id :");
        scanf("%[^\n]", new.branch_id);
        if (!checkbr(new.branch_id, new.university_id))
        {
            printf("The branch-id already exists\n");
            return;
        }
        strcpy(br->branch_id, strupr(new.branch_id));
    }
    fflush(stdin);

    printf("\nDo you want to change Branch?: ");
    scanf("%c", &ch1);
    if (ch1 == 'Y')
    {
        fflush(stdin);
        printf("\nPlease Enter the Branch name: ");
        scanf("%[^\n]", new.branch);
        strcpy(br->branch, strupr(new.branch));
    }
    printf("\nBranch Data was Updated.\n");
}

void stUpdate()
{ // updates details of student
    system("cls");
    struct student new;
    char ch1;
    int flag = 0;
    fflush(stdin);
    printf("Enter the University Id: ");
    scanf("%[^\n]", new.university_id);
    if (!checkuni(new.university_id))
    {
        printf("Error...No such University corresponding to University Id\n");
        return;
    }
    fflush(stdin);
    printf("Enter the Branch Id: ");
    scanf("%[^\n]", new.branch_id);
    struct branch *br = headbr;
    if (checkbr(new.branch_id, new.university_id))
    {
        printf("\nSuch type of branch-id is not present. Please Enter correct id.\n");
        return;
    }
    fflush(stdin);
    printf("Enter the student's roll no.: ");
    scanf("%d", &new.roll);
    if (checkroll(new.roll, new.branch_id, headst1))
    {
        if (checkroll(new.roll, new.branch_id, headst2))
        {
            printf("Invalid roll number\n");
            return;
        }
    }
    struct student *st1;
    for (struct student *temp = headst1; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->branch_id, strupr(new.branch_id)) == 0 && temp->roll == new.roll)
        {
            st1 = temp;
            break;
        }
    }
    for (struct student *temp = headst2; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->branch_id, strupr(new.branch_id)) == 0 && temp->roll == new.roll)
        {
            st1 = temp;
            break;
        }
    }
    system("cls");
    printf("\nIf you Want to change press ('Y') else press('N')");
    fflush(stdin);
    printf("\nDo you want to change Name of the student?: ");
    scanf("%c", &ch1);
    if (ch1 == 'Y')
    {
        fflush(stdin);
        printf("\nPlease Enter new Name: ");
        scanf("%[^\n]", new.name);
        strcpy(new.name, strupr(new.name));
        printf("%s\n", new.name);
        strcpy(st1->name, new.name);
        printf("%s\n", st1->name);
    }
    fflush(stdin);
    printf("\nDo you want to change cgpa?: ");
    scanf("%c", &ch1);
    if (ch1 == 'Y')
    {
        fflush(stdin);
        printf("\nPlease Enter New cgpa: ");
        scanf("%f", &new.cgpa);
        if (new.cgpa >= 6)
            flag = 1;
        else
            flag = 2;
    }
    fflush(stdin);
    printf("\nDo you want to change Roll Number? ");
    scanf("%c", &ch1);
    if (ch1 == 'Y')
    {
        while (1)
        {
            fflush(stdin);
            printf("\nPlease Enter New Roll No.: ");
            scanf("%d", &new.roll);
            if (!checkroll(new.roll, new.branch_id, st1))
            {
                printf("Roll number already in use.\n");
                printf("Please enter new roll number.\n");
                continue;
            }
            break;
        }
    }
    if (flag == 1)
    {
        struct student *st = (struct student *)malloc(sizeof(struct student));
        strcpy(st->name, st1->name);
        strcpy(st->university_id,
               new.university_id);
        strcpy(st->branch_id, new.branch_id);
        st->roll = new.roll;
        st->cgpa = new.cgpa;
        del_stu(&headst2, new.university_id, new.branch_id, st1->roll);
        if (headst1 == NULL)
        {
            headst1 = lstst1 = st;
            st->next = NULL;
            lstst1 = st;
        }
        else
        {
            lstst1->next = st;
            st->next = NULL;
            lstst1 = st;
        }
    }
    else if (flag == 2)
    {
        struct student *st = (struct student *)malloc(sizeof(struct student));
        strcpy(st->name, st1->name);
        strcpy(st->university_id,
               new.university_id);
        strcpy(st->branch_id, new.branch_id);
        st->roll = new.roll;
        st->cgpa = new.cgpa;
        del_stu(&headst1, new.university_id, new.branch_id, st1->roll);
        if (headst2 == NULL)
        {
            headst2 = lstst2 = st;
            st->next = NULL;
            lstst2 = st;
        }
        else
        {
            lstst2->next = st;
            st->next = NULL;
            lstst2 = st;
        }
    }
    printf("\nStudentData was Updated Successfully.\n");
}

void dis_uni_ascending()
{ // displays  the  university  in  ascending  order according to year of start
    system("cls");
    if (headuni == NULL)
        printf("University Database is empty\n");
    else
    {
        struct university *temp = headuni, *current, *t;
        int temp1;
        char temp2[30], temp3[30], temp4[30];

        printf("\n	\n");
        printf("\n\tList of Universities\n");
        printf("\n	\n");
        printf("University	ID\t\tName\t\t\t\t\t\t\tLocation\t\tYear of Start\n");
        for (current = headuni; current->next != NULL; current = current->next)
        {

            for (t = current->next; t != NULL; t = t->next)
            {
                if (current->yos > t->yos)
                {
                    temp1 = t->yos;
                    strcpy(temp2, t->university_id);
                    strcpy(temp3, t->name);
                    strcpy(temp4, t->location);
                    t->yos = current->yos;
                    strcpy(t->university_id, current->university_id);
                    strcpy(t->name, current->name);
                    strcpy(t->location, current->location);
                    current->yos = temp1;
                    strcpy(current->university_id, temp2);
                    strcpy(current->name, temp3);
                    strcpy(current->location, temp4);
                }
            }
        }
        while (temp != NULL)
        {
            printf("%-20s\t%-40s\t\t%-20s\t%d\n", temp->university_id, temp->name, temp->location, temp->yos);
            temp = temp->next;
        }
    }
}

void substring()
{ // displays strings matching with entered substring
    system("cls");
    char strng[13], *rt;
    int flag = 0;
    fflush(stdin);
    printf("Enter the sub string: ");
    scanf("%[^\n]", strng);
    strcpy(strng, strupr(strng));
    struct university *temp1 = headuni;
    struct branch *temp2 = headbr;
    struct student *temp3 = headst1;
    struct student *temp4 = headst2;
    while (temp1 != NULL)
    {
        rt = strstr(temp1->name, strng);
        if (rt)
            printf("%s\n", temp1->name, flag++);
        rt = strstr(temp1->location, strng);
        if (rt)
            printf("%s\n", temp1->location, flag++);
        rt = strstr(temp1->university_id, strng);
        if (rt)
            printf("%s\n", temp1->university_id, flag++);

        temp1 = temp1->next;
    }
    if (flag == 0)
        printf("No match found in University Database\n");
    flag = 0;
    while (temp2 != NULL)
    {
        rt = strstr(temp2->branch_id, strng);
        if (rt)
            printf("%s\n", temp2->branch_id, flag++);
        rt = strstr(temp2->branch, strng);
        if (rt)
            printf("%s\n", temp2->branch, flag++);
        temp2 = temp2->next;
    }
    if (flag == 0)
        printf("No match found in Branch Database\n");
    flag = 0;
    while (temp3 != NULL)
    {
        rt = strstr(temp3->name, strng);
        if (rt)
            printf("%s\n", temp3->name, flag++);
        temp3 = temp3->next;
    }
    while (temp4 != NULL)
    {
        rt = strstr(temp4->name, strng);
        if (rt)
            printf("%s\n", temp4->name, flag++);
        temp4 = temp4->next;
    }
    if (flag == 0)
        printf("No match found in Student Database\n");
}
