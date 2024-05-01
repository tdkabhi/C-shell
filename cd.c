#include "headers.h" // Include header file for declarations

// Function to change directory based on arguments provided
void cd_func(char *string[], INT num, char *relative, char *correct, char *previous)
{
    if (num > 1) // If more than one argument is provided, show error
    {
        perror("Incorrect number of arguments supplied for command cd");
        return;
    }
    else if (num == 1) // If exactly one argument is provided
    {
        INT dir_ret; // Variable to store return status of chdir()

        if (string[0][0] == '~') // Check if the argument starts with '~' (home directory)
        {
            // Allocate memory and construct the path to the home directory
            char *modify_path = (char *)calloc(600, sizeof(char));
            strcpy(modify_path, correct); // Copy home directory path into modify_path
            strcat(modify_path, &string[0][1]); // Append the rest of the path after '~'
            dir_ret = chdir(modify_path); // Change directory to modify_path
        }
        else if (string[0][0] == '-') // Check if argument is '-'
        {
            if (previous[0] == '#') // If previous directory is not set
            {
                perror("OLDPWD NOT SET");
                return;
            }
            else // Previous directory is set
            {
                char *modify_path = (char *)calloc(600, sizeof(char)); // Allocate memory for path

                if (previous[0] == '~') // If previous path starts with '~'
                {
                    char *modify_path1 = (char *)calloc(600, sizeof(char));
                    strcpy(modify_path1, correct); // Copy home directory path
                    strcat(modify_path1, &previous[1]); // Append rest of the previous path after '~'
                    dir_ret = chdir(modify_path1); // Change to this constructed path
                    printf("%s\n", modify_path1); // Print the path
                }
                else // If previous path does not start with '~'
                {
                    strcpy(modify_path, previous); // Use previous path as is
                    dir_ret = chdir(modify_path); // Change to previous path
                    printf("%s\n", modify_path); // Print the path
                }
            }
        }
        else // If the argument is a normal path
        {
            dir_ret = chdir(string[0]); // Change directory to the specified path
        }

        if (dir_ret == -1) // If chdir() failed
        {
            perror(NULL); // Print error
            return;
        }
        else // If chdir() succeeded
        {
            strcpy(previous, relative); // Update previous directory with current relative path

            // Get the absolute path of the current directory
            char *dir_absolute = getcwd(NULL, 300);
            if (dir_absolute == NULL) // If getcwd failed
            {
                perror(NULL);
                return;
            }

            char *p = strstr(dir_absolute, correct); // Check if current path includes the home directory
            if (p) // If the path includes the home directory
            {
                INT len1 = strlen(dir_absolute); // Length of current absolute path
                INT len2 = strlen(correct); // Length of home directory path
                char *curr_dir1 = (char *)calloc(len1 - len2 + 2, sizeof(char)); // Allocate for relative path
                curr_dir1[0] = '~'; // Start relative path with '~'

                // Copy the part of the path after the home directory
                INT i = 1;
                for (i = 1; i <= len1 - len2; i++)
                {
                    curr_dir1[i] = dir_absolute[len2 + i - 1];
                }
                curr_dir1[i] = '\0'; // Null-terminate
                strcpy(relative, curr_dir1); // Update relative path
            }
            else // If the path does not include the home directory
            {
                strcpy(relative, dir_absolute); // Set relative path as absolute path
            }
        }
    }
    else if (num == 0) // If no arguments are provided, go to home directory
    {
        INT dir_ret; // Variable to store return status of chdir()
        char *modify_path = (char *)calloc(600, sizeof(char)); // Allocate memory for path

        strcpy(modify_path, correct); // Set modify_path to home directory
        dir_ret = chdir(modify_path); // Change directory to home directory
        if (dir_ret == -1) // If chdir() failed
        {
            perror(NULL); // Print error
            return;
        }
        else // If chdir() succeeded
        {
            strcpy(previous, relative); // Update previous directory with current relative path

            // Get absolute path of the current directory
            char *dir_absolute = getcwd(NULL, 300);
            if (dir_absolute == NULL) // If getcwd failed
            {
                perror(NULL);
                return;
            }

            char *p = strstr(dir_absolute, correct); // Check if path includes home directory
            if (p) // If path includes home directory
            {
                INT len1 = strlen(dir_absolute); // Length of current absolute path
                INT len2 = strlen(correct); // Length of home directory path
                char *curr_dir1 = (char *)calloc(len1 - len2 + 2, sizeof(char)); // Allocate for relative path
                curr_dir1[0] = '~'; // Start relative path with '~'

                // Copy the rest of the path after home directory
                INT i = 1;
                for (i = 1; i <= len1 - len2; i++)
                {
                    curr_dir1[i] = dir_absolute[len2 + i - 1];
                }
                curr_dir1[i] = '\0'; // Null-terminate
                strcpy(relative, curr_dir1); // Update relative path
            }
            else // If path does not include home directory
            {
                strcpy(relative, dir_absolute); // Set relative path as absolute path
            }
        }
    }
}
