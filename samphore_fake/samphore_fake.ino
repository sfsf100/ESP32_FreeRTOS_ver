
/*
在我們的程式中，我們將使用setup函數啟動可配置數量的任務，然後它將等待信號量以完成所有任務。這種協調將使用前面提到的計數信號量來實現。
當任務嘗試取得沒有單位的信號量（信號量計數器等於0）時，它將停止，直到信號量計數被其他任務遞增或發生定義的逾時。

然後，我們將計數信號量聲明為全域變量，因此可以透過setup函數和任務來存取它。我們使用xSemaphoreCreateCounting 函數來建立信號量

此函數接收訊號量可以達到的最大計數和初始值作為輸入參數。由於我們將此用於同步目的，因此我們將指定最大計數等於要啟動的任務數，並將其初始化為0

使用相同的任務函數來啟動多個任務，因此我們不需要為每個新任務實作程式碼。我們將檢查後者的程式碼。

我們將建立固定到ESP32的核心1的任務。
這是因為，在看到這個先前的文章中，設定功能被固定到核心1。這將是我們更容易理解信號燈的功能不引入多核心執行的複雜性。如果您需要了解推出固定到特定的ESP32核心任務的更多信息，請查看之前的教程。
*/

int nTasks=4;
SemaphoreHandle_t barrierSemaphore = xSemaphoreCreateCounting( nTasks, 0 );


/*
  啟動任務後，我們將執行for迴圈嘗試取得信號量與啟動任務的次數一樣多。因此，當信號量中的單元數量與任務數量相同時，設定函數只應從該執行點傳遞。
  由於會有增加信號量的任務，我們應該保證Arduino設定功能只有在所有任務完成後才能完成。
*/
//啟動任務後，我們將執行for迴圈嘗試取得信號量與啟動任務的次數一樣多。因此，當信號量中的單元數量與任務數量相同時，設定函數只應從該執行點傳遞。
//由於會有增加信號量的任務，我們應該保證Arduino設定功能只有在所有任務完成後才能完成。
void genericTask()
{
  for(i= 0; i< nTasks; i++){
    xSemaphoreTake(barrierSemaphore, portMAX_DELAY);
}
 
Serial.println("Tasks launched and semaphore passed...");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(112500);
  delay(1000);
 
  Serial.println("Starting to launch tasks..");
 
  int i;
 
  for(i= 0; i< nTasks; i++){
    xTaskCreatePinnedToCore(
                    genericTask,    /* Function to implement the task */
                    "genericTask",  /* Name of the task */
                    10000,          /* Stack size in words */
                    (void *)i,      /* Task input parameter */
                    0,              /* Priority of the task */
                    NULL,           /* Task handle. */
                    1);             /* Core where the task should run */
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  vTaskSuspend(NULL);

}

xTaskCreatePinnedToCore(
                    coreTask,   /* Function to implement the task */
                    "coreTask", /* Name of the task */
                    10000,      /* Stack size in words */
                    NULL,       /* Task input parameter */
                    0,          /* Priority of the task */
                    NULL,       /* Task handle. */
                    taskCore);  /* Core where the task should run */
