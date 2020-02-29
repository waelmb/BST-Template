#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

// #include <string>
#include "_test.h"
#include "_tutil.h"


// #include "header.c"



// string Desc = "Basic test of to_vec";
// char *Desc = "Basic test of to_vec";

int test2(bst<int> *t) {
int success = 1;
int i;

  std::vector<int> *a = t->extract_range(50, 54);
  int exp;
  if(a->size() == 5) {
    exp = 50;
    for(i=0; i<5; i++) {
      if((*a)[i] != exp)
         success = 0;
      exp++;
    }
  }
  else 
    success = 0;

  delete a;
  return success;
}

int test(int h, int n) {
  // BST *t = build_balanced(h);
  //
  bst<int> *t = build_balanced(h);

  int success = 1;
  int i, exp;

  std::vector<int> *a = t->extract_range(10, 19);

  if(a->size() == 10) {
    exp = 10;
    for(i=0; i<10; i++) {
      if((*a)[i] != exp)
         success = 0;
      exp++;
    }
  }
  else 
    success = 0;
  

  delete t;
  delete a;
  return success;
}



int main(int argc, char *argv[]) {
  int n = __N;
  int n2 = __N2;
  int height = __HEIGHT;
  int height2 = __HEIGHT2;
  int ntrials = __NTRIALS;

  // clock_t budget;

  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2)
    ntrials = atoi(argv[2]);

  set_ntrials(ntrials);

  // budget = calibrate_linear(n, ntrials);


  START("[extract_range] balanced tree + extract_range (correctness only)");

  TEST_RET_MESSAGE(baseline(), "COMPILATION", 1, 2.0); 
  TEST_RET_MESSAGE(test(height, n), "CORRECTNESS-ONLY-TEST", 1, 3.0); 

  bst<int> *t1 = build_balanced(height);
  bst<int> *t2 = build_balanced(height2);

  TIME_RATIO(test2(t1), test2(t2), "", 1, 1.4, 5.0);
  report();

  END;
}

