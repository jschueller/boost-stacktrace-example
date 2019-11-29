// g++ -D_GLIBCXX_ASSERTIONS -DBOOST_STACKTRACE_USE_ADDR2LINE -g -no-pie main.cxx -ldl


#include <signal.h>     // ::signal, ::raise
#include <boost/stacktrace.hpp>

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void print_stacktrace(int signum) {
  ::signal(signum, SIG_DFL);
  std::cerr << "Stack trace:\n" << boost::stacktrace::stacktrace() << '\n';
  ::raise(SIGABRT);
}

void crash ()
{
  std::vector<double> x(5);
  for (int i =0; i < 100; ++ i)
    x[i] += 3.0 * i;
}

int main(int argc, char *argv[])
{
  int ret = 0;

  ::signal(SIGSEGV, &print_stacktrace);
  ::signal(SIGABRT, &print_stacktrace);

crash ();
  return ret;
}

