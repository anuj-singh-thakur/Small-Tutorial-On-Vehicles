
#pragma once


#define UNIVERSE_FILE_PATH "files/training/output/universe/universe.csv"
#define TOKHURA_DISTANCE_FILE_PATH "files/utility/tokhura_distance_weight.txt"

#define LBG_DISTORTION_PATH "files/training/output/codebook/distortion_LBG.csv"
#define LBG_CODE_BOOK_PATH "files/training/output/codebook/CodeBook_LBG.csv"


#define M 30000 /*UNIVERSE_SIZE*/ 
#define DELTA 0.00001  /*threshold between two consecutive distortion of codebook*/
#define epsilon 0.03   /*(1-epsilon) or (1+eplison) */
#define KC 32   /*No of regions/Clusters */

#define NORMALIZED_VALUE 5000
#define P 12 /*Ceptral Coefficient*/
#define Q 12
#define FRAME_SIZE 320
#define DATA_POINT_SKIP 80

#define MAX_VALUE 99999999

long double TDW[P]={0}; /*Tokhura Distance Weight Vector*/
long code_book_size=KC;


#define MAX_ARRAY_SIZE 30000
#define OUTPUT_SEPERATOR ','
#define FILE_NAME_SEPERATOR '_'
#define FILE_NAME_SIZE 150

#define READ_MODE "r+"
#define WRITE_MODE "w+"
#define APPEND_MODE "a+"

#define VEHICAL_IMAGE_MAPPING "files\\vehicals.txt"
#define IMAGE_PATH "files\\images\\"
#define UNIVESE "files/training/output/universe/universe.csv"
#define PATH "files/training/input/"
#define OBSERVATION_PATH "files/training/output/observation_sequence/"
#define MODEL_PATH "files/training/output/models/"
#define CONVERGE_MODEL_PATH "files/training/output/converge_models/"
#define AVG_MODEL_PATH "files/avg_model/"
#define TEST_PATH "files/testing/"
#define LIVE_TRAINING_PATH "files\\live_training\\"
#define LIVE_TRAINING_COMMAND "files\\testing\\live\\Recording_Module.exe"
#define SECONDS 3
#define ROLL_NO "224101008"
#define LANG "E"
#define FILE_FORMAT_TXT ".txt"
#define FILE_FORMAT_CSV ".csv"
#define FILE_FORMAT_WAV ".wav"


#define PI_VALUE 3.142857142857142857
#define HAMMING_WINDOW_FLAG 1
#define RAISED_SIN_WINDOW_FLAG 1
#define NORMALIZED_FLAG 1

#define MAX_OBJECT_COUNT 7
#define MAX_FILE_COUNT 20


#define TRAINING_MODE 0
#define LIVE_TESTING_MODE 1
#define LIVE_INPUT_FILE_PATH "files\\testing\\live\\input.txt"
#define LIVE_TRIM_INPUT_FILE_PATH "files\\testing\\live\\input_trim.txt"
#define LIVE_RECORD_COMMAND "files\\testing\\live\\Recording_Module.exe 3 files\\testing\\live\\input.wav files\\testing\\live\\input.txt"
#define SILENCE_ENERGY_THRESHOLD 150
#define MAX_LIVE_FRAME_320 50
#define LARGE_ARRAY_SIZE 48000

#define OBJECT_MAPPING_PATH "files/mapping.txt"

#define OBJECT_SIZE 50
char OBJECTS[OBJECT_SIZE][FILE_NAME_SIZE];
int OBJECT_COUNT = MAX_OBJECT_COUNT;
int FILE_COUNT = MAX_FILE_COUNT;