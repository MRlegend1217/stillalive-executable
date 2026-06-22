#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    const char *config_path = "hollywood.conf";
    FILE *config = fopen(config_path, "rb");
    if (!config) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    if (fseek(config, 0, SEEK_END) != 0) {
        perror("fseek");
        fclose(config);
        return EXIT_FAILURE;
    }

    long size = ftell(config);
    if (size < 0) {
        perror("ftell");
        fclose(config);
        return EXIT_FAILURE;
    }
    rewind(config);

    char *buffer = malloc(size > 0 ? size : 1);
    if (!buffer) {
        perror("malloc");
        fclose(config);
        return EXIT_FAILURE;
    }

    if (fread(buffer, 1, size, config) != (size_t)size) {
        perror("fread");
        free(buffer);
        fclose(config);
        return EXIT_FAILURE;
    }
    fclose(config);

    for (long i = 0; i < size; i++) {
        if (write(STDOUT_FILENO, buffer + i, 1) != 1) {
            perror("write");
            free(buffer);
            return EXIT_FAILURE;
        }

        // Base typing delay (approx 75 milliseconds) matching "Still Alive" tempo
        long delay = 75000; 

        // Punctuation and layout breaks matching the GLaDOS terminal engine mechanics
        if (buffer[i] == '.' || buffer[i] == '?' || buffer[i] == '!') {
            delay = 250000; // 250ms distinctive thought pause
        } else if (buffer[i] == ',' || buffer[i] == ':') {
            delay = 100000; // 100ms conversational pause
        } else if (buffer[i] == '\n' || buffer[i] == '\r') {
            delay = 150000; // 150ms carriage-return mechanical drop
        }

        usleep(delay);
    }

    free(buffer);
    return EXIT_SUCCESS;
}
