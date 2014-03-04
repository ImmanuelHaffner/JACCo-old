0

int main() {
  goto blubb;
blubb: return 1;
}

int foo() {
blubb: return 1;
}
