#include <iostream>
#include "vector/vector.hpp"

using namespace std;


template<class T>
struct S {
  S() : _val(T()) {}		// default constructor: call T's default constructor T()
  explicit S(T val) : _val(val) {}

  T& get();
  const T& get() const; // (const S).get() might be needed. both consts in definition are necessary

  void set(const T& val);
  const S<T>& operator=(const S& s1);

private:
  T _val;
};

template<class T> T& S<T>::get()		{	return _val;	}
template<class T> const T& S<T>::get() const	{	return _val;	}
template<class T> void S<T>::set(const T& val)	{	_val = val;	} // copy assignment in type
template<class T> const S<T>& S<T>::operator=(const S& s1) { // copy assignment in type
  this->_val = s1.get();
  return *this;
}

// read  sequence
template<class T> istream &input_sequence(istream& is, vector<T>& vec2)  {
  is.exceptions(is.exceptions() | ios_base::badbit); // bad state also throws an exception
  char ch;
  T t1;

  // try to read a T
  if (!(is >> t1))	return is;
  vec2.push_back(t1);

  // next char must be:  ']'  or  ','
  if (!(is >> ch))	return is;

  if (ch == ',')	return input_sequence(is, vec2);
  if (ch == ']')	{	  is.putback(ch);	return is;	} // success

  is.clear(ios_base::failbit);
  return is;
}

// read   vector<T>
template<class T> istream& operator>>(istream& is, vector<T>& vec1) {
  is.exceptions(is.exceptions() | ios_base::badbit); // bad state also throws an exception

  char ch;
  // try to read a '['
  if (!(is >> ch))	return is;
  if (ch != '[')	{	is.clear(ios_base::failbit);	return is;	}

  // try to read a ']'
  if (!(is >> ch))	return is;
  if (ch == ']')	{	vec1.clear();	return is;	}
  is.putback(ch);

  // try to read a sequence
  vector<T> vec2; // strong guarantee: define a new vector. on error, the original vector will remain intact
  if (!input_sequence(is, vec2))    return is;

  // try to read a ']'
  if (!(is >> ch))	return is;
  if (ch != ']')	{	is.clear(ios_base::failbit);	return is;	}

  // success
  vec1 = vec2;
  return is;
}

// read   S<T>
template<class T> istream& operator>>(istream& is, S<T>& ss1) {
  is.exceptions(is.exceptions() | ios_base::badbit); // bad state also throws an exception
  T val1;
  if (is >> val1)
    ss1.set(val1);
  return is;
}


// write  vector<T>
template<class T> ostream& operator<<(ostream& os, const vector<T>& vec1) {
  os << '[';
  for (int i = 0; i < vec1.size(); ++i) {
    os << vec1[i];
    if (i < vec1.size() - 1)
      os << ' ';
  }
  os << ']';
  return os;
}

// write  S<T>
template<class T> ostream& operator<<(ostream& os, const S<T>& ss1) {
  os << ss1.get();
  return os;
}


int main() {

  S<double> s1, s2(3.14), s3(2.17);
  cout << "s1==" << s1 << endl;
  cout << "s2==" << s2 << endl;
  cout << "s3==" << s3 << endl;

  s1 = s2;
  cout << "s1==" << s1 << endl;
  cout << "s2==" << s2 << endl;
  cout << "s3==" << s3 << endl;

  s3 = (s2 = (s1 = S<double>(5.555)));
  cout << "s1==" << s1 << endl;
  cout << "s2==" << s2 << endl;
  cout << "s3==" << s3 << endl;


  // (s1 = s2) = s3; // not alowed because operator= returns const reference

  /*

  S<int> s_int(4); // = 4; NOT ALOWED because of explicit constructor definition
  cout << "s_int==" << s_int << endl;

  s_int.set(12);
  cout << "s_int==" << s_int << endl;

  cout << "enter an integer: ";
  cin >> s_int;
  cout << "s_int==" << s_int << endl;


  S<char> s_char('a');
  cout << "s_char==" << s_char << endl;

  cout << "enter a char: ";
  cin >> s_char;
  cout << "s_char==" << s_char << endl;


  S<double> s_double(3.14);
  cout << "s_double==" << s_double << endl;

  cout << "enter a double: ";
  cin >> s_double;
  cout << "s_double==" << s_double << endl;


  S<string> s_str("hello");
  cout << "s_str==" << s_str << endl;

  cout << "enter a string: ";
  cin >> s_str;
  cout << "s_str==" << s_str << endl;


  // testing vector
  vector<int> vi;
  vi.push_back(1);
  vi.push_back(2);
  vi.push_back(3);
  vi.push_back(4);
  vi.push_back(5);

  S<vector<int> > s_vec(vi);
  cout << "s_vec==" << s_vec << endl;

  cout << "enter an integer vector: ";
  cin >> s_vec;
  cout << "s_vec==" << s_vec << endl;



  // testing the default constructor
  S<int> s_int2;
  cout << "s_int2" << s_int2 << endl;

  S<vector<int> > s_vec2;
  cout << "s_vec2" << s_vec2 << endl;

  // test get(), get() const
  S<double> sd;
  cout << "sd==" << sd << endl;
  sd.set(3.14);
  cout << "sd==" << sd << endl;

  */
}
