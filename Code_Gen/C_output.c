#include <stdio.h>
#include <stdlib.h>
#include "Builtins.h"
void quackmain();
int main(int argc, char** argv) {
quackmain();
}
struct class_Pt_struct;
typedef struct class_Pt_struct* class_Pt;
typedef struct obj_Pt_struct {
class_Pt clazz;
obj_Int x;
obj_Int y;
} *obj_Pt;
struct class_Pt_struct {
obj_Pt (*constructor) (obj_Int, obj_Int);
obj_String (*STRING) (obj_Pt);
obj_Obj (*PRINT) (obj_Obj);
obj_Int (*switcher) (obj_Pt);
obj_Int (*PLUS) (obj_Pt, obj_Pt);
};
extern class_Pt the_class_Pt;
obj_Pt new_Pt(obj_Int x, obj_Int y){
obj_Pt new_thing = (obj_Pt) malloc(sizeof(struct obj_Pt_struct));
new_thing->clazz = the_class_Pt;
obj_Int tmp_0 = x;
new_thing->x = tmp_0;
obj_Int tmp_1 = y;
new_thing->y = tmp_1;
return new_thing;
}
obj_String Pt_method_STRING(obj_Pt this) {
return str_literal("Object of type: Pt");
}
obj_Int Pt_method_switcher(obj_Pt this){
obj_Pt tmp_4 = this;
obj_Int tmp_3 = tmp_4->x;
obj_Int tmp_5 = int_literal(0);
obj_Boolean tmp_2=tmp_3->clazz->LESS(tmp_3,tmp_5);
if( lit_true == tmp_2) { goto true0;}
goto false2;
true0:
{
obj_Int tmp_6 = int_literal(0);
return tmp_6;
goto endif3;
}
false2:
{
obj_Pt tmp_8 = this;
obj_Int tmp_7 = tmp_8->x;
return tmp_7;
}
endif3: ;
}
obj_Int Pt_method_PLUS(obj_Pt this, obj_Pt other){
obj_Pt tmp_11 = other;
obj_Int tmp_10 = tmp_11->x;
obj_Pt tmp_13 = this;
obj_Int tmp_12 = tmp_13->x;
obj_Pt tmp_16 = other;
obj_Int tmp_15 = tmp_16->x;
obj_Int tmp_9 = tmp_10->clazz->PLUS(tmp_10,tmp_12);
return tmp_9;
}
struct class_Pt_struct the_class_Pt_struct={
new_Pt, 
Pt_method_STRING,
Obj_method_PRINT, 
Pt_method_switcher, 
Pt_method_PLUS
};
class_Pt the_class_Pt = &the_class_Pt_struct;
void quackmain() {
obj_Pt c;
c = new_Pt(int_literal(1),int_literal(2));
obj_Pt b;
b = new_Pt(int_literal(13),int_literal(42));
obj_Int a;
obj_Int tmp_20 = int_literal(1);
obj_Pt tmp_23 = b;
obj_Pt tmp_25 = b;
obj_Pt tmp_28 = b;
obj_Int tmp_21 = tmp_23->clazz->switcher(tmp_23)->clazz->PLUS(tmp_23->clazz->switcher(tmp_23),tmp_25->clazz->PLUS(tmp_25,c));
obj_Int tmp_30 = int_literal(1);
obj_Int tmp_19 = tmp_20->clazz->PLUS(tmp_20,tmp_21);
a = tmp_19;
obj_Int tmp_32 = a;
tmp_32->clazz->PRINT(tmp_32);
}
