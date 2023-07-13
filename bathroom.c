#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

sem_t empty;
sem_t turnstile;
sem_t female_mutex, male_mutex;
sem_t f_count, m_count;

int female_count=0, male_count=0;

struct arguments {
  int a;
  char* b;
};

char* global_state_initializer(int size){

  char* array = malloc(size * sizeof(char));

  for (int i = 0; i < size; i++) {
    array[i] = 'X';
  }

  return array;
}

void print_global_state(char * global_state, int spaces){
	for(int i = 0; i < spaces; i++){
		printf("%c ", global_state[i]);
	}
	printf("\n");
	
}

void f_thread(void *arg){

	struct arguments *args = (struct arguments *)arg;
	
	int spaces = args->a;

	char* global_state = (char*)args->b;

	sem_wait(&turnstile);
	sem_wait(&female_mutex);
	female_count+=1;
	if(female_count==1)
		sem_wait(&empty);
	sem_post(&female_mutex);
	sem_post(&turnstile);

	sem_wait(&f_count);

	int bathroom_index;
	for(int i = 0 ; i < spaces ; i++){
		if('X' == global_state[i]){
			bathroom_index = i;
			global_state[i] = 'F';
			break;
		};
	}
	print_global_state(global_state, spaces);

	sleep((rand() % 4) + 1);
	sem_post(&f_count);
	
	global_state[bathroom_index] = 'X';
	print_global_state(global_state, spaces);

	sem_wait(&female_mutex);
	female_count-=1;
	if(female_count==0)
		sem_post(&empty);
	sem_post(&female_mutex);
	return;
}

void m_thread(void *arg){

	struct arguments *args = (struct arguments *)arg;
	
	int spaces = args->a;

	char* global_state = (char*)args->b;

	sem_wait(&turnstile); 
	sem_wait(&male_mutex);  
	male_count+=1;  
	if(male_count==1)
		sem_wait(&empty); 
	sem_post(&male_mutex);  
	sem_post(&turnstile);

	sem_wait(&m_count); 

	int bathroom_index;
	for(int i = 0 ; i < spaces ; i++){
		if('X' == global_state[i]){
			bathroom_index = i;
			global_state[i] = 'M';
			break;
		};
	}
	print_global_state(global_state, spaces);


	sleep((rand() % 4) + 1);
	sem_post(&m_count);

	global_state[bathroom_index] = 'X';
	print_global_state(global_state, spaces);

	sem_wait(&male_mutex);
	male_count-=1;
	if(male_count==0)
		sem_post(&empty); 
	sem_post(&male_mutex);  
	return;
}

int main(int argc, char *argv[]){
	
	int spaces = atoi(argv[1]);
	int max_people = atoi(argv[2]);
	char* global_state = global_state_initializer(spaces);
	int seed = time(NULL);
	srand(seed);
	struct arguments args = {spaces, global_state};
	sem_init(&empty, 0, 1);
	sem_init(&turnstile, 0, 1);
	sem_init(&female_mutex, 0, 1);
	sem_init(&male_mutex, 0, 1);
	sem_init(&f_count, 0, spaces);
	sem_init(&m_count, 0, spaces);
	printf("##### Bathroom Open ##### \n");
	print_global_state(global_state, spaces);

	pthread_t thr[max_people];
	for(int i = 0 ; i < max_people ; i++){
		int gender = rand() % 2;
		//int gender = 0;
		void *t_func = (gender == 0) ? m_thread : f_thread;
		pthread_create(&thr[i], NULL, t_func, &args);
		sleep(1);

	}

	for(int i = 0 ; i < max_people ; i++){
		pthread_join(thr[i], NULL);
	}
	printf("### Bathroom Closed ### \n");
	return 0;
}
