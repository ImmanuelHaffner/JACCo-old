5


int * foo(){
  int * p;
  *p = 5;
  return p;
}

int main(){
  return *foo();
}
