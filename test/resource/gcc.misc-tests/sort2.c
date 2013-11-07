





typedef unsigned char boolean;

void Sort_array();
int Tab[100];

main () {
   int I,J,K,L;

for (L = 0; L < 1000; L++) {

   K = 0;
   for (I = 9; I >= 0; I--)
      for (J = I*10; J < (I+1)*10; J++)
  Tab[K++] = J&1 ? J+1 : J-1;


   Sort_array(Tab,99);

}
   return 0;
}

void Sort_array(Tab,Last) int Tab[]; int Last; {
   boolean Swap;
   int Temp,I;
   do {
      Swap = 0;
      for (I = 0; I<Last; I++)
  if (Tab[I] > Tab[I+1]) {
     Temp = Tab[I];
     Tab[I] = Tab[I+1];
     Tab[I+1] = Temp;
     Swap = 1;
     }
      }
   while (Swap);
}


void Print_array() {
   int I,J;

   for (I=0; I<=9; I++) {

      for (J=0; J<=9; J++);

      }
}
