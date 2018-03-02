#include <iostream>
#include <string.h>
 using namespace std;
 void encode( char* src, char* dest, int num_bytes);
 std::string ascii = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
 int main()
 {
   // Declare arrays to store original and encoded strings.
   char st[80];
   char encoded[120];
   // Read in original string.
   cout << "Enter text: ";
   cin.getline(st, 80);
   // Print back out along with the # of characters.
   int len = strlen(st);
   cout << "You typed in \"" << st << "\" (" << len << " characters)" << endl;
   // Round length down to a multiple of 3.
   len -= (len % 3);
   // Encode the string - every 3 characters of original becomes
   // 4 characters of result.
   int dest_index = 0;
   for (int i=0; i<len; i+=3)
   {
   encode(st+i, encoded+dest_index, 3);
   dest_index += 4;
   }

   char filler[3] = {}; //creates filling for end
   for (int i = 0; i<strlen(st)-len; i++){
     filler[i] = st[len+i];
   }
   encode(&filler[0], encoded+dest_index, strlen(st)-len);
   dest_index += 4; //change dest index again
   // Null terminate destination string.
   encoded[dest_index] = 0;
   // Print encoded value.
   cout << "Encoded value: ";
   cout << encoded << endl;
   return 0;
 }
 void encode( char* src, char* dest, int num_bytes)
 {
   if(num_bytes >= 1){
     unsigned char mask = 0b11111100; //creates mask
     unsigned char ch0 = mask & src[0]; //ands together to keep the 6 bits
     ch0 >>= 2; //shift to adjust for 2 removed
     dest[0] = ascii.at(ch0); // assign to new spot


     unsigned char mask2 = 0b00000011;
     unsigned char last2 = mask2 & src[0];
     last2<<=4; //shift to adjust

     unsigned char mask3 = 0b11110000;
     unsigned char first4 = mask3 & src[1];
     first4 >>= 4;

     unsigned char ch1 = last2 | first4; //combine 2 subsections
     dest[1] = ascii.at(ch1); // assign to new spot
   }

   if(num_bytes >= 2){
     unsigned char mask4 = 0b00001111;
     unsigned char last4 = mask4 & src[1];
     last4 <<=2; //shift bits

     unsigned char mask5 = 0b11000000;
     unsigned char first2 = mask5 & src[2];
     first2 >>= 6;

     unsigned char ch2 = first2 | last4; //combine them
     dest[2] = ascii.at(ch2);
   }

   if (num_bytes >= 3){
     unsigned char mask6 = 0b00111111;
     unsigned char ch3 = mask6 & src[2];
     dest[3] = ascii.at(ch3);
     //already in correct spot, don't shift
   }

  if (num_bytes == 1){
    dest[2] = '=';
    dest[3] = '=';
  }

  else if(num_bytes == 2){
    dest[3] = '=';
  }
}

void decode(char* src, char* dest){
  int dest_count = 0;
  int buff_count = 0;
  char buffer = 0;
  unsigned char ascii_count = 0;
  for(int i=0; i<strlen(src); i++){
    if (src[i] == '='){  //ignore if padded
      break;
    }
    for (int j=0; j<ascii.length(); j++){
      if(src[i] == ascii.at(j)){ //check if equal to ascii
        break;
      }
      ascii_count++;
    }
  }
  if (buff_count == 0){
    buffer = ascii_count <<2; //adjust for 2 empty spots
    buff_count == 6; //adjust for 6 new thing inside
  }
  else if(buff_count == 6){
    unsigned char newmask = 0b00110000;
    unsigned char temp = ascii_count & newmask;
    temp >>= 4;
    dest[dest_count] = buffer | temp; //or them together
    dest_count++;
    buffer = 0b00001111 & ascii_count; //and with ascii_count
    buffer <<= 4;
    buff_count = 4; //set to 4
  }
  else if(buff_count == 4){
    //ran out of time here
    //this would be the same as 6 but adjustments are different
  }
  else if(buff_count == 2){
    //just grab last 6 or them with buffer
    //set buffer back to 0
  }

//dest[dest_count] = '\0'
}
