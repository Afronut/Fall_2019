/*
 * File: pager-lru.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains an lru pageit
 *      implmentation.
 */

#include <stdio.h>
#include <stdlib.h>

#include "simulator.h"
void swap_page(Pentry q[MAXPROCESSES], int tick, int timestamps[MAXPROCESSES][MAXPROCPAGES], int pro_count);

void print_table(int timestamps[MAXPROCESSES][MAXPROCPAGES]);
void print_page(Pentry q[MAXPROCESSES]);

void pageit(Pentry q[MAXPROCESSES])
{

    /* This file contains the stub for an LRU pager */
    /* You may need to add/remove/modify any part of this file */

    /* Static vars */
    static int initialized = 0;
    static int tick = 1; // artificial time
    static int timestamps[MAXPROCESSES][MAXPROCPAGES];

    /* Local vars */
    int proctmp;
    int pagetmp;
    int pro_count; // process counter 
    int page_num; // page number 

    /* initialize static vars on first run */
    if (!initialized)
    {
        for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++)
        {
            for (pagetmp = 0; pagetmp < MAXPROCPAGES; pagetmp++)
            {
                timestamps[proctmp][pagetmp] = 0;
            }
        }
        initialized = 1;
    }
    /* TODO: Implement LRU Paging */
    for (pro_count = 0; pro_count < MAXPROCESSES; pro_count++)
    {
        if (q[pro_count].active)
        {
            page_num = q[pro_count].pc / PAGESIZE; // find page number 
            timestamps[pro_count][page_num] = tick; // get the tick of the giving page
            // printf("%d\n", pro_count);
            // try to page in and check if the page number for the process is valid
            if (!pagein(pro_count, page_num) && !q[pro_count].pages[page_num])
            {
                swap_page(q, tick, timestamps, pro_count);  // swap a page
                // print_page(q);

            }
        }
        /* advance time for next pageit iteration */
    }
    tick++;
    // print_table(timestamps);
}

void swap_page(Pentry q[MAXPROCESSES], int tick, int timestamps[MAXPROCESSES][MAXPROCPAGES], int pro_count)
{
    int lru = -1; 
    int to_evict = 0;
    int pagetmp; 
    // loop to find the least recently used page
    for (pagetmp = 0; pagetmp < q[pro_count].npages; pagetmp++)
    {
        if (tick - timestamps[pro_count][pagetmp] > lru && q[pro_count].pages[pagetmp])
        {
            to_evict = pagetmp;
            lru = tick - timestamps[pro_count][pagetmp];
            // printf("%d\n", to_evict);
        }
    }
    pageout(pro_count, to_evict);
}

void print_table(int timestamps[MAXPROCESSES][MAXPROCPAGES])
{
    FILE *fptr;
    fptr = fopen("table", "a+");
    if (fptr == NULL)
    {
        perror("Error!\n");
        return;
    }

    for (size_t i = 0; i < (size_t)MAXPROCESSES; i++)
    {
        for (size_t j = 0; j < (size_t)MAXPROCPAGES; j++)
        {
            fprintf(fptr, "%s", "|");
            fprintf(fptr, "%d", timestamps[i][j]);
        }
        fprintf(fptr, "%s", "--------------------------------------------\n");
    }
    fclose(fptr);
}

void print_page(Pentry q[MAXPROCESSES])
{
    FILE *fptr;
    fptr = fopen("table", "a+");
    if (fptr == NULL)
    {
        perror("Error!\n");
        return;
    }
    // for (size_t i = 0; i < (size_t)MAXPROCPAGES; i++)
    // {
        for (size_t j = 0; j < (size_t)MAXPROCPAGES; j++)
    {
        fprintf(fptr, "%s", "|");
        fprintf(fptr, "%ld", q[j].pc/PAGESIZE);
    }
    // fprintf(fptr, "%s", "&&");
    // }
    
    
    fprintf(fptr, "%s", "\n--------------------------------------------\n");
    fclose(fptr);
}