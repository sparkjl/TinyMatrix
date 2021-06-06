#include "includes.h"

//Task_HandleTypeDef      htask[TASK_NUM];
//uint8_t                 htask_index;

void api_task_tick(void)
{
  uint8_t i = 0;
  
  for(i=0; i<htask_index; i++)
  {
    if(htask[i].tick < htask[i].time)
    {
      htask[i].tick++;
    }
    else if(htask[i].tick == htask[i].time)
    {
      htask[i].tick = 0;
      htask[i].run = 1;
    }
  }
}

void api_task_handle(void)
{
  uint8_t i = 0;
  
  for(i=0; i<htask_index; i++)
  {
    if(htask[i].run == 1)
    {
      htask[i].p_task();
      htask[i].run = 0;
    }
  }
}

uint8_t api_task_create(void (*p_task)(void), uint16_t run_time)
{
  uint8_t i = 0;
  
  for(i=0; i<htask_index; i++)
  { 
    /* the task has been created */
    if(htask[i].p_task == p_task)
      return 0;
  }
	
  if(htask_index < TASK_NUM)
  {
    htask[htask_index].run = 0;
    htask[htask_index].tick = 0;
    htask[htask_index].time = run_time;
    htask[htask_index].p_task = p_task;
  }
  else
  {
    /* task queue is full */
    return 0;
  }
	
  htask_index++;
  return 1;	
}

uint8_t api_task_delete(void (*p_task)(void))
{
  uint8_t i, k = 0;

  for(i=0; i<htask_index; i++)
  {
    if(htask[i].p_task == p_task)
      break;
  }
  
  /* the task has not been created */
  if(i == htask_index)
  {
    return 0;
  }

  for(k=i; k<htask_index-1; k++)
  {
    htask[k] = htask[k+1];
  }

  htask[htask_index-1].run = 0;
  htask[htask_index-1].tick = 0;
  htask[htask_index-1].time = 0;
  htask[htask_index-1].p_task = NULL;

  htask_index--;
  return 1;
}


