///*** 2.7.1 ***///
/*
struct list {
    int64_t value;
    struct list* next;
};
*/
void print_int64(int64_t i);


/* Запустить функцию f на каждом элементе списка  */
void list_foreach(const struct list* l, void (f)(int64_t)) {
    if(l != NULL){
        while(l->next){
        (f)(l->value);
        l = l->next;
    }
    (f)(l->value);
    }
}

/* Вывести список с помощью foreach и дополнительной функции */
void list_print(const struct list* l) { 
    list_foreach(l,print_int64_space);
}

///*** 2.7.2 ***///
/*
struct list {
    int64_t value;
    struct list* next;
};
*/

/* Изменить каждый элемент списка с помощью функции f  */
void list_map_mut(struct list* l, int64_t (f) (int64_t))  {
    if(l != NULL){
        while(l->next){
            int64_t vl = (f)(l->value);
            l->value = vl;
            l = l->next;
        }
        int64_t vl = (f)(l->value);
        l->value = vl;
    }
}


static int64_t triple( int64_t x ) { return x * 3; }

/* Используя list_map_mut умножьте все элементы списка на 3 */
void list_triple(struct list* l ) { 
    list_map_mut(l,triple);
}

///*** 2.7.3 ***///
/*
struct list {
    int64_t value;
    struct list* next;
};
*/
/* Вы можете пользоваться следующими функциями */
void print_int64(int64_t i);
struct list* node_create( int64_t value );



/*  Создать новый список, в котором каждый элемент получен из соответствующего
    элемента списка l путём применения функции f */
struct list* list_map(const struct list* l, int64_t (f) (int64_t))  {
    
    if( l == NULL){
        return NULL;
    }
    struct list* lmap = NULL;
        lmap = malloc(sizeof(struct list));
        lmap->value = (f)(l->value);
        lmap->next = list_map(l->next,f); 
        return lmap;
    
}

int64_t copy_function(int64_t val){
    return val;
}
int64_t abs_function(int64_t val){
    if(val >= 0){
        return val;
    }
    else{
        return val*(-1);
    }
}

struct list* list_copy(const struct list* l ) {
     if( l != NULL){
        return list_map(l,copy_function);
    }
    return NULL;
}

struct list* list_abs(const struct list* l ) {
    if( l != NULL){
        return list_map(l,abs_function);
    }
    return NULL;
}

///*** 2.7.4 ***///
/*
struct list {
    int64_t value;
    struct list* next;
};
*/
/* Вы можете пользоваться этими функциями */
void print_int64(int64_t i);
struct list* node_create( int64_t value );
void list_destroy( struct list* list );

static int64_t sum( int64_t x, int64_t y) { return x + y; }

typedef int64_t folding(int64_t, int64_t);

/* Свернуть список l с помощью функции f. */
int64_t list_fold( const struct list* l, int64_t init, folding f) {
  int64_t result = init;
  if(l != NULL){
      while(l->next){
          result = f(result,l->value);
          l = l->next;
      }
      result = f(result,l->value);
  }
  return result;
}

/* Просуммируйте список с помощью list_fold и sum */
int64_t list_sum(const struct list* l ) {
    int64_t result = 0;
    if(l != NULL){
        result = list_fold(l,0,sum);
    }
    return result;
}

///*** 2.7.5 ***///
/*
struct list {
    int64_t value;
    struct list* next;
};
*/
void print_int64(int64_t i);

struct list* node_create( int64_t value );
void list_destroy( struct list* list );


/*  Сгенерировать список длины sz с помощью значения init и функции f
 Результат: init, f(init), f(f(init)), ... */
struct list* list_iterate( int64_t init, size_t sz, int64_t(f)(int64_t)) {
 struct list* list = NULL;
 if(sz > 0){
     list = node_create(init);
     list->next = list_iterate((f)(init),sz-1,(f));
 }
 return list;
}