#include <stdio.h>
#include <stdlib.h>

void split_file(const char *filename, int part_size) {
    FILE *source = fopen(filename, "rb");
    if (!source) {
        perror("Erreur d'ouverture du fichier source");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    int bytes_read, part_number = 1;
    char part_filename[256];
   while (!feof(source)) {
       // Créer un nom de fichier pour chaque partie
     snprintf(part_filename, sizeof(part_filename), "%s.part%d", filename, part_number++);
        
        FILE *dest = fopen(part_filename, "wb");int main(int argc, char *argv[]) {
    int part_size;

    if (argc != 3) {
        fprintf(stderr, "Utilisation : %s nomfichier taille\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    part_size = atoi(argv[2]);
    if (part_size <= 0) {
        fprintf(stderr, "Taille invalide.\n");
        exit(EXIT_FAILURE);
    }
        if (!dest) {
            perror("Erreur de création de fichier de sortie");
            fclose(source);
            exit(EXIT_FAILURE);
        }
       int remaining_size = part_size;
        while (remaining_size > 0 && (bytes_read = fread(buffer, 1, (sizeof(buffer) < remaining_size) ? sizeof(buffer) : remaining_size, source)) > 0) {
            fwrite(buffer, 1, bytes_read, dest);
            remaining_size -= bytes_read;
        }
        fclose(dest);
    }
    fclose(source);
}
int main(int argc, char *argv[]) {
    int part_size;

    if (argc != 3) {
        fprintf(stderr, "Utilisation : %s nomfichier taille\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    part_size = atoi(argv[2]);
    if (part_size <= 0) {
        fprintf(stderr, "Taille invalide.\n");
        exit(EXIT_FAILURE);
    }

    split_file(argv[1], part_size);
    printf("Fichier divisé avec succès.\n");
    return 0;
}

