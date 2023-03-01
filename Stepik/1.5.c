///*** 1.5.1 ***///
int main() {
  int input1 = read_int(); // читаем первое число
  int input2 = read_int(); // читаем второе число

  printf("%d", input1 + input2); // печатаем сумму  

  return 0;   
}

///*** 1.5.2 ***///
int discriminant(int a, int b, int c) {
    return b*b-4*a*c ;
}

int root_count( int x ) {
   int D = x ;
   if (D > 0) {
       return 2;
   }
    else if (D < 0){return 0;}
    else{ return 1;}
}

int main() {
    // Считайте три числа в локальные переменные (см. предыдущий шаг)
    int a = read_int();
    int b = read_int();
    int c = read_int();

    // выведите результат запуска root_count с аргументами a, b и c.
    printf("%d", root_count(discriminant(a,b,c)));
    return 0;
}