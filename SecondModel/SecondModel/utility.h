#pragma once

/*Utility Function to Copy files from One directory to Another*/
void copyInitialModel(){
	char* initial_model_path = "files\\initial_model\\";
	char* avg_model_path =  "files\\avg_model\\";
	char make_dir_cmnd[FILE_NAME_SIZE] = {'\0'};
	
	char copy_cmnd[FILE_NAME_SIZE] = {'\0'};

	for(int i=0;i<OBJECT_COUNT;i++){

		for(int j=0;j<3;j++){
			sprintf(copy_cmnd,"COPY %s%s %s%s_%s_%s",initial_model_path,modelFileName[j],avg_model_path,ROLL_NO,OBJECTS[i],modelFileName[j]);
			system(copy_cmnd);
			//printf("%s\n",copy_cmnd);
		}
	}
}
void copyObservation(){
	char *training_obs_path = "files\\training\\output\\observation_sequence\\";
	char *training_model_path  = "files\\training\\output\\models\\";
	char copy_obs_cmnd[FILE_NAME_SIZE] = {'\0'};
	
	sprintf(copy_obs_cmnd,"COPY %s%s %s",training_obs_path,"*.txt",training_model_path);
	printf("%s\n",copy_obs_cmnd);
	system(copy_obs_cmnd);
		
}


/*Utility Function to Copy files from One directory to Another*/
void copyModelFiles(){
	char* avg_model_path =  "files\\avg_model\\";
	char *training_model_path  = "files\\training\\output\\models\\";
	
	char copy_init_model_cmnd[FILE_NAME_SIZE] = {'\0'};


	for(int i=0;i<OBJECT_COUNT;i++){

		for(int j=1;j<=FILE_COUNT;j++){
		
			for(int k=0;k<3;k++){
				sprintf(copy_init_model_cmnd,"COPY %s%s_%s_%s %s%s_%s_%d_%s",avg_model_path,ROLL_NO,OBJECTS[i],modelFileName[k],training_model_path,ROLL_NO,OBJECTS[i],j,modelFileName[k]);
				//printf("%s\n",copy_init_model_cmnd);
				system(copy_init_model_cmnd);
			}
		}
	}
}

void getLiveTrainingFileName(char fileName[],char* objectName,int fileNo,char *ext){
	sprintf(fileName,"%s%s_%s_%d%s",LIVE_TRAINING_PATH,ROLL_NO,objectName,fileNo,ext);
}
void getLiveTrainingCommand(char fileName[],char* wavFile,char* textFile){
	sprintf(fileName,"%s %d %s %s",LIVE_TRAINING_COMMAND,SECONDS,wavFile,textFile);
}

void getLiveTrainingFilePath(char fileName[],char* objectName,int fileNo,char *ext){
	sprintf(fileName,"%s%s_%s_%d%s",PATH,ROLL_NO,objectName,fileNo,ext);
}


void initObjects(){
	FILE *fp = fopen(OBJECT_MAPPING_PATH,READ_MODE);

	if(fp==NULL){
		printf("\ninitObjects(): can't open mapping file\n");
		return;
	}

	int objCount=0;
	char objName[FILE_NAME_SIZE] = {'\0'};
	FILE *logFile = fopen("log_obj.txt","w");

	while(fscanf(fp,"%s",objName)!=-1){
		strcpy(OBJECTS[objCount],objName);
		fprintf(logFile,"%s\n",OBJECTS[objCount]);
		objCount+=1;
	}
	OBJECT_COUNT = objCount;
	fclose(logFile);
	fclose(fp);
}

void startTraining(){
	initObjects();
	generateUniverse();
	generateCodebook();
	generateObservationSequence();
	
	copyInitialModel();
	copyObservation();
	int i=0;
	do{
		copyModelFiles();
		generateModels();
		generateAverageModel();
		i++;
	}while(i<2);
}