///*** 2.6.1 ***///
// используйте typedef чтобы определить ftype
typedef size_t f(struct array, int64_t);
typedef char ftype(const float*,size_t*);


///*** 2.6.2 ***///
// Мы хотим, чтобы в структуре user хранились ссылки только на строчки из кучи.
typedef struct { char* addr; } string_heap ;

/*  Тип для идентификаторов пользователей
    и его спецификаторы ввода и вывода для printf */
typedef uint64_t uid;
#define PRI_uid PRIu64
#define SCN_uid SCNu64

enum city {C_SARATOV, C_MOSCOW, C_PARIS, C_LOS_ANGELES, C_OTHER};

/*  Массив, где элементам перечисления сопоставляются их текстовые представления */
const char* city_string[] = {
  [C_SARATOV] = "Saratov",
  [C_MOSCOW] = "Moscow",
  [C_PARIS] = "Paris",
  [C_LOS_ANGELES] = "Los Angeles",
  [C_OTHER] = "Other"
};


struct user {
  const uid id;
  const string_heap name;
  enum city city;
};

int uid_cmp(const void* u1, const void* u2){
    const struct user* user_1 = (const struct user*) u1;
    const struct user* user_2 = (const struct user*) u2;
    if(user_1->id > user_2->id) return 1;
    if(user_1->id < user_2->id) return -1;
    return 0;
}

int name_cmp(const void* u1, const void* u2){
    const struct user* user_1 = (const struct user*) u1;
    const struct user* user_2 = (const struct user*) u2;
    if(*user_1->name.addr > *user_2->name.addr) return 1;
    if(*user_1->name.addr < *user_2->name.addr) return -1;
    return 0;
}

int city_cmp(const void* u1, const void* u2){
    const struct user* user_1 = (const struct user*) u1;
    const struct user* user_2 = (const struct user*) u2;
    return strcmp(city_string[user_1->city],city_string[user_2->city]);
}

/* Сортировать массив пользователей по полю uid по возрастанию */
void users_sort_uid(struct user users[], size_t sz) {
  qsort(users,sz,sizeof(struct user),uid_cmp);
}

/* Сортировать массив пользователей по полю name */
/* Порядок строк лексикографический; можно использовать компаратор 
   строк -- стандартную функцию strcmp */
void users_sort_name(struct user users[], size_t sz) {
  qsort(users,sz,sizeof(struct user),name_cmp);
}

/* Сортировать массив по _текстовому представлению_ города */
void users_sort_city(struct user users[], size_t sz) {
  qsort(users,sz,sizeof(struct user),city_cmp);
}

///*** 2.6.3 ***///
enum move_dir { MD_UP, MD_RIGHT, MD_DOWN, MD_LEFT, MD_NONE };

// Робот и его callback'и
// callback'ов может быть неограниченное количество
struct callbacks {
    void (*handler)(enum move_dir);
    struct callbacks *next;
};
struct robot {
  const char* name;
  struct callbacks *current;
};

// Определите тип обработчика событий move_callback с помощью typedef
typedef void(move_callback)(enum move_dir);

// Добавить callback к роботу, чтобы он вызывался при движении
// В callback будет передаваться направление движения
void register_callback(struct robot* robot, move_callback new_cb) {
      struct callbacks* new = NULL;
      new = malloc(sizeof(struct callbacks));
      *new = (struct callbacks){.handler = new_cb,.next = robot->current};
      robot -> current = new;
}

// Отменить все подписки на события.
// Это нужно чтобы освободить зарезервированные ресурсы
// например, выделенную в куче память
void unregister_all_callbacks(struct robot* robot) {
  while(robot->current != NULL){
      struct callbacks *old = robot -> current;
      robot -> current = robot->current->next;
      unregister_all_callbacks(robot);
      free(old);
  }
}

// Вызывается когда робот движется
// Эта функция должна вызвать все обработчики событий
void move(struct robot* robot, enum move_dir dir) {
  if(robot->current != NULL){
      robot->current->handler(dir);
      move(&(struct robot){.name = robot->name, .current = robot-> current->next},dir);
  }
}