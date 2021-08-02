#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


#define ISO_8601_TIME_DATE_LENGHT 22


int evaluate_args(int argc, char** argv, char* valid_flags, int* active_flag_place);
int return_longest_array_in_matrix(char** matrix, int matrix_rows);
int set_iso_8601_time(char* buffer, size_t buffer_size);


int main(int argc, char* argv[]) {

    /* You need to add one letter to valid_flags, */
    /* and one string to flag_messages. */
    /* When changes are made. Re-compile with make. */
    char valid_flags[] = "htwf";
    char* flag_messages[] = {"high", "toilet", "workout", "fun"};


    /* Check if user has inputed an equal amount of flags and messages */
    if (strlen(valid_flags) != (sizeof(flag_messages) / sizeof(flag_messages[0]))) {
        fprintf(stderr, "Number of flags does not equal messages\nPlease edit code and re-compile\n");
        exit(EXIT_FAILURE);
    }

    int valid_flags_count = strlen(valid_flags);
    int active_flag_place[valid_flags_count];
    int i;


    /* Disable all flags */
    for (i = 0; i < valid_flags_count; ++i) {
        active_flag_place[i] = 0;
    }

    /* Enable flags entered by user */
    evaluate_args(argc, argv, valid_flags, active_flag_place);


    int active_flags_count = 0;
    for (i = 0; i < valid_flags_count; ++i) {
        if (active_flag_place[i] == 1) {
            ++active_flags_count;
        }
    }


    /* Filter out unactive flags */
    char* active_messages[active_flags_count];
    int total_message_lenght = 0;

    {
        int j = 0;
        for (i = 0; i < valid_flags_count; ++i) {
            if (active_flag_place[i] == 1) {
                active_messages[j] = flag_messages[i];
                total_message_lenght += strlen(active_messages[j]);
                ++j;
            }
        }
    }


    /* Handle if user did not enter flags */
    if (active_flags_count == 0) {
        active_messages[0] = "tracker";
        total_message_lenght += strlen(active_messages[0]);
        ++active_flags_count;
    }


    /* Formats messages to make them readable */
    char* message_cat;
    {
        char message_separator[] = ", ";
        if ((message_cat = malloc((total_message_lenght) + (strlen(message_separator) * (active_flags_count - 1)) * sizeof(char))) == NULL) {
            perror("Unable to allocate memory");
            exit(EXIT_FAILURE);
        }

        for (i = 0; i < active_flags_count - 1; ++i) {
            strcat(message_cat, active_messages[i]);
            strcat(message_cat, message_separator);
        }

        strcat(message_cat, active_messages[i]);
    }



    /* Gets time in ISO 8601 format: YYYY-MM-DDThh:mm+0000 */
    char time_date_ISO_8601[ISO_8601_TIME_DATE_LENGHT];
    set_iso_8601_time(time_date_ISO_8601, ISO_8601_TIME_DATE_LENGHT);



    int longest_message_lenght = return_longest_array_in_matrix(active_messages, active_flags_count);
    char* file_names[longest_message_lenght];

    {
        /* Sets file names. */

        char* home_path = getenv("HOME");
        char* home_to_name = "/var/tracker/";
        size_t file_name_space;

        for (i = 0; i < active_flags_count; ++i) {
            file_name_space = (strlen(home_path) + strlen(home_to_name) + strlen(active_messages[i])) * sizeof(char);

            if ((file_names[i] = malloc(file_name_space)) == NULL) {
                perror("Unable to allocate memory");
                exit(EXIT_FAILURE);
            }

            strcat(file_names[i], home_path);
            strcat(file_names[i], home_to_name);
            strcat(file_names[i], active_messages[i]);

        }
    }



    FILE** fp = malloc(sizeof(FILE *) * active_flags_count);

    {
        /* Opens files and writes to them */
        for (i = 0; i < active_flags_count; ++i) {
            if ((fp[i] = fopen(file_names[i], "a")) == NULL) {
                fprintf(stderr, "FILE: %s could not be opened\n", file_names[i]);
                exit(EXIT_FAILURE);
            }
        }

        /* writes date to end of file */
        for (i = 0; i < active_flags_count; ++i) {
            fprintf(fp[i], "%s %s\n", time_date_ISO_8601, message_cat);
        }

        for (i = 0; i < active_flags_count; ++i) {
            printf("%s %s. has been written to: %s\n", time_date_ISO_8601, message_cat, file_names[i]);
        }
    }

    /* Frees allocated memory and closes files */
    for (i = 0; i < active_flags_count; ++i) {
        fclose(fp[i]);
        free(file_names[i]);
    }
    free(fp);
    free(message_cat);

    return EXIT_SUCCESS;
}


int evaluate_args(int argc, char** argv, char* valid_flags, int* active_flag_place) {
    /* Evaluates arguments. */
    /* Changes modes to true if vaild flag is found. */
    /* Takes use of modes and list of vaild flags. */

    if (argc == 1) {
        /* No args */
        return 0;
    } else {

        extern int opterr;
        opterr = 0;
        int option;

        int i;
        while ((option = getopt(argc, argv, valid_flags)) != -1) {
            for (i = 0; i < strlen(valid_flags); ++i) {
                if (valid_flags[i] == option) {
                    active_flag_place[i] = 1;
                    break;
                } else if (option == '?') {
                    fprintf(stderr, "Error: Flag [-%c] is not implemented\n", optopt);
                    exit(EXIT_FAILURE);
                }
            }
        }

        int index;
        for (index = optind; index < argc; index++) {
            fprintf (stderr, "Error: Not a valid argument: %s\n", argv[index]);
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}


int return_longest_array_in_matrix(char** matrix, int matrix_rows) {

    if (matrix_rows < 1) {
        return EXIT_FAILURE;
    }

    int longest_array_lenght = 0;
    int i;

    for (i = 0; i < matrix_rows; ++i) {
        if (sizeof(matrix[i]) > longest_array_lenght) {
            longest_array_lenght = sizeof(matrix[i]);
        }
    }

    return longest_array_lenght;
}


/* ISO_8601 = YYYY-MM-DDThh:mm+0000 */
int set_iso_8601_time(char* buffer, size_t buffer_size) {
    if (buffer_size < ISO_8601_TIME_DATE_LENGHT) {
        fprintf(stderr, "Buffer size too small\n");
        return EXIT_FAILURE;
    }


    /* Sets time for time date. */
    time_t raw_time; 
    struct tm* tm_info; 

    time(&raw_time); 
    tm_info = localtime(&raw_time); 


    strftime(buffer, buffer_size, "%Y-%m-%dT%H:%M%z", tm_info);

    return EXIT_SUCCESS;
}
