#include "headers.h" // Includes header file with necessary declarations

// Function to move a stopped background job to a running state
void BG(char *string[], long long int num_tokens, List *LIST)
{
    if (num_tokens == 1) // Check if exactly one argument is provided
    {
        char *ptr1;
        INT job_number = strtol(string[0], &ptr1, 10); // Convert job number from string to integer

                struct node *head = LIST->root; // Start at the beginning of the job list
        while (head != NULL) // Traverse the job list
        {
            if (head->idx == job_number) // Find job with matching job number
            {
                INT pid = head->Element; // Get the process ID (PID)
                INT return_kill = kill(pid, SIGCONT); // Send SIGCONT to resume the process
                if (return_kill == -1) // Error handling for kill command
                {
                    perror(NULL); // Print error if unable to resume
                    return;
                }
                return; // Exit function if job is successfully resumed
            }

                       head = head->Next; // Move to the next job in the list if not found
        }
        perror("No job with given job number exists"); // Print error if no matching job is found
        return; // Exit function if job is not found
    }
    return;
}
