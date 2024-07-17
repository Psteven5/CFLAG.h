#include <assert.h>
#include <stdlib.h>

#include "CFLAG.h"

/* You do need to name argc and argv respectively! */
int main(int argc, char **argv) {
  
  /* The actual variable values are the default flag values. */
  char const *name = NULL;
  int rcount = 1;
  bool crash = false;
  bool helpFlag = false;

  /* Calling CFLAG creates a command line flag with the same name of the variable. */
  /* CFLAGS does this for multiple at the same time! (convenience...) */
  /* So this creates 3 flags: -name, -rcount, -crash, and -help. */

  /* They can be set with -FLAG=VALUE and -FLAG VALUE. */
  /* The value is automatically parsed based on the variable type. */

  /* Specifying no value sets the variable to NULL. (-FLAG= or -FLAG) */
  /* Boolean flags are the inverse, as they are set to true and disregard all values! */
  CFLAGS(name, rcount, crash);

  /* Calling CFLAG again on the same flag fetches the next value. */
  /* For example: -mynameis=what -mynameis=who -mynameis="chka-chka, Slim Shady". */
  /* The value stays the same if there is no more of the flag to be found. */
  CFLAG(rcount);

  /* Calling the single CFLAG with a second argument allows you to pick a different name. */
  /* Now the var is still helpFlag, but the actual flag is -help. */
  CFLAG(helpFlag, "help");
  
  if (helpFlag) {
    assert(0 && "define your own help section for the flags here :))");
  }

  if (crash) {
    for (int _ = rcount; _ > 0; --_) {
      printf(
          "I remember it now!\n"
          "He is the bandicoot that crashes into things!\n"
          "...that's why his name is Crash-\n");
    }
    abort();
  }

  if (NULL != name) {
    if (0 == strncmp("Crash Bandicoot", name, sizeof("Crash Bandicoot"))) {
      printf(
          "The name is %s!\n"
          "Although I don't remember what he does...\n", name);
    } else {
      printf("No, that isn't the name...\n");
    }
  } else {
    printf("I don't remember the name...\n");
  }
}
