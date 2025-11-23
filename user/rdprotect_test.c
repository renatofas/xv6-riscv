#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  char *addr;
  
  printf("rdprotect_test: inicio\n");
  
  // Allocate one page
  addr = sbrk(4096);
  if(addr == (char*)-1){
    printf("rdprotect_test: sbrk failed\n");
    exit(1);
  }
  
  printf("rdprotect_test: pagina asignada en %p\n", addr);
  
  // Write to page (should work)
  addr[0] = 'A';
  printf("rdprotect_test: escritura inicial OK\n");
  
  // Protect page (remove read permission)
  if(mrdprotect(addr, 1) < 0){
    printf("rdprotect_test: mrdprotect failed\n");
    exit(1);
  }
  
  printf("rdprotect_test: mrdprotect aplicado\n");
  
  // Try to write (may fail due to RISC-V restriction)
  printf("rdprotect_test: intentando escribir...\n");
  addr[0] = 'B';
  printf("rdprotect_test: escritura OK\n");
  
  // Try to read (should fault)
  printf("rdprotect_test: intentando leer...\n");
  char c = addr[0];
  printf("rdprotect_test: lectura = %c (no deberia llegar aqui)\n", c);
  
  // Restore permission
  if(munrdprotect(addr, 1) < 0){
    printf("rdprotect_test: munrdprotect failed\n");
    exit(1);
  }
  
  printf("rdprotect_test: munrdprotect aplicado\n");
  
  // Read should work now
  c = addr[0];
  printf("rdprotect_test: lectura restaurada = %c\n", c);
  
  printf("rdprotect_test: test completado\n");
  exit(0);
}