#include <iostream>
#include <stdlib.h>

using namespace std;

int main(void) {

  cout << "Mail_error returvaerdi: " << system("/home/pi/scripts/mail_error.sh") << endl;
  cout << "Mail_alarm returvaerdi: " << system("/home/pi/scripts/mail_alarm.sh") << endl;
  return 0;
}
