// $Id: l8stat.c,v 1.1 2013-11-26 10:27:48-08 - - $
// Michael Walton (mwwalton@ucsc.edu)

#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <locale.h>

#define SEC_PER_DAY (24 * 60 * 60)

void print_err(char *bname, char *pathname, int *exit_status) {
  *exit_status = EXIT_FAILURE;
  fflush (NULL);
  fprintf (stderr, "%s: %s: %s\n", bname, pathname, strerror (errno));
  fflush (NULL);
}

void print_local (time_t t) {
  struct tm *lt;
  lt = localtime(&t);
  char timebuf[80];
  char *timefmt;

  time_t now;
  time(&now);

  double elapsed = difftime(now, t);
  double future = difftime(t,now);
  double seconds_days = SEC_PER_DAY * 180;

  if (elapsed <= seconds_days && future <= seconds_days) {
    timefmt = "%b %e %R";
  } else timefmt = "%b %e  %Y";

  strftime(timebuf, sizeof(timebuf), timefmt, lt);
  printf("%s ",timebuf);
}

void print_stats (char *pathname, struct stat fileStat) {
  char linkname[PATH_MAX + 1];
  ssize_t retval = readlink (pathname, linkname, sizeof linkname);

  if (retval >= 0) {
    lstat(pathname, &fileStat);
    int mode = fileStat.st_mode;
    int size = fileStat.st_size;
    time_t time = fileStat.st_mtime;

    printf("%06o%10d ", mode, size);
    print_local(time);

    linkname[retval < PATH_MAX + 1 ? retval : PATH_MAX] = '\0';
    printf ("%s -> %s\n", pathname, linkname);
  } else {
    int mode = fileStat.st_mode;
    int size = fileStat.st_size;
    time_t time = fileStat.st_mtime;
    printf("%06o%10d ", mode, size);
    print_local(time);
    printf("%s\n",pathname);
  }
}

int main (int argc, char **argv) {
  int exit_status = EXIT_SUCCESS;
  setlocale (LC_NUMERIC, "en_US");
  char *bname = basename(argv[0]); 

  if (argc > 1) {
    for (int argi = 1; argi < argc; ++argi) {
      char *pathname = argv[argi];
      struct stat fileStat;
      int exists = stat(pathname, &fileStat);

      if (exists >= 0) {
        print_stats(pathname, fileStat);
      } else {
        print_err(bname, pathname, &exit_status);
      }
    }
  } else {
    char *pathname = ".";
    struct stat fileStat;
    stat(pathname, &fileStat);
    print_stats(pathname, fileStat);
  }

  return exit_status;
}
