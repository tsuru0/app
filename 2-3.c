#include <stdio.h>
#include <stdlib.h>

struct _cell{
    int tag;
    
    union{
        struct{struct _cell *car,*cdr;} cons;
        int num;
        struct{char *name;struct _cell *value;} symbol;
    }data;
};

typedef struct _cell cell;
typedef cell *ptr;

//#define nil  NULL   //これでも良い。
cell NIL;
ptr nil=&NIL;

ptr  car(ptr p){
    return p->data.cons.car;
}

ptr  cdr(ptr p){
    return p->data.cons.cdr;
}

ptr  cons(ptr car,ptr cdr){
    
    ptr p;
    
    p=malloc(sizeof(cell));
    p->data.cons.car=car;
    p->data.cons.cdr=cdr;
    p->tag=0;  //0はcons
    
    return p;
}

ptr  makeint(int n){
    
    ptr p;
    
    p=cons(nil,nil);
    p->data.num=n ;
    p->tag=1  ;//1は整数データ
    
    return p;
}

ptr  makesymbol(char *name){
    
    ptr p;
    
    p=cons(nil,nil);
    p->data.symbol.name=name ;
    p->tag=2  ;//2はシンボル
    
    return p;
}

ptr print_cons(ptr p); //プロトタイプ宣言

ptr print(ptr p){
    
    if(p==nil){
        printf("()");
        return nil;
    }
    
    switch(p->tag){
        case 0:  //リストのprint
            putchar('(');//先頭の(の印刷
            print_cons(p);//リストの項目を印刷する。
            break;
        case 1:  //int
            printf("%d ",p->data.num);
            break;
        case 2:  //symbol
            printf("%s ",p->data.symbol.name);
            break;
        default:
            printf("Abnormal data! Fatal!\n");
            exit(1);
    }
    
    return nil;
}

ptr print_cons(ptr p){  //  p is cons
    ptr next;
    
    print(car(p)); //これはprintでないといけない。
    
    next=cdr(p);
    
    if(next==nil)
        putchar(')');
    else if(next->tag==0){ //list が続く
        print_cons(next);
    }
    else{  //非真性リスト
        printf(" . ");
        print(next);
        putchar(')');
    }
    
    return nil;
}

ptr list2(ptr p, ptr q){
    q = cons(q, nil);
    p = cons(p, q);
    
    return p;
}

//ここからmainを作る。

int main(void){
    ptr a, b, c;
    ptr p, q, r;
    
    //(a )を作成
    a = makesymbol("a");
    p = cons(a, nil);
    
    
    //(b c )を作成
    b = makesymbol("b");
    c = makesymbol("c");
    q = cons(b, c);
    
    //((b c ))を作成
    q = cons(q, nil);

    //(a (b c ))を作成
    r = cons(a, q);

    //データの表示
    print(p);
    printf("\n");
    
    print(r);
    printf("\n");
    
    return 0;
}
