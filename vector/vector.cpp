
template<class T, class A = allocator<T> >
class vector {
  /*  invariant:
      if 0 <= n < sz, elem[n] is element n
      sz <= space;
      if sz < space there is space for (space-sz) elements afrer elem[sz-1]
  */

  int sz;				  // the size
  T* elem;				  // a pointer to the elements
  int space;				  // size + free space
public:
  vector() : sz(0), elem(0), space(0) {}
  explicit vector(int s);

  vector(const vector&);		     // copy constructor
  vector& operator=(const vector&);	     // copy assignment

  ~vector();				      // destructor

  T& operator[](int n) {  return elem[n];  } // access: return reference
  const T& operator[](int n) const {  return elem[n];  }

  int size() const {  return sz;  }	     // the current size
  int capacity const {  return space;  }

  void resize(int newsize);		     // growth
  void push_back(const T& d);
  void reserve(int newalloc);
};


// fix from arguments constructor
template<class T>
explicit vector<T>::vector(int s) : sz(s), elem(new T[s]), space(s) {
    for (int i = 0; i < sz; ++i)  elem[i] = 0; // elements are initialized
  }


// fix copy constructor
template<class T>
vector<T>:vector(const vector& other) {}

// fix copy assignment
template<class T>
vector& vector<T>::operator=(const vector<T>& rhs) {
  if (this == &rhs)  return *this;	     // self assignment, no work needed

  if (rhs.sz <= space) {		     // enough space, no need for new allocation
    for (int i = 0; i < rhs.sz; ++i)  elem[i] = rhs.elem[i]; // copy elements
    sz = rhs.sz;
    return *this;
  }

  T* p = new double[rhs.sz];		      // allocate new space
  for (int i = 0; i < rhs.sz; ++i)	      // copy elements
    p[i] = rhs.elem[i];
  delete[] elem;			      // deallocate old space
  space = sz = rhs.sz;			      // set new size
  elem = p;				      // set new elements
  return *this;				      // return a self reference
}


// fix destructor
template<class T>
vector<T>::~vector() {  delete[] elem;  }



template<class T, class A>
void vector<T, A>::reserve(int newalloc) {
  if (newalloc <= space)  return;	      // never decrease allocation
  T* p = alloc.allocate(newalloc);	      // allocate new space
  for (int i = 0; i < sz; ++i)  alloc.construct(&p[i], elem[i]); // copy
  for (int i = 0; i < sz; ++i)  alloc.destroy(&elem[i]);         // destroy
  alloc.deallocate(elem, space);	       // deallocate old space
  elem = p;
  space = newalloc;
}

template<class T. class A>
void vector<T, A>::push_back(const T& val) {
  if (space == 0)  reserve(8);					   // start with space for 8 elements
  else if (sz == space)  reserve(2 * space);			   // get more space
  alloc.construct(&elem[sz], val);				   // add val at end
  ++sz;								   // increase the size
}


template<class T, class A>
void vector<T, A>::resize(int newsize, T val = T()) {
  reserve(newsize);						      // allocate more space if needed
  for (int i = sz; i < newsize; ++i)  alloc.construct(&elem[i], val); // construct (make bigger: add default elements)
  for (int i = newsize; i < sz; ++i)  alloc.destroy(&elem[i]);	      // destroy (make smaller: destroy some elements, keep space)
  sz = newsize;
}
