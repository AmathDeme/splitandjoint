#include <stdio.h>
#include <stdlib.h>

void join_files(int part_count, char *parts[], const char *output_filename) {
    FILE *output = fopen(output_filename, "wb");
    if (!output) {
        perror("Erreur d'ouverture du fichier de sortie");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    int bytes_read;
    int i;
    FILE *part;

    for (i = 0; i < part_count; i++) {
        part = fopen(parts[i], "rb");
        if (!part) {
            perror("Erreur d'ouverture de la partie");
            fclose(output);
            exit(EXIT_FAILURE);
        }

        while ((bytes_read = fread(buffer, 1, sizeof(buffer), part)) > 0) {
            fwrite(buffer, 1, bytes_read, output);
        }
        fclose(part);
    }

    fclose(output);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Utilisation : %s fichier_sortie part1 part2 ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    join_files(argc - 2, &argv[2], argv[1]);
    printf("Fichiers joints avec succès en '%s'.\n", argv[1]);
    return 0;
}