#include iostream
#include pandemicTracker.hpp

use namesspace std;


string makeNextFileName() {

  string csvFileName;
  return csvFileName;
}

int main () {
  //prompte for start date and length of analysis interval
  makeNextFileName();

  while (true) {
    string csvFn = makeNextFileName();
    if (csvFn == NULL_STRING) {
      //analysis interval over
      break;
    }
    cout << csvFn << endl;
  }

  cout << "End of test suite << endl;

}
