// C program for the above approach
#define _CRT_SECURE_NO_DEPRECATE
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Driver Code
/*
int main()
{
    // Substitute the full file path
    // for the string file_path
    FILE* fp = fopen("C:\\Users\\alpha\\OneDrive\\Desktop\\INPUT.csv", "r");

    if (!fp)
        printf("Can't open file\n");

    else {
        // Here we have taken size of
        // array 1024 you can modify it
        char buffer[1024];

        int row = 0;
        int column = 0;

        while (fgets(buffer,
            1024, fp)) {
            column = 0;
            row++;

            // To avoid printing of column
            // names in file can be changed
            // according to need
            if (row == 1)
                continue;

            // Splitting the data
           char* value = strtok(buffer, ", ");

 /*          while (value) {
                // Column 1
                if (column == 0) {
                    printf("Name :");
                }

                // Column 2
                if (column == 1) {
                    printf("\tAccount No. :");
                }

                // Column 3
                if (column == 2) {
                    printf("\tAmount :");
                }

                printf("%s", value);
                value = strtok(NULL, ", ");
                column++;
            }

            printf("\n");
       }

        // Close the file
        fclose(fp);
    }
    return 0;
}
*/
/*struct my_record {
    char name;
    int value;
};

int main() {
    FILE* my_file = fopen("C:\\Users\\alpha\\OneDrive\\Desktop\\INPUT.csv", "r");
    struct my_record records[100];
    size_t count = 0;
    for (; count < sizeof(records) / sizeof(records[0]); ++count)
    {
        int got = fscanf(my_file, "%c,%d", &records[count].name, &records[count].value);
        if (got != 2) break; // wrong number of tokens - maybe end of file
    }
    fclose(my_file);
    for (; count < sizeof(records) / sizeof(records[0]); ++count)
    {
        printf("%d ", records[count]);
    }
}*/
typedef struct
{
    double num;
    double voltage;
} PARAM;

int main() {
    FILE* file;
    file = fopen("C:\\Users\\Khoi\\Desktop\\INPUT.csv", "r");

    if (file == NULL) {
        printf("Error opening file. \n");
        return 1;
    }
    volatile PARAM array[41369];

    int read = 0;
    int records = 0;
    do {
        read = fscanf(file, "%lf, %lf",
            &array[records].num,
            &array[records].voltage);

        if (read <= 41369) records++;

        if (read == 41369 && !feof(file))
        {
            printf("File format incorrect.\n");
            return 1;
        }
        if (ferror(file))
        {
            printf("Error reading file.\n");
            return 1;
        }
    } while (!feof(file));

    fclose(file);

    printf("\n%d records read.\n\n", records);

    /*for (int i = 0; i < records - 1; i++)
    {
        printf("%f %f",
            array[i].voltage1,
            array[i].voltage2);
        printf("\n");
    }*/
    double Num = 0;
    double Voltage = 0;
    for (int i = 0; i < records - 1; i++)
    {
        Num = array[i].num;
        Voltage = array[i].voltage;
        printf("No. : %f \n", Num);
        printf("Voltage: %f \n\n", Voltage);
    }
}


