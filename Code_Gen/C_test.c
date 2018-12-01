#include <stdio.h>
#include <stdlib.h>
#include "Builtins.h"
void quackmain();
int main(int argc, char** argv) {
quackmain();
}
struct class_Bt_struct;
typedef struct class_Bt_struct* class_Bt;
typedef struct obj_Bt_struct {
class_Bt clazz;
obj_Int x;
obj_Int y;
} *obj_Bt;
struct class_Bt_struct {
obj_Bt (*constructor) (obj_Int, obj_Int);
obj_Int (*PLUS) (obj_Bt, obj_Int);
obj_Nothing (*Times) (obj_Bt, obj_Int);
};
extern class_Bt the_class_Bt;
obj_Bt new_Bt(obj_Int x, obj_Int y){
obj_Bt new_thing = (obj_Bt) malloc(sizeof(struct obj_Bt_struct));
new_thing->clazz = the_class_Bt;
obj_Int tmp_0 = x;
new_thing->x = tmp_0;
obj_Int tmp_1 = y;
new_thing->y = tmp_1;
return new_thing;
}
obj_Int Bt_method_PLUS(obj_Bt this, obj_Int f){
obj_Int g;
obj_Int tmp_3 = f;
obj_Int tmp_4 = int_literal(1);
obj_Int tmp_6 = f;
obj_Int tmp_2 = tmp_3->clazz->PLUS(tmp_3,tmp_4);
g = tmp_2;
obj_Int tmp_7 = g;
return tmp_7;
}
void Bt_method_Times(obj_Bt this, obj_Int s){
}
struct class_Bt_struct the_class_Bt_struct={
new_Bt, 
Bt_method_PLUS, 
Bt_method_Times
};
class_Bt the_class_Bt = &the_class_Bt_struct;
void quackmain() {
obj_Bt z;
z = new_Bt(int_literal(9),int_literal(8));
obj_Int y;
obj_Int tmp_10 = int_literal(3);
obj_Int tmp_12 = int_literal(4);
obj_Bt tmp_14 = z;
obj_Int tmp_13 = tmp_14->x;
obj_Int tmp_16 = int_literal(4);
obj_Int tmp_11 = tmp_12->clazz->TIMES(tmp_12,tmp_13);
obj_Int tmp_18 = int_literal(3);
obj_Int tmp_9 = tmp_10->clazz->PLUS(tmp_10,tmp_11);
y = tmp_9;
obj_Int tmp_20 = y;
tmp_20->clazz->PRINT(tmp_20);
}

