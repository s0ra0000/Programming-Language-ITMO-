///*** 2.4.1 ***///
struct list {
  int64_t value;
  struct list* next;
};

struct list* node_create( int64_t value ) {

   if(value>0){
       struct list *b =(struct list*)malloc(sizeof(struct list)*value);
       b->value = value;
       return b;
   }
    else{
        struct list *b =(struct list*)malloc(sizeof(struct list));
       b->value = value;
         return b;
    }
  
}

///*** 2.4.2 ***///

// Вам доступна функция
struct list* node_create( int64_t value );

void list_add_front(struct list** old, int64_t value ) {
  struct list *new = node_create(value);
  new->value = value;
  new->next = (*old);
    (*old) = new;
   
}

///*** 2.4.3 ***///
size_t list_length(const void *list) {
  size_t length = 0;
    struct list *currentPtr = (struct list*)list;
    while(currentPtr != NULL){
        currentPtr = currentPtr->next;
        length++;
    }
  return length;
}


///*** 2.4.4 ***///
void list_destroy( struct list* list ) {
    struct list* tmp = NULL;
    if(list != NULL){
        while(list->next){
              tmp = list;
              list = list->next;
              free(tmp);
          }
    }
    free(list);
}

///*** 2.4.5 ***///
struct list* list_last( struct list * list ) {
    struct list *last = NULL;
  if(list != NULL){
      while(list->next){
          list = list->next;
          last = list;
      }
      
  }
    return last;
}

///*** 2.4.6 ***///
void list_add_back( struct list** old, int64_t value ) {
     struct list *last = NULL;
     if(*old == NULL){
         list_add_front(old,value);
     }else{
      last = list_last(*old);
    struct list *new = node_create(value);
    new->value = value;
    last->next = new;
     }
   
}

///*** 2.4.7 ***///
int64_t list_sum( const void* list ) {
     int64_t sum = 0;
    struct list *list_sum = (struct list*)list;
    if(list_sum != NULL){
     sum = list_sum->value;
     while(list_sum->next){
         list_sum = list_sum->next;
         sum+=list_sum->value;
     }
    }
    return sum;
}

///*** 2.4.8 ***///
struct maybe_int64 list_at(const void* list, size_t idx ) {
  struct maybe_int64 val = none_int64;
   struct list *my_list = (struct list*)list;
    size_t index = 0;
    if(my_list != NULL){
        while(my_list->next){
            if(index == idx){
                   val = some_int64(my_list->value);
                return val;
            }
            index++;
            my_list = my_list->next;
        }
    }
    return val;
}

///*** 2.4.9 ***///
void list_add_front( struct list** old, int64_t value );

// создать перевернутую копию списка
struct list* list_reverse(const struct list* list ) {
    //struct list *my_list = (const )list;
    
    if(list != NULL){
        struct list* reversed_list = NULL;
        reversed_list = malloc(sizeof(struct list));
        *reversed_list = (struct list){.value = list->value, .next = NULL};
        list = list->next;
        while(list){
            list_add_front(&reversed_list,list->value);
            list =list->next;
        }
    return reversed_list;
    }
    else{
        return NULL;
    }
}

///*** 2.4.10 ***///
struct maybe_int64 maybe_read_int64() {
    int64_t val;
    struct maybe_int64 read_val = none_int64;
    if(scanf("%" SCNd64, &val)>0){
        read_val = some_int64(val);
        return read_val;
    }
    return read_val;
}


///*** 2.4.11 ***///
struct list* list_read() {
    struct list *new = NULL;
    struct list *list = new;
    struct maybe_int64 val;
    val = maybe_read_int64();
    
    while(val.valid){
        if(!list){
            new = node_create(val.value);
            list = new;
        }else{
            new->next = node_create(val.value);
            new = new->next;
        }
        val = maybe_read_int64();
    }
    return list;
}




