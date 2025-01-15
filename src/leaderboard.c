#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

void save_to_leaderboard(int score, char *name){
    FILE *file = fopen("bin/leaderboard.txt", "a+");
    if (file == NULL){
        printw("Error opening file!\n");
        refresh();
        exit(1);
    }
    rewind(file);


    // Read existing scores
    int scores[6] = {0};
    char names[6][50] = {0};
    int count = 0;
    while (fscanf(file, "%s %d", names[count], &scores[count]) != EOF && count < 5) {
        count++;
    }
    fclose(file);

    // Add new score
    scores[count] = score;
    strcpy(names[count], name);
    count++;

    // Sort scores
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (scores[i] < scores[j]) {
                int temp_score = scores[i];
                scores[i] = scores[j];
                scores[j] = temp_score;
                char temp_name[50];
                strncpy(temp_name, names[i], 50);
                strncpy(names[i], names[j], 50);
                strncpy(names[j], temp_name, 50);
            }
        }
    }

    // Save top 5 scores
    file = fopen("bin/leaderboard.txt", "w");
    if (file == NULL){
        printf("Error opening file!\n");
        exit(1);
    }
    for (int i = 0; i < 5 && i < count; i++) {
        fprintf(file, "%s %d\n", names[i], scores[i]);
    }
    fclose(file);
}

void print_leaderboard(){
    FILE *file = fopen("bin/leaderboard.txt", "r");
    if (file == NULL){
        printw("Error opening file!\n");
        refresh();
        exit(1);
    }

    int scores[5] = {0};
    char names[5][50] = {0};
    int count = 0;
    while (fscanf(file, "%s %d", names[count], &scores[count]) != EOF && count < 5) {
        count++;
    }
    fclose(file);

    clear();
    printw("Leaderboard:\n");
    refresh();
    for (int i = 0; i < count; i++) {
        printw("%d. %s %d\n", i + 1, names[i], scores[i]);
        refresh();
    }
}