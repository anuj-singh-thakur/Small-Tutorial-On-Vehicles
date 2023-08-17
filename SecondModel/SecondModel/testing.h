
#pragma once

/*Utility Function to get test files name created dynamically*/
void getTestFileName(char fileName[],char *path,int objectIndex,int fileNo,char *fn){
	if(fn[0]=='c'){
		sprintf(fileName,"%s%s%s_%s_%d_%s%s",TEST_PATH,path,ROLL_NO,OBJECTS[objectIndex],fileNo,fn,FILE_FORMAT_CSV);
	}else if(fn[0]=='o'){
		sprintf(fileName,"%s%s%s_%s_%d_%s%s",TEST_PATH,path,ROLL_NO,OBJECTS[objectIndex],fileNo,fn,FILE_FORMAT_TXT);
	}else{
		sprintf(fileName,"%s%s%s_%s_%d%s",TEST_PATH,path,ROLL_NO,OBJECTS[objectIndex],fileNo,FILE_FORMAT_TXT);
	}
}



/*this function will generated observation sequence for test files*/
void generateObsForTest(){
	char *input = "input/";
	char *output = "output/";

	long double codebook[KC][P]={0};
	readCodeBook(codebook,LBG_CODE_BOOK_PATH);
	/*Initialize TDW vector*/
	getTokhuraDistanceWeight();
	printf("\n-------Observation Sequence------------\n");
	
	for(int i=0;i<OBJECT_COUNT;i++){
		printf("\n---------VehicleName: %s-------------\n",OBJECTS[i]);

		for(int j=FILE_COUNT+1;j<=15;j++){
			printf(".");
			char fileName[FILE_NAME_SIZE]={'\0'};
			getTestFileName(fileName,input,i,j,"t");
			//printf("%s\n",fileName);
			
			char tempFileName[FILE_NAME_SIZE]={'\0'};
			getTestFileName(tempFileName,output,i,j,"ceps");
			//printf("%s\n",tempFileName);
			
			FILE *tfp = fopen(tempFileName,WRITE_MODE);
			if(tfp==NULL){
				printf("\ngenerateObservationSequence(): Can't open %s file in %s Mode \n",tempFileName,WRITE_MODE);
				return;
			}
			
			readTextFileAndWriteCepstral(fileName,tfp);
			
			fclose(tfp);
			
			char outputFileName[FILE_NAME_SIZE]={'\0'};
			getTestFileName(outputFileName,output,i,j,"obs");
			//printf("%s\n",outputFileName);
			//printf("\n----------------------\n");
			
			writeObservationSequence(codebook,outputFileName,tempFileName);
		}
	}
	printf("\n");
}




/*
* testInputFiles():	this function will test all the pre-recorded files and show the indivisual digit probability and over-all accuracy
*/
void testInputFiles(){
	generateObsForTest();
	char *output = "output/";
	long double total_probability = 0.0;
	for(int l=0;l<OBJECT_COUNT;l++){
		printf("\n\n---------VehicleName: %s-------------\n",OBJECTS[l]);

		long double totalFileCount = 0;
		long double totalMatchCount = 0;
		for(int j=FILE_COUNT+1;j<=15;j++){
			
			long double max_p_star = 0.0;
			int index = -1;
			char O_FILE_NAME[FILE_NAME_SIZE]={'\0'};
			getTestFileName(O_FILE_NAME,output,l,j,"obs");
			readOSequence(O_FILE_NAME,O);
			printf("\n\n-----------modelProbablity: -----------\n",l);
		
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
				
				if(max_p_star<p_star){
					max_p_star = p_star;
					index = i;
				}
				printf("\n %.8e",p_star);
			}
			printf("\nVehicle: [%s] Probability: [%.8e] -->  %s",OBJECTS[index],max_p_star,O_FILE_NAME);
			totalFileCount+=1;
			if(l==index){
				totalMatchCount+=1;
			}
		}
		long double prob = totalMatchCount/totalFileCount;
		total_probability+= prob;
		printf("\n\nAccuracy: %.4Lf\n",prob*100);
	}
	
	printf("\n\n!!-------Final Accuracy: [ %.4Lf ]  ----------------!!\n",(total_probability/OBJECT_COUNT)*100);
	printf("\n");
}

