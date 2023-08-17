


#pragma once

/********************----Declare All the function here------************************************/
void generateCodebook();
void getTokhuraDistanceWeight();
void LBG_Algorithm();
long double nearestNeighbour(long double centroid[KC][P],long double CIs_Values[P],int *index);
long double calculateTokhuraDistance(long double X[],long double Y[]);
long double calculateAverageDistortion(long double min_distortion[KC],long mappingCount[KC]);
void calculateAndUpdateCentroid(long double centroid[KC][P],long double mappingSum[KC][P],long mappingCount[KC]);
void writeCodeBook(long double centroid[KC][P],char *fileName);
void readCodeBook(long double centroid[KC][P],char *fileName);
/***********************----------------------------------**************************************/
void generateCodebook(){
	
	/*Initialize TDW vector*/
	getTokhuraDistanceWeight();
	LBG_Algorithm();
}


/*  getTokhuraDistanceWeight: fill the weights from the file into given array
 *  TDW[] ==> contains all the tokhura distance weight at the end of this function.
 */
void getTokhuraDistanceWeight(){
	FILE *fp = fopen(TOKHURA_DISTANCE_FILE_PATH,READ_MODE);
	if(fp==NULL){
		printf("\ngetTokhuraDistanceWeight(): Can't open %s file in %s mode\n",TOKHURA_DISTANCE_FILE_PATH,READ_MODE);
		return;
	}
	int index=0;
	while(!feof(fp)){
		fscanf(fp,"%Lf",&TDW[index]);
		index++;
	}
	fclose(fp);
}
/* calculateTokhuraDistance: Calculate Tokhura Distance between given two vector.
 * @param1: long double X[] : X vector contains Cepstral Coefficient.
 * @param2: long double X[] : Y vector contains Cepstral Coefficient.
 *
 * return : calculated Tokhura Distance.
 */
long double calculateTokhuraDistance(long double X[],long double Y[]){
	long double tokhura_distance = 0;
	long double temp = 0;
	
	for(int i=0;i<P;i++){
		temp = X[i] - Y[i];
		tokhura_distance += TDW[i]*(temp*temp);
	}
	
	return tokhura_distance;
}	


/* nearestNeighbour: given KC cluster find the minimum distortion for the given Cepstral Vecotr and assign 
 *					 the cluster Index for this Cepstral Vector that represent it belong to index cluster. 	
 * @param1: long double centroid[KC][P] : Contains Centroid for all the KC cluster 	
 * @param2: long double CIs_Values[P] : One of the Cepstral Coefficient Vector
 * @param3: int *index : finally we will assign index value which represent cluster
 *
 * return : minimum distortion value among all the KC clusters.
 */
long double nearestNeighbour(long double centroid[KC][P],long double CIs_Values[P],int *index){
	long double min_dist = MAX_VALUE;
	
	for(int i=0;i<code_book_size;i++){
		long double temp = calculateTokhuraDistance(centroid[i],CIs_Values);
		if(min_dist>=temp){
			*index = i;
			min_dist = temp;
		}
	}

	return min_dist;
}
/* calculateAndUpdateCentroid: given mappingSum and mappingCount for each cluster, calculate and update new centroid for each KC cluster.
 *	
 * @param1: long double centroid[KC][P] : Contains Centroid for all the KC cluster
 * @param2: long double mappingSum[KC][P]: Contains Sum of all the Vector which mapped to particular cluster.
 * @param3: long mappingCount[KC] : Contains Count of all the Vector which mapped to particular cluster
 */

void calculateAndUpdateCentroid(long double centroid[KC][P],long double mappingSum[KC][P],long mappingCount[KC]){
	for(int i=0;i<code_book_size;i++){
		for(int j=0;j<P;j++){
			//centroid[i][j]+=mappingSum[i][j];
			//centroid[i][j] = centroid[i][j]/(1+mappingCount[i]);
			centroid[i][j] = mappingSum[i][j]/(mappingCount[i]==0?1:mappingCount[i]);
		}
	}
}



/* calculateAverageDistortion: calculate average distortion from given total distortion for each cluster.
 * 
 * @param1: long double min_distortion[KC] --> contains distortion for each cluster.
 * @param2: long mappingCount[KC] : Contains Count of all the Vector which mapped to particular cluster
 */
long double calculateAverageDistortion(long double min_distortion[KC],long mappingCount[KC]){
	long double avg_dist = 0;
	long total_record = 0;
	for(int i=0;i<code_book_size;i++){
		//min_distortion[i] = min_distortion[i]/(mappingCount[i]==0?1:mappingCount[i]);
		total_record += mappingCount[i];
		avg_dist+= min_distortion[i]; 
		//printf("%d) %Lf\n",i+1,min_distortion[i]);
	}
	avg_dist/=total_record;
	//avg_dist/= M;
	//printf("Avg : %Lf\n\n",avg_dist);
	return avg_dist;
}

/* writeCodeBook: write centroid value for each cluster.
 * 
 * @param1:long double centroid[KC][P] : Contains Centroid for all the KC cluster 	 
 * @param2:  char *fileName : CodeBook Name.
 *
 */
void writeCodeBook(long double centroid[KC][P],char *fileName){
	FILE *fp = fopen(fileName,WRITE_MODE);
	if(fp==NULL){
		printf("\nInside writeCodeBook: can't open %s file in %s mode \n",fileName,WRITE_MODE);
		return;
	}

	for(int i=0;i<KC;i++){
		for(int j=0;j<P;j++){
			fprintf(fp,"%Lf%c",centroid[i][j],((j==P-1)?'\n':','));	
		}
	}
	fclose(fp);
}
/* readCodeBook: read codebook .
 * 
 * @param1:long double centroid[KC][P] : Contains Centroid for all the KC cluster 	 
 * @param2:  char *fileName : CodeBook Name.
 *
 */

void readCodeBook(long double centroid[KC][P],char *fileName){
	FILE *fp = fopen(fileName,READ_MODE);
	if(fp==NULL){
		printf("\nInside readCodeBook(): can't open %s file in %s mode \n",fileName,READ_MODE);
		return;
	}

	for(int i=0;i<KC;i++){
		for(int j=0;j<P;j++){
			fscanf(fp,"%Lf,",&centroid[i][j]);	
		}
	}
	fclose(fp);
}



/* LBG_Algorithm Implementation
 *
 *
 */

void LBG_Algorithm(){

	FILE *fp = fopen(UNIVERSE_FILE_PATH,READ_MODE); 

	if(fp==NULL){
		printf("\nInside LBG_Algorithm: Can't Open %s File in %s Mode \n",UNIVERSE_FILE_PATH,READ_MODE);
		return;
	}
	long double centroid[KC][P]={0};
	/*Initial Code Book Size..*/
	code_book_size = 1;
	long current_code_book_size=1;
	long record_count=0;
	long double avg_distortion = 0;
	long double prev_distortion=0;
		
	
	/*Initial Centroid from Universe data*/
	while(!feof(fp)){
		int j=0;
		long double temp=0;
		int eflag = 0;
		while(j<P){
			fscanf(fp,"%Lf,",&temp);
			if(feof(fp)){
				eflag = 1;
				break;
			}
			centroid[0][j]+=temp;
			j++;
		}
		if(eflag){
			break;
		}	
		record_count+=1;
	}
	printf("\n\n...Initializing Centroid from Universe...\n\n");

	for(int i=0;i<P;i++){
		centroid[0][i] = centroid[0][i]/record_count;
	}

	for(int i=0;i<P;i++){
		printf("%Lf ",centroid[0][i]);
	}
	printf("\n\n");
	FILE *dist = fopen(LBG_DISTORTION_PATH,WRITE_MODE);
	if(dist==NULL){
		printf("\nInside LBG_Algorithm: Can't Open %s File in %c Mode \n",LBG_DISTORTION_PATH,WRITE_MODE);
		return;
	}

	do{
		/*Double the Code book Size from given Current Code book size */
		int len = 2*current_code_book_size - 1; 
		for(int i=0;i<current_code_book_size;i++){
			for(int j=0;j<P;j++){
				centroid[len-i][j]=centroid[i][j]*(1-epsilon);	
				centroid[i][j] = centroid[i][j]*(1+epsilon);
			}
		}

		current_code_book_size+=current_code_book_size;
		code_book_size = current_code_book_size;
		printf("CodeBookSize: %d\n",code_book_size);
		
		/*printf("\n\n---------Centroid before-----------\n\n ");
		for(int x=0;x<code_book_size;x++){
			for(int y=0;y<P;y++){
				printf("%Lf ",centroid[x][y]);
			}
			printf("\n");
		}*/

		do{
			printf(".");
			prev_distortion = avg_distortion;
			long mappingCount[KC]={0};
			long double min_distortion[KC]={0};
			long double mappingSum[KC][P] = {0};
			long double CIs_Values[P]={0};
			/*Set File Pointer to begining*/
			fseek(fp,0,SEEK_SET);
			int index = -1;
			long double min_dist = 0;
		
			while(!feof(fp)){
				int j=0;
				while(j<P){
					fscanf(fp,"%Lf,",&CIs_Values[j]);
					j++;
				}

				index = -1;
				min_dist = nearestNeighbour(centroid,CIs_Values,&index);

				if(index>=0 && index<code_book_size){
					mappingCount[index] += 1;
					min_distortion[index] += min_dist;
					for(int x=0;x<P;x++){
						mappingSum[index][x]+= CIs_Values[x];
					}
				}
			}
			/*printf("\n\n");
			for(int x=0;x<code_book_size;x++){
				printf("cluster: %d total: %d distortion: %Lf\n",x+1,mappingCount[x],min_distortion[x]);
			}*/
			avg_distortion = calculateAverageDistortion(min_distortion,mappingCount);
			fprintf(dist,"%Lf,",avg_distortion);
			calculateAndUpdateCentroid(centroid,mappingSum,mappingCount);	
		}while(abs(avg_distortion-prev_distortion)>DELTA);
			
		printf("\nAvg_distortion: %Lf\n",avg_distortion);
		printf("Prev_distortion: %Lf\n",prev_distortion);
		printf("Difference: %Lf\n\n",abs(avg_distortion-prev_distortion));
	
	}while(current_code_book_size<KC);


	/*printf("\n\n---------LBG Centroid-----------\n\n");
	for(int x=0;x<code_book_size;x++){
		for(int y=0;y<P;y++){
			printf("%Lf ",centroid[x][y]);
		}
		printf("\n");
	}*/

	writeCodeBook(centroid,LBG_CODE_BOOK_PATH);

	/*...Close all open files...*/
	fclose(dist);
	fclose(fp);
}


