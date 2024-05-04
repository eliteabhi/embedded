#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <mosquitto.h>
#include <cjson/cJSON.h>

#include <ssd1306.h>
#include <bmp280_i2c.h>

#include <morse.h>

void message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    ssd1306_oled_clear_screen(); // Clear OLED screen

    if (message->payloadlen)
    {
        printf("%s %s\n", message->topic, (char *)message->payload);
        cJSON *root = cJSON_Parse(message->payload);
        if (root)
        {
            // 'name' case
            const cJSON *name = cJSON_GetObjectItemCaseSensitive(root, "name");
            if (cJSON_IsString(name) && (name->valuestring != NULL)) {

                printf("Name: %s\n", name->valuestring);

            }

            else {

                printf("Name value is not a string: %s\n", name->valuestring); // Invalid type

            }

            // ----------------------------------------------------------------

            // 'number' case
            const cJSON *number = cJSON_GetObjectItemCaseSensitive(root, "number");
            if (cJSON_IsNumber(number)) {

                printf("Number: %d\n", number->valueint);

            }

            else {

                printf("Number value is not a number: %s\n", number->valueint); // Invalid type

            }

            // ----------------------------------------------------------------

            // 'string_msg' case
            const cJSON *string_msg = cJSON_GetObjectItemCaseSensitive(root, "string_msg");
            if (cJSON_IsString(string_msg)) {

                print_message_on_oled( string_msg ); // Print to OLED screen

            }

            else {

                printf("string_msg value is not a string: %s\n", string_msg->valuestring); // Invalid type

            }

            // ----------------------------------------------------------------

            // 'int_msg' case
            const cJSON *int_msg = cJSON_GetObjectItemCaseSensitive(root, "int_msg");
            if (cJSON_IsNumber(int_msg)) {

                print_message_on_oled( int_msg ); // Print to OLED screen

            }
            
            else {

                printf("int_msg value is not a number: %s\n", int_msg->valueint); // Invalid type

            }

            // ----------------------------------------------------------------

            // 'task' case
            const cJSON *task = cJSON_GetObjectItemCaseSensitive(root, "task");
            if ( cJSON_IsString(task) ) { // If value is a string

                cJSON* result = cJSON_CreateObject(); // Create empty json object
                
                char* task_str = task->valuestring; // Get task as string

                if ( strstr( task_str, "temperature" ) != NULL ) { // If task contains 'temperature'

                    struct bmp280_i2c bmp = read_temp_pressure(); // Get values from BMP280

                    cJSON_AddNumberToObject( result, "temperature", bmp.temperature ); // Add 'temperature' item to result object

                }

                else if ( strstr( task_str, "pressure" ) != NULL ) { // If task contains 'pressure'

                    struct bmp280_i2c bmp = read_temp_pressure(); // Get values from BMP280

                    cJSON_AddNumberToObject( result, "pressure", bmp.pressure ); // Add 'pressure' item to result object

                }

                else {

                    printf("INVALID TASK\n"); // Invalid task

                }

                cJSON* item = NULL;
                cJSON_ArrayForEach(item, result) {

                    print_message_on_oled(item);

                }

                cJSON_Delete(result);

            }

            else {

                printf( "Task value is not a string: %s\n", task->valuestring );  // Invalid type

            }

            // ----------------------------------------------------------------

            // 'morse' case
            const cJSON *morse = cJSON_GetObjectItemCaseSensitive(root, "morse");
            if ( cJSON_IsString( morse ) ) { // If values is a string

                char* morse_str = $( morse->valuestring ); // Get morse code as string

                print_message_on_oled( morse ); // Print to OLED screen

                printf( "Blinking Builtin LED...\n" ); // Log to console that LED will blink

                morse_blink_led( morse_str ); // Blink builtin LED

            }

            else {

                printf( "Morse value is not a string: %s\n", morse->valuestring ); // Invalid type

            }

            cJSON_Delete(root);
        
        }
        
        else
        {
            printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        }

    }

    else
    {
        printf("%s (null)\n", message->topic);
    }
    
}

void print_message_on_oled( cJSON *message ) { // Prints message onto OLED screen

    char* label = message->string; // Get key 'label' from json object

    strcat( label, ": " ); // Append ': '

    ssd1306_oled_write_string( 0, label ); // Print 'label' onto OLED screen

    if ( cJSON_IsNumber( message ) ) { // If value is a double

        double display_num = message->valuedouble; // Get value from json object

        char display_num_as_str[2]; // NULL string object of length 1 + '\0'

        if ( fmod( display_num, 1.0 ) != 0.0 ) { // If not integer

            sprintf( display_num_as_str, "%f", display_num ); // Cast as float

        }

        else {

            sprintf( display_num_as_str, "%d", (int) display_num ); // Cast as int
        
        }


        printf("%s%s\n", label, display_num_as_str); // Log to terminal

        ssd1306_oled_write_string( 0, display_num_as_str ); // Print value to OLED screen

    }

    else if ( cJSON_IsString( message ) ) { // If value is a string

        char* display_str = &( message->valuestring ); // Get value from json object

        printf("%s%s\n", label, display_str ); // Log to terminal

        ssd1306_oled_write_string( 0, display_str ); // Print value to OLED screen

    }

    ssd1306_oled_write_string( 0, "\n" ); // Print NewLine to OLED screen

}

int main(int argc, char *argv[])
{
    struct mosquitto *mosq;

    // Initialize the Mosquitto library
    mosquitto_lib_init();

    // Create a new Mosquitto runtime instance with a random client ID
    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq)
    {
        fprintf(stderr, "Could not create Mosquitto instance\n");
        exit(-1);
    }

    // Assign the message callback
    mosquitto_message_callback_set(mosq, message_callback);

    // Connect to an MQTT broker
    if (mosquitto_connect(mosq, "localhost", 1883, 60) != MOSQ_ERR_SUCCESS)
    {
        fprintf(stderr, "Could not connect to broker\n");
        exit(-1);
    }

    // Subscribe to the topic
    mosquitto_subscribe(mosq, NULL, "test/topic", 0);

    // Start the loop
    mosquitto_loop_start(mosq);

    printf("Press Enter to quit...\n");
    getchar();

    // Cleanup
    mosquitto_loop_stop(mosq, true);
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}
