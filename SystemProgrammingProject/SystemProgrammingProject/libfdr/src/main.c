#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "fields.h"

typedef struct {
  char *key;
  char *value;
} JsonITEM;

void removeChar(char* s, char c)
{
 
    int j, n = strlen(s);
    for (int i = j = 0; i < n; i++)
        if (s[i] != c)
            s[j++] = s[i];
 
    s[j] = '\0';
}

int main(int argc, char **argv)
{
  JRB t, tmp;
  IS is;
  JsonITEM *p;
  int nsize, i;

  is = new_inputstruct(NULL);
  t = make_jrb();


 while(get_line(is) > 0) {
  // is->line : o satirdaki eleman sayisini verir
    
    /*for (i = 0; i < is->NF; i++) {
      printf("%s " , is->fields[i]);
    }*/
    
    if(strcmp(is->fields[0],"{") && strcmp(is->fields[0],"}")){
      p = malloc(sizeof(JsonITEM));
      p->key = (char *) malloc(sizeof(char)*(strlen(is->fields[0])+1));
      if(is->NF!=1){
      	p->value = (char *)  malloc(sizeof(char)*(strlen(is->fields[1])+1));
      	/////


        removeChar(is->fields[0], 34);
        removeChar(is->fields[0], 58);
        //int size=strlen(is->fields[1]);
        //if(is->fields[1][size-1]  == 44){
        removeChar(is->fields[1], 44);
        //}
        removeChar(is->fields[1], 34);
       
      	strcpy(p->value, is->fields[1]);
      }
      /////
      strcpy(p->key, is->fields[0]);
      
      
      jrb_insert_str(t, p->key, new_jval_v((void *) p));

    }
  }
  
  
  
  jrb_traverse(tmp, t) {
    p = (JsonITEM *) tmp->val.v;
    printf("%s %s\n", p->key, p->value);
  }
  jettison_inputstruct(is);
  return 0;
}
