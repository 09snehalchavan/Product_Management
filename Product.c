#include <stdio.h>
#include <string.h>

struct Product
{
    int product_id;
    char product_name[100];
    int product_price;
    int product_quantity;
};

struct Product p[100];
int count = 0;

void clear_input_buffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

int read_positive_int(const char *prompt)
{
    int value;

    while (1)
    {
        printf("%s", prompt);
        if (scanf("%d", &value) != 1)
        {
            printf("\nInvalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (value > 0)
        {
            return value;
        }

        printf("\nValue must be greater than 0.\n");
    }
}

int read_non_negative_int(const char *prompt)
{
    int value;

    while (1)
    {
        printf("%s", prompt);
        if (scanf("%d", &value) != 1)
        {
            printf("\nInvalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (value >= 0)
        {
            return value;
        }

        printf("\nValue must be 0 or greater.\n");
    }
}

void read_product_name(char name[100], const char *prompt)
{
    while (1)
    {
        printf("%s", prompt);
        scanf("%99s", name);

        if (name[0] != '\0')
        {
            return;
        }

        printf("\nProduct name cannot be empty.\n");
    }
}

void create_product_file()
{
    FILE *fp = fopen("Product.txt", "a+");
    if (fp == NULL)
    {
        printf("\nUnable to create Product.txt file.\n");
        return;
    }
    fclose(fp);
}

int is_product_id_exist(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (p[i].product_id == id)
        {
            return 1;
        }
    }
    return 0;
}

void load_product()
{
    create_product_file();

    FILE *fp = fopen("Product.txt", "r");
    if (fp == NULL)
    {
        return;
    }

    while (fscanf(fp, "%d %s %d %d",
                  &p[count].product_id,
                  p[count].product_name,
                  &p[count].product_price,
                  &p[count].product_quantity) == 4)
    {
        count++;
    }

    fclose(fp);
}

void save_product()
{
    FILE *fp = fopen("Product.txt", "w");
    if (fp == NULL)
    {
        printf("\nUnable to save product data.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d %s %d %d\n",
                p[i].product_id,
                p[i].product_name,
                p[i].product_price,
                p[i].product_quantity);
    }

    fclose(fp);
}

void add_product()
{
    int n;

    while (1)
    {
        printf("\nHow many products do you want to add? = ");
        if (scanf("%d", &n) != 1)
        {
            printf("\nInvalid input. Please enter a valid number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (n <= 0)
        {
            printf("\nPlease enter a valid number.\n");
            continue;
        }
        break;
    }

    if (count + n > 100)
    {
        printf("\nStorage limit reached. You can add at most %d products.\n", 100 - count);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        int index = count + i;
        int id;

        printf("\nEnter Product %d Details!!!\n", i + 1);

        do
        {
            printf("Enter Product ID = ");
            if (scanf("%d", &id) != 1)
            {
                printf("\nInvalid product ID. Please enter a valid number.\n");
                clear_input_buffer();
                id = -1;
                continue;
            }
            clear_input_buffer();

            if (id <= 0)
            {
                printf("\nProduct ID must be greater than 0.\n");
                continue;
            }

            if (is_product_id_exist(id))
            {
                printf("\nProduct ID already exists. Please enter a different ID.\n");
            }
        } while (id <= 0 || is_product_id_exist(id));

        p[index].product_id = id;
        read_product_name(p[index].product_name, "Enter Product Name = ");
        p[index].product_price = read_positive_int("Enter Product Price = ");
        p[index].product_quantity = read_non_negative_int("Enter Product Quantity = ");
    }

    count += n;
    save_product();
    printf("\nProducts added successfully.\n");
}

void display_product()
{
    if (count == 0)
    {
        printf("\nNo products available.\n");
        return;
    }

    printf("\n---------------------------------------------------------\n");
    printf("Product ID\tProduct Name\tProduct Price\tProduct Quantity\n");
    printf("---------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("%d\t\t%s\t\t%d\t\t%d\n",
               p[i].product_id,
               p[i].product_name,
               p[i].product_price,
               p[i].product_quantity);
    }

    printf("---------------------------------------------------------\n");
}

void search_product()
{
    int id;
    int found = 0;

    printf("\nEnter Product ID to search = ");
    if (scanf("%d", &id) != 1)
    {
        printf("\nInvalid product ID. Please enter a valid number.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (id <= 0)
    {
        printf("\nProduct ID must be greater than 0.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (p[i].product_id == id)
        {
            printf("\nProduct Found!\n");
            printf("ID: %d\n", p[i].product_id);
            printf("Name: %s\n", p[i].product_name);
            printf("Price: %d\n", p[i].product_price);
            printf("Quantity: %d\n", p[i].product_quantity);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nProduct with ID %d not found.\n", id);
    }
}

void low_product()
{
    int threshold;
    int found = 0;

    threshold = read_non_negative_int("\nEnter low stock threshold = ");

    printf("\nProducts with quantity <= %d:\n", threshold);

    for (int i = 0; i < count; i++)
    {
        if (p[i].product_quantity <= threshold)
        {
            printf("ID: %d | Name: %s | Price: %d | Quantity: %d\n",
                   p[i].product_id,
                   p[i].product_name,
                   p[i].product_price,
                   p[i].product_quantity);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No product is below the threshold.\n");
    }
}

void update_product()
{
    int id;
    int found = 0;

    printf("\nEnter Product ID to update = ");
    if (scanf("%d", &id) != 1)
    {
        printf("\nInvalid product ID. Please enter a valid number.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    for (int i = 0; i < count; i++)
    {
        if (p[i].product_id == id)
        {
            printf("\nCurrent Product Details:\n");
            printf("Name: %s\n", p[i].product_name);
            printf("Price: %d\n", p[i].product_price);
            printf("Quantity: %d\n", p[i].product_quantity);

            read_product_name(p[i].product_name, "\nEnter new Product Name = ");
            p[i].product_price = read_positive_int("Enter new Product Price = ");
            p[i].product_quantity = read_non_negative_int("Enter new Product Quantity = ");

            save_product();
            printf("\nProduct updated successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nProduct with ID %d not found.\n", id);
    }
}

void delete_product()
{
    int id;
    int found = 0;

    printf("\nEnter Product ID to delete = ");
    if (scanf("%d", &id) != 1)
    {
        printf("\nInvalid product ID. Please enter a valid number.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (id <= 0)
    {
        printf("\nProduct ID must be greater than 0.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (p[i].product_id == id)
        {
            for (int j = i; j < count - 1; j++)
            {
                p[j] = p[j + 1];
            }
            count--;
            save_product();
            printf("\nProduct deleted successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nProduct with ID %d not found.\n", id);
    }
}

void total_inventory_value()
{
    long long total = 0;

    for (int i = 0; i < count; i++)
    {
        total += (long long)p[i].product_price * p[i].product_quantity;
    }

    printf("\nTotal Inventory Value = %lld\n", total);
}

int main()
{
    int choice;
    load_product();

    printf("\n====================Inventory Management System====================\n");
    printf("\n1. Add Product");
    printf("\n2. List of Product");
    printf("\n3. Find the Product");
    printf("\n4. Low Stock Product");
    printf("\n5. Update Product");
    printf("\n6. Delete Product");
    printf("\n7. Total Inventory Value");
    printf("\n8. Exit\n");

    do
    {
        printf("\nEnter your choice = ");
        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid choice. Please select a valid option.\n");
            clear_input_buffer();
            choice = 0;
        }
        else
        {
            clear_input_buffer();
        }

        switch (choice)
        {
        case 1:
            add_product();
            break;

        case 2:
            display_product();
            break;

        case 3:
            search_product();
            break;

        case 4:
            low_product();
            break;

        case 5:
            update_product();
            break;

        case 6:
            delete_product();
            break;

        case 7:
            total_inventory_value();
            break;

        case 8:
            printf("\nThank You So Much....!!!!!\n");
            break;

        default:
            printf("\nPlease choose a valid option...!!!!!\n");
        }

    } while (choice != 8);

    return 0;
}