#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "fields.h"
#include <fcntl.h>
#include <unistd.h>
typedef struct {
    char * key;
    char * value;
}
JsonITEM;

void removeChar(char * s, char c) {
    int j, n = strlen(s);
    for (int i = j = 0; i < n; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}

void freeJsonITEM(JsonITEM* jsonItem){
if(jsonItem!=NULL){
	if(jsonItem->key!=NULL)
	free(jsonItem->key);
	if(jsonItem->value!=NULL)
	free(jsonItem->value);
	if(jsonItem!=NULL)
	free(jsonItem);
	}
}

int main(int argc, char ** argv) {
    JRB t, tmp;
    IS is;
    JsonITEM * p;
    int nsize, i;

    is = new_inputstruct("./.kilit");
    t = make_jrb();

    while (get_line(is) > 0) {
        // is->line : o satirdaki eleman sayisini verir

        /*for (i = 0; i < is->NF; i++) {
          printf("%s " , is->fields[i]);
        }*/

        if (strcmp(is -> fields[0], "{") && strcmp(is -> fields[0], "}")) {
            p = malloc(sizeof(JsonITEM));
            p -> key = (char * ) malloc(sizeof(char) * (strlen(is -> fields[0]) + 1));
            if (is -> NF != 1) {
                p -> value = (char * ) malloc(sizeof(char) * (strlen(is -> fields[1]) + 1));
                /////

                removeChar(is -> fields[0], 34);
                removeChar(is -> fields[0], 58);
                //int size=strlen(is->fields[1]);
                //if(is->fields[1][size-1]  == 44){
                removeChar(is -> fields[1], 44);
                //}
                removeChar(is -> fields[1], 34);

                strcpy(p -> value, is -> fields[1]);
            }
            /////
            strcpy(p -> key, is -> fields[0]);

            jrb_insert_str(t, p -> key, new_jval_v((void * ) p));

        }
    }

//////encrtyped fonksiyonu
    if (!strcmp("-e", argv[1])) {
    	if(argv[2]==NULL || argv[3]==NULL){
    		printf("dosya yok!\n");
    		return 0;
    	}
  	jettison_inputstruct(is);
        is = new_inputstruct(argv[2]);
        if(is==NULL){
          printf("acilmaya calisilan dosya bulunamadi!\n");
         return 0;
        }

        FILE *fp=fopen(argv[3],"w");
        printf("encrypt ediliyor\n");
        while (get_line(is) >= 0) {                               
            for (i = 0; i < is -> NF; i++) {
             int flag=0;
                jrb_traverse(tmp, t) {
                    p = (JsonITEM * ) tmp -> val.v;
                    if (!strcmp(is -> fields[i], p -> key)) {
                    flag=1;
    					fprintf(fp,"%s ",p->value);
                    }                    
                }
               if(flag==0)
               {
            	 fprintf(fp,"%s ",is->fields[i]);  
               }
            }
           
        }
        printf("encrypt edildi\n");
        fclose(fp);
    }
    
//////deccrtyped fonksiyonu
    if (!strcmp("-d", argv[1])) {
    	if(argv[2]==NULL || argv[3]==NULL){
    		printf("dosya yok!\n");
    		return 0;
    	}
    	jettison_inputstruct(is);
        is = new_inputstruct(argv[2]);
        if(is==NULL){
         printf("acilmaya calisilan dosya bulunamadi!\n");
         return 0;
        }
        
        FILE *fp=fopen(argv[3],"w");
        
        printf("dencrypt ediliyor\n");
        while (get_line(is) >= 0) {          
            for (i = 0; i < is -> NF; i++) {
                int flag=0;
                jrb_traverse(tmp, t) {
                    p = (JsonITEM * ) tmp -> val.v;
                    if (!strcmp(is -> fields[i], p -> value)) {
                    flag=1;
    					fprintf(fp,"%s ",p->key);
                    }
                }
               if(flag==0)
               {
            	 fprintf(fp,"%s ",is->fields[i]);  
               }
            }
        }
        printf("dencrypt edildi\n");
        fclose(fp);
    }
    
    jrb_traverse(tmp, t) {
                    p = (JsonITEM * ) tmp -> val.v;

                    if (p!=NULL) {
    					freeJsonITEM(p);
                    }
                }

    jettison_inputstruct(is);
    return 0;
}
