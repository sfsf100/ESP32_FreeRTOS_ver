TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_4;



/* Task2 with priority 2 */
static void MyTask2(void* pvParameters)
{
  while(1)
  {    
    Serial.println("Task2 Running, Creating Task4");
    //xTaskCreate(MyTask4, "Task4", 100, NULL, 4, &TaskHandle_4);
    
    Serial.println("Back in Task2, Deleting itself");
    vTaskDelete(NULL);     //Delete own task by passing NULL(TaskHandle_2 can also be used)
  }
}

/* Task1 with priority 1 */
static void MyTask1(void* pvParameters)
{
  while(1)
  {
    Serial.println("Task1 with Priority:");
    Serial.print(uxTaskPriorityGet(TaskHandle_1));
    Serial.print("Creating Task2");
    
    xTaskCreate(MyTask2, "Task2", 1200, NULL, 3, &TaskHandle_2);
    
    Serial.println("Task1 with Priority:");
    Serial.print(uxTaskPriorityGet(TaskHandle_1));
    Serial.print(" Deleting All");
    vTaskDelete(TaskHandle_2);   // Delete task2 and task4 using their handles
   // vTaskDelete(TaskHandle_4); 
    vTaskDelete(TaskHandle_1);    // Delete the task using the TaskHandle_1
  }
}


void setup()
{
  
  Serial.begin(115200);
  //Serial.println(F("In Setup function"));

  /* Create three tasks with priorities 1,2 and 3. Capture the Task details to respective handlers */
  xTaskCreate(MyTask1, "Task1", 1200, NULL, 1, &TaskHandle_1);  

}


void loop()
{
  // Hooked to IDle task, it will run whenever CPU is idle
  Serial.println("Loop function");
  delay(50);
}
