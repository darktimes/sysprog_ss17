#include <stdio.h>
#include "String.h"
#include "SymbolTable.h"

int main()
{
	SymbolTable st;


  String str1 ("hello");
  String str2 ("world");
  String str3;
  str3 = String(str1);

  Symbol* sym1 = st.create(str1);
  Symbol* sym2 = st.create(str2);
  Symbol* sym3 = st.create(str3);

  printf("sym1: %s\n", sym1->ident2.getStr());
  printf("sym1: %s\n", sym2->ident2.getStr());
  printf("sym1: %s\n", sym3->ident2.getStr());

  return 0;
}
