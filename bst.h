/* Project 3: BSTs
*  CS251, Summer 2019
*  Wael Abdulelah Mobeirek
*************************************/
#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <vector>

template <typename T>
class bst {

  private: 
    struct bst_node {
      T      val;
      bst_node *left;
      bst_node *right;
      int numLeft;
      int numRight;

      bst_node ( const T & _val = T{}, bst_node * l = nullptr, bst_node *r = nullptr, int numLeft = 0, int numRight = 0)
        : val { _val },  left { l }, right {r} 
      { }
    };



  public:
    // constructor:  initializes an empty tree
    bst(){
      root = nullptr;
    }

  private:
    // helper function which recursively deallocates nodes
    //   in a tree.
    static void delete_nodes(bst_node *r){
      if(r==nullptr) return;
      delete_nodes(r->left);
      delete_nodes(r->right);
      delete r;
    }

  public:
    // destructor
    ~bst() {
      delete_nodes(root);
    }

  private:

	//Checks if a tree is balanced or not
	static bool isBalanced(bst_node* r) {
		//check for empty tree
		if(r == nullptr) {
			return true;
		}
		
		//get min and max
		int max, min;
		if(r->numLeft > r->numRight) {
			max = r->numLeft;
			min = r->numRight;
		}
		else {
			max = r->numRight;
			min = r->numLeft;
		}
		
		//Determine if balanced
		if(max <= ((2 * min) +1)) {
			return true;
		}
		else {
			return false;
		}
	}
	
	//stores nodes in a vector and resets it's information
	static void export_nodes(std::vector<bst_node*>* v, bst_node* r) {	
	    	//if empty, return
	    	if(r == nullptr) {
	    		return;
			} 
			else {				
				//store in order
				export_nodes(v, r->left);
				v->push_back(r);
				export_nodes(v, r->right);
				
				//reset node
				r->left = nullptr;
				r->right = nullptr;
				r->numLeft = 0;
				r->numRight = 0;
			}
	}
	
	static bst_node* insert_balanced(std::vector<bst_node*>* v, int start, int end) {
		  if(start > end) {
		  	return nullptr;
		  }
		  int mid = (start+end)/2;
		  //printf("insert_balanced: start %d, mid %d, end %d\n", start, mid, end);
		  
		  bst_node* r = v->at(mid);
		  
		  //recursively build left_subtree
		  r->left = insert_balanced(v, start, mid-1);
		  
		  if(r->left != nullptr) {
		  	//printf("%d numLeft++ at %d\n", r->val, r->numLeft);
		  	r->numLeft = 1 + r->left->numLeft + r->left->numRight;
		  }
		
		  //recursibely build right_subtree
		  r->right = insert_balanced(v, mid+1, end);
		  
		   if(r->right != nullptr) {
		   	//printf("%d numRight++ at %d\n", r->val, r->numRight);
		  	r->numRight = 1 + r->right->numLeft + r->right->numRight;
		  }
		  
		  return r;
	}
	
	
	//rebalances a tree
	//PSUEDOCODE:
		//export the tree in order into a vector
		// re-insert the nodes in a self-balanced order
	static bst_node* rebalance(bst_node* r) {
		
		//allocate memory for a new vector
		std::vector<bst_node*>* v = new std::vector<bst_node*>();
    	int n = fast_size(r);
    	//printf("root node %d: numLeft = %d and numRight %d\n", r->val, r->numLeft, r->numRight);
    	//_inorder(r);
    	//printf("rebalance: n-1 is %d\n", n-1);
    	
    	//export the nodes into the vector
    	export_nodes(v, r);
    	
    	/*
    	for(int i = 0; i < n; i++) {
    		printf("node %d: numLeft = %d and numRight %d\n", (v->at(i))->val, (v->at(i))->numLeft, (v->at(i))->numRight);
		}
		*/
		
    	//re-insert the nodes in a self-balanced order
    	r = insert_balanced(v, 0, n-1);
    	
    	//free vector
    	delete v;
    	
    	//return
    	return r;
	}
	

/**
 * function:  insert()
 * desc:      recursive helper function inserting x into
 *            binary search tree rooted  at r.
 *
 * returns:   pointer to root of tree after insertion.
 *
 * notes:     if x is already in tree, no modifications are made.
 */
    static bst_node * _insert(bst_node *r, T & x, bool &success){
      if(r == nullptr){
        success = true;
        //printf("%d was inserted\n", x);
        bst_node* node =  new bst_node(x, nullptr, nullptr, 0, 0);
        //printf("%d has %d numLeft and %d numRight\n", node->val, node->numLeft, node->numRight);
        node->numLeft = 0;
        node->numRight = 0;
        //printf("%d has %d numLeft and %d numRight\n", node->val, node->numLeft, node->numRight);
        return node;
      }

      if(r->val == x){
        success = false;
        return r;
      }
      if(x < r->val){
        r->left = _insert(r->left, x, success);
        //printf("left node %d has %d numLeft and %d numRight\n", r->left->val, r->left->numLeft, r->left->numRight);
        //increment numLeft since we're inserting on the left subtree
        if(success) {
        	//printf("%d numLeft++ at %d\n", r->val, r->numLeft);
      		r->numLeft++;
      		if(!isBalanced(r)){
      			//printf("***insert: %d found a violation numLeft %d and numRight %d\n", r->val, r->numLeft, r->numRight);
      			r = rebalance(r);
			}
		}
        return r;
      }
      else {
        r->right = _insert(r->right, x, success);
        //increment numRight since we're inserting on the right subtree
        if(success) {
        //	printf("right %d numRight++ at %d\n", r->val, r->numRight);
        //	printf("node %d has %d numLeft and %d numRight\n", r->right->val, r->right->numLeft, r->right->numRight);
      		r->numRight++;
      		if(!isBalanced(r)){
      			//printf("***insert: %d found a violation numLeft %d and numRight %d\n", r->val, r->numLeft, r->numRight);
      			r = rebalance(r);
			}
		}
        return r;
      }
    }


  public:
  /**
   * function:  insert
   * desc:      inserts x into BST given by t.  Note that
   *            a BST stores a SET -- no duplicates.  Thus,
   *            if x is already in t when call made, no 
   *            modifications to tree result.
   *
   * note:      helper function does most of the work.
   *
   */
   bool insert(T & x){
      bool success;
      root = _insert(root, x, success);
      return success;
   }

/**
 * function:  contains()
 * desc:      returns true or false depending on whether x is an
 *            element of BST (calling object)
 *
 */
    bool contains(const T & x){
      bst_node *p = root;

      while(p != nullptr){

        if(p->val == x)
          return true;
        if(x < p->val){
          p = p->left;
        }
        else
          p = p->right;
      }
      return false;  
    }

  private:
    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node * _min_node(bst_node *r ){
      if(r==nullptr)
        return nullptr; // should never happen!
      while(r->left != nullptr)
        r = r->left;
      return r;
    }

    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node * _max_node(bst_node *r ){
      if(r==nullptr)
        return nullptr; // should never happen!
      while(r->right != nullptr)
        r = r->right;
      return r;
    }

    // recursive helper function for node removal
    //   returns root of resulting tree after removal.
    static bst_node * _remove(bst_node *r, T & x, bool &success){
      bst_node *tmp;
      bool sanity;

      if(r==nullptr){
        success = false;
        return nullptr;
      }
      if(r->val == x){
        success = true;

        if(r->left == nullptr){
          tmp = r->right;
          delete r;
          return tmp;
        }
        if(r->right == nullptr){
          tmp = r->left;
          delete r;
          return tmp;
        }
        // if we get here, r has two children
        r->val = _min_node(r->right)->val;
        r->numRight--;
        r->right = _remove(r->right, r->val, sanity);
        if(!sanity)
          std::cerr << "ERROR:  remove() failed to delete promoted value?\n";
        return r;
      }
      if(x < r->val){
        r->left = _remove(r->left, x, success);
        //decrement numLeft since we're deleting from the left subtree
        if(success) {
      		r->numLeft--;
      		if(!isBalanced(r)){
      			//printf("delete: %d found a violation numLeft %d and numRight %d\n", r->val, r->numLeft, r->numRight);
      			r = rebalance(r);
			}
		}
      }
      else {
        r->right = _remove(r->right, x, success);
        //decrement numRight since we're deleting from the right subtree
        if(success) {
      		r->numRight--;
      		if(!isBalanced(r)){
      			//printf("delete: %d found a violation numLeft %d and numRight %d\n", r->val, r->numLeft, r->numRight);
      			r = rebalance(r);
			}
		}
      }
      return r;

    }

  public:

    bool remove(T & x){
      bool success;
      root = _remove(root, x, success);
      return success;
    }


  private:
    // recursive helper function to compute size of
    //   tree rooted at r
    static int _size(bst_node *r){
      if(r==nullptr) return 0;
      return _size(r->left) + _size(r->right) + 1;
    }

  public: 
    int size() {
      return _size(root);
    }
    
    static int fast_size(bst_node* root) {
    	if(root==nullptr) return 0;
    	return (root->numLeft + root->numRight + 1);
	}

  private:

    static int _height(bst_node *r){
      int l_h, r_h;

      if(r==nullptr) return -1;
      l_h = _height(r->left);
      r_h = _height(r->right);
      return 1 + (l_h > r_h ? l_h : r_h);
    }

  public:

    int height() {
      return _height(root);
    }

    bool min(T & answer) {
      if(root == nullptr){
        return false;
      }
      answer = _min_node(root)->val;
      return true;
    }

    T max() {
      return _max_node(root)->val;
    }

    /******************************************
     *
     * "stubs" for assigned TODO functions below 
     *
     *****************************************/

    /* TODO
     * Function:  to_vector
     * Description:  allocates a vector of type T and populates
     *               it with the elements of the tree in sorted
     *               order.  A pointer to the vector is returned.
     *
     * runtime:  O(n) where n is the tree size.
     *
     */
    std::vector<T> * to_vector() {
    	//allocate memory for a new vector
		std::vector<T>* v = new std::vector<T>();
    	
    	//populate the vector using a helper method
    	_to_vector(v, root);
    	
    	//return the vector
    	return v;
    }
    
    private:
    //recursive helper method for to_vector()
    	static void _to_vector(std::vector<T>* v, bst_node* r) {	
	    	//if empty, return
	    	if(r == nullptr) {
	    		return;
			} 
			else {				
				//store in order
				_to_vector(v, r->left);
				v->push_back(r->val);
				_to_vector(v, r->right);
			}
		}
		
		
    public:
    /* TODO
     * Function:  get_ith
     * Description:  determines the ith smallest element in t and
     *    "passes it back" to the caller via the reference parameter x.  
     *    i ranges from 1..n where n is the number of elements in the 
     *    tree.
     *
     *    If i is outside this range, false is returned.
     *    Otherwise, true is returned (indicating "success").
     *
     * Runtime:  O(h) where h is the tree height
     */
    bool get_ith(int i, T &x) {
    	//if ith is out of range, return false
    	if(i < 1 || i > fast_size(root)) {
    		return false;
		}
    	return _get_ith(i, x, root);
    }

	private:
		//PSUEDOCODE:
	     //compare ith to num of nodes of the left subtree and right subtree
	    	//if num leftsbutree + 1 = ith
				//then this is ith, return left_subtree+1;
	    	//if less than or equal to left_subtree
	    		//search the left_subtree
	    	//else, (must be more than left_subtree+1) go right
	    		//search the right_subtree
		static bool _get_ith(int i, T &x, bst_node* r) {
    		//if this is the smallest ith element
			if(r != nullptr && i == r->numLeft+1) {
    			x = r->val;
				return true;
			}
			else if(r != nullptr && i <= r->numLeft) {
				//search left_subtree
				return _get_ith(i, x, r->left);
			}
			else if(r != nullptr && i > r->numLeft){
				//search right_subtree
				return _get_ith(i-(r->numLeft+1), x, r->right);
			}
   		}
		
	public:	
    /* 
     * get_ith_SLOW:  slow version of get_ith which gives the right answer, but
     *   does so by "walking the entire tree".
     * might be helpful for debugging?
     * Private helper below does most of the work
     */
    bool get_ith_SLOW(int i, T &x) {
      int n = size();
      int sofar=0;

      if(i < 1 || i > n) 
        return false;

      _get_ith_SLOW(root, i, x, sofar);
      return true;
    }

  private:
    // recursive helper function that does most of the work
    static void _get_ith_SLOW(bst_node *t, int i, T &x, int &sofar) {
      if(t==nullptr) 
        return;
      _get_ith_SLOW(t->left, i, x, sofar);

      if(sofar==i) 
        return;
      sofar++;
      if(sofar==i) {
        x = t->val;
        return;
      }
      _get_ith_SLOW(t->right, i, x, sofar);
    }

  public:

    /* TODO
     * Function: position_of 
     * Description:  this is like the inverse of
     *       get_ith:  given a value x, determine the 
     *       position ("i") where x would appear in a
     *       sorted list of the elements and return
     *       the position as an integer.
     *       If x is not in the tree, -1 is returned.
     *       Examples:
     *           if x happens to be the minimum, 1 is returned
     *           if x happens to be the maximum, n is returned where
     *               n is the tree size.                  
     *                  
     *       Notice the following property:  for a bst t with n nodes,                  
     *           pick an integer pos:1 <= pos <= n.                  
     *           Now consider the following:
     *       
                    T x;
                    int pos, pos2;
                    // set pos to a value in {1..n}
                    t.get_ith(pos, x);  // must return true since pos is in {1..n}

                    // now let's find the position of x (just retrieved) 
                    pos2 = t.position_of(x);
                    if(pos != pos2) {
                        std::cout << "THERE MUST BE A BUG!\n";
                    }

                 See how position_of performs the inverse operation of get_ith?
     *       
     * Return:  -1 if x is not in the tree; otherwise, returns the position where x 
     *          would appear in the sorted sequence of the elements of the tree (a
     *          value in {1..n}          
     *
     * Runtime:  O(h) where h is the tree height
     */
     //NOTE: BINARY SEARCH
     //PSUEDOCODE:
     //if this_val == x
      		//return the num_left_subtree + 1;
    	//else
    		//if larger, return num_left_subtree + search on the right
    		
    		//if smaller, search on the left
    int position_of(const T & x) {
    	//check for out of range
		if(_min_node(root)->val > x || _max_node(root)->val < x) {
    		return -1;
		}
		
		int pos = _position_of(x, root);
		
		//if the element in the ith position doesn't match with the given element
		int result;
		bool success = get_ith(pos,result);
		if(success && result != x) {
			//then it doesn't exist in the BST
			return -1;
		}
		
		//Otherwise, return pos
      	return pos;
    }
	
	private:
		static int _position_of(const T & x, bst_node* r) {
      		if(r != nullptr && r->val == x) {
      			//printf("_position_of(%d) found val\n", x); //FIXME: comment out
      			return (r->numLeft+1);
			}
			else if(r != nullptr && r->val < x){
				//printf("_position_of(%d) went to the right\n", x); //FIXME: comment out
				return (r->numLeft + 1 + _position_of(x, r->right));
			}
			else if(r != nullptr && r->val > x){
				//printf("_position_of(%d) went to the left\n", x); //FIXME: comment out
				return _position_of(x, r->left);
			}
			else {
				//printf("_position_of() = DNE\n"); //FIXME: comment out
				return 0;
			}
    	}
		
	public:
    /* TODO
     * Function:  num_geq
     * Description:  returns the number of elements in tree which are 
     *       greater than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     */
     //NOTE: find element using BINARY SEARCH then calculate num of elements greater than it
     //PSUEDOCODE:
     //if this_val == x
    		//then, return num_right_subtree + 1
    	//else
    		//if this_val < x
    			//then, return search the right subtree
    		//else (this_val must be > x) 
    			//then, return 1 + num_right_subtree + search the left subtree
    int num_geq(const T & x) {
    	return _num_geq(x, root);
    }
	
	private:
		static int _num_geq(const T & x, bst_node* r) {
    		if(r != nullptr && r->val == x) {
    			return (r->numRight + 1);
			}
			else if(r != nullptr && r->val < x) {
				return _num_geq(x, r->right);
			}
			else if(r != nullptr && r->val > x) {
				return (r->numRight + 1 + _num_geq(x, r->left));
			}
			else {
				return 0;
			}
   		}
		
	public:
		
    /*
     * function:     num_geq_SLOW
     * description:  same functionality as num_geq but sloooow (linear time)
     *                (private helper does most of the work)
     *
     */
    int num_geq_SLOW(const T & x) {
      return _num_geq_SLOW(root, x);
    }

  private:
    static int _num_geq_SLOW(bst_node * t, const T & x) {
      int total;

      if(t==nullptr) return 0;
      total =_num_geq_SLOW(t->left, x) + _num_geq_SLOW(t->right, x);

      if(t->val >= x)
        total++;
      return total;
    }
    
  public:

    /* TODO
     * Function:  num_leq
     * Description:  returns the number of elements in tree which are less
     *      than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
     //PSUEDOCODE
     //if this_val == x
    		//then, return num_left_subtree + 1
    	//else
    		//if this_val < x
    			//then, return 1 + num_left_subtree + search the right subtree
    		//else (this_val must be > x) 
    			//then, return search the left subtree
    int num_leq(const T &x) {
    	return _num_leq(x, root);
    }
	
	private:
		static int _num_leq(const T &x, bst_node* r) {
			if(r != nullptr && r->val == x) {
    			return (r->numLeft + 1);
			}
			else if(r != nullptr && r->val < x) {
				return (r->numLeft + 1 + _num_leq(x, r->right)); 
			}
			else if(r != nullptr && r->val > x){
				return _num_leq(x, r->left);
			}
			else {
				return 0;
			}
		}
	public:
    /*
     * function:     num_leq_SLOW
     * description:  same functionality as num_leq but sloooow (linear time)
     *               (private helper _num_leq_SLOW does most of the work)
     */
    int num_leq_SLOW(const T & x) {
      return _num_leq_SLOW(root, x);
    }
  private:

    // helper for num_leq_SLOW
    static int _num_leq_SLOW(bst_node *t, const T &x) {
      int total;

      if(t==nullptr) return 0;
      total =_num_leq_SLOW(t->left, x) + _num_leq_SLOW(t->right, x);

      if(t->val <= x)
        total++;
      return total;
    }

  public:

    /* TODO
     * Function:  num_range
     * Description:  returns the number of elements in tree which are
     *       between min and max (inclusive).
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
     //PSUEDOCODE:
     	//a = num_geq(min)
    	//b = num_leq(max)
    	//n = number of nodes in tree
    	//return (a+b) - n 
    int num_range(const T & min, const T & max) {
    	if(max < min) {
    		return 0;
		}
    	return (this->num_geq(min) + this->num_leq(max) - fast_size(root));
    }

    /*
     * function:     num_range_SLOW
     * description:  same functionality as num_range but sloooow (linear time)
     *               (private helper _num_range_SLOW does most of the work)
     *
     */
    int num_range_SLOW(const T & min, const T & max) {
      return _num_range_SLOW(root, min, max);
    }

  private:
    static int _num_range_SLOW(bst_node *t, const T &min, const T &max) {
      int total;

      if(t==nullptr) return 0;
      total =_num_range_SLOW(t->left, min, max) + 
                _num_range_SLOW(t->right, min, max);

      if(t->val >= min && t->val <= max)
        total++;
      return total;
    }

  public:

    /*
     * TODO
     * function:     extract_range
     * Description:  allocates a vector of element type T
     *               and populates it with the tree elements
     *               between min and max (inclusive) in order.  
     *               A pointer to the allocated and populated
     *               is returned.
     *
     * notes/comments:  even if the specified range is empty, a
     *                  vector is still allocated and returned;
     *                  that vector just happens to be empty.
     *                  (The function NEVER returns nullptr).
     *
     * runtime:  the runtime requirement is "output dependent".
     *           Let k be the number of elements in the specified range
     *           (and so the length of the resulting vector) and let h
     *           be the height of the tree.  The runtime must be:
     *
     *                  O(h + k)
     *
     *           So...while k can be as large as n, it can be as small
     *           as zero.  
     *
     */
     //PSUEDOCODE
     //store in-order in the given range only
    	//if(current_node == nullptr)
    		//return;
    	//else
    		//store in order
    std::vector<T> * extract_range(const T & min, const T & max) {
    	//allocate memory for a new vector
		std::vector<T>* v = new std::vector<T>();
    	
    	//populate the vector using a helper method
    	if(max >= min) { //make sure it's in range
    		_extract_range(min, max, v, root);
		}
    	
    	//return the vector
    	return v;
    }
	
	private:
		static void _extract_range(const T & min, const T & max, std::vector<T>* v, bst_node* r) {
			if(r == nullptr) {
				return;
			} 
			else {
				//go to the left, if and only if the curr_val is more than the min
				if(r->val > min ) {
					_extract_range(min, max, v, r->left);
				}
				
				//push to vector if and only if in range
				if(r->val >= min && r->val <= max) {
					v->push_back(r->val);
				}
				
				//go to the right, if and only if the curr_val is less than the max
				if(r->val < max) {
					_extract_range(min, max, v, r->right);	
				}
				
			}
		}
	
	public:
  /***************************************************
  *  PREORDER AND INORDER TREE TRAVERSALS BELOW      * 
  *                                                  * 
  ***************************************************/

  private:
    static void indent(int m){
      int i;
      for(i=0; i<m; i++)
        std::cout << "-";
    }

    static void _inorder(bst_node *r){
      if(r==nullptr) return;
      _inorder(r->left);
      std::cout << "[ " << r->val << " ]\n";
      //printf("with numLeft: %d and numRight: %d\n", r->numLeft, r->numRight);
      _inorder(r->right);
    }

    static void _preorder(bst_node *r, int margin){
      if(r==nullptr) {
        indent(margin);
        std::cout << " nullptr \n";
      } 
      else {
        indent(margin);
        std::cout << "[ " << r->val << " ]\n";
        _preorder(r->left, margin+3);
        _preorder(r->right, margin+3);
      }
    }
    
    static void numNodes(bst_node *r) {
      if(r==nullptr) {
      	printf("total nodes: 0\n");
	  }
	  else {
	  	int t = r->numLeft + r->numRight + 1;
	  	printf("total nodes: %d\n", t );
	  }
	}

  public:
    void inorder() {
      std::cout << "\n======== BEGIN INORDER ============\n";
      _inorder(root);
      numNodes(root);
      std::cout << "\n========  END INORDER  ============\n";
    }


    void preorder() {

      std::cout << "\n======== BEGIN PREORDER ============\n";
      _preorder(root, 0);
      std::cout << "\n========  END PREORDER  ============\n";

    }

  /***************************************************
  *  END PREORDER AND INORDER TREE TRAVERSALS        * 
  *                                                  * 
  ***************************************************/

  private:
    /* 
     * Recursive  helper function _from_vec, used by
     * from_sorted_arr(...). The function must return a sub-tree that is
     * perfectly balanced, given a sorted array of elements a.
     */
    static bst_node * _from_vec(const std::vector<T> &a, int low, int hi){
      int m;
      bst_node *root;

      if(hi < low) return nullptr;
      m = (low+hi)/2;
      root = new bst_node(a[m]);
      root->left  = _from_vec(a, low, m-1);
      root->right = _from_vec(a, m+1, hi);
      return root;

    }

  public:
    static bst * from_sorted_vec(const std::vector<T> &a, int n){

      bst * t = new bst();
      t->root = _from_vec(a, 0, n-1);
      return t;
    }

  private:

    /*
     * DO NOT MODIFY THE TWO FUNCTIONS BELOW!!!
     */
    static void _to_preorder_vec(bst_node *t, std::vector<T> &vec) {
      if(t==nullptr) return;
      vec.push_back(t->val);
      _to_preorder_vec(t->left, vec);
      _to_preorder_vec(t->right, vec);
    }
    std::vector<T> * to_preorder_vec() {
      std::vector<T> *vec = new std::vector<T>();
      _to_preorder_vec(root, *vec);
      return vec;
    }

  /*
   * Finally, the data members of the bst class
   */
  private:
    bst_node *root;


}; // end class bst

#endif
