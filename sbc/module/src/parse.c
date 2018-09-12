//
//  parse.c
//  parse
//
//  created by Supersure on 2018/7/29.
//  Copyright © 2018年 Supersure. All rights reserved.
//

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "parse.h"

static int init(void);
static int split(unsigned char split_mode, const char *spliter, ...);
static int match(const char *label);
static int get(char **pDst);
static void end_parse(void);

parse_string string = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    
    0,
    
    init,
    split,
    match,
    get,
    end_parse
};

/**
 * strnstr - 在src串的前n个字符中对model串进行匹配
 * @src: 源串
 * @label: 匹配串
 * @pos: 在src的前pos字符中查找
 * @returnValue: 匹配到的dst串起始地址
 * add by Supersure
**/
char* strnstr(const char* src, const char* label, int pos)
{
	char* pHead_index = NULL;
	
	if(NULL == src || NULL == label)
		return NULL;
	
	if(strlen(src) < pos)
		return NULL;
	
	pHead_index = strstr((const char *)src, (const char *)label);
	
	if(pHead_index < src + pos)
		return pHead_index;
	else
		return NULL;
	
}

/**
 * shift_to_label - 在src串的前n个字符中对model串进行匹配
 * @src: 源串
 * @label: 匹配串
 * @labelNumber: 找到第label_number个label串
 * @returnValue: 第n个label串起始地址
 * add by Supersure
**/
static char * shift_to_label(const char *src, const char * label, int label_number)
{
    int i;
    char *Index = (char *)src;
    int label_length = (int)strlen(label);
    
    for(i=0; i<label_number-1; i++) {
        Index = strstr((const char *)Index + label_length, (const char *)label);
        if(NULL == Index)
            break;
    }
    return Index;
}

/**
 * list_traverse - 遍历到当前链表最后一个节点
 * @pRoot: 当前链表头
 * @returnValue: 当前链表最后一个节点地址
 * add by Supersure
**/
static tag_struct * list_traverse(tag_struct *pRoot)
{
    tag_struct *pIndex = pRoot;
    if(NULL == pIndex)
        return NULL;
    
    while(NULL != pIndex->next)
        pIndex = pIndex->next;
    
    return pIndex;
}

/**
 * list_single_split - 单串分隔
 * @pIndex: 需要进行分隔的节点
 * @spliter: 分隔串
 * @returnValue: 分隔次数
 * add by Supersure
**/
static int list_single_split(tag_struct *pIndex, const char *spliter)
{
    int         split_count         =   0;
    char *      split_head_index    =   NULL;
    char *      split_tail_index    =   NULL;
    char *      split_head          =   NULL;
    char *      split_tail          =   NULL;
    tag_struct  *pNode              =   NULL;
    
    if(NULL == pIndex)
        return -1;
    
    /*递归地进入最后一个子链表头*/
    if(NULL != pIndex->child)
        list_single_split(pIndex->child, spliter);
    
    /*递归地进入链表最后一个节点*/
    if(NULL != pIndex->next)
        list_single_split(pIndex->next, spliter);
    
    if(NULL == pIndex->child) {
        
        if(NULL == pIndex->pHead)
            return 0;
        
        split_head = pIndex->pHead;
        split_tail = pIndex->pTail;
        split_head_index =  pIndex->pHead;
        
        /*找到第一个分隔串所在位置*/
        split_tail_index =  strstr(split_head_index, spliter);
        
        if(NULL == split_tail_index)
            return 0;
        
        /*如果无法找到分隔串或分隔串在尾节点之后，分隔结束*/
        if(split_tail_index > split_tail || split_tail_index == NULL)
            return 0;
        
        /*否则分隔成功，创建子链表头，并进入*/
        pIndex->status = TAG_STA_SPLITED;
        pIndex->child = (tag_struct *)calloc(sizeof(tag_struct), 1);
        if(NULL == pIndex->child)
            return -1;
        pIndex = pIndex->child;
        
        /*开始遍历串并分隔，直到找不到合适的分隔串位置*/
        while(1) {
            split_count ++;
            
            /*插入新节点，作为子串*/
            pNode = (tag_struct *)calloc(sizeof(tag_struct), 1);
            if(NULL == pNode)
               return -1;
            
            pNode->pSpliter = (char *)calloc(sizeof(char), sizeof(spliter));
            if(NULL == pNode->pSpliter)
                return -1;
            
            strcpy(pNode->pSpliter, spliter);
            pNode->pHead = split_head_index;
            pNode->pTail = split_tail_index;
            pNode->status = TAG_STA_UNSPLITED;
            pNode->split_length = (unsigned int)(split_tail_index - split_head_index);
            pNode->next = pIndex->next;
            pIndex->next = pNode;
            pIndex = list_traverse(pIndex);
            
            /*尝试找到下一个分隔串起始位置*/
            split_head_index = split_tail_index + strlen(spliter);
            split_tail_index = strstr((const char *)split_head_index, (const char *)spliter);
            
            /*如果下一个分隔串的起始位置无法找到或在串尾之后，视为最后一次分隔*/
            if((split_tail_index == NULL || split_tail_index > split_tail) && split_head_index != split_head) {
                
                /*在当前链表尾插入新节点*/
                pNode = (tag_struct *)calloc(sizeof(tag_struct), 1);
                if(NULL == pNode)
                    return -1;
                
                pNode->pSpliter = (char *)calloc(sizeof(char), sizeof(spliter));
                if(NULL == pNode->pSpliter)
                    return -1;
                
                strcpy(pNode->pSpliter, spliter);
                pNode->pHead = split_head_index;
                pNode->pTail = split_tail;
                pNode->status = TAG_STA_UNSPLITED;
                pNode->split_length = (unsigned int)(pNode->pHead - pNode->pTail);
                pNode->next = pIndex->next;
                pIndex->next = pNode;
                
                break;
            }
            
        }
    }
    string.tag_number += split_count;
    return split_count;
    
}

/**
 * list_pair_split - 对串分隔
 * @pIndex: 需要进行分隔的节点
 * @spliter1: 左分隔串
 * @spliter2: 右分隔串
 * @returnValue: 分隔次数
 * add by Supersure
**/
static int list_pair_split(tag_struct *pIndex, const char *spliter_1, const char *spliter_2)
{
    int         split_count         =   0;
    int         cmp_count           =   0;
    int         spliter_differerce  =   0;
    char *      spliter_index       =   NULL;
    char *      split_head_index    =   NULL;
    char *      split_head          =   NULL;
    char *      split_tail          =   NULL;
    tag_struct  *pNode              =   NULL;
    
    if(NULL == pIndex)
        return -1;
    
    /*递归地进入最后一个子链表头*/
    if(NULL != pIndex->child)
        list_pair_split(pIndex->child, spliter_1, spliter_2);
    
    /*递归地进入链表最后一个节点*/
    if(NULL != pIndex->next)
        list_pair_split(pIndex->next, spliter_1, spliter_2);
    
    
    if(NULL == pIndex->child) {
        
        if(NULL == pIndex->pHead)
            return -1;
        
        /*找到第一个左分隔串所在位置*/
        split_head = strstr((const char *)pIndex->pHead, (const char *)spliter_1);
        
        /*如果第一个左分隔串的位置无法找到或在串尾之后，分隔结束*/
        if(NULL == split_head || split_head > pIndex->pTail)
            return 0;
        
        /*找到第一个右分隔串所在位置*/
        split_tail = strstr((const char *)pIndex->pHead, (const char *)spliter_2);
        
        /*如果第一个右分隔串的位置无法找到或在串尾之后，分隔结束*/
        if(NULL == split_tail || split_tail > pIndex->pTail)
            return 0;
        
        spliter_index = split_head;
        split_tail = pIndex->pTail;
        
        /*否则分隔成功，创建子链表头，并进入*/
        pIndex->child = (tag_struct *)calloc(sizeof(tag_struct), 1);
        if(NULL == pIndex->child)
            return -1;
        pIndex = pIndex->child;
        
        
        /*开始遍历串并分隔，直到找不到合适的左分隔串位置*/
        while(1)
        {
            /*找到下一个左分隔串的起始位置*/
            split_head_index = strstr((const char *)spliter_index, (const char *)spliter_1);
            
            /*如果下一个左分隔串的位置无法找到或在串尾之后，分隔结束*/
            if(NULL == split_head_index || split_head_index > split_tail)
                return 0;
            
            /*否则开始寻找与当前左分隔串匹配的右分隔串*/
            spliter_index = split_head_index;
            
            /*开始遍历串并分隔，直到找到匹配的右分隔串或分隔结束*/
            while(1) {
                
                /*遍历长度计数*/
                cmp_count += strlen(spliter_1);
                
                /*找到一个新的左分隔串，分隔对差分加一*/
                if(strnstr(spliter_index, spliter_1, cmp_count)) {
                    spliter_differerce ++;
                    spliter_index = strnstr(spliter_index, spliter_1, cmp_count) + strlen(spliter_1);
                    cmp_count = 0;
                }
                
                 /*找到一个新的右分隔串，分隔对差分减一*/
                if(strnstr(spliter_index, spliter_2, cmp_count)) {
                    spliter_differerce --;
                    spliter_index = strnstr(spliter_index, spliter_2, cmp_count) + strlen(spliter_2);
                    cmp_count = 0;
                }
                
                /*如果分隔对查分等于零，则找到了与当前左分隔串匹配的右分隔串*/
                if(spliter_differerce == 0) {
                    split_count ++;
                    
                    /*在当前链表尾插入新节点*/
                    pNode = (tag_struct *)calloc(sizeof(tag_struct), 1);
                    if(NULL == pNode)
                        return -1;
                    
                    pNode->pSpliter = (char *)calloc(sizeof(char), sizeof(spliter_1));
                    if(NULL == pNode->pSpliter)
                        return -1;
                    
                    pNode->pSpliter_pair = (char *)calloc(sizeof(char), sizeof(spliter_2));
                    if(NULL == pNode->pSpliter_pair)
                        return -1;
                    
                    strcpy(pNode->pSpliter, spliter_1);
                    strcpy(pNode->pSpliter_pair, spliter_2);
                    pNode->pHead = split_head_index + strlen(spliter_1);
                    pNode->pTail = spliter_index - strlen(spliter_1);
                    pNode->status = TAG_STA_UNSPLITED;
                    pNode->split_length = (unsigned int)(pNode->pHead - pNode->pTail);
                    pNode->next = pIndex->next;
                    pIndex->next = pNode;
                    pIndex = list_traverse(pIndex);
                    cmp_count = 0;
                    break;
                }
            }
        }
    }
    
    string.tag_number += split_count;
    return split_count;
}

/**
 * list_sym_split - 对称串分隔
 * @pIndex: 需要进行分隔的节点
 * @spliter: 分隔串
 * @returnValue: 分隔次数
 * add by Supersure
**/
static int list_sym_split(tag_struct *pIndex, const char *spliter)
{
    char *      split_head_index    =   NULL;
    char *      split_tail_index    =   NULL;
    tag_struct  *pNode              =   NULL;
    
    if(NULL == pIndex)
        return -1;
    
    /*递归地进入最后一个子链表头*/
    if(NULL != pIndex->child)
        list_sym_split(pIndex->child, spliter);
    
    /*递归地进入链表最后一个节点*/
    if(NULL != pIndex->next)
        list_sym_split(pIndex->next, spliter);
    
    if(NULL == pIndex->child) {
        
        /*找到第一个分隔串的起始位置*/
        split_head_index = shift_to_label(pIndex->pHead, spliter, 1);
        
        /*如果第一个分隔串的位置无法找到或在串尾之后，分隔结束*/
        if(NULL == split_head_index || split_head_index > pIndex->pTail)
            return 0;
        
        /*找到第二个分隔串的起始位置*/
        split_tail_index = shift_to_label(pIndex->pHead, spliter, 2);
        
        /*如果第二个分隔串的位置无法找到或在串尾之后，分隔结束*/
        if(NULL == split_tail_index || split_head_index > pIndex->pTail)
            return 0;
        
        /*否则分隔成功，创建子链表头，并进入*/
        pIndex->child = (tag_struct *)calloc(sizeof(tag_struct), 1);
        if(NULL == pIndex->child)
            return -1;
        pIndex = pIndex->child;
        
        /*在当前链表尾插入新节点*/
        pNode = (tag_struct *)calloc(sizeof(tag_struct), 1);
        if(NULL == pNode)
            return -1;
        
        pNode->pSpliter = (char *)calloc(sizeof(char), sizeof(spliter));
        if(NULL == pNode->pSpliter)
            return -1;
        
        strcpy(pNode->pSpliter, spliter);
        pNode->pHead = split_head_index + strlen(spliter);
        pNode->pTail = split_tail_index;
        pNode->split_length = (int)(pNode->pTail - pNode->pHead);
        pNode->status = TAG_STA_UNSPLITED;
        pNode->next = pIndex->next;
        pIndex->next = pNode;

    }
    
    return 0;
}

/**
 * list_sym_split - 串匹配
 * @pIndex: 需要进行匹配的节点
 * @label: 匹配模板串
 * @returnValue: 匹配状态
 * add by Supersure
**/
static int list_match(tag_struct *pIndex, const char *label)
{
    char        *match_head_index   =   NULL;
    char        *match_tail_index   =   NULL;
    tag_struct  *pNode      =   NULL;
    
    if(NULL == pIndex)
        return -1;
    
    /*递归地进入最后一个子链表头*/
    if(NULL != pIndex->child)
        list_match(pIndex->child, label);
    
    /*递归地进入链表最后一个节点*/
    if(NULL != pIndex->next)
        list_match(pIndex->next, label);
    
    if(NULL == pIndex->child) {
        
        /*找到分隔串所在位置*/
        match_head_index = strnstr(pIndex->pHead, label, pIndex->split_length);
        
        /*如果分隔串的位置无法找到或在串尾之后，分隔结束*/
        if(NULL == match_head_index || match_head_index > pIndex->pTail)
            return 0;
        match_tail_index = pIndex->pTail;
        
        /*否则分隔成功，创建子链表头，并进入*/
        pIndex->child = (tag_struct *)calloc(sizeof(tag_struct), 1);
        if(NULL == pIndex->child)
            return -1;
        pIndex = pIndex->child;
        
        /*在当前链表尾插入新节点*/
        pNode = (tag_struct *)calloc(sizeof(tag_struct), 1);
        if(NULL == pNode)
            return -1;
        
        pNode->pSpliter = (char *)calloc(sizeof(char), sizeof(label));
        if(NULL == pNode->pSpliter)
            return -1;
        
        pIndex = list_traverse(pIndex);
        strcpy(pNode->pSpliter, label);
        pNode->pHead = match_head_index + strlen(label);
        pNode->pTail = match_tail_index;
        pNode->status = TAG_STA_UNSPLITED;
        pNode->split_length = (unsigned int)(pNode->pHead - pNode->pTail);
        pNode->next = pIndex->next;
        pIndex->next = pNode;
        
        
    }
    return 0;
 
}

/**
 * list_free - 释放分隔进程内存
 * @pIndex: 内存链表头
 * @returnValue: %NUL
 * add by Supersure
**/
static void list_free(tag_struct *pIndex)
{
    if(NULL == pIndex)
        return;
    
    if(NULL != pIndex->child)
        list_free(pIndex->child);
    
    if(NULL != pIndex->next)
        list_free(pIndex->next);
    
    free(pIndex);
}

/**
 * init - 初始化分隔进程内存
 * @param: %NUL
 * @returnValue: 初始化状态
 * add by Supersure
**/
static int init()
{
    string.tag = (tag_struct *)calloc(sizeof(tag_struct), 1);
    if(NULL == string.tag)
        return -1;
    
    if(NULL == string.pHead || NULL == string.pTail)
        return -1;
    
    string.tag->pHead = string.pSrc + strlen(string.pHead);
    string.tag->pTail = string.pSrc + strlen(string.pSrc)-strlen(string.pTail);
    string.tag->split_length = (unsigned int)(string.tag->pTail - string.tag->pHead);
    
    string.tag_index = string.tag;
    
    return 0;
    
}

/**
 * split - 用户调用函数, 进行串分隔
 * @split_mode: 分隔类型
 * @spliter: 分隔串
 * @returnValue: 分隔状态
 * add by Supersure
**/
static int split(unsigned char split_mode, const char *spliter, ...)
{
    va_list     ap;
    char        *split_pair;
    if(SINGLE_SPLIT == split_mode)
        return list_single_split(string.tag, spliter);
    else if(PAIR_SPLIT == split_mode){
        va_start(ap, spliter);
        split_pair = va_arg(ap, char*);
        va_end(ap);
        return list_pair_split(string.tag, spliter, split_pair);
    }
    else if(SYM_SPLIT == split_mode){
        return list_sym_split(string.tag, spliter);
    }
    
    else
        return 0;
}

/**
 * match - 用户调用函数, 进行串匹配
 * @label: 匹配模板串
 * @returnValue: 匹配状态
 * add by Supersure
**/
static int match(const char *label)
{
    return list_match(string.tag, label);
}

static int get(char **pDst)
{
    return 0;
}

/**
 * end_parse - 结束串操作
 * @param: void
 * @returnValue: void
 * add by Supersure
**/
static void end_parse()
{
    list_free(string.tag);
    memset( string.tag, 0, sizeof(parse_string));
}




