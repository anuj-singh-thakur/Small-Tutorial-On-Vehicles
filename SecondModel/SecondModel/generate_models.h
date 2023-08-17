
#pragma once

#define N 5
#define M 32
#define MAX_T 360
#define THREASHOLD 1.e-50
#define MAX_ITERATION 40

/*define all the necessary matrix and vector and initialized with zero*/
long double A[N+1][N+1]={0};
long double B[N+1][M+1]={0};
int O[MAX_T+1]={0};
long double PI[N+1]={0};

long double alpha[MAX_T+1][N+1]={0};
long double beta[MAX_T+1][N+1]={0};
long double gamma[MAX_T+1][N+1] = {0};
int gamma_state_sequence[MAX_T+1]={0};

long double jae[MAX_T+1][N+1][N+1]={0};

long double delta[MAX_T+1][N+1] = {0};
int SI[MAX_T+1][N+1]={0};
int q_star[MAX_T+1] = {0};
long double p_star =0.0;

int T= MAX_T;

char* modelFileName[] = {"A.txt","B.txt","PI.txt","obs.txt"};


/********************----Declare All the function here------************************************/
void generateModels();
void readAMatrix(char *fileName,long double A[N+1][N+1]);
void readBMatrix(char *fileName,long double B[N+1][M+1]);
void readOSequence(char *fileName,int O[]);
void readPIVector(char *fileName,long double PI[N+1]);
void getModelFileName(char fileName[],int digitNo,int fileNo,char *fn);
void calculateAlpha();
void calculateBeta();
void calculateGamma();
void calculateDelta();
void calculateJae();
void calculatePIComplement();
void calculateAComplementMatrix();
void calculateBComplementMatrix();
void adjustValueOfMatrix();
void generateAverageModel();
void writeAComplementMatrix(char *fileName,long double A[N+1][N+1]);
void writeBComplementMatrix(char *fileName,long double B[N+1][M+1]);
void writePIComplement(char *fileName,long double PI[N+1]);
/***********************----------------------------------**************************************/


void getModelFileName(char fileName[],int objectIndex,int fileNo,char *fn){

	sprintf(fileName,"%s%s_%s_%d_%s",MODEL_PATH,ROLL_NO,OBJECTS[objectIndex],fileNo,fn);
}

void getConvergeModelFileName(char fileName[],int objectIndex,int fileNo,char *fn){
	sprintf(fileName,"%s%s_%s_%d_%s",CONVERGE_MODEL_PATH,ROLL_NO,OBJECTS[objectIndex],fileNo,fn);
}

void getAvgModelFileName(char fileName[],int objectIndex,char *fn){
	sprintf(fileName,"%s%s_%s_%s",AVG_MODEL_PATH,ROLL_NO,OBJECTS[objectIndex],fn);
}

void AddTwoMatrix(long double tempA[N+1][N+1],long double A[N+1][N+1],long double tempB[N+1][M+1],long double B[N+1][M+1]){
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			tempA[i][j]+=A[i][j];
		}
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			tempB[i][j]+=B[i][j];
		}
	}
}
void getAvgOfMatrix(long double tempA[N+1][N+1],long double tempB[N+1][M+1],int len){
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			tempA[i][j]/=len;
		}
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			tempB[i][j]/=len;
		}
	}
			
}


void generateAverageModel(){
	printf("\n------Average Model-----------\n");

	for(int i=0;i<OBJECT_COUNT;i++){
		printf("\n---------VehicleName: %s-------------\n",OBJECTS[i]);

		char tA[FILE_NAME_SIZE] ={'\0'}; 
		getAvgModelFileName(tA,i,modelFileName[0]);
		char tB[FILE_NAME_SIZE] ={'\0'}; 
		getAvgModelFileName(tB,i,modelFileName[1]);
			
		char tPI[FILE_NAME_SIZE] ={'\0'};
		getAvgModelFileName(tPI,i,modelFileName[2]);
		
		long double tempA[N+1][N+1]={0.0};
		long double tempB[N+1][M+1]={0.0};
		long double tempPI[N+1] = {0.0,1.0,0.0,0.0,0.0,0.0};
		
		for(int j=1;j<=FILE_COUNT;j++){
			char A_FILE_NAME[FILE_NAME_SIZE] ={'\0'}; 
			char B_FILE_NAME[FILE_NAME_SIZE] ={'\0'}; 
			
			getConvergeModelFileName(A_FILE_NAME,i,j,modelFileName[0]);
			getConvergeModelFileName(B_FILE_NAME,i,j,modelFileName[1]);
			
			readAMatrix(A_FILE_NAME,A);
			readBMatrix(B_FILE_NAME,B);
			
			AddTwoMatrix(tempA,A,tempB,B);
		}
		getAvgOfMatrix(tempA,tempB,FILE_COUNT);
		writePIComplement(tPI,tempPI);
		writeAComplementMatrix(tA,tempA);
		writeBComplementMatrix(tB,tempB);
	}
}

void showMatrix(){
	printf("\n-----A values------------\n");
	
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			printf("%Lf  ",A[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	printf("\n-----B values------------\n");
	
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			printf("%Lf  ",B[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	printf("\n-----PI values------------\n");
	for(int i=1;i<=N;i++){
		printf("%Lf\t",PI[i]);
	}
	
	printf("\n\n");
	printf("\n-----Observation values------------\n");
	
	for(int i=1;i<=T;i++){
		printf("%d\t",O[i]);
	}
	
	printf("\n\n");
	printf("\n-----alpha values------------\n");
	for(int t=1;t<=T;t++){
		for(int j=1;j<=N;j++){
			printf("%.8e\t\t",alpha[t][j]);
		}
		printf("\n");
	}
	printf("\n-----beta values------------\n");
	
	for(int t=1;t<=T;t++){
		for(int j=1;j<=N;j++){
			printf("%.8e\t\t",beta[t][j]);
		}
		printf("\n");
	}
	printf("\n-----gamma values------------\n");
	
	for(int t=1;t<=T;t++){
		for(int j=1;j<=N;j++){
			printf("%.8e\t\t",gamma[t][j]);
		}
		printf("\n");
	}
	printf("\n-----delta values------------\n");
	for(int t=1;t<=T;t++){
		for(int j=1;j<=N;j++){
			printf("%.8e\t\t",delta[t][j]);
		}
		printf("\n");
	}
	
	printf("\n-----jai values------------\n");

	for(int t=1;t<=T-1;t++){
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				if(j==N){
					printf("%.8e\n",jae[t][i][j]);
				}else{
					printf("%.8e\t",jae[t][i][j]);
				}
			}
		}
		printf("\n---------------------------------\n");
	}
	
}

void generateModels(){
	printf("\nModel Generation:\n\n");
	for(int i=0;i<OBJECT_COUNT;i++){
		printf("\n---------VehicleName: %s-------------\n",OBJECTS[i]);

		for(int j=1;j<=FILE_COUNT;j++){
			printf("fileNo: %d\n",j);
			
			char A_FILE_NAME[FILE_NAME_SIZE] ={'\0'}; 
			getModelFileName(A_FILE_NAME,i,j,modelFileName[0]);
			char B_FILE_NAME[FILE_NAME_SIZE] ={'\0'}; 
			getModelFileName(B_FILE_NAME,i,j,modelFileName[1]);
			
			char PI_FILE_NAME[FILE_NAME_SIZE] ={'\0'};
			getModelFileName(PI_FILE_NAME,i,j,modelFileName[2]);

			char O_FILE_NAME[FILE_NAME_SIZE] ={'\0'};
			getModelFileName(O_FILE_NAME,i,j,modelFileName[3]);
			/*
			printf("%s\n",A_FILE_NAME);
			printf("%s\n",B_FILE_NAME);
			printf("%s\n",O_FILE_NAME);
			printf("%s\n",PI_FILE_NAME);
			*/

			
			readAMatrix(A_FILE_NAME,A);
			readBMatrix(B_FILE_NAME,B);
			readPIVector(PI_FILE_NAME,PI);
			readOSequence(O_FILE_NAME,O);
			long double prev_p_star = 0.0;
			p_star = 0.0;
			int itreation = 0;
			do{
				//printf("diff: %.8e\n",abs(p_star-prev_p_star));
				
				prev_p_star = p_star;

				calculateAlpha();
				calculateBeta();
				calculateGamma();
				calculateDelta();
				calculateJae();

				//calculatePIComplement();
				calculateAComplementMatrix();
				calculateBComplementMatrix();
				adjustValueOfMatrix();
				itreation+=1;
				
			}while(p_star>prev_p_star && itreation<=MAX_ITERATION);
			
			printf("\tp_star = %.16e\n",p_star);
 
			getConvergeModelFileName(A_FILE_NAME,i,j,modelFileName[0]);
			
			getConvergeModelFileName(B_FILE_NAME,i,j,modelFileName[1]);
			
			/*
			printf("%s\n",A_FILE_NAME);
			printf("%s\n",B_FILE_NAME);
			*/

			writeAComplementMatrix(A_FILE_NAME,A);
			writeBComplementMatrix(B_FILE_NAME,B);
		}
	}
}


/*Reading a A matrix from input file*/
void readAMatrix(char *fileName,long double A[N+1][N+1]){
	FILE *fp = fopen(fileName,READ_MODE);
	if(fp==NULL){
		printf("\n readAMatrix(): Can't open %s file\n",fileName);
		return;
	}
	while(!feof(fp)){
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				fscanf(fp,"%Lf",&A[i][j]);
			}
		}
	}

	fclose(fp);
}

/*Reading a B matrix from input file*/
void readBMatrix(char *fileName,long double B[N+1][M+1]){
	FILE *fp = fopen(fileName,READ_MODE);
	if(fp==NULL){
		printf("\nreadBMatrix() : Can't open %s file\n",fileName);
		return;
	}
	
	while(!feof(fp)){
		for(int i=1;i<=N;i++){
			for(int j=1;j<=M;j++){
				fscanf(fp,"%Lf",&B[i][j]);
			}
		}
	}
	fclose(fp);
}

/*Reading a Observation sequence from input file*/
void readOSequence(char *fileName,int O[]){
	FILE *fp = fopen(fileName,READ_MODE);
	if(fp==NULL){
		printf("\nreadOSequence(): Can't open %s file\n",fileName);
		return;
	}
	int obsLength = 1;
	int temp=0;
	while(!feof(fp)){
		fscanf(fp,"%d",&temp);
		
		if(feof(fp)){
			break;
		}
		O[obsLength++] = temp;
	}
	//new length of T
	T = obsLength-1;
	fclose(fp);
}

/*Reading PI values from input file*/
void readPIVector(char *fileName,long double PI[N+1]){
	FILE* fp = fopen(fileName,READ_MODE);
	if(fp==NULL){
		printf("\nreadPIVector(): Can't open %s file\n",fileName);
		return;
	}
	while(!feof(fp)){
		for(int i=1;i<=N;i++){
			fscanf(fp,"%Lf",&PI[i]);
		}
	}
	fclose(fp);
}


/*Calculating Alpha matrix based on the A,B matrix, Oberservation Sequence(O) and PI values*/
void calculateAlpha(){
	//step1: Initialization:
	for(int i=1;i<=N;i++){
		alpha[1][i] = PI[i] * B[i][O[1]];
	}
	for(int t=1;t<T;t++){
		for(int j=1;j<=N;j++){
			long double sum = 0;
			for(int i=1;i<=N;i++){
				sum+= alpha[t][i] * A[i][j];
			}
			alpha[t+1][j] = sum*B[j][O[t+1]]; 
		}
	}
	long double probability=0;
	for(int i=1;i<=N;i++){
		probability+= alpha[T][i];
	}
	//printf("\nfinal Termination probability of alpha : %.16e\n",probability);
	//printf("\n\n");	
}


/*Calculating Beta matrix based on the A,B matrix, Oberservation Sequence(O) and PI values*/
void calculateBeta(){
	//Initialization of Beta:
	for(int i=1;i<=N;i++){
		beta[T][i] = 1;
	}
	
	//Intermediate calculatation of Beta
	for(int t=T-1;t>=1;t--){
		for(int i=1;i<=N;i++){
			long double sum = 0;
			for(int j=1;j<=N;j++){
				sum += A[i][j] * B[j][O[t+1]] * beta[t+1][j];
			}
			beta[t][i] = sum;
		}
	}
}

/*Calculating Beta matrix based on the Alpha,Beta matrix*/
void calculateGamma(){
	for(int t=1;t<=T;t++){	
		long double sum = 0;
	
		for(int i=1;i<=N;i++){
			sum+= alpha[t][i]*beta[t][i];
		}

		for(int i=1;i<=N;i++){
			gamma[t][i] = alpha[t][i]*beta[t][i]/sum;
		}
		
	}
	for(int t=1;t<=T;t++){	
		long double max=0;
		int index = 0;
		for(int i=1;i<=N;i++){
			if(max<gamma[t][i]){
				index=i;
				max=gamma[t][i];
			}
		}
		//printf("Time t: %d probability: %.4Lf   state: %d\n",t,max,index);
		gamma_state_sequence[t] = index;
	}
}


/*writing delta matrix into output file*/
void calculateDelta(){
	//--------Initialization: Delta Value----------
	for(int i=1;i<=N;i++){
		delta[1][i] = PI[i] * B[i][O[1]];
		SI[1][i]=0;
	}
	
	for(int t=2;t<=T;t++){
		for(int j=1;j<=N;j++){
			long double max=0.0;
			int index=0;
			for(int i=1;i<=N;i++){
				long double temp = delta[t-1][i] * A[i][j];
				if(temp>=max){
					max = temp;
					index = i;
				}
			}
			delta[t][j] = max * B[j][O[t]];
			SI[t][j] = index;
			//printf("t: %d state: %d delta[%d][%d]=%.32e \n",t,SI[t][j],t,j,delta[t][j]);
		}	
	}
	//-----Termination Step------
	for(int i=1;i<=N;i++){
		if(p_star < delta[T][i]){
			p_star = delta[T][i];
			q_star[T] = i;
		}
	}
	//printf("\np_star = %.16e\n\n",p_star);

	for(int t=T-1;t>0;t--){
		q_star[t] = SI[t+1][q_star[t+1]];
		//printf("%d  ",q_star[t]);
	}
}

/*Calculating Jae based on the A,B,Alpha and Beta matrix*/
void calculateJae(){
	for(int t=1;t<=T-1;t++){
		long double sum_of_prob = 0.0;

		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				sum_of_prob += ((A[i][j] * alpha[t][i]) * (B[j][O[t+1]] * beta[t+1][j]));
			}
		}

		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				jae[t][i][j] = 	((A[i][j] * alpha[t][i]) * (B[j][O[t+1]] * beta[t+1][j]))/sum_of_prob;
			}
		}
	}
}

void calculatePIComplement(){
	for(int i=1;i<=N;i++){
		PI[i] = gamma[1][i];
	}
}
void writePIComplement(char *fileName,long double PI[N+1]){
	FILE *fp = fopen(fileName,WRITE_MODE);
	if(fp==NULL){
		printf("\nwritePIComplement():Can't open %s file in %s Mode\n",fileName,WRITE_MODE);
		return;
	}
	//printf("\n----PI complement values-------------\n");
	for(int i=1;i<=N;i++){
		fprintf(fp,"%Lf\t",PI[i]);
		//printf("%Lf\t",PI[i]);
	}
	
	fclose(fp);
}


/*Calculate A Complement based on gamma and jae values at time*/
void calculateAComplementMatrix(){
	/*
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			long double no_of_trans_from_si_to_sj = 0.0;
			long double no_of_trans_from_si = 0.0;

			for(int t=1;t<=T-1;t++){
				no_of_trans_from_si_to_sj += jae[t][i][j];
				no_of_trans_from_si += gamma[t][i];
			}	
			// probability: (si to sj transition) ==> (no of transition from state si to sj) / (total transition from state si)
			A[i][j] =  no_of_trans_from_si_to_sj / no_of_trans_from_si;
		}
	}*/
	 
	// [11 12] [22 23] [33 34] [44 45]  
	for(int i=1;i<N;i++){
		for(int j=i;j<=i+1;j++){
			long double no_of_trans_from_si_to_sj = 0.0;
			long double no_of_trans_from_si = 0.0;

			for(int t=1;t<=T-1;t++){
				no_of_trans_from_si_to_sj += jae[t][i][j];
				no_of_trans_from_si += gamma[t][i];
			}	
			// probability: (si to sj transition) ==> (no of transition from state si to sj) / (total transition from state si)
			A[i][j] =  no_of_trans_from_si_to_sj / no_of_trans_from_si;
		}
	}

}


/*Calculate B Complement based on gamma and jae values at time*/
void calculateBComplementMatrix(){
	for(int j=1;j<=N;j++){
		for(int k=1;k<=M;k++){
			long double no_of_times_in_sj = 0.0;
			long double no_of_times_in_sj_obs_k = 0.0;
	
			for(int t=1;t<=T;t++){
				if(O[t]==k){
					no_of_times_in_sj_obs_k += gamma[t][j];
				}
			}		

			for(int t=1;t<=T;t++){
				no_of_times_in_sj += gamma[t][j];
			}
			/* 
			*  probability being in state j and observing k
			*            = (Expected no of times in state sj and observing symbol k) / (Expected No of times in state sj) 
			*/
			B[j][k] = no_of_times_in_sj_obs_k / no_of_times_in_sj;
		}
	}
}

void adjustValueOfMatrix(){

	for(int i=1;i<=N;i++){
		long double a_sum=0.0;
		long double a_max=0.0;
		int a_max_index = 0;

		for(int j=1;j<=N;j++){
			a_sum+= A[i][j];
			if(a_max < A[i][j]){
				a_max = A[i][j];
				a_max_index = j;
			}
		}
		A[i][a_max_index]+= (1-a_sum);
	}
	long double defualt_probability = 1.e-30;
	//printf("%e",defualt_probability);
	for(int j=1;j<=N;j++){
		long double b_sum=0.0;
		long double b_max=0.0;
		int b_max_index = 0;
		for(int k=1;k<=M;k++){
			if(/*B[j][k]!=0.0&&*/B[j][k]<defualt_probability){
				B[j][k]=defualt_probability;
			}
			b_sum+= B[j][k];
			
			if(b_max < B[j][k]){
				b_max = B[j][k];
				b_max_index = k;
			}
		}
		B[j][b_max_index]+= (1-b_sum);
	}
}


/*writing A Complement into output file*/
void writeAComplementMatrix(char *fileName,long double A[N+1][N+1]){
	FILE *fp = fopen(fileName,WRITE_MODE);
	if(fp==NULL){
		printf("\n\nwriteAComplementMatrix(): Can't open %s file for writing\n",fileName);
		return;
	}
	//printf("\n\n---------A Complement Matrix-----------\n\n");
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			if(j==N)
				fprintf(fp,"%.16e\n",A[i][j]);
			else
				fprintf(fp,"%.16e\t\t",A[i][j]);
		}
	}
	fclose(fp);
}

/*writing B Complement into output file*/
void writeBComplementMatrix(char *fileName,long double B[N+1][M+1]){
	FILE *fp = fopen(fileName,WRITE_MODE);
	if(fp==NULL){
		printf("\n\nwriteBComplementMatrix():Can't open %s file for writing\n",fileName);
		return;
	}
	//printf("\n\n---------B Complement Matrix-----------\n\n");
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			if(j==M)
				fprintf(fp,"%.16e\n",B[i][j]);
			else
				fprintf(fp,"%.16e\t\t",B[i][j]);
		}
	}
	fclose(fp);
}
