#include "FreeRTOS.h"
#include "task.h"

#include "prv_i2c.h"
#include "prv_interrupt.h"
#include "prv_plic.h"
#include "prv_serial.h"
#include "Semphr.h"

#include "lcd_I2C_lib.h"

static SemaphoreHandle_t log_mutex;

void log_write(const char *msg)
{
    xSemaphoreTake(log_mutex, portMAX_DELAY);
    printf("Log Write : %s\n", msg);
    xSemaphoreGive(log_mutex);
}

void toggleLedTask0(void *delay_amt)
{
    while(1)
    {
        LED_ToggleOutput((uint8_t) 0);
        log_write("[Toggle LED0 Task]: Now Toggling LED0 pin.");
        vTaskDelay(pdMS_TO_TICKS((uint64_t)(uintptr_t) delay_amt));
    }
}

void toggleLedTask1(void *delay_amt)
{
    while(1)
    {
        LED_ToggleOutput((uint8_t) 1);
        log_write("[Toggle LED1 Task]: Now Toggling LED1 pin.");
        vTaskDelay(pdMS_TO_TICKS((uint64_t)(uintptr_t) delay_amt));
    }
}

void toggleLedTask2(void *delay_amt)
{
    while(1)
    {
        LED_ToggleOutput((uint8_t) 2);
        log_write("[Toggle LED2 Task]: Now Toggling LED2 pin.");
        vTaskDelay(pdMS_TO_TICKS((uint64_t)(uintptr_t) delay_amt));
    }
}

void toggleLedTask3(void *delay_amt)
{
    while(1)
    {
        LED_ToggleOutput((uint8_t) 3);
        log_write("[Toggle LED3 Task]: Now Toggling LED3 pin.");
        vTaskDelay(pdMS_TO_TICKS((uint64_t)(uintptr_t) delay_amt));
    }
}

void toggleLedTask4(void *delay_amt)
{
    while(1)
    {
        LED_ToggleOutput((uint8_t) 4);
        log_write("[Toggle LED4 Task]: Now Toggling LED4 pin.");
        vTaskDelay(pdMS_TO_TICKS((uint64_t)(uintptr_t) delay_amt));
    }
}

void toggleLedTask5(void *delay_amt)
{
    while(1)
    {
        LED_ToggleOutput((uint8_t) 5);
        log_write("[Toggle LED5 Task]: Now Toggling LED5 pin.");
        vTaskDelay(pdMS_TO_TICKS((uint64_t)(uintptr_t) delay_amt));
    }
}

void toggleLedTask6(void *delay_amt)
{
    while(1)
    {
        LED_ToggleOutput((uint8_t) 6);
        log_write("[Toggle LED6 Task]: Now Toggling LED6 pin.");
        vTaskDelay(pdMS_TO_TICKS((uint64_t)(uintptr_t) delay_amt));
    }
}

void toggleLedTask7(void *delay_amt)
{
    while(1)
    {
        LED_ToggleOutput((uint8_t) 7);
        log_write("[Toggle LED7 Task]: Now Toggling LED7 pin.");
        vTaskDelay(pdMS_TO_TICKS((uint64_t)(uintptr_t) delay_amt));
    }
}

void uartTask(void *msg)
{
    while(1)
    {
        log_write(msg);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void displayTimeTask(void *pvParameter)
{
    PLIC_INTERRUPT_CONFIG_t i2c_int_config = {
        .attach_interrupt_module = ATTACH_I2C0DNF_TO_INTERRUPT,
        .set_priority = INTERRUPT_PRIORITY_1
    };

    Set_Interrupt0(&i2c_int_config);

    uint32_t i2c_freq = I2C_FREQ(400000);
    I2C0_Initialize(i2c_freq, 7, 6);

    LCD_Initialize(0x27);
    LCD_noBlink();
    LCD_noCursor();

    uint32_t s = 0, m = 0, h = 0;

    while(1)
    {
        s += 1;
        if (s == 60)
        {
            s = 0;
            m += 1;
        }
        if (m == 60)
        {
            m = 0;
            h += 1;
        }

        LCD_setCursor(0, 1);
        LCD_print("%02d:%02d:%02d", h, m, s);
        log_write("[Display Task]: Now updating display time in hh:mm:ss format");
        vTaskDelay(pdMS_TO_TICKS(990));
    }
}

int main()
{
    Serial_Initialize(115200);

    log_mutex = xSemaphoreCreateMutex();

    /* Toggle Led Task */
    xTaskCreate(
        toggleLedTask0,              /* Function to toggle Led. */
        "led0",                      /* Text name for the task. */
        configMINIMAL_STACK_SIZE,    /* Stack size in words. */
        (void *)(uintptr_t) 100,     /* (Optional) delay amount. */
        tskIDLE_PRIORITY+2,          /* Task priority. */
        NULL);                       /* Task's handle - here set to NULL. */

    /* Toggle Led Task */
    xTaskCreate(
        toggleLedTask1,              /* Function to toggle Led. */
        "led1",                      /* Text name for the task. */
        configMINIMAL_STACK_SIZE,    /* Stack size in words. */
        (void *)(uintptr_t) 200,     /* (Optional) delay amount. */
        tskIDLE_PRIORITY+2,          /* Task priority. */
        NULL);                       /* Task's handle - here set to NULL. */

    /* Toggle Led Task */
    xTaskCreate(
        toggleLedTask2,              /* Function to toggle Led. */
        "led2",                      /* Text name for the task. */
        configMINIMAL_STACK_SIZE,    /* Stack size in words. */
        (void *)(uintptr_t) 300,     /* (Optional) delay amount. */
        tskIDLE_PRIORITY+2,          /* Task priority. */
        NULL);                       /* Task's handle - here set to NULL. */

    /* Toggle Led Task */
    xTaskCreate(
        toggleLedTask3,              /* Function to toggle Led. */
        "led3",                      /* Text name for the task. */
        configMINIMAL_STACK_SIZE,    /* Stack size in words. */
        (void *)(uintptr_t) 400,     /* (Optional) delay amount. */
        tskIDLE_PRIORITY+2,          /* Task priority. */
        NULL);                       /* Task's handle - here set to NULL. */

    /* Toggle Led Task */
    xTaskCreate(
        toggleLedTask4,              /* Function to toggle Led. */
        "led4",                      /* Text name for the task. */
        configMINIMAL_STACK_SIZE,    /* Stack size in words. */
        (void *)(uintptr_t) 500,     /* (Optional) delay amount. */
        tskIDLE_PRIORITY+2,          /* Task priority. */
        NULL);                       /* Task's handle - here set to NULL. */

    /* Toggle Led Task */
    xTaskCreate(
        toggleLedTask5,              /* Function to toggle Led. */
        "led5",                      /* Text name for the task. */
        configMINIMAL_STACK_SIZE,    /* Stack size in words. */
        (void *)(uintptr_t) 600,     /* (Optional) delay amount. */
        tskIDLE_PRIORITY+2,          /* Task priority. */
        NULL);                       /* Task's handle - here set to NULL. */

    /* Toggle Led Task */
    xTaskCreate(
        toggleLedTask6,              /* Function to toggle Led. */
        "led6",                      /* Text name for the task. */
        configMINIMAL_STACK_SIZE,    /* Stack size in words. */
        (void *)(uintptr_t) 700,     /* (Optional) delay amount. */
        tskIDLE_PRIORITY+2,          /* Task priority. */
        NULL);                       /* Task's handle - here set to NULL. */

    /* Toggle Led Task */
    xTaskCreate(
        toggleLedTask7,              /* Function to toggle Led. */
        "led7",                      /* Text name for the task. */
        configMINIMAL_STACK_SIZE,    /* Stack size in words. */
        (void *)(uintptr_t) 800,     /* (Optional) delay amount. */
        tskIDLE_PRIORITY+2,          /* Task priority. */
        NULL);                       /* Task's handle - here set to NULL. */

    /* Uart Task */
    xTaskCreate(
        uartTask,                     /* Function to toggle Led. */
        "log",                       /* Text name for the task. */
        configMINIMAL_STACK_SIZE,    /* Stack size in words. */
        "Hello World!!!",            /* (Optional) toggle LED pin 5. */
        tskIDLE_PRIORITY+1,          /* Task priority. */
        NULL);                       /* Task's handle - here set to NULL. */

    /* Display Task */
    BaseType_t xReturned = xTaskCreate(
        displayTimeTask,             /* Function to display time since active. */
        "disp",                      /* Text name for the task. */
        configMINIMAL_STACK_SIZE*2,  /* Stack size in words. */
        NULL,                        /* No parameter is passed. */
        tskIDLE_PRIORITY+3,          /* Task priority. */
        NULL);                       /* Task's handle - here set to NULL. */
    
    /* Test scenario to check if the Task wasn't created. */
    if (xReturned != pdPASS)
    {
        LED_SetOutputHigh(2);
        while(1);
    }

    vTaskStartScheduler();
}


void vApplicationMallocFailedHook( void )
{
    /* vApplicationMallocFailedHook() will only be called if
     * configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
     * function that will get called if a call to pvPortMalloc() fails.
     * pvPortMalloc() is called internally by the kernel whenever a task, queue,
     * timer or semaphore is created using the dynamic allocation (as opposed to
     * static allocation) option.  It is also called by various parts of the
     * demo application.  If heap_1.c, heap_2.c or heap_4.c is being used, then the
     * size of the	heap available to pvPortMalloc() is defined by
     * configTOTAL_HEAP_SIZE in FreeRTOSConfig.h, and the xPortGetFreeHeapSize()
     * API function can be used to query the size of free heap space that remains
     * (although it does not provide information on how the remaining heap might be
     * fragmented).  See http://www.freertos.org/a00111.html for more
     * information. */
    LATD = 0xff;
    printf( "\r\n\r\nMalloc failed\r\n" );
    portDISABLE_INTERRUPTS();

    for( ; ; )
    {
    }
}

void vApplicationStackOverflowHook(
    TaskHandle_t xTask,
    char *pcTaskName)
{
    printf("STACK OVERFLOW: %s\r\n", pcTaskName);

    while(1);
}
