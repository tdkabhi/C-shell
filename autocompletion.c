#include "headers.h" // Includes necessary headers for the project
#include <dirent.h> // For working with directory entries

// Extern variables used globally across the shell environment
extern char *user_name; // Stores the username for the prompt
extern char *system_name; // Stores the system name for the prompt
extern char *relative_path; // Stores the current directory for the prompt

// Comparator function to sort directory entries alphabetically
int compare2(const void *arg1, const void *arg2) {
    return (strcmp((*((struct dirent **)arg1))->d_name, (*((struct dirent **)arg2))->d_name));
}

// Another comparator function for sorting strings
int sortstring(const void *str1, const void *str2) {
    char *const *pp1 = str1;        
    char *const *pp2 = str2;
    return strcmp(*pp1, *pp2);
}

/*
Function: autocomplete
Purpose: Implements autocompletion for shell commands by listing all possible 
         files/directories matching the user's input.
Parameters:
 - char *dir: Directory to search in.
 - char *input_find: Partial input to match files/directories against.
 - char *input: Full user input string.
 - INT slash_index: Index where '/' was found in the input.
 - INT end_index: End index of the current input.
Returns: A long long int status code (-2 for errors, other values indicate success).
*/


// Structure to store directory entries
/*
struct dirent {
    ino_t          d_ino;       // inode number
    off_t          d_off;       // offset to the next dirent 
    unsigned short d_reclen;    // length of this record
    unsigned char  d_type;      // type of file; not supported by all file system types
    char           d_name[256]; // filename
};
*/

long long int autocomplete(char *dir, char *input_find, char *input, INT slash_index, INT end_index) {
    
    // Allocate memory for output string to display matched entries
    char *print_string = (char *)calloc(1000, sizeof(char));
    print_string[0] = '\0';
    struct dirent **name_list;

    // Scans the directory for entries and sorts them alphabetically
    INT num_directory_entries = scandir(dir, &name_list, NULL, alphasort);
    if (num_directory_entries == -1) { // Error handling for invalid directories
        if (errno == ENOTDIR) {
            printf("\n");
            perror("Directory not found in autocomplete: ");
            return -2; // Return error code
        } else {
            perror(NULL); // Print other errors
            return -2;
        }
    }

    if (num_directory_entries == 0) { // Handle empty directories
        printf("\n");
        perror("Number of directory entries is 0 in autocompletion");
        return -2;
    }

    // Sorts directory entries using the custom compare2 function
    qsort(name_list, num_directory_entries, sizeof(name_list[0]), compare2);
    INT find_len = strlen(input_find); // Length of the input pattern to match

    // Array to store matched entries
    char *found_strings[num_directory_entries + 1];
    for (INT i = 0; i < num_directory_entries + 1; i++) {
        found_strings[i] = (char *)calloc(600, sizeof(char));
    }

    INT found_strings_index = 0; // Index for matched entries
    INT dir_index = -1;

    // Loop to find all matches that start with input_find
    for (INT i = 0; i < num_directory_entries; i++) {
        if (strlen(input_find) == 0 && (strcmp(name_list[i]->d_name, ".") != 0) && 
            (strcmp(name_list[i]->d_name, "..") != 0)) {
            strcpy(found_strings[found_strings_index], name_list[i]->d_name);
            found_strings_index++;
            dir_index = i;
        } else if (strncmp(input_find, name_list[i]->d_name, find_len) == 0 && 
                   (strcmp(name_list[i]->d_name, ".") != 0) && 
                   (strcmp(name_list[i]->d_name, "..") != 0)) {
            strcpy(found_strings[found_strings_index], name_list[i]->d_name);
            found_strings_index++;
            dir_index = i;
        }
    }

// This loop iterates through all entries (num_directory_entries(output of scandir)) in the directory.
// It checks if input_find is an empty string or if input_find matches the beginning of a directory entry name (name_list[i]->d_name).
// Entries . and .. are ignored to avoid matching the current and parent directories.
// If a match is found, the name is copied to found_strings, an array that stores all matching entries.
// The found_strings_index is incremented to keep track of the number of matches, and dir_index is updated with the current index, storing the last matched entry index

    if (found_strings_index == 0) {
        return 0; // No matches found
    } else if (found_strings_index == 1) { // Single match found
        char *string = (char *)calloc(1000, sizeof(char));
        strcpy(string, &dir[0]);//Copies the directory name to string

        // Checks if directory is valid, adds '/' if it is a directory
        if (strcmp(&dir[0], ".") == 0) {
            strcat(string, "/");
        }
        strcat(string, &(name_list[dir_index]->d_name)[0]);
        struct stat fs;
        //The struct stat structure in C, defined in <sys/stat.h>, holds information about files and directories. 
        //This structure is commonly used to obtain detailed metadata about files, such as permissions, ownership, size, and modification times.

        INT R = stat(string, &fs);//GIVES INFO ABOUT FILE WBICH IS PASSED IN STRING IN fs.
        if (R == -1) {//If stat() fails, it returns -1.
            printf("string is %s\n", string);
            perror("Invalid path to lstat in autocompletion");
            return -2;
        }
// Here, if found_strings_index is 0, no matches were found, so the function exits with a return value of 0.
// If there’s only one match, it allocates memory for string, constructs a path using dir and the matching entry name, and stores this path in string.
// It then uses stat() on string to check if this match is a valid path.
// If stat() fails (return value -1), it prints an error with perror and exits with -2.
        // Determines if the match is a directory or file

        INT J = S_ISDIR(fs.st_mode);//st_mode is a member of the stat structure that holds the file type and mode.S_ISDIR checks if the file is a directory.
        INT F = S_ISREG(fs.st_mode);//S_ISREG checks if the file is a regular file.

        if (J) { // Directory: Adds '/' after name
            strcat(print_string, &(name_list[dir_index]->d_name)[0]);
            INT print_length = strlen(print_string);
            print_string[print_length] = '/';
            print_string[print_length + 1] = '\0';
            input[slash_index + 1] = '\0';
            strcat(input, print_string);
            printf("%s", &input[end_index + 1]);
            INT display_size = 1000;
            char *display = (char *)calloc(display_size, sizeof(char));
            sprintf(display, "\r%s<%s@%s:%s>\033[0m", KMAG, user_name, system_name, relative_path);
            write(1, display, strlen(display));
            printf("%s", input);
//             The S_ISDIR and S_ISREG macros are used on fs.st_mode to determine if the match is a directory (J) or a regular file (F).
// If it’s a directory (J is true), the function adds a / after the directory name in print_string.
// It then updates input with print_string and displays this completed input line to the user.
// Finally, it updates the prompt display with user and system information, showing the autocompleted input.
        } else if (F) { // File: Adds a space after name
            strcat(print_string, &(name_list[dir_index]->d_name)[0]);
            INT print_length = strlen(print_string);
            print_string[print_length] = ' ';
            print_string[print_length + 1] = '\0';
            input[slash_index + 1] = '\0';
            strcat(input, print_string);
            INT display_size = 1000;
            char *display = (char *)calloc(display_size, sizeof(char));
            sprintf(display, "\r%s<%s@%s:%s>\033[0m", KMAG, user_name, system_name, relative_path);
            write(1, display, strlen(display));
            printf("%s", input);
//             If the match is a regular file (F is true), it appends a space to print_string after the file name.
// input is updated with the matched file name and displayed to the user in the prompt.
// If there are multiple matches, the function sorts them alphabetically using qsort and displays them all.
        }
    } else {
        // Multiple matches found: Sort them and display
        qsort(found_strings, found_strings_index, sizeof(found_strings[0]), sortstring);
        INT same_prefix;
        printf("\n");

        // Display each match and highlight directories with '/'
        for (INT i = 0; i < found_strings_index; i++) {
            char *string = (char *)calloc(1000, sizeof(char));
            strcpy(string, &dir[0]);
            if (strcmp(&dir[0], ".") == 0) {
                strcat(string, "/");
            }
            strcat(string, found_strings[i]);
            struct stat fs;
            INT R = stat(string, &fs);
            if (R == -1) {
                printf("dir is %s and string is %s\n", &dir[0], string);
                perror("Invalid directory in lstat in autocompletion");
                return -2;
            }
//             A loop iterates over each found match.
// For each match, it constructs the full path by combining dir and the matched entry name, storing the result in string.
// It calls stat() on this path to check if it’s valid.
// If stat() fails, it prints an error message with the directory name and string path, then exits with -2.
            INT J = S_ISDIR(fs.st_mode);
            INT F = S_ISREG(fs.st_mode);
            if (J) {
                printf("%s/\n", found_strings[i]);
            } else if (F) {
                printf("%s\n", found_strings[i]);
            }
        }

        // Finds common prefix among multiple matches
        INT len1 = strlen(found_strings[0]);
        INT len2 = strlen(found_strings[found_strings_index - 1]);
        INT min_len = len1 < len2 ? len1 : len2;
        for (INT i = 0; i < min_len; i++) {
            if (found_strings[0][i] == found_strings[found_strings_index - 1][i]) {
                print_string[i] = found_strings[0][i];
                print_string[i + 1] = '\0';
            } else {
                break;
            }
        }
//         S_ISDIR and S_ISREG macros are again used to check if each match is a directory or file.
// Directories are displayed with a trailing / and files without.
// The function then determines the longest common prefix among the matches, comparing the first and last matches (since the list is sorted).
// It sets print_string to the common prefix for use in the final output.

        // Display updated prompt and input
        INT display_size = 1000;
        char *display = (char *)calloc(display_size, sizeof(char));
        sprintf(display, "%s<%s@%s:%s>\033[0m", KMAG, user_name, system_name, relative_path);
        write(1, display, strlen(display));
        input[slash_index + 1] = '\0';
        strcat(input, print_string);
        INT input_length = strlen(input);
        input[input_length] = '\0';
        printf("%s", input);
        free(print_string);
//         The prompt is updated with the common prefix print_string added to input.
// The prompt is formatted to show user, system, and directory information and the autocompleted input.
// Finally, print_string memory is freed, and the function returns 0 to indicate success.
    }
    return 0; // Success
}
