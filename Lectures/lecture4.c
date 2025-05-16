
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the person struct
typedef struct {
    int age;
    float height;
    int name_len; // number of bytes in the name (excluding null terminator)
    char name[];  // flexible array member
} Person;

int main() {
    // Sample data
    const char *sample_name = "Alice";
    int age = 25;
    float height = 5.6;

    // Calculate name length
    int name_len = strlen(sample_name);

    // Allocate memory for Person + name
    Person *p = malloc(sizeof(Person) + name_len + 1); // +1 for null terminator

    if (!p) {
        perror("malloc");
        return 1;
    }

    // Fill in data
    p->age = age;
    p->height = height;
    p->name_len = name_len;
    strcpy(p->name, sample_name); // copy name into the flexible array

    // Write to file
    FILE *fp = fopen("person.bin", "wb");
    if (!fp) {
        perror("fopen");
        free(p);
        return 1;
    }

    fwrite(p, sizeof(Person) + name_len + 1, 1, fp);
    fclose(fp);
    free(p);

    // Read from file
    fp = fopen("person.bin", "rb");
    if (!fp) {
        perror("fopen (read)");
        return 1;
    }

    // Read static part first
    Person temp;
    fread(&temp, sizeof(Person), 1, fp);

    // Allocate memory for full structure with name
    Person *p_read = malloc(sizeof(Person) + temp.name_len + 1);
    if (!p_read) {
        perror("malloc (read)");
        fclose(fp);
        return 1;
    }

    // Copy static part
    *p_read = temp;

    // Read name
    fread(p_read->name, temp.name_len + 1, 1, fp);
    fclose(fp);

    // Display read data
    printf("Read from file:\n");
    printf("Age: %d\n", p_read->age);
    printf("Height: %.2f\n", p_read->height);
    printf("Name: %s\n", p_read->name);

    free(p_read);
    return 0;
}
