//
//  parse.h
//  parse
//
//  created by Supersure on 2018/7/29.
//  Copyright © 2018年 Supersure. All rights reserved.
//

#ifndef parse_h
#define parse_h

#define TAG_STA_UNSPLITED       0
#define TAG_STA_SPLITED         1

#define SINGLE_SPLIT            1
#define SYM_SPLIT               2
#define PAIR_SPLIT              3

typedef char *  pString;

typedef struct tag{
    pString         pHead;
    pString         pTail;
    pString         pSpliter;
    pString         pSpliter_pair;
    
    unsigned char   status;
    unsigned int    split_length;
    
    struct tag      *child;
    struct tag      *next;
}tag_struct;

typedef struct {
    
    pString         pSrc;
    pString         pHead;
    pString         pTail;
    tag_struct      *tag;
    tag_struct      *tag_index;
    
    int             tag_number;
    
    int             (*init)(void);
    int             (*split)(unsigned char split_mode, const char *spliter, ...);
    int             (*match)(const char *label);
    int             (*get)(char **pDst);
    void            (*end_parse)(void);
    
}parse_string;

extern parse_string string;

#endif /* parse_h */
