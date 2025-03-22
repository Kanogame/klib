#include "error.h"
#include <err.h>
#include <execinfo.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// prints formated stack trace
void printStacktrace(int calledFromSigInt) {
  void *buffer[MAX_BACKTRACE_LINES];
  char **strings;

  int nptrs = backtrace(buffer, MAX_BACKTRACE_LINES);
  strings = backtrace_symbols(buffer, nptrs);
  if (strings == NULL) {
    perror("backtrace_symbols");
    exit(EXIT_FAILURE);
  }

  unsigned int i = 1;
  if (calledFromSigInt != 0)
    ++i;
  for (; i < (unsigned int)(nptrs - 2); ++i) {
    // if addr2line failed, print what we can
    if (addr2line(_programName, buffer[i], nptrs - 2 - i - 1) != 0)
      fprintf(stderr, "[%i] %s\n", nptrs - 2 - i - 1, strings[i]);
  }

  free(strings);
}

// Resolve symbol name and source location given the path to the executable and
// an address returns 0 if address has been resolved and a message has been
// printed; else returns 1
int addr2line(char const *const program_name, void const *const addr,
              int lineNb) {
  char addr2line_cmd[512] = {0};

  /* have addr2line map the address to the relent line in the code */
  sprintf(addr2line_cmd, "addr2line -f -e %.256s %p", program_name, addr);

  /* This will print a nicely formatted string specifying the
  function and source line of the address */

  FILE *fp;
  char outLine1[1035];
  char outLine2[1035];

  /* Open the command for reading. */
  fp = popen(addr2line_cmd, "r");
  if (fp == NULL)
    return 1;

  while (fgets(outLine1, sizeof(outLine1) - 1, fp) != NULL) {
    // if we have a pair of lines
    if (fgets(outLine2, sizeof(outLine2) - 1, fp) != NULL) {
      // if symbols are readable
      if (outLine2[0] != '?') {
        // only let func name in outLine1
        int i;
        for (i = 0; i < 1035; ++i) {
          if (outLine1[i] == '\r' || outLine1[i] == '\n') {
            outLine1[i] = '\0';
            break;
          }
        }

        // don't display the whole path
        int lastSlashPos = 0;

        for (i = 0; i < 1035; ++i) {
          if (outLine2[i] == '\0')
            break;
          if (outLine2[i] == '/')
            lastSlashPos = i + 1;
        }
        fprintf(stderr, "[%i] %p in %s at %s", lineNb, addr, outLine1,
                outLine2 + lastSlashPos);
        fflush(stderr);
      } else {
        pclose(fp);
        return 1;
      }
    } else {
      pclose(fp);
      return 1;
    }
  }

  pclose(fp);

  return 0;
}

void posixSignalHandler(int sig) {
  printStacktrace(1);
  switch (sig) {
  case SIGABRT:
    fputs("SIGABRT: usually caused by an abort() or assert()\n", stderr);
    break;
  case SIGFPE:
    fputs("SIGFPE: arithmetic exception, such as divide by zero\n", stderr);
    break;
  case SIGILL:
    fputs("SIGILL: illegal instruction\n", stderr);
    break;
  case SIGINT:
    fputs("SIGINT: interactive attention signal, probably a ctrl+c\n", stderr);
    break;
  case SIGSEGV:
    fputs("SIGSEGV: segfault\n", stderr);
    break;
  case SIGTERM:
  default:
    fputs("SIGTERM: a termination request was sent to the program\n", stderr);
    break;
  }
  _Exit(EXIT_FAILURE);
}

void setSignalHandler(sig_t handler) {
  signal(SIGABRT, handler);
  signal(SIGFPE, handler);
  signal(SIGILL, handler);
  signal(SIGINT, handler);
  signal(SIGSEGV, handler);
  signal(SIGTERM, handler);
}

void initExceptions(char *programName) {
  setSignalHandler(posixSignalHandler);
  _programName = programName;
}
