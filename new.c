/*Task left:
1. Left to remove books that are returned, from lenders.txt and lendersWithoutName.txt
Make Seperate function for that
2. Left to add uppercase to all the elements*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#define AvailableBooks "AvailableBooks.txt"
#define BooksLended "lenders.txt"
#define BooksLendedWithoutNames "lendersWithoutName.txt"

struct books
{
    char id[10];
    char books[50];
}b1;


// To add current time
char* times(void)
{
	struct tm* ptr;
	time_t t;
	t = time(NULL);
	ptr = localtime(&t);
	return asctime(ptr);
}


// Making files for books which are lended
int lendFileWithoutName(char tmp[100])
{
    FILE *lend;
    lend = fopen(BooksLendedWithoutNames, "a");
    if(lend == NULL)
    {
        printf("Error");
        return 0;
    }
    // tmp[strcspn(tmp, "\n")] = '\0';
    fprintf(lend, "%s\n", tmp);
    fclose(lend);
}
// Making a file function for writing to lend.
int lendfiles(char tmp[100], char name[100])
{  
    FILE *fptr;
    fptr = fopen(BooksLended, "a");
    if (fptr == NULL)
    {
        printf("Error");
        return 0;
    }
    fprintf(fptr, "%s taken by %s on %s", tmp, name, times());
    fclose(fptr);
    return 0;

}

int writeToAvailableBooks(char bookID[10], char bookName[50])
{
    FILE *fptr;
    fptr = fopen(AvailableBooks, "a");
    if (fptr == NULL)
    {
        printf("Error!");
    }
    fprintf(fptr, "%s %s \n", bookID, bookName);
    fclose(fptr);

    
}




// Work in progress
int removeFromLenders(char bookID[10], char bookName[50])
{
    char id[10];
    char temp[100];
    FILE *tempLenders;
    FILE *tempLendersWithoutName;
    FILE *lenders;
    FILE *lendersWN;

    lenders = fopen(BooksLended, "a+");
    lendersWN = fopen(BooksLendedWithoutNames, "a+");

    tempLenders = fopen("temp_lenders.txt", "a");
    tempLendersWithoutName = fopen("temp_lendersWithoutName.txt", "a");

    if (tempLenders == NULL || tempLendersWithoutName == NULL || lenders == NULL || lendersWN == NULL)
    {
        printf("Error Opening File!");
        return 0;
    }
    while (fgets(temp, sizeof(temp), lenders))
    {
        
        sscanf(temp, "%s", id); // It is used to store a string before any whitespace to variable id.
        // printf("Comparing '%s' with '%s' \n", id, bookID);
        if (strcmp(id, bookID) != 0)
        {
            fputs(temp, tempLenders);
        }
        
    }
    fclose(lenders);
    fclose(tempLenders);
    remove(BooksLended);
    rename("temp_lenders.txt", BooksLended);
    for (int i = 0; temp[i] != '\0'; i++)
    {
        temp[i] = '\0';
    }
    
    while (fgets(temp, sizeof(temp), lendersWN))
    {
        sscanf(temp, "%s", id);
        if (strcmp(id, bookID) != 0)
        {
            fputs(temp, tempLendersWithoutName);
        }
        
    }
    fclose(tempLendersWithoutName);
    fclose(lendersWN);
    remove(BooksLendedWithoutNames);
    rename("temp_lendersWithoutName.txt", BooksLendedWithoutNames);

    return 0;
}




int returnfiles(char bookID[10], char bookName[50])
{
        FILE *returns;
        returns = fopen("returned.txt", "a");
        if (returns == NULL)
        {
            printf("Error returning book ");
            return 0;
        }
        fprintf(returns, "%s %s returned on %s\n", bookID, bookName, times());
        fclose(returns);
}


// To display all the available books
int displayBooks()
{
    char list;
    FILE *fptr;
    fptr = fopen(AvailableBooks, "r");
    printf("\nID  BOOK \n");
    printf("----------------------------------------------------------------------------------- \n");
    if (fptr == NULL)
    {
        printf("Empty file");
    }
    else
    {
        list = fgetc(fptr);
        while ((list != EOF))
        {
            printf("%c", list);
            list = fgetc(fptr);
        }
        
        // printf("\n Display Books");
    }
    fclose(fptr);
    return 0;
}



// To lend Books
int lendBooks(char selectedBookID[10])
{
    char name[100];   // Name of lender
    char tmp[100];    // Temporary variable to store content of a file

    FILE *fptr;
    FILE *tempfile;     
    fptr = fopen(AvailableBooks, "r");
    tempfile = fopen("temp.txt", "w");
    if (fptr == NULL || tempfile == NULL)
    {
        printf("Empty file");
    }
    else
    {
        while (fgets(tmp, 100, fptr) != NULL)   // tmp contains id and book name until \n
        {
            char id[10];
            sscanf(tmp, "%s", id); // It is used to store a string before any whitespace to variable id.
            if (strcmp(id, selectedBookID) != 0)
            {
                fputs(tmp, tempfile);
            }
            else
            {
                printf("Enter your name: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                tmp[strcspn(tmp, "\n")] = '\0';
                lendfiles(tmp, name);
                lendFileWithoutName(tmp);
            }
            
        }
    }
    fclose(fptr);
    fclose(tempfile);
    remove(AvailableBooks);
    rename("temp.txt", AvailableBooks);
    printf("\nLended successfully");
    return 0;
}


// Work in progress
// Check whether the book which is being returned is in the availableBooks or not.
// If yes say returned successfully and record the time.
int returnBooks(char bookID[10], char bookName[50])
{

    char bookinlend[50];    // Which have data from fgerts
    char tempid[10];    // ID from lendersWithoutName.txt
    char id[10];    // ID of book in the file
    // char bookID[10], bookName[50];  // Id and bookname that user will enter to return
    char bookFromLendersWNTxt[50];
    FILE *fptr;
    FILE *lend;
    FILE *lendWithoutName;

    char tmp[100];
    int count = 0;
    fptr = fopen(AvailableBooks, "a");
    lend = fopen(BooksLended, "a");
    lendWithoutName = fopen(BooksLendedWithoutNames, "a+");



    while (fgets(bookinlend, sizeof(bookinlend), lendWithoutName) != NULL)
    {
        // printf("%s", bookinlend);


        // Check if bookinlend is empty or not. If empty then continue.
        int is_empty = 1;
        for (int i = 0; bookinlend[i] != '\0'; i++)
        {
            if (!isspace((unsigned char) bookinlend[i]))
            {
                is_empty = 0;
                break;
            }
            
        }

        if (is_empty)
        {
            continue;
        }
        

        // To store numeric value i.e ID from the file
        int i=0;
        while (bookinlend[i] != ' ' && bookinlend[i] != '\0')
        {
            tempid[i] = bookinlend[i];
            i++;
            // printf("%s", tempid);
        }
        tempid[i] = '\0';

        // printf("%s", tempid);
        // Skipping the first whitespace after ID
        while (bookinlend[i] == ' ')
        {
            i++;
        }

        // Adding all the characters excluding ID in bookFromLendersWNTxt
        int j = 0;
        while (bookinlend[i] != '\0' && bookinlend[i] != '\n')
        {
            bookFromLendersWNTxt[j] = bookinlend[i];
            i++;
            j++;
        }
        bookFromLendersWNTxt[j] = '\0';
        // printf("%s", bookFromLendersWNTxt);


        // Now actual process to start returning books. 

        // Remove newline character from bookName
        bookName[strcspn(bookName, "\n")] = '\0';

        // Remove newline character from bookFromLendersWNTxt
        bookFromLendersWNTxt[strcspn(bookFromLendersWNTxt, "\n")] = '\0';

        // printf("%s", tempid);
        if (strcmp(tempid, bookID) == 0)
        {
            // printf("\n No book with this id was lended");
            // return 0;
        
        // printf("Comparing: '%s' and '%s'\n", bookName, bookFromLendersWNTxt);
        // printf(strcmp(bookName, bookFromLendersWNTxt));
            if (strcmp(bookName, bookFromLendersWNTxt) == 0)
            {
                printf("Retuned Successfully \n");
                fclose(fptr);
                fclose(lend);
                fclose(lendWithoutName);

                returnfiles(bookID, bookName);
                writeToAvailableBooks(bookID, bookName);
                removeFromLenders(bookID, bookName);
                return 0;
            }
            else
            {
                printf("This book was not lended.");
                return 0;
            }


        }

 
        for (int i = 0; tempid[i] != '\0'; i++)
        {
            tempid[i] = '\0';
        }
        // printf("The id is: %s", tempid);
    }
    printf("No book with this id was lended\n");
        
}

    



int addBooks(char bookID[10], char bookName[50])
{
    char temp[100];
    char id[10];
    FILE *fptr;
    fptr = fopen(AvailableBooks, "a+");
    while (fgets(temp, sizeof(temp), fptr))
    {
        sscanf(temp, "%s", id);
        printf("%s", id);
        if (strcmp(id, bookID) != 0)
        {
            fprintf(fptr, "%s %s", bookID, bookName);

        }
        else
        {
            printf("Id already exists.");
        }
        
    }
    printf("Added Successfully\n");
    fclose(fptr);
}



// Main function
int main()
{
    printf("\t\t Welcome to Library Management System By Shishir and Sulav \n");
    printf("----------------------------------------------------------------------------------- \n");

    printf("Notice: \n");
    printf("Please delete all the files that are previously creatd by this program.. Without deleting too the program might work \n");
    char choice;
    char availableBooks[100][50];
    int count=0;

    // Open file for appending
    FILE *fptr;
    fptr = fopen(AvailableBooks, "w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(0);
    }
    else
    {
        printf("File opened successfully \n");
        fprintf(fptr, "1 C Programming\n31 Engineering Physics\n09 Mathematics");
        fflush(fptr);
        fclose(fptr);
    }
    while (fgets(availableBooks[count], sizeof(availableBooks[count]), fptr) != NULL)
    {
        availableBooks[count][strcspn(availableBooks[count], "\n")] = '\0';
        count++;
    }
    // for (int i = 0; i < count; i++)
    // {
    //     printf("%s", availableBooks[i]);
    // }
    

    


    // If we want to add book. If we don't press 0
    // printf("How many books you want to add initially: (If not press 0)  ");
    // int n;
    // scanf("%d", &n);
    // getchar();

    // for(int i=1; i<=n; i++)
    // {
    //     printf("Add book id: ");
    //     scanf("%s", b1.id);

    //     printf("Add name of book: ");
    //     fgets(b1.books, 50, stdin);

    //     /* Write information to the file*/
    //     fprintf(fptr, "%s: %s", b1.id, b1.books);
    // }
    // printf("Add books with id:");
    // fclose(fptr);

    char bookID[10];
    char bookName[50];
    
    int continues = 1;

    do{
        // Emptying bookID and bookName
        for (int i = 0; bookID[i] != '\0'; i++)
        {
            bookID[i] = '\0';
        }
        for (int i = 0; bookName[i] != '\0'; i++)
        {
            bookName[i] = '\0';
        }
        

        // Taking choice of user
        printf("\nEnter 'D' to display books, 'L' to lend books, 'A to add books, 'R' to return books and 'S' to see the lended books: ");
        scanf(" %c", &choice);
        choice = toupper(choice);

        switch (choice)
        {
        case 'D':
            // printf("Display books");
            displayBooks();
            break;


        case 'L':
            printf("----------------------Lend books ----------------------\n");
            displayBooks();
            char selectedBookID[10];
            printf("\n\nPlease select the id of book you want to lend \n");
            printf("Which book you want to lend: ");
            scanf("%s", selectedBookID);
            getchar();
            lendBooks(selectedBookID);
            break;


        case 'A':
            printf("---------------------Add books------------------\n\n");
            printf("Enter id of the book: ");
            scanf("%s", bookID);
            getchar();
            printf("Enter name of book: ");
            fgets(bookName, sizeof(bookName), stdin);
            addBooks(bookID, bookName);
            break;


        case 'R':
            printf("----------------------Return books-----------------\n\n");

            printf("Please Enter the exact Id of the book you lended \n");
            // char bookID[10];
            // char bookName[50];

            printf("Enter id of book you want to return: ");
            scanf("%s", bookID);
            getchar();
            printf("\nPlease Enter Exact name of the book. Also consider upper and lower case characters\n");
            printf("Enter name of book:");
            fgets(bookName, 50, stdin);
            returnBooks(bookID, bookName);
            break;

        case 'S':
            printf("\n--------------------- Here are the books which are lended:------------------- \n\n");
            FILE *lend;
            char temp[100];
            lend = fopen(BooksLended, "r");
            while (fgets(temp, sizeof(temp), lend))
            {
                printf("%s", temp);
            }
            fclose(lend);
            break;

        default:
            printf("Invalid input");
            break;
        }

        printf("\n\nPress 0 to exit and 1 to continue: ");
        scanf("%d", &continues);

    }while(continues != 0);

    printf("\n Exited Library Management System");
    return 0;    
}
