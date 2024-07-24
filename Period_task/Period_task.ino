#define LED1 18
#define LED2 19
//unsigned long runTime;     //宣告變數

void vPeriodicTask( void *pvParameters ) 
{ 
  TickType_t xLastWakeTime; 
  const TickType_t xDelay3ms = pdMS_TO_TICKS( 3000 ); 
  /* The xLastWakeTime variable needs to be initialized with the current tick 
  count.  Note that this is the only time the variable is explicitly written to. 
  After this xLastWakeTime is managed automatically by the vTaskDelayUntil() 
  API function. */ 
  xLastWakeTime = xTaskGetTickCount(); 
  /* As per most tasks, this task is implemented in an infinite loop. */ 
  for( ;; ) 
  {
  
    //vPrintString( "Periodic task is running\r\n" ); 
    vTaskDelayUntil( &xLastWakeTime, xDelay3ms ); 
    Serial.println("Periodic task is running\r\n");
   }
} 



void vApplicationIdleHook_a() {
    // 打印空闲任务的状态信息
    Serial.println("Idle task running...\n");
    // 或者使用其他方式记录状态信息
}

void taskA(void *pvParam)
{
   pinMode(LED1, OUTPUT);   // 將接腳設定為輸出模式
   while(1){
       
    Serial.println("taskA NOW\n ");
    digitalWrite(LED1,!digitalRead(LED1));//切換腳位
    //Serial.println("A NOW is IDLE\n");
    vTaskDelay(pdMS_TO_TICKS(1000)); //delay 250ms
    vApplicationIdleHook_a();
   }  
}

void taskB(void *pvParam)
{
   pinMode(LED2, OUTPUT);   // 將接腳設定為輸出模式
   while(1){
    //runTime = millis();
   
     Serial.println("taskB NOW\n");
    digitalWrite(LED2,!digitalRead(LED2));//切換腳位
   
    vTaskDelay(2000/portTICK_PERIOD_MS); //delay 500ms
     Serial.println("B Idle task running...\n");
   }  
}


void setup() {
  Serial.begin(115200);
  //Serial.println("idle ");
  // put your setup code here, to run once:
  xTaskCreate(taskA,"taskA",1000,NULL,1,NULL);
  xTaskCreate(taskB,"taskB",1000,NULL,1,NULL);
  xTaskCreate(vPeriodicTask, "PeriodicTask", 1000, NULL,1, NULL);

  vTaskStartScheduler();
}

void loop() {
  
  // put your main code here, to run repeatedly:

}
