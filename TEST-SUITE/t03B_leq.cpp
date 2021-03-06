#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


#include "_test.h"
#include "_tutil.h"




// char *Desc= "num_leq test 2";

int test(int h, int n) {
  static bool FIRST = true;
  bst<int> *t = build_balanced(h);
  int success = 1;
  int i;
  int x;
  int target;

/**
  if(FIRST) {
	  printf("BEGIN SIZE_SANITY AFTER INSERTIONS %%%%%%\n");
	  t->size_sanity();
	  printf("END SIZE_SANITY AFTER INSERTIONS %%%%%%\n\n");
  }
**/

  int n4 = n/4;
  int n2 = n/2;
  int lo = n2-n4;
  int hi = n2+n4;

  rem_range(t, lo, hi);

/**
  if(FIRST) {
	  printf("BEGIN SIZE_SANITY AFTER REMOVALS %%%%%%\n");
	  t->size_sanity();
	  printf("END SIZE_SANITY AFTER REMOVALS %%%%%%\n\n");
  }
**/

  for(i=1; i<lo; i++) {
    x = t->num_leq( i);
    if(x != i) {
	if(FIRST) {
	    printf("DEBUG:  num_leq(%d)=%d ; expected: %d\n", i, x, i);
	}
	success = 0;
    }
  }
  for(i=lo; i<=hi; i++) {
    x = t->num_leq( i);
    if(x != lo-1) {
      success = 0;
      if(FIRST) 
        printf("DEBUG:  num_leq(%d)=%d ; expected: %d\n", i, x, lo-1);
    }
  }

  target = (lo-1)+1;
  for(i=hi+1; i<=n; i++, target++) {
    x = t->num_leq( i);
    if(x != target){
      success = 0;
      if(FIRST) 
        printf("DEBUG:  num_leq(%d)=%d ; expected: %d\n", i, x, target);
    }
  }
  FIRST = false;
  bst_free(t);
  return success;
}



int main(int argc, char *argv[]) {
  int n = __N;
  int n2 = __N2;
  int height = __HEIGHT;
  int height2 = __HEIGHT2;
  int ntrials = __NTRIALS;
  clock_t budget;

  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2)
    ntrials = atoi(argv[2]);

  set_ntrials(ntrials);



  START("[num_leq]:  balanced tree + remove-middle-n/2 + num_leq scan");

  printf("@@@@@ n=%d ; n2=%d ; h=%d ; h2=%d\n\n", n, n2, height, height2);

  TEST_RET_MESSAGE(baseline(), "COMPILATION", 1, 1.0); 
  TEST_RET_MESSAGE(test(height, n), "CORRECTNESS-ONLY-TEST", 1, 1.5); 
  TIME_RATIO(test(height, n), test(height2, n2), "", 1, 2.5, 2.5);


  report();

  END;
}

