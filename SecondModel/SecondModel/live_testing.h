
#pragma once

/*
* recordVoice(): this function is used to run a exe files which record a sound based on the parameter given in command
*/
void recordVoice(){
	system(LIVE_RECORD_COMMAND);
}



/*
*removeSilence(): utility function which is used for removing silence and extracting only actual voice part from the input file generated during live testing
*/
int removeSilence(){
	FILE *fp = fopen(LIVE_INPUT_FILE_PATH,READ_MODE);

	if(fp==NULL){
		printf("\nremoveSilence():Can't open %s file in %s mode\n",LIVE_INPUT_FILE_PATH,READ_MODE);
		return -1;
	}
	long double inputArray[LARGE_ARRAY_SIZE]={0};
	int index = 0;
	int currentIndex = 0;
	long double threshold = SILENCE_ENERGY_THRESHOLD;
	long double temp=0;
	long double sum=0.0;
	int count=0;
	int frame_count=0;
	long double max = 1.0;
	fseek(fp,50,SEEK_SET);

	while(fscanf(fp,"%Lf",&temp)!=EOF){
		if(abs(temp)>max){
			max = abs(temp);
		}	
	}
	printf("Max Value: %Lf",max);
	if(max<=100.0){
		printf("\n\n!!------- Recording is not correct.---------------!!\n\n");
		return -1;
	}
	
	fseek(fp,50,SEEK_SET);

	while(!feof(fp)){	
		count = 1;
		sum=0.0;
		
		while(count<=FRAME_SIZE){
			fscanf(fp,"%Lf",&temp);
			if(feof(fp))
				break;
			
			temp = (temp/max)*NORMALIZED_VALUE;
			inputArray[currentIndex++] = temp;
			sum += (temp*temp);
			count++;

			if(currentIndex>=LARGE_ARRAY_SIZE){
				printf("\nInput file is large..\n");
				return -1;
			}
			
		}
		if(feof(fp))
			break;
		if(count>=FRAME_SIZE){
			long double avg = sum/FRAME_SIZE;
			if(avg>=threshold){
				frame_count+=1;
				index = currentIndex;
			}else{
				currentIndex = index;
			}
		}
		if(frame_count>=MAX_LIVE_FRAME_320)
			break;
	}
	fclose(fp);
	fp = fopen(LIVE_INPUT_FILE_PATH,WRITE_MODE);

	if(fp==NULL){
		printf("\nremoveSilence():Can't open %s file in %s mode\n",LIVE_INPUT_FILE_PATH,WRITE_MODE);
		return -1;
	}
	for(int i=0;i<index;i++){
		fprintf(fp,"%Lf\n",inputArray[i]);
	}

	fclose(fp);
	return 0;
}


/*
*removeSilence(): utility function which is used for removing silence and extracting only actual voice part from the input file generated during live testing
*/
int removeSilenceUsingMax(char *live_input_file_path,char *live_trim_input_file_path){
	FILE *fp = fopen(live_input_file_path,READ_MODE);

	if(fp==NULL){
		printf("\nremoveSilenceUsingMax():Can't open %s file in %s mode\n",LIVE_INPUT_FILE_PATH,READ_MODE);
		return -1;
	}
	long double inputArray[LARGE_ARRAY_SIZE]={0};
	long double threshold = SILENCE_ENERGY_THRESHOLD;
	long double temp=0;
	long double sum=0.0;
	long double max = 1.0;
	fseek(fp,50,SEEK_SET);
	
	long double max_energy = 0.0;
	long double cur_energy = 0.0;
	int frame_index = 0;
	int frame_count = 0;
	int data_point = 0;
	
	while(fscanf(fp,"%Lf",&temp)!=EOF){
		if(abs(temp)>max){
			max = abs(temp);
		}

		data_point+=1;
		cur_energy+= (temp*temp);
		
		if(data_point>= (FRAME_SIZE)){
			if(max_energy<=cur_energy){
				max_energy = cur_energy;
				frame_index = frame_count;
			}
			//printf("%d) Max Energy: %Lf\n",frame_count,cur_energy);
			cur_energy=0;
			data_point=0;
			
			frame_count+=1;
		}
	}
	printf("Max Value: %Lf\n",max);
	
	if(max<=100.0){
		printf("\n\n!!------- Recording is not correct.---------------!!\n\n");
		return -1;
	}
	printf("Max Energy: %Lf\n",max_energy);
	printf("Max Frame Count: %d\n",frame_index);
	int t1 = frame_index - 11;
	int t2 = frame_index + 15;
	int left = t1>0?t1:0;
	int right = t2<frame_count?t2:frame_count;
	
	fseek(fp,50,SEEK_SET);
	frame_count = 0;
	data_point = 0;
	while(fscanf(fp,"%Lf",&temp)!=EOF){
		if(left<=frame_count){
			break;
		}
		data_point+=1;
		if(data_point>=FRAME_SIZE){
			frame_count+=1;
			data_point=0;
		}
	}
	int index=0;
	int total_frame = right-left+1;
	printf("\nTotal Frame : [%d]  start: [%d]  end: [%d]\n\n",total_frame,left,right);
	frame_count = 0;
	while(fscanf(fp,"%Lf",&temp)!=EOF){
		inputArray[index++] = temp;
		
		if(index%FRAME_SIZE==0){
			frame_count+=1;
		}
		if(frame_count>=total_frame){
			break;
		}
	}

	fclose(fp);
	
	fp = fopen(live_trim_input_file_path,WRITE_MODE);
	if(fp==NULL){
		printf("\nremoveSilence():Can't open %s file in %s mode\n",LIVE_INPUT_FILE_PATH,WRITE_MODE);
		return -1;
	}
	for(int i=0;i<index;i++){
		fprintf(fp,"%Lf\n",inputArray[i]);
	}

	fclose(fp);
	
	return 0;
}




/* 
* doLiveTesting(): Controller function for doing live testing 
* first record the voice
* then call remove silence utility function and finally check minimum probability from all the models(0-9)
*
*/
int doLiveTesting(long double codebook[KC][P]){
	printf("\n--------------Record Voice--------------\n");
	recordVoice();
	//int status = 1;//removeSilence();
	int status = removeSilenceUsingMax(LIVE_INPUT_FILE_PATH,LIVE_TRIM_INPUT_FILE_PATH);
	if(status==-1){
		printf("\ndoLiveTesting(): can't remove silence from input file\n");
		return -1;
	}
	
	char* tempFileName = "files/testing/live/input_ceps.csv";
	char* outputFileName = "files/testing/live/input_obs.txt";
	FILE *tfp = fopen(tempFileName,WRITE_MODE);
	if(tfp==NULL){
		printf("\ngenerateObservationSequence(): Can't open %s file in %s Mode \n",tempFileName,WRITE_MODE);
		return -1;
	}
	readTextFileAndWriteCepstral(LIVE_TRIM_INPUT_FILE_PATH,tfp);
	fclose(tfp);
	writeObservationSequence(codebook,outputFileName,tempFileName);

	readOSequence(outputFileName,O);
		
	long double max_p_star = 0.0;
	int index = -1;
	for(int i=0;i<OBJECT_COUNT;i++){
		char A_FILE_NAME[FILE_NAME_SIZE] ={'\0'}; 
		getAvgModelFileName(A_FILE_NAME,i,modelFileName[0]);
		char B_FILE_NAME[FILE_NAME_SIZE] ={'\0'}; 
		getAvgModelFileName(B_FILE_NAME,i,modelFileName[1]);
			
		char PI_FILE_NAME[FILE_NAME_SIZE] ={'\0'};
		getAvgModelFileName(PI_FILE_NAME,i,modelFileName[2]);
				
		readAMatrix(A_FILE_NAME,A);
		readBMatrix(B_FILE_NAME,B);
		readPIVector(PI_FILE_NAME,PI);
				
		p_star = 0.0;
		calculateAlpha();
		calculateBeta();
		calculateDelta();
		//showMatrix();
		if(max_p_star<p_star){
			max_p_star = p_star;
			index = i;
		}
		printf("\nModel for Vehicle [%s] \t %.8e",OBJECTS[i],p_star);
	}
	if(index>-1)
		printf("\n\nVehicle: [%s] Probability: [%.8e] ",OBJECTS[index],max_p_star);
	else
		printf("\nInvalid Name...\n");

	return index;
}
