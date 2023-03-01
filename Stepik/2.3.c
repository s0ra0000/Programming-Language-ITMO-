///*** 2.3.1 ***///
// упакованное число 42 выводится как "Some 42"
// Ошибка выводится как None
void maybe_int64_print( struct maybe_int64 i ) {
    if(i.valid){
        printf("Some %"PRId64,i.value);
    }
    else{
        printf("None");
    }
}

// Если обе упаковки содержат ошибку, то результат ошибка
// Если ровно одна упаковка содержит ошибку, то результат -- вторая
// Если обе упаковки содержат число, то результат это минимум из двух чисел.
struct maybe_int64 maybe_int64_min(struct maybe_int64 a, struct maybe_int64 b) {
    if(a.valid && b.valid){
        if(a.value >= b.value){
            return b;
        } else{
            return a;
        }
    }
    else if((!a.valid) && b.valid){
        return b;
    }
    else if(a.valid &&(!b.valid)) {
        return a;
    }
    else{
        return a;
    }
}

///*** 2.3.2 ***///
/*

struct maybe_int64 {
  int64_t value;
  bool valid;
};

struct maybe_int64 some_int64(int64_t i) {
  return (struct maybe_int64) { i, true };
}

const struct maybe_int64 none_int64 = { 0 };
*/

size_t read_size() { size_t sz = 0; scanf("%zu", &sz); return sz; }

struct array_int {
  int64_t* data;
  size_t size;
};

void array_int_fill( int64_t* array, size_t sz ) {
  for( size_t i = 0; i < sz; i = i + 1 ) {
    array[i] = read_int64();
  }
}

struct array_int array_int_read() {
  const size_t size = read_size();
  if (size > 0) {
    int64_t* array = malloc( sizeof(int64_t) * size);
    array_int_fill( array, size );
    return (struct array_int) { .data = array, .size = size };
  }
  else return (struct array_int) {0};
}

// возвращает ошибку если индекс за пределами массива
struct maybe_int64 array_int_get( struct array_int a, size_t i ) {
     struct maybe_int64 b = none_int64;
     if(a.size > i){
         b = some_int64((a.data)[i]);
         return b;
     }
    return b;
}

// возвращает false если индекс за пределами массива
bool array_int_set( struct array_int a, size_t i, int64_t value ){
  if(a.size>i){
      (a.data)[i] = value;
      return true;
  }
     return false;
}

void array_int_print( struct array_int array ) {
  for (size_t i = 0; i < array.size; i = i + 1) {
    printf("%" PRId64 " " , array_int_get( array, i).value);
  }
}

struct maybe_int64 array_int_min( struct array_int array ) {
    struct maybe_int64 minimum = none_int64;
    if(array.size > 0){
       int64_t min = (array.data)[0];    
     for(size_t i = 0; i<array.size; i++){
         if(min > (array.data)[i]){
             min = (array.data)[i];
             
          }
      }
        minimum = some_int64(min);
    }
     return minimum;
}

void array_int_free( struct array_int a ) { 
    if ( a.size > 0 ) {
        free(a.data); 
        a.size = 0;
    } 
}

///*** 2.3.3 ***///
/* Вы можете пользоваться этими функциями из предыдущих заданий */
size_t read_size() { size_t i; scanf("%zu", &i); return i; }

void array_int_fill( int64_t* array, size_t sz );

struct array_int array_int_read();
struct maybe_int64 array_int_get( struct array_int a, size_t i );
bool array_int_set( struct array_int a, size_t i, int64_t value );
void array_int_print( struct array_int array );
struct maybe_int64 array_int_min( struct array_int array );
void array_int_free( struct array_int a );

void array_int_normalize( struct array_int array, int64_t m ) {
  for (size_t i = 0; i < array.size; i = i + 1) {
    array.data[i] = array.data[i] - m;
  }
}

/*  ---- maybe int[] ---- */

struct maybe_array_int {
  struct array_int value;
  bool valid;
};

struct maybe_array_int some_array_int(struct array_int array) {
  return (struct maybe_array_int) { array, true };
}
const struct maybe_array_int none_array_int = { {NULL, 0}, false };


/*  ---- int[][] ---- */

struct array_array_int {
  struct array_int* data;
  size_t size;
};

/*  --- строки ---  */

struct maybe_array_int array_array_int_get_row( struct array_array_int a, size_t i ) {
  if ( 0 <= i && i < a.size ) { return some_array_int( a.data[i] ); }
  else { return none_array_int; }
}

bool array_array_int_set_row( struct array_array_int a, size_t i, struct array_int value ) {
  if (0 <= i && i < a.size) {
    a.data[i] = value;
    return true;
  }
  else { return false; }
}

/*  --- get/set ---  */

struct maybe_int64 array_array_int_get( struct array_array_int a, size_t i, size_t j ) {
     if(a.size < i && a.data[i].size < j){
         struct maybe_int64 val;
         val.value = a.data[i].data[j];
         val.valid = true;
         return val;
     }
    return none_int64;
}

bool array_array_int_set( struct array_array_int a, size_t i, size_t j, int64_t value ) {
     if(a.size < i && a.data[i].size < j){
         a.data[i].data[j] = value;
         return true;
     }
    return false;
}

/*  --- read/print ---  */

struct array_array_int array_array_int_read() {
    struct array_array_int array;
    size_t size = read_size();
    array.size = size;
    array.data = malloc(sizeof(struct array_array_int)*size);
    for(size_t i = 0; i<size; i++){
        array.data[i] = array_int_read();
    }
    return array;
}


void array_array_int_print( struct array_array_int array) {
      for(size_t i=0; i<array.size; i++){
          array_int_print(array.data[i]);
          printf("\n");
      }
    
}


/*  --- min/normalize ---  */

// найти минимальный элемент в массиве массивов
struct maybe_int64 array_array_int_min( struct array_array_int array ) {
    struct maybe_int64 min = none_int64;
    if(array.size > 0){
        min = array_int_min(array.data[0]);
        for(size_t i=1; i<array.size; i++){
            if(array.data[i].size > 0){
                if(min.value > array_int_min(array.data[i]).value)
                    min = array_int_min(array.data[i]);
            } 
        } 
        return min;
    }
    return none_int64;
}

// вычесть из всех элементов массива массивов число m
void array_array_int_normalize( struct array_array_int array, int64_t m) {
  for (size_t i = 0; i < array.size; i = i + 1) {
    const struct maybe_array_int cur_row = array_array_int_get_row( array, i );
    if (cur_row.valid) {
         array_int_normalize( cur_row.value, m );
    }
  }
}

void array_array_int_free( struct array_array_int array ) {
  for(size_t i=0; i<array.size; i++){
      if(array.data[i].size > 0) array_int_free(array.data[i]);
  }
  free(array.data);
}

///*** 2.3.4 ***///
/* Вы можете пользоваться следующими определениями:

struct maybe_int64 {int64_t value; bool valid;};
struct maybe_int64 some_int64(int64_t i);
const struct maybe_int64 none_int64 = { 0, false };
void maybe_int64_print( struct maybe_int64 i );


struct array_int {int64_t* data; size_t size;};
struct array_int array_int_create( size_t sz );

struct array_int array_int_create( size_t sz ) {
    return (struct array_int) { .data = malloc( sizeof( int64_t ) * sz ), .size = sz };
}

int64_t* array_int_last( struct array_int a );
struct maybe_int64 array_int_get( struct array_int a, size_t i );
bool array_int_set( struct array_int a, size_t i, int64_t value );
void array_int_print( struct array_int array );
void array_int_free( struct array_int* a );

*/

struct stack {
  size_t count;
  struct array_int data;
};

// Количество элементов в стеке
size_t stack_count( const struct stack* s ){
    return s->count;
}

// Создаем и деинициализируем стек
struct stack stack_create( size_t size ){
    
    return (struct stack){.count = 0,.data = array_int_create(size)};
}
void stack_destroy( struct stack* s ){
    array_int_free(&(s->data));
}

// Стек полный
bool stack_is_full( const struct stack * s){
    if(stack_count(s) == s->data.size){
        return true;
    }
    return false;
}
// Стек пустой
bool stack_is_empty( const struct stack * s){
    if(stack_count(s) == 0){
        return true;
    }
    return false;
}

// Поместить значение в стек
bool stack_push( struct stack* s, int64_t value ){
    if(stack_is_full(s)) return false;
    return array_int_set(s->data,(s->count)++,value);
}

// Вынуть значение с вершины стека. Может вернуть none_int64
struct maybe_int64
stack_pop( struct stack* s ){
    if(stack_is_empty(s)) return none_int64;
    struct maybe_int64 val = array_int_get(s->data,--(s->count));
    int64_t* last = array_int_last(s->data);
    *last = 0;
    return val;
}

void stack_print( const struct stack* s ) {
  for (size_t i = 0; i < stack_count( s ); i = i + 1 ) {
    print_int64( array_int_get( s->data, i).value );
    printf(" ");
  }
}