
#include <cstdint>
#include <cstdio>
int main () {
  int hir = 0xFf;


  long hex[] = {0, 0xfffffffffffffff, };

  for(int i = 0; i < 20; ++i) {
    printf("Hexadecimal%b", hex[i]);
  }
}
