
#pragma once

/********************----Declare All the function here------************************************/
void generateUniverse();
void generateObservationSequence();
void getObservationFileName(char fileName[],int digitNo,int fileNo,char *name);
void readTextFileAndWriteCepstral(char *fileName,FILE *ufp);
void writeObservationSequence(long double codebook[KC][P],char *outputFileName,char *inputFileName);
void getFileName(char fileName[],int digitNo,int fileNo);
void normalizeTheDataPoints(long double arr[],int len,long double maxValue);
void applyRaisedSinWindow(long double C[]);
void generateRIAICI(long double arr[],int len,FILE *ufp);
void calculateRIAICI(long double arr[],int start,FILE *fp);


/***********************----------------------------------**************************************/

/* 
 * ex: 224101008_bus_12.txt
 */
void getFileName(char fileName[],int objectIndex,int fileNo){
	
	sprintf(fileName,"%s%s_%s_%d%s",PATH,ROLL_NO,OBJECTS[objectIndex],fileNo,FILE_FORMAT_TXT);
}

void generateUniverse(){
	printf("\n\n-------Universe Generation Started-------\n\n");

	FILE *ufp = fopen(UNIVESE,WRITE_MODE);
	if(ufp==NULL){
		printf("\ngenerateUniverse(): Can't open %s file in %s Mode \n",UNIVESE,WRITE_MODE);
		return;
	}
	for(int i=0;i<OBJECT_COUNT;i++){

		printf("\nVehicleName: %s \n",OBJECTS[i]);
		for(int j=1;j<=FILE_COUNT;j++){
			printf(".");
			long double inputArray[MAX_ARRAY_SIZE]={0};
			long double maxValue = 0;
			int fileLength = 0;
			
			char fileName[FILE_NAME_SIZE]={'\0'};
			getFileName(fileName,i,j);
			readTextFileAndWriteCepstral(fileName,ufp);
			//printf("%s\n",fileName);
		}
	}

	fclose(ufp);
	printf("\n\n-------Universe Generated Successfully-------\n");
}

/* normalizeTheDataPoints : Based on the maxValue value it will normalized all the data points given in the array.
 * 
 * @param1: double arr[] --> set of data points
 * @param2: int len --> size of the array
 * @param3: long maxValue ---> maximum absolute value from the given data points  
 * 
 */
void normalizeTheDataPoints(long double arr[],int len,long double maxValue){
	for(int i=0;i<len;i++){
		arr[i] = (arr[i]/maxValue)*NORMALIZED_VALUE;	
	}
}
/* applyRaisedSinWindow: applying liftering to the cepstral coefficients
 * @param1: long double C[] --> Ci's ( c1 to c12)
 *
 */

void applyRaisedSinWindow(long double C[]){
	double W[Q+1];

	for(int m=1;m<=Q;m++){
		W[m] = (1 + (Q/2)*(sin((PI_VALUE*m)/Q)));
		C[m] = C[m] * W[m];
	}	
}


void generateRIAICI(long double arr[],int len,FILE *ufp){
	int i=0;
	while(i<=len-FRAME_SIZE){
		calculateRIAICI(arr,i,ufp);	
		i+= DATA_POINT_SKIP;
	}
}

/* calculateRIAICI: Calculate Ai's and Ri's using Levinsion Durbin's Algorithm
 *					Calculate Ci's using Co-variance method.
 * 
 * @param1: long double arr[] --> contains datapoints
 * @param2: int start[] --> starting pointing of a frame
 * @param3: FILE *fp --> file pointer
 *
 */
void calculateRIAICI(long double arr[],int start,FILE *fp){
	
	long double R[P+1]={0};
	/*calculate Ri's*/
	for(int k=0;k<=P;k++){
		long double sum=0; 
		for(int j=0;j<=(FRAME_SIZE-1-k);j++){
			sum += (arr[start+j]*arr[start+j+k]);
		}
		R[k] = sum;
	}
	/*
	for(int k=0;k<=P;k++){
		printf("R[%d]=%Lf\n",k,R[k]);
	}*/

	long double E[P+1] = {0};
	E[0] = R[0];

	long double K[P+1] = {0};
	K[1] = R[1]/E[0]; 

	long double alpha[P+1][P+1]={0};
	/*calculate Ei's*/
	for(int i=1;i<=P;i++){
		if(i!=1){
			long double sum = 0;
			for(int j=1;j<=i-1;j++){
				sum += (alpha[i-1][j] * R[i-j]);
			}
			K[i] = (R[i] - sum)/E[i-1];				
		}
		alpha[i][i] = K[i];
		for(int j=1;j<=i-1;j++){
			alpha[i][j] = alpha[i-1][j] - K[i]*alpha[i-1][i-j];
		}
		E[i] = (1- K[i]*K[i])*E[i-1]; 
	}
	/*
	printf("\n\n");
	for(int j=1;j<=P;j++){
		printf("alpha[%d][%d] = %lf \n",P,j,alpha[P][j]);
	}*/

	long double C[P+1]={0};
	/* calculate Ci's */
	for(int m=1;m<=P;m++){
		long double temp = 0;

		for(int k=1;k<=(m-1);k++){
			temp += (((long double)k/m)* C[k] * alpha[P][m-k]);
		}

		C[m] = alpha[P][m] + temp;
	}
	/* // show the values of Ci's 
	printf("\n\n");
	for(int i=1;i<=P;i++){
		printf("C[%d] = %lf\n",i,C[i]);
	}
	*/

	if(RAISED_SIN_WINDOW_FLAG){
		applyRaisedSinWindow(C);
	}
	
	//printf("\n\n");
	for(int i=1;i<=P;i++){
		//printf("C[%d] = %Lf\n",i,C[i]);
		fprintf(fp,"%Lf%c",C[i],i==P?'\n':OUTPUT_SEPERATOR);
	}
}
/*
* ex: 224101008_bus_12_obs.txt
*/
void getObservationFileName(char fileName[],int objectIndex,int fileNo,char *name){
	sprintf(fileName,"%s%s_%s_%d_%s%s",OBSERVATION_PATH,ROLL_NO,OBJECTS[objectIndex],fileNo,name,(name[0]=='c'?FILE_FORMAT_CSV:FILE_FORMAT_TXT));
}


void readTextFileAndWriteCepstral(char *fileName,FILE *ufp){
	FILE *fp = fopen(fileName,READ_MODE);
	if(fp==NULL){
		printf("\nreadTextFileAndWriteCepstral(): Can't open %s file in %s Mode \n",fileName,READ_MODE);
		return;
	}
	long double inputArray[MAX_ARRAY_SIZE]={0};
	long double maxValue = 0;	
	int fileLength=0;
			
	long double temp=0;
	while(fileLength<MAX_ARRAY_SIZE){
		fscanf(fp,"%Lf",&temp);
		if(feof(fp)){
			break;
		}
		inputArray[fileLength++] = temp;
		if(abs(temp)>maxValue){
			maxValue = abs(temp);
		}
	}
	fclose(fp);
	if(NORMALIZED_FLAG && maxValue > NORMALIZED_VALUE){
			//printf("\nNoramlization..\n");
		normalizeTheDataPoints(inputArray,fileLength,maxValue);
	}

	generateRIAICI(inputArray,fileLength,ufp);	
}

void writeObservationSequence(long double codebook[KC][P],char *outputFileName,char *inputFileName){
	FILE *tfp = fopen(inputFileName,READ_MODE);
	if(tfp==NULL){
		printf("\nwriteObservationSequence(): Can't open %s file in %s Mode \n",inputFileName,READ_MODE);
		return;
	}

	FILE *ofp = fopen(outputFileName,WRITE_MODE);
	if(ofp==NULL){
		printf("\nwriteObservationSequence(): Can't open %s file in %s Mode \n",outputFileName,WRITE_MODE);
		return;
	}
	while(!feof(tfp)){
		long double CIs_Values[P]={0};
		int j=0;
		long double temp=0;
		int eflag = 0;
		while(j<P){
			fscanf(tfp,"%Lf,",&temp);
			if(feof(tfp)){
				eflag = 1;
				break;
			}
			CIs_Values[j]=temp;
			j++;
		}
		if(eflag){
			break;
		}

		/*using nearest neighbour method we will find observation for given cepstral coefficient */
		int index=-1;
		nearestNeighbour(codebook,CIs_Values,&index);
		fprintf(ofp,"%d\n",index+1); //nearest neighbour will return index between 0 and codebookSize-1 so we will have to write index+1

	}

	fclose(ofp);
	fclose(tfp);
}

void generateObservationSequence(){

	long double codebook[KC][P]={0};
	readCodeBook(codebook,LBG_CODE_BOOK_PATH);
	/*Initialize TDW vector*/
	getTokhuraDistanceWeight();

	/*printf("\n----------codebook--------------------\n");
	for(int i=0;i<KC;i++){
		for(int j=0;j<P;j++){
			printf("%Lf%c",codebook[i][j],((j==P-1)?'\n':','));	
		}
	}*/
	printf("\n-------Observation Sequence Generation Started --------------\n");
	for(int i=0;i<OBJECT_COUNT;i++){
		for(int j=1;j<=FILE_COUNT;j++){
			
			char fileName[FILE_NAME_SIZE]={'\0'};
			getFileName(fileName,i,j);
			//printf("%s\n",fileName);
			
			char tempFileName[FILE_NAME_SIZE]={'\0'};
			getObservationFileName(tempFileName,i,j,"ceps");
			//printf("%s\n",tempFileName);
			
			FILE *tfp = fopen(tempFileName,WRITE_MODE);
			if(tfp==NULL){
				printf("\ngenerateObservationSequence(): Can't open %s file in %s Mode \n",tempFileName,WRITE_MODE);
				return;
			}
			
			readTextFileAndWriteCepstral(fileName,tfp);
			
			fclose(tfp);

			char outputFileName[FILE_NAME_SIZE]={'\0'};
			getObservationFileName(outputFileName,i,j,"obs");
			//printf("%s\n",outputFileName);
			//printf("\n----------------------\n");
			
			writeObservationSequence(codebook,outputFileName,tempFileName);

			printf(".");
		}
	}
	printf("\n-------Observation Sequence Generation End --------------\n");
}




