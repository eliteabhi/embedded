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
    ssd1306_oled_clear_screen();
    if (message->payloadlen)
    {
        printf("%s %s\n", message->topic, (char *)message->payload);
        cJSON *root = cJSON_Parse(message->payload);
        if (root)
        {
            const cJSON *name = cJSON_GetObjectItemCaseSensitive(root, "name");
            if (cJSON_IsString(name) && (name->valuestring != NULL)) {

                printf("Name: %s\n", name->valuestring);

            }

            const cJSON *number = cJSON_GetObjectItemCaseSensitive(root, "number");
            if (cJSON_IsNumber(number)) {

                printf("Number: %d\n", number->valueint);

            }

            const cJSON *string_msg = cJSON_GetObjectItemCaseSensitive(root, "string_msg");
            print_message_on_oled( string_msg );


            const cJSON *int_msg = cJSON_GetObjectItemCaseSensitive(root, "int_msg");
            print_message_on_oled( int_msg );
            

            const cJSON *task = cJSON_GetObjectItemCaseSensitive(root, "task");
            if ( cJSON_IsString(task) ) {

                cJSON* result = cJSON_CreateObject();
                
                char* task_str = task->valuestring;

                if ( strstr( task_str, "temperature" ) != NULL ) {

                    struct bmp280_i2c bmp = read_temp_pressure();

                    cJSON_AddNumberToObject( result, "temperature", bmp.temperature );

                }

                else if ( strstr( task_str, "pressure" ) != NULL ) {

                    struct bmp280_i2c bmp = read_temp_pressure();

                    cJSON_AddNumberToObject( result, "pressure", bmp.pressure );

                }

                else {

                    printf("INVALID TASK\n");

                }

                cJSON* item = NULL;
                cJSON_ArrayForEach(item, result) {

                    print_message_on_oled(item);

                }

                cJSON_Delete(result);

            }

            const cJSON *morse = cJSON_GetObjectItemCaseSensitive(root, "morse");
            if ( cJSON_IsString( morse ) ) {

                char* morse_str = $( morse->valuestring );

                print_message_on_oled( morse );

                printf( "Blinking Builtin LED...\n" );
                
                morse_blink_led( morse_str );

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

void print_message_on_oled( cJSON *message ) {

    char* label = message->string;

    strcat( label, ": " );

    ssd1306_oled_write_string( 0, label );

    if ( cJSON_IsString( message ) ) {

        float display_num = message->valuedouble;

        char display_num_as_str[2];

        if ( fmod( display_num, 1.0 ) != 0.0 ) {

            sprintf( display_num_as_str, "%f", display_num );

        }

        else {

            sprintf( display_num_as_str, "%d", (int) display_num );
        
        }


        printf("%s%s\n", label, display_num_as_str);

        ssd1306_oled_write_string( 0, display_num_as_str );

    }

    else if ( cJSON_IsString( message ) ) {

        char* display_str = &( message->valuestring );

        printf("%s%s\n", label, display_str );

        ssd1306_oled_write_string( 0, display_str );

    }

    ssd1306_oled_write_string( 0, "\n" );

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
