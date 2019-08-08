#include "zeroevenodd.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_zero = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_odd = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_even = PTHREAD_COND_INITIALIZER;

int count = 0;
int flag_zero = 1;
int flag_odd = 0;
int flag_even = 0;

int main(int argc, char** argv)
{
#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] zero-even-odd print testing started\n", pthread_self(), __func__, __LINE__);
#endif
	if(argc != 2)
	{
#ifdef _ENABLE_LOGS_ERR_
		printf("thread: [%ld] function: [%s] line: [%d] zero-even-odd usage: ./zero-even-odd <zero-even-odd print upto number>\n", pthread_self(), __func__, __LINE__);
#endif
		return -1;
	}
#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] arguments passed: [%s] [%s]\n", pthread_self(), __func__, __LINE__, argv[0], argv[1]);
#endif
	int freq = atoi(argv[1]);
#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] print upto number: [%d]\n", pthread_self(), __func__, __LINE__, freq);
#endif
	ZeroEvenOdd* zeoobj = zeroEvenOddCreate(freq);

	pthread_t pthread[3];

#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] threads started\n", pthread_self(), __func__, __LINE__);
#endif

	int pret1, pret2, pret3;
	pret1 = pthread_create(&pthread[0], NULL, (void*)zero, (void*)zeoobj);
	if(pret1)
	{
#ifdef _ENABLE_LOGS_THREAD_ERR_
		printf("thread: [%ld] function: [%s] line: [%d] thread zero print creation failed\n", pthread_self(), __func__, __LINE__);
#endif
		return -1;	
	}
	pret2 = pthread_create(&pthread[1], NULL, (void*)even, (void*)zeoobj);
	if(pret2)
	{
#ifdef _ENABLE_LOGS_THREAD_ERR_
		printf("thread: [%ld] function: [%s] line: [%d] thread even creation failed\n", pthread_self(), __func__, __LINE__);
#endif
		return -1;
	}
	pret3 = pthread_create(&pthread[2], NULL, (void*)odd, (void*)zeoobj);
	if(pret3)
	{
#ifdef _ENABLE_LOGS_THREAD_ERR_
		printf("thread: [%ld] function: [%s] line: [%d] thread odd creation failed\n", pthread_self(), __func__, __LINE__);
#endif
		return -1;
	}

	pthread_join(pthread[0], NULL);
	pthread_join(pthread[1], NULL);
	pthread_join(pthread[2], NULL);
#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] zero-even-odd print testing completed\n", pthread_self(), __func__, __LINE__);
#endif
	return 0;

}

// allocate call for ZeroEvenOdd object

ZeroEvenOdd* zeroEvenOddCreate(int n) {
#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] enter\n", pthread_self(), __func__, __LINE__);
#endif

	ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));
	obj->n = n;
	return obj;
}


//zero function

void zero(ZeroEvenOdd* obj) {
#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] enter\n", pthread_self(), __func__, __LINE__);
#endif
	while(1)
	{
		pthread_mutex_lock(&mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
		printf("thread: [%ld] function: [%s] line: [%d] after mutex lock\n", pthread_self(), __func__, __LINE__);
#endif
		while(flag_zero == 0 && (flag_odd == 1 || flag_even == 1))
		{
#ifdef _ENABLE_LOGS_THREAD_INFO_
			printf("thread: [%ld] function: [%s] line: [%d] before cond_zero wait\n", pthread_self(), __func__, __LINE__);
#endif
			pthread_cond_wait(&cond_zero, &mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
			printf("thread: [%ld] function: [%s] line: [%d] after cond_zero wait\n", pthread_self(), __func__, __LINE__);
#endif
		}
		pthread_mutex_unlock(&mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
		printf("thread: [%ld] function: [%s] line: [%d] after mutex unlock\n", pthread_self(), __func__, __LINE__);
#endif

		printf("%d\n", 0);
		pthread_mutex_lock(&mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
		printf("thread: [%ld] function: [%s] line: [%d] after mutex lock\n", pthread_self(), __func__, __LINE__);
#endif
		flag_zero = 0;
		count++;
		if(count %2 == 0)
		{
			flag_even = 1;
			pthread_cond_signal(&cond_even);
#ifdef _ENABLE_LOGS_THREAD_INFO_
			printf("thread: [%ld] function: [%s] line: [%d] after cond_even signal\n", pthread_self(), __func__, __LINE__);
#endif
		}
		else
		{
			flag_odd = 1;
			pthread_cond_signal(&cond_odd);
#ifdef _ENABLE_LOGS_THREAD_INFO_
			printf("thread: [%ld] function: [%s] line: [%d] after cond_odd signal\n", pthread_self(), __func__, __LINE__);
#endif
		}
		pthread_mutex_unlock(&mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
		printf("thread: [%ld] function: [%s] line: [%d] after mutex unlock\n", pthread_self(), __func__, __LINE__);
#endif
		if(count == obj->n)
			break;
	}
#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] exit\n", pthread_self(), __func__, __LINE__);
#endif
}


// even function

void even(ZeroEvenOdd* obj) {
#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] enter\n", pthread_self(), __func__, __LINE__);
#endif

	while(1)
	{
		pthread_mutex_lock(&mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
		printf("thread: [%ld] function: [%s] line: [%d] after mutex lock\n", pthread_self(), __func__, __LINE__);
#endif
		if((count+2) > obj->n)
		{
			pthread_mutex_unlock(&mutex);
			break;
		}

		while(flag_zero == 1 && flag_even == 0)
		{
#ifdef _ENABLE_LOGS_THREAD_INFO_
			printf("thread: [%ld] function: [%s] line: [%d] before cond_even wait\n", pthread_self(), __func__, __LINE__);
#endif
			pthread_cond_wait(&cond_even, &mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
			printf("thread: [%ld] function: [%s] line: [%d] after cond_even wait\n", pthread_self(), __func__, __LINE__);
#endif
		}
		pthread_mutex_unlock(&mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
		printf("thread: [%ld] function: [%s] line: [%d] after mutex unlock\n", pthread_self(), __func__, __LINE__);
#endif
		printf("%d\n", count);

		pthread_mutex_lock(&mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
		printf("thread: [%ld] function: [%s] line: [%d] after mutex lock\n", pthread_self(), __func__, __LINE__);
#endif
		flag_zero = 1;
		flag_even = 0;
		pthread_cond_signal(&cond_zero);
#ifdef _ENABLE_LOGS_THREAD_INFO_
		printf("thread: [%ld] function: [%s] line: [%d] after cond_zero signal\n", pthread_self(), __func__, __LINE__);
#endif
		pthread_mutex_unlock(&mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
		printf("thread: [%ld] function: [%s] line: [%d] after mutex unlock\n", pthread_self(), __func__, __LINE__);
#endif
		if(count == obj->n)
			break;
	}
#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] exit\n", pthread_self(), __func__, __LINE__);
#endif
}


//odd function

void odd(ZeroEvenOdd* obj) {
#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] enter\n", pthread_self(), __func__, __LINE__);
#endif
	while(1)
	{
		pthread_mutex_lock(&mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
		printf("thread: [%ld] function: [%s] line: [%d] after mutex lock\n", pthread_self(), __func__, __LINE__);
#endif
		if(obj->n >= 2)
			if((count+2) > obj->n)
			{
				pthread_mutex_unlock(&mutex);
				break;
			}

		while(flag_zero == 1 && flag_odd == 0)
		{
#ifdef _ENABLE_LOGS_THREAD_INFO_
			printf("thread: [%ld] function: [%s] line: [%d] before cond_odd wait\n", pthread_self(), __func__, __LINE__);
#endif
			pthread_cond_wait(&cond_odd, &mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
			printf("thread: [%ld] function: [%s] line: [%d] after cond_odd wait\n", pthread_self(), __func__, __LINE__);
#endif
		}
		pthread_mutex_unlock(&mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
		printf("thread: [%ld] function: [%s] line: [%d] after mutex unlock\n", pthread_self(), __func__, __LINE__);
#endif
		printf("%d\n", count);

		pthread_mutex_lock(&mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
		printf("thread: [%ld] function: [%s] line: [%d] after mutex lock\n", pthread_self(), __func__, __LINE__);
#endif
		flag_zero = 1;
		flag_odd = 0;
		pthread_cond_signal(&cond_zero);
#ifdef _ENABLE_LOGS_THREAD_INFO_
		printf("thread: [%ld] function: [%s] line: [%d] after cond_zero signal\n", pthread_self(), __func__, __LINE__);
#endif
		pthread_mutex_unlock(&mutex);
#ifdef _ENABLE_LOGS_THREAD_INFO_
		printf("thread: [%ld] function: [%s] line: [%d] after mutex unlock\n", pthread_self(), __func__, __LINE__);
#endif
		if(count == obj->n)
			break;
	}
#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] exit\n", pthread_self(), __func__, __LINE__);
#endif
}

//free call for ZeroEvenOdd object

void zeroEvenOddFree(ZeroEvenOdd* obj)
{
#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] enter\n", pthread_self(), __func__, __LINE__);
#endif

	free(obj);
}


