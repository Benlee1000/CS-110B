#include <iostream>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <ctype.h>

using namespace std; 

/*
 * ******* INSTRUCTIONS ****
 * Make the modifications required to generate the output shown in block
 * comments in main().  To do these modifications, replace the underscores 
 * ("_________"), which show where the modifications should go, with the 
 * required code.  There are two main parts to these modifications:
 * 
 * 1.  (15 points) Supply a constructor for class B (1.a), and complete the 
 *     first line in the D instance method pop (1.b), so that the while 
 *     loop in main() generates these two lines of output:
 *     Line 1: d->pop() == 42
 *     Line 2: d->pop() == 7
 *
 * 2.  (15 points) Complete the call to the C instance method append() 
 *     before the last  cout statement (2.a), and define the C instance 
 *     method get().  Both are required so that the output of that last 
 *     cout statement will be "c->get(1) == 3" 
 */


class B {
  int answer;
public:
  int getAnswer() {return this->answer; }
  B(string n) { this->answer = stoi(n) % 5; }
  //1.b Supply the B consructor needed to generate
  //    the specified while loop output.
  B() {
      this->answer = 42;
    } //B contstror

}; //class B

class D : public B {
  int answer;
  vector<int> numbers;
public:
  int length() { return this->numbers.size(); }


  //Remove the last element from the numbers vector and
  // return it.  
  int pop() {
    //1.a supply the right-hand side of the assignent
    // statement tht will initialize the variable ret.
    int ret = numbers.back(); //access last element
    this->numbers.erase(this->numbers.end()-1);
    return ret;
  } //pop()
  
  D(int num) {
    numbers.push_back(num);
    numbers.push_back(this->getAnswer());
  }; //D constuctor
}; //class D

class C {
  vector<B*> bases;
public:
  C() { this->bases.push_back(new B());}
  void append(int i)  {
    char s[10];
    sprintf(s,"%d",i);
    string cppStr = s;
    this->bases.push_back(new B(cppStr) );
  } //append()
  void append()  {this->bases.push_back(new B() ); }

  //2.b Define the instance method get in order to
  //    generate the specified output for problem 2.
  //    get() returns the answer field of one of the objects
  //	on the bases vector.
  int get(int index)  {
    return bases.at(index)->getAnswer();
  }
};//class C	 
	
int main( )
{
  D *d = new D(7);

  while (d->length() > 0) {
    /* 1. (15 points) Supply a constructor for B (1.a), and complete the first
     * line in the D instance method pop (1.b) so that this while loop 
     * genrerates two lines of output:
     * Line 1: d->pop() == 42
     * Line 2: d->pop() == 7
     */
    cout << "d->pop() == " <<  d->pop() << endl;
  } //while there are numbers left to pop

  C *c = new C();

  /*  2. (15 points) Complete the call to the C instance method append (2.a), 
   *  and define the C instance method get (2.b), in order to output
   *  "c->get(1) == 3" with the cout statement 
   *
   * 2.a Call the version of the C instance method append that needed
   *     so that c->get(1) will output 3. Note that one version of append
   *     takes no parameters, and the other requires selecting an integer 
   *     parameter.
   */
  c->append(13);
  //If parts 2.a and 2.b (defining the get method) are done correctly,
  // the output of this last cout statement will be:
  // "c->get(1) == 3"
  //
  cout << "c->get(1) == "  << c->get(1) << endl;
} //main()
  
