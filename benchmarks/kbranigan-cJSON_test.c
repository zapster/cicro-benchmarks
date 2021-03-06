#include "chayai.h"  // first include!

#include <stdlib.h>
#include <assert.h>

#include "kbranigan-cJSON/cJSON.h"

/* a bunch of json: */
char text1[] =
        "{\n"
        "\"name\": \"Jack (\\\"Bee\\\") Nimble\", \n"
        "\"format\": {\"type\":       \"rect\", \n"
        "\"width\":      1920, \n"
        "\"height\":     1080, \n"
        "\"interlace\":  false,\"frame rate\": 24\n"
        "}\n"
        "}";

char text2[] = "[\"Sunday\", \"Monday\", \"Tuesday\", \"Wednesday\", \"Thursday\", \"Friday\", \"Saturday\"]";

char text3[] =
        "[\n"
        "    [0, -1, 0],\n"
        "    [1, 0, 0],\n"
        "    [0, 0, 1]\n"
        "\t]\n";

char text4[] =
        "{\n"
        "\t\t\"Image\": {\n"
        "\t\t\t\"Width\":  800,\n"
        "\t\t\t\"Height\": 600,\n"
        "\t\t\t\"Title\":  \"View from 15th Floor\",\n"
        "\t\t\t\"Thumbnail\": {\n"
        "\t\t\t\t\"Url\":    \"http:/*www.example.com/image/481989943\",\n"
        "\t\t\t\t\"Height\": 125,\n"
        "\t\t\t\t\"Width\":  \"100\"\n"
        "\t\t\t},\n"
        "\t\t\t\"IDs\": [116, 943, 234, 38793]\n"
        "\t\t}\n"
        "\t}";

char text5[] =
        "[\n"
        "\t {\n"
        "\t \"precision\": \"zip\",\n"
        "\t \"Latitude\":  37.7668,\n"
        "\t \"Longitude\": -122.3959,\n"
        "\t \"Address\":   \"\",\n"
        "\t \"City\":      \"SAN FRANCISCO\",\n"
        "\t \"State\":     \"CA\",\n"
        "\t \"Zip\":       \"94107\",\n"
        "\t \"Country\":   \"US\"\n"
        "\t },\n"
        "\t {\n"
        "\t \"precision\": \"zip\",\n"
        "\t \"Latitude\":  37.371991,\n"
        "\t \"Longitude\": -122.026020,\n"
        "\t \"Address\":   \"\",\n"
        "\t \"City\":      \"SUNNYVALE\",\n"
        "\t \"State\":     \"CA\",\n"
        "\t \"Zip\":       \"94085\",\n"
        "\t \"Country\":   \"US\"\n"
        "\t }\n"
        "\t ]";


/* Parse text to JSON, then render back to text, and print! */
void doit(char *text)
{
    char *out = NULL;
    cJSON *json = NULL;

    json = cJSON_Parse(text);
    assert(json != NULL);

    out = cJSON_Print(json);
    assert(out != NULL);

    cJSON_Delete(json);
    free(out);
}

BENCHMARK(kbranigan, cJSON, 100, 100) {

    for(int i = 0; i < 20; i++) {
        doit(text1);
        doit(text2);
        doit(text3);
        doit(text4);
        doit(text5);
    }
}

int main(int argc, char** argv) {

    REGISTER_BENCHMARK(kbranigan, cJSON); // Ultralightweight JSON parser

    RUN_BENCHMARKS(argc, argv);

    return 0;
}