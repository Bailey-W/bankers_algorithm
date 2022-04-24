///////////////////
// Bailey Wimer
// 04/20/22
// bankers.c
// An implementation of the bankers algorithm in C
// Requires input.txt (see readme)
//

#include <stdio.h>

//True and false defined instead of including <stdbool.h>
#define FALSE 0
#define TRUE 1


int main(int argc, char **argv) {
  //File pointer
  FILE *fp;
  //Character buffer to read into from the file
  char buff[255];

  // Open the file "input.txt" in the source directory
  fp = fopen("./input.txt", "r");
  // Error handling in case the file doesn't exist
  if(!fp) {
    printf("Failed to open input.txt\n");
    return(1);
  }
  // The number of resources and the number of processes for the algorithm
  int numResources, numProcesses;
  // resource and process numbers get read from the first line of the file
  fscanf(fp, "%d", &numResources);
  fscanf(fp, "%d", &numProcesses);

  // The matrix of each process' allocated resources
  int allocated[numProcesses][numResources];
  // The matrix of each process' maximum resources
  int max[numProcesses][numResources];
  // The vector of available resources
  int available[numResources];
  // The matrix of resources left to fulfill each process
  int need[numProcesses][numResources];

  // The vector of process numbers in order that they will be safe to execute
  int safeSequence[numProcesses];
  // A vector of booleans (essentially) to track whether each process has been used in the safe sequence
  int used[numProcesses];

  // An int to track where in the safe sequence the program is
  int index = 0;

  // set used for each process to false by default
  for(int i = 0; i < numProcesses; ++i)
    used[i] = FALSE;

  // Reading in of each process' resource information
  for(int i = 0; i < numProcesses; ++i) {
    // for each process, loop through both the allocated and the max vectors
    for(int j = 0; j < 2 * numResources; ++j) {
      // if the number that is being read is for the allocated matrix
      if(j < numResources) {
        fscanf(fp, "%d", &allocated[i][j]);
      }
      // the number being read is for the max matrix
      else {
        fscanf(fp, "%d", &max[i][j - numResources]);
      }
    }
  }
  // Read in the available resource vector
  for(int i = 0; i < numResources; ++i) {
    fscanf(fp, "%d", &available[i]);
  }

  // Calculate the needed resources by subtracting the already allocated resources from the maximum resources
  for(int i = 0; i < numProcesses; ++i) {
    for(int j = 0; j < numResources; ++j) {
      need[i][j] = max[i][j] - allocated[i][j];
    }
  }

  // Banker's algorithm
  // The most you will ever have to loop through all processes is once for each process (i.e. for 5 processes, loop through all processes 5 times max)
  for(int k = 0; k < numProcesses; ++k) {
    // Loop through each process
    for(int i = 0; i < numProcesses; ++i) {
      // If the process is not yet in the safe sequence
      if(used[i] == 0) {
        int flag = FALSE;
        // determine if there are currently enough resources available to satisfy this process
        for(int j = 0; j < numResources; ++j) {
          if(need[i][j] > available[j]) {
            // if there aren't, set the flag to true and break out of this for loop
            flag = TRUE;
            break;
          }
        }
        // If it looped through all resources and the flag was never set, then add it to the safe sequence
        if(flag == FALSE) {
          // add current process to the sequence and increment the index after
          safeSequence[index++] = i;
          // "free up" the process' resources by adding them to the available resources
          for(int j = 0; j < numResources; ++j) {
            available[j] += allocated[i][j];
          }
          // mark the process as having been used in the safe sequence
          used[i] = TRUE;
        }
      }
    }
  }

  // A loop to check if all processes were used
  for(int i = 0; i < numProcesses; ++i) {
    //if any process was not used
    if(used[i] == FALSE) {
      printf("Not safe!\n");
      //exit the program
      return(0);
    }
  }
  // If you got this far, then it is safe
  printf("Safe! The sequences is: \n");
  // Print out the safe sequnce, then exit the program
  for(int i = 0 ; i < numProcesses - 1; ++i)
    printf("P%d => ", safeSequence[i]);
  printf("P%d\n", safeSequence[numProcesses - 1]);

  return(0);
}
