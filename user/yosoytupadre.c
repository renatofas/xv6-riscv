#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static void check(const char* tag, int expected, int got) {
  printf("%s: %s (got=%d, expected=%d)\n",
         tag, (expected == got ? "[OK]" : "[FAIL]"), got, expected);
}

int
main(void)
{
  int me   = getpid();
  int ppid = getppid();
  printf("Yo = %d, Mi padre = %d\n", me, ppid);

  // Pruebas de ancestros: 0 (yo), 1 (padre), 2 (abuelo), 3 (inexistente=-1)
  int a0 = getancestor(0);
  int a1 = getancestor(1);
  int a2 = getancestor(2);
  int a3 = getancestor(3);

  printf("anc(0)=%d, anc(1)=%d, anc(2)=%d, anc(3)=%d\n", a0, a1, a2, a3);

  // Chequeos esperados en un arranque normal: init=1, sh=2
  // OJO: el PID "me" puede variar (3,4,5...), según lo que ya haya corrido.
  check("anc(0)==me", me, a0);
  check("anc(1)==ppid", ppid, a1);
  // El abuelo suele ser init (1) si corres desde sh:
  // No falles la tarea si no es 1 por algo extraño; es informativo.
  printf("(Info) Abuelo esperado ~ 1, got=%d\n", a2);

  // anc(3) normalmente no existe -> -1
  check("anc(3)==-1", -1, a3);

  exit(0);
}
