#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define TRUE 1

struct Customers
{
    int reg;
    char name[100];
    int age;
    char gender;
    char phoneNumber[20];
    char address[100];
    char membershipcard;
    int cardPoints;
}customer[100];
struct Items
{
    int itemCode;
    char name[100];
    char category[100];
    int quantity;
    float price;
}item[100];
// struct Bill
// {
//     char itemName[100];
//     int quantity;
//     float price;
// };

//Customer
int readCustomerFile()
{
    FILE *customer_File;
    int numberOfCustomers;
    customer_File = fopen("customerInfo.txt", "r");
    if (customer_File == NULL){
        printf("Error! customerInfo.txt Not Found!");
        return -1;
    }
    fscanf(customer_File, "%d", &numberOfCustomers);
    for (int i = 0; i < numberOfCustomers; i++)
    {
        fscanf(customer_File, "%d %s %d %c %s %s %c %d", &customer[i].reg, customer[i].name, &customer[i].age,
               &customer[i].gender, customer[i].phoneNumber, customer[i].address, &customer[i].membershipcard,
               &customer[i].cardPoints);
    }
    fclose(customer_File);
    return numberOfCustomers;
}
void writeCustomerFile(int numberOfCustomers)
{
    FILE *customer_File;
    customer_File = fopen("customerInfo.txt", "w");
    fprintf(customer_File, "%d\n", numberOfCustomers);
    for (int i = 0; i < numberOfCustomers; i++)
    {
        fprintf(customer_File, "%d %s %d %c %s %s %c %d\n", customer[i].reg, customer[i].name, customer[i].age,
                customer[i].gender, customer[i].phoneNumber, customer[i].address, customer[i].membershipcard,
                customer[i].cardPoints);
    }
    fclose(customer_File);
    return;
}
void display(int n)
{
    for (int i = 0; i < n; i++)
    {
        if (customer[i].membershipcard == 'Y')
        {
            printf("name:");
            puts(customer[i].name);
            printf("registration number : %d\n", customer[i].reg);
        }
    }
}
int searchCustomer(int size, char name[])
{
    struct Customers searchResult[100];
    int count = 0;
    int searchSize = 0;
    for (int i = 0; i < size; i++){
        if (strcmp(customer[i].name, name) == 0){
            searchResult[searchSize].reg = customer[i].reg;
            strcpy(searchResult[searchSize].name, customer[i].name);
            searchResult[searchSize].age = customer[i].age;
            searchResult[searchSize].gender = customer[i].gender;
            strcpy(searchResult[searchSize].phoneNumber, customer[i].phoneNumber);
            strcpy(searchResult[searchSize].address, customer[i].address);
            searchResult[searchSize].membershipcard = customer[i].membershipcard;
            searchResult[searchSize].cardPoints = customer[i].cardPoints;
            searchSize++;
        }
    }
    if (searchSize > 0)
    {
        printf("\n%d match(es) Found!\n", searchSize);
        for (int i = 0; i < searchSize; i++)
        {
            printf("Reg No: %d Name: %s Age: %d Gender: %c Phone: %s Address: %s Membership: %c Card Points: %d\n",searchResult[i].reg, searchResult[i].name, searchResult[i].age,
                   searchResult[i].gender, searchResult[i].phoneNumber, searchResult[i].address, searchResult[i].membershipcard,
                   searchResult[i].cardPoints);
        }
        return searchSize;
    }
    Beep(610,500);
    printf("                                                   *******************\n");
    printf("                                                      !! NOT FOUND !!   \n");
    printf("                                                    *******************\n\n");
    return 0;

}
int deleteCustomer(int numberOfCustomers)
{
    int searchSize;
    char searchName[100];
    int searchReg;
    int foundFlag = 0;
    printf("Enter the name: ");
    scanf("%s", searchName);
    if (searchSize = searchCustomer(numberOfCustomers, searchName))
    {
        if (searchSize > 1)
        {
            printf("Enter the registration number of whom you you want to delete: ");
            scanf("%d", &searchReg);
        }
        for (int i = 0; i < numberOfCustomers; i++)
        {
            if ((strcmp(customer[i].name, searchName) == 0) &&
                ((customer[i].reg == searchReg) || searchSize == 1))
            {
                for (int j = i; j < numberOfCustomers; j++)
                {
                    customer[j] = customer[j + 1];
                }
                writeCustomerFile(numberOfCustomers - 1);
                numberOfCustomers--;
                foundFlag = 1;
                break;
            }
        }
    }
    if (foundFlag == 1){
    printf("                      *********************    *******************\n");
    printf("                                 !!DELETED SUCCESSFULLY!!          \n");
    printf("                      *********************    *******************\n\n");

    } else
    {
        Beep(610,500);
    printf("                      *********************    *******************\n");
    printf("                   !!Delete Failed! Wrong Name or Registration Number!!\n");
    printf("                      *********************    *******************\n\n");
    }
    printf("Returning to Main Menu....\n");
    return numberOfCustomers;
}
void editCustomer(int numberOfCustomers)
{
    int searchSize;
    char searchName[100];
    int searchReg;
    int foundFlag = 0;
    printf("Enter the name: ");
    scanf("%s", searchName);
    if (searchSize = searchCustomer(numberOfCustomers, searchName))
    {
        if (searchSize > 1)
        {
            printf("Enter the registration number of whom you you want to edit: ");
            scanf("%d", &searchReg);
        }


        for (int i = 0; i < numberOfCustomers; i++)
        {
            if ((strcmp(customer[i].name, searchName) == 0) &&
                ((customer[i].reg == searchReg) || searchSize == 1))
            {
                printf("Enter name, age, gender, phone, address, membership and points:\n");
                scanf("%s %d %c %s %s %c %d", customer[i].name, &customer[i].age,
                      &customer[i].gender, customer[i].phoneNumber, customer[i].address, &customer[i].membershipcard,
                      &customer[i].cardPoints);
                writeCustomerFile(numberOfCustomers);
                foundFlag = 1;
                break;
            }
        }
    }
    if (foundFlag == 1){
        printf("Edit Successful!\n");
    } else
    {
        Beep(610,500);
        printf("                      *********************    *******************\n");
        printf("                      !! Edit Failed! Wrong Registration Number !!\n");
        printf("                      *********************    *******************\n\n");
    }
    printf("Returning to Main Menu....\n");
}
void displayAllCustomers(int numberOfCustomers)
{
    for (int i = 0; i < numberOfCustomers; i++)
    {
        printf("Reg No: %d Name: %s Age: %d Gender: %c Phone: %s Address: %s Membership: %c Card Points: %d\n", customer[i].reg, customer[i].name, customer[i].age,
                customer[i].gender, customer[i].phoneNumber, customer[i].address, customer[i].membershipcard,
                customer[i].cardPoints);
    }
}
int addCustomer(int numberOfCustomers)
{
    customer[numberOfCustomers].reg = customer[numberOfCustomers-1].reg + 1;
    printf("\nEnter Name: ");
    scanf("%s", customer[numberOfCustomers].name);
    printf("Enter Age: ");
    scanf("%d", &customer[numberOfCustomers].age);
    printf("Enter Gender(M/F): ");
    scanf(" %c", &customer[numberOfCustomers].gender);
    printf("Enter Phone Number: ");
    scanf("%s", customer[numberOfCustomers].phoneNumber);
    printf("Enter Address: ");
    scanf("%s", customer[numberOfCustomers].address);
    printf("Enter Membership status(Y/N): ");
    scanf(" %c", &customer[numberOfCustomers].membershipcard);
    if (customer[numberOfCustomers].membershipcard == 'Y')
    {
        printf("Enter Card Points: ");
        scanf("%d", &customer[numberOfCustomers].cardPoints);
    } else
    {
        customer[numberOfCustomers].cardPoints = 0;
    }
    numberOfCustomers++;
    writeCustomerFile(numberOfCustomers);
    printf("Successfully added!\n");
    return numberOfCustomers;
}

//Item
int readItemFile()
{
    FILE *item_File;
    int numberOfItems;
    item_File = fopen("itemInfo.txt", "r");
    if (item_File == NULL){
        printf("Error! itemInfo.txt Not Found!");
        return -1;
    }
    fscanf(item_File, "%d", &numberOfItems);
    for (int i = 0; i < numberOfItems; i++)
    {
        fscanf(item_File, "%d %s %s %d %f",&item[i].itemCode, item[i].name, item[i].category, &item[i].quantity, &item[i].price);
    }
    fclose(item_File);
    return numberOfItems;
}
void writeItemFile(int numberOfItems)
{
    FILE *item_File;
    item_File = fopen("itemInfo.txt", "w");
    fprintf(item_File, "%d\n", numberOfItems);
    for (int i = 0; i < numberOfItems; i++)
    {
        fprintf(item_File, "%d %s %s %d %.2f\n",item[i].itemCode, item[i].name, item[i].category,
                item[i].quantity, item[i].price);
    }
    fclose(item_File);
    return;
}
int searchItem(int size, char name[])
{
    struct Items searchResult[100];
    int count = 0;
    int searchSize = 0;
    for (int i = 0; i < size; i++){
        if (strcmp(item[i].name, name) == 0){
            searchResult[searchSize].itemCode = item[i].itemCode;
            strcpy(searchResult[searchSize].name, item[i].name);
            strcpy(searchResult[searchSize].category, item[i].category);
            searchResult[searchSize].quantity = item[i].quantity;
            searchResult[searchSize].price = item[i].price;
            searchSize++;
        }
    }
    if (searchSize > 0)
    {
        printf("\n%d match(es) Found!\n", searchSize);
        for (int i = 0; i < searchSize; i++)
        {
            printf("Code: %d Name: %s Category: %s Quantity: %d Price: %.2f\n",searchResult[i].itemCode, searchResult[i].name, searchResult[i].category,
                searchResult[i].quantity, searchResult[i].price);
        }
        return searchSize;
    }
    Beep(610,500);
    printf("                                                   *******************\n");
    printf("                                                      !! NOT FOUND !!   \n");
    printf("                                                    *******************\n\n");
    return 0;

}
int deleteItem(int numberOfItems)
{
    char searchName[100];
    int searchReg;
    int foundFlag = 0;
    int searchSize;
    printf("Enter the name: ");
    scanf("%s", searchName);
    if (searchSize = searchItem(numberOfItems, searchName))
    {
        if (searchSize > 1)
        {
            printf("Enter the registration number of whom you you want to delete: ");
            scanf("%d", &searchReg);
        }
        for (int i = 0; i < numberOfItems; i++)
        {
            if ((strcmp(item[i].name, searchName) == 0) &&
                ((item[i].itemCode == searchReg) || searchSize == 1))
            {
                for (int j = i; j < numberOfItems; j++)
                {
                    item[j] = item[j + 1];
                }
                writeItemFile(numberOfItems - 1);
                numberOfItems--;
                foundFlag = 1;
                break;
            }
        }
    }
    if (foundFlag == 1){
        printf("Delete Successful!\n");
    } else
    {
        Beep(610,500);
        printf("Delete Failed! Wrong Item code.\n");
    }
    printf("Returning to Main Menu....\n");

    return numberOfItems;
}
void editItem(int numberOfItems)
{
    char searchName[100];
    int searchReg;
    int foundFlag = 0;
    int searchSize;
    printf("Enter the name: ");
    scanf("%s", searchName);
    if (searchSize = searchItem(numberOfItems, searchName))
    {
        if (searchSize > 1)
        {
            printf("Enter the registration number of whom you you want to edit: ");
            scanf("%d", &searchReg);
        }

        for (int i = 0; i < numberOfItems; i++)
        {
            if ((strcmp(item[i].name, searchName) == 0) &&
                ((item[i].itemCode == searchReg) || searchSize == 1))
            {
                printf("Enter name, category, quantity, price:\n");
                scanf("%s %s %d %f", item[i].name, item[i].category,
                      &item[i].quantity, &item[i].price);
                writeItemFile(numberOfItems);
                foundFlag = 1;
                break;
            }
        }
    }
    if (foundFlag == 1){
        printf("Edit Successful!\n");
    } else
    {
        Beep(610,500);
        printf("Edit Failed! Wrong Item code.\n");
    }
    printf("Returning to Main Menu....\n");
}
void displayAllItems(int numberOfItems)
{
    for (int i = 0; i < numberOfItems; i++)
    {
        printf("Code: %d Name: %s Category: %s Quantity: %d Price: %.2f\n",item[i].itemCode, item[i].name, item[i].category,
                item[i].quantity, item[i].price);
    }
}
int addItem(int numberOfItems)
{
    item[numberOfItems].itemCode = item[numberOfItems-1].itemCode + 1;
    printf("\nEnter Name: ");
    scanf("%s", item[numberOfItems].name);
    printf("Enter Category: ");
    scanf("%s", item[numberOfItems].category);
    printf("Enter Quantity: ");
    scanf("%d", &item[numberOfItems].quantity);
    printf("Enter price: ");
    scanf("%f", &item[numberOfItems].price);
    numberOfItems++;
    writeItemFile(numberOfItems);
    printf("Successfully added!\n");
    return numberOfItems;
}
int showAllItemsInStock(int size)
{
    struct Items searchResult[100];
    int count = 0;
    int searchSize = 0;
    for (int i = 0; i < size; i++){
        if (item[i].quantity > 0){
            searchResult[searchSize] = item[i];
            // searchResult[searchSize].itemCode = item[i].itemCode;
            // strcpy(searchResult[searchSize].name, item[i].name);
            // strcpy(searchResult[searchSize].category, item[i].category);
            // searchResult[searchSize].quantity = item[i].quantity;
            // searchResult[searchSize].price = item[i].price;
            searchSize++;
        }
    }
    if (searchSize > 0)
    {
        printf("\n%d products are in stock!\n", searchSize);
        for (int i = 0; i < searchSize; i++)
        {
            printf("Code: %d Name: %s Category: %s Quantity: %d Price: %.2f\n",searchResult[i].itemCode, searchResult[i].name, searchResult[i].category,
                searchResult[i].quantity, searchResult[i].price);
        }
        return 1;
    }
    printf("Everything is out of stock!\n");
    return 0;

}

//Common
void displayMenu()
{
    time_t now;
    time(&now);
    printf("\n\t\t\t\t\t\t%s",ctime(&now));

    printf("                                   ****************************************************\n");
    printf("                                   WELCOME TO THE MAIN MENU OF GROCERY MANAGMENT SYSTEM\n");
    printf("                                   ****************************************************\n\n");

    printf("\t\t\t\t\t------------------------------------------\n");
    printf("\t\t\t\t\t|1.Calculate Bill                        |\n");
    printf("\t\t\t\t\t|2.Delete a customer info                |\n");
    printf("\t\t\t\t\t|3.modify contact no. and address        |\n");
    printf("\t\t\t\t\t|4.Search a customer information         |\n");
    printf("\t\t\t\t\t|5.Display all customer                  |\n");
    printf("\t\t\t\t\t|6.Add customer                          |\n");
    printf("\t\t\t\t\t|7.Add item                              |\n");
    printf("\t\t\t\t\t|8.Display membership holder info.       |\n");
    printf("\t\t\t\t\t|9.Search an Item                        |\n");
    printf("\t\t\t\t\t|10.Delete an Item                       |\n");
    printf("\t\t\t\t\t|11.Edit an Item                         |\n");
    printf("\t\t\t\t\t|12.Show all items inStock               |\n");
    printf("\t\t\t\t\t|13.Display all items                    |\n");
    printf("\t\t\t\t\t|14.Exit                                 |\n");
    printf("\t\t\t\t\t------------------------------------------\n");
}
int searchItemInStock(int size, char name[])
{
    struct Items searchResult[100];
    int count = 0;
    int searchSize = 0;
    for (int i = 0; i < size; i++){
        if (strcmp(item[i].name, name) == 0 && item[i].quantity > 0){
            searchResult[searchSize].itemCode = item[i].itemCode;
            strcpy(searchResult[searchSize].name, item[i].name);
            strcpy(searchResult[searchSize].category, item[i].category);
            searchResult[searchSize].quantity = item[i].quantity;
            searchResult[searchSize].price = item[i].price;
            searchSize++;
        }
    }
    if (searchSize > 0)
    {
        printf("\n%d matches Found!\n", searchSize);
        for (int i = 0; i < searchSize; i++)
        {
            printf("Code: %d Name: %s Category: %s Quantity: %d Price: %.2f\n",searchResult[i].itemCode, searchResult[i].name, searchResult[i].category,
                searchResult[i].quantity, searchResult[i].price);
        }
        return searchSize;
    }
    printf("Out of Stocks!\n");
    return 0;

}
void calculateBill(int numberOfItems, int numberOfCustomers)
{
    struct Items bill[100];
    char name[100];
    int code;
    float total = 0;
    int foundFlag = 0;
    int billIndex = 0;
    char askNew;
    char customerName[100];
    int searchSizeI;

    while (TRUE)
    {
        printf("\nEnter item name or 'stop': ");
        scanf("%s", name);
        if (strcmp(name, "stop") == 0)
        {
            break;
        }
        if (searchSizeI = searchItemInStock(numberOfItems, name))   //function returns 1 if the searched item is in stock. else returns 0.
        {
            if (searchSizeI > 1)
            {
                printf("\nEnter item code: ");
                scanf("%d", &code);
            }
            foundFlag = 0;
            for (int i = 0; i < numberOfItems; i++)     //checking for required item info.
            {
                if ((strcmp(item[i].name, name) == 0) &&    //selecting exact item
                    ((item[i].itemCode == code) || searchSizeI == 1))
                {
                    foundFlag = 1;
                    printf("Enter the quantity: ");
                    scanf("%d", &bill[billIndex].quantity); //taking quantity input
                    if (bill[billIndex].quantity > item[i].quantity) //checking if input exceeds the stock amount
                    {
                        printf("Not enough stock!\n");
                        break;
                    }
                    item[i].quantity -= bill[billIndex].quantity;
                    writeItemFile(numberOfItems);   //updating item stock in file.
                    strcpy(bill[billIndex].name, item[i].name); //storing in separate array
                    bill[billIndex].price = item[i].price;
                    total = total + (bill[billIndex].quantity * bill[billIndex].price);
                    billIndex++;
                    break;
                }
            }
            if (foundFlag == 0) //if name and code does not match
            {
                printf("Wrong item code!\n");
            }

        }

    }
    if (billIndex > 0)
    {
        printf("\t\t\t\t\b\bCustomer's Bill\n");
        printf("SN.   Name\t\tQuantity\t Price(TK)\t  Total(TK)\n");
        for (int i = 0; i < billIndex; i++) //to print the items added to cart
        {
            printf("%2d    %s\t\t%4d\t\t%8.2fTK\t %8.2fTK\n", i + 1, bill[i].name, bill[i].quantity, bill[i].price, bill[i].quantity*bill[i].price);
        }
        printf("\t\t\t\t\b\bTotal Amount: %.2fTK\n", total);
    }
    printf("Returning to Main Menu....\n");
}


int main()
{
    system("color 8F");
    int numberOfCustomers;

    int numberOfItems;

    char searchName[100];

    numberOfCustomers = readCustomerFile(customer);
    if (numberOfCustomers == -1){
        return -1;
    }

    numberOfItems = readItemFile(item);
    if (numberOfCustomers == -1){
        return -1;
    }

    int x;
    while (TRUE)
    {

        displayMenu();
        printf("\nenter your choice:");
        scanf("%d", &x);
        system("cls");
        switch (x)
        {
            case 1:
                calculateBill(numberOfItems, numberOfCustomers);

                break;

            case 2:

                numberOfCustomers = deleteCustomer(numberOfCustomers);
                break;

            case 3:

                editCustomer(numberOfCustomers);
                break;

            case 4:
                printf("Enter the name: ");
                scanf("%s", searchName);
                searchCustomer(numberOfCustomers, searchName);
                break;

            case 5:

                displayAllCustomers(numberOfCustomers);
                break;

            case 6:

                numberOfCustomers = addCustomer(numberOfCustomers);
                break;

            case 7:

                numberOfItems = addItem(numberOfItems);
                break;

            case 8:

                display(numberOfCustomers);
                break;

            case 9:
                system("color 5F");
                printf("Enter the name: ");
                scanf("%s", searchName);
                searchItem(numberOfItems, searchName);
                break;
            case 10:

                numberOfItems = deleteItem(numberOfItems);
                break;

            case 11:

                editItem(numberOfItems);
                break;
            case 12:
                showAllItemsInStock(numberOfCustomers);
                break;
            case 13:
                displayAllItems(numberOfItems);
                break;
            case 14:
                printf("Thank you for using our application!");
                return 0;
            default:
                printf("Thank you for using our application!");
                return 0;
        }
    }
}

