SemaphoreHandle_t package_delivered_semaphore;

void delivery_truck_task(void *pvParameters) {
  int truck_number = (int)pvParameters;
  while (1) {
    // Wait for a package to be delivered
    // ...
    // Notify the warehouse that a package has been delivered
    xSemaphoreGive(package_delivered_semaphore);
    Serial.printf("Package delivered by truck: %d\n", truck_number);
    //wait for some time
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void warehouse_worker_task(void *pvParameters) {
  int worker_number = (int)pvParameters;
  while (1) {
    // Wait for a package to be delivered
    xSemaphoreTake(package_delivered_semaphore, portMAX_DELAY);
    Serial.printf("Package received by worker: %d\n", worker_number);
    // Receive the package
    // ...
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  // Create the semaphore
  package_delivered_semaphore = xSemaphoreCreateCounting(10, 0);

  // Create multiple delivery truck tasks
  for (int i = 0; i < 5; i++) {
    xTaskCreate(delivery_truck_task, "Delivery Truck", 2048, (void *)i, tskIDLE_PRIORITY, NULL);
  }

  // Create multiple warehouse worker tasks
  for (int i = 0; i < 3; i++) {
    xTaskCreate(warehouse_worker_task, "Warehouse Worker", 2048, (void *)i, tskIDLE_PRIORITY, NULL);
  }
}

void loop() {
  // Empty loop
}
