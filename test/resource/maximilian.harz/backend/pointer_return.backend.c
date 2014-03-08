5


int * foo(){
  int x;
  int *p;
  p = &x;
  *p = 5;
  return p;
}

int main(){
  return *foo();
}
