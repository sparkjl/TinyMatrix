#ifndef __API_TASK_H_
#define __API_TASK_H_

/* task number definition */
#define TASK_NUM                      (uint8_t)(64u)

/* task handler definition */
typedef struct
{
  uint8_t       run;                  /* task execute flag */
  uint16_t      tick;                 /* task execute tick */
  uint16_t      time;                 /* task execute time */
  
  void          (*p_task)(void);      /* task function */
} Task_HandleTypeDef;


static Task_HandleTypeDef      htask[TASK_NUM];
static uint8_t                 htask_index;

void api_task_tick(void);
void api_task_handle(void);

uint8_t api_task_create(void (*p_task)(void), uint16_t run_time);
uint8_t api_task_delete(void (*p_task)(void));

#endif /* __API_TASK_H_ */

