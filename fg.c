#include "headers.h" // Includes necessary headers

// Function to move a job to the foreground
void FG(char *string[], long long int num_tokens, List *LIST)
{
    if (num_tokens == 1) // Ensure exactly one argument is provided
    {
        char *ptr1;
        INT job_number = strtol(string[0], &ptr1, 10); // Convert job number from string to integer
        struct node *head = LIST->root; // Points to the start of the job list
        while (head != NULL) // Traverse the job list
        {
            if (head->idx == job_number) // Find job with matching job number
            {
                INT pid = head->Element; // Retrieve process ID (PID)
                INT calling_group_id = getpgid(0); // Get process group ID for current shell
                setpgid(pid, calling_group_id); // Move job to the shell's group
                signal(SIGTTOU, SIG_IGN); // Temporarily ignore terminal signals
                signal(SIGTTIN, SIG_IGN); // Ignore terminal signals

                INT tc_return1 = tcsetpgrp(0, pid); // Set terminal control to the job
                if (tc_return1 == -1) // Check for errors
                {
                    perror(NULL); // Display error if setting terminal fails
                    return;
                }
                INT return_kill = kill(pid, SIGCONT); // Resume job with SIGCONT signal
                if (return_kill == -1) // Error handling for kill
                {
                    perror(NULL);
                    return;
                }

                int status;
                waitpid(pid, &status, WUNTRACED|WSTOPPED); // Wait for job to complete or stop
                INT tc_return2 = tcsetpgrp(0, getpgid(0)); // Return terminal control to shell
                if (tc_return2 == -1) // Error handling
                {
                    perror(NULL);
                    return;
                }
                signal(SIGTTIN, SIG_DFL); // Reset terminal signals to default
                signal(SIGTTOU, SIG_DFL); // Reset terminal signals to default

                char *string2 = (char *)malloc(600 * sizeof(char));
                string2 = find_string(LIST, head->Element); // Get job description
                DELETE(LIST, find(LIST, head->Element, string2)); // Remove job from list
                free(string2); // Free allocated memory
                return;
            }
            head = head->Next; // Move to next job if not found
        }
        perror("No job with given job number exists"); // Error if job not found
        return;
    }
}
