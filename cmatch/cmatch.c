// Michael Walton (mwwalton@ucsc.edu)
// $Id: cmatch.c,v 1.35 2013-10-29 12:50:31-07 - - $

#define _GNU_SOURCE

#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *program_name = NULL;
int exit_status = EXIT_SUCCESS;
#define STDIN_NAME "-"

typedef struct options {
   bool ignore_case;
   bool filenames_only;
   bool number_lines;
} options;

void scan_options (int argc, char **argv, options *opts) {
   opts->ignore_case = false;
   opts->filenames_only = false;
   opts->number_lines = false;
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "iln");
      if (opt == EOF) break;
      switch (opt) {
         case 'i':
            opts->ignore_case = true;
            break;
         case 'l':
            opts->filenames_only = true;
            break;
         case 'n':
            opts->number_lines = true;
            break;
         default:
            exit_status = EXIT_FAILURE;
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                  program_name, optopt);
            break;
      }
   }
}

void match(FILE *input, char *filename,
      char *target, options *opts, int n) {
   char buffer[1024];
   char *sub = NULL;
   for (int linenr = 1;; ++linenr) {
      char *buf = fgets(buffer, sizeof buffer, input);
      if (buf == NULL) break;
      if (opts->ignore_case) {
         sub = strcasestr(buf,target);
      } else {
         sub = strstr(buf,target);
      }
      if (sub != NULL) {
         if (opts->filenames_only) {
            printf ("%s\n", filename);
            break;
         } else {
            if (opts->number_lines) {
               if (n > 1) {
                  printf ("%s:%d:%s", filename, linenr, buf);
               } else {
                  printf ("%d:%s",linenr,buf);
               }
            } else {
               if (n > 1) {
                  printf ("%s:%s",filename,buf);
               } else {
                  printf ("%s", buf);
               }
            }
         }
      }
   }
}

void usage_err() {
   fprintf(stderr,"Usage: %s [-iln] string [filename...]\n", program_name);
   fflush(NULL);
   exit_status = EXIT_FAILURE;
}

int main (int argc, char **argv) {
   int argshift = 1;
   options opts;
   program_name = basename (argv[0]);
   scan_options (argc, argv, &opts);

   if (argc == 1) {
      usage_err();
   }else {
      if (strstr(argv[1],STDIN_NAME) != NULL) {
         ++argshift;
      }
      char *target = argv[argshift];
      ++argshift;
      if (argshift == argc) {
         match(stdin, STDIN_NAME, target, &opts, 0);
      } else {
         int filenum = argc - argshift;
         for (int argi = argshift; argi < argc; ++argi) {
            char *filename = argv[argi];
            if (strcmp (filename, STDIN_NAME) == 0) {
               match(stdin, STDIN_NAME, target, &opts, 0);
            }else {
               FILE *input = fopen (filename, "r");
               if (input != NULL) {
                  match(input, filename, target, &opts, filenum);
                  fclose (input);
               }else {
                  exit_status = EXIT_FAILURE;
                  fflush (NULL);
                  fprintf (stderr, "%s: %s: %s\n", program_name,
                        filename, strerror (errno));
                  fflush (NULL);
               }
            }
         }
      }
   }
   return exit_status;
}
