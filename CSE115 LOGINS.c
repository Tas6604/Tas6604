#include <stdio.h>

int main() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Writing predefined usernames and passwords
    fprintf(file, "Ahona Ahona123\n");
    fprintf(file, "Rafi Rafi123\n");
    fprintf(file, "Mushfik Mushfik123\n");
    fprintf(file, "Shaoni Shaoni123\n");
    fprintf(file, "Rahat Rahat123\n");

    fclose(file);
    printf("User list written to users.txt successfully.\n");

    return 0;
}
