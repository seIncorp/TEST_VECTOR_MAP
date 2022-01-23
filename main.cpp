#include <iostream>
#include <map>
#include <vector>
#include <chrono>



#define NUM_TEST                        5
#define NUM_OBJECTS                     10000
#define NUM_POSITION_SEARCHED_OBJECT    5550
#define NUM_POSITION_DELETED_OBJECT     5000



typedef struct TEST_S
{
	TEST_S(int a_, int b_) : a{ a_ }, b{ b_ }
	{};

	int a;
	int b;
} TEST;


std::vector<TEST_S> a1;
std::map<int, TEST_S> map_test;


unsigned long vector_insert_time_MICRO[NUM_TEST]{ 0 };
unsigned long vector_push_back_time_MICRO[NUM_TEST]{ 0 };

unsigned long vector_search_time_NANO[NUM_TEST]{ 0 };
unsigned long vector_deleting_item_time_NANO[NUM_TEST]{ 0 };
unsigned long vector_deleting_all_time_NANO[NUM_TEST]{ 0 };

unsigned long map_insert_time_MICRO[NUM_TEST]{ 0 };
unsigned long map_search_time_NANO[NUM_TEST]{ 0 };
unsigned long map_deleting_item_time_NANO[NUM_TEST]{ 0 };
unsigned long map_deleting_all_time_NANO[NUM_TEST]{ 0 };


void test_Insert_VECTOR();
void test_push_back_VECOR();
void test_insert_MAP();


int main(int argc, char *argv[]) {

	unsigned long average = 0;

    printf("Number of repeated test: %d\n", NUM_TEST);


	test_Insert_VECTOR();

	test_push_back_VECOR();

	test_insert_MAP();
	

	return 0;
}

void test_insert_MAP()
{
    std::cout << "****** TESTING map::insert *******" << std::endl;
	
    unsigned long average = 0;
    
    for (int i = 0; i < NUM_TEST; i++)
	{
		// insert
		auto start = std::chrono::high_resolution_clock::now();
		for (int a = 0; a < NUM_OBJECTS; a++)
			map_test.insert({ a, TEST_S(1,a) });
		auto stop = std::chrono::high_resolution_clock::now();

		auto duration_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		auto duration_micro = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		auto duration_mili = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

		map_insert_time_MICRO[i] = duration_micro.count();


		//  search
		start = std::chrono::high_resolution_clock::now();
		TEST temp = map_test.at(NUM_POSITION_SEARCHED_OBJECT);
		stop = std::chrono::high_resolution_clock::now();
		duration_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		map_search_time_NANO[i] = duration_nano.count();


		// delete one item
		start = std::chrono::high_resolution_clock::now();
		map_test.erase(NUM_POSITION_DELETED_OBJECT);
		stop = std::chrono::high_resolution_clock::now();
		duration_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		map_deleting_item_time_NANO[i] = duration_nano.count();


		// delete all
		start = std::chrono::high_resolution_clock::now();
		map_test.clear();
		stop = std::chrono::high_resolution_clock::now();
		duration_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		map_deleting_all_time_NANO[i] = duration_nano.count();
	}

	printf("INSERT time in MICRO seconds (all %d objects): ", NUM_OBJECTS);
	for (int i = 0; i < NUM_TEST; i++)
	{
		printf("%lu ", map_insert_time_MICRO[i]);
		average += map_insert_time_MICRO[i];
	}
	printf(" AVARAGE: %lu\n", (average / NUM_TEST));

	average = 0;
	printf("SEARCH time in NANO seconds (item position %d): ",NUM_POSITION_SEARCHED_OBJECT);
	for (int i = 0; i < NUM_TEST; i++)
	{
		printf("%lu ", map_search_time_NANO[i]);
		average += map_search_time_NANO[i];
	}
	printf(" AVARAGE: %lu\n", (average / NUM_TEST));

	average = 0;
	printf("DELETING ONE ITEM time in NANO seconds (item position %d): ",NUM_POSITION_DELETED_OBJECT);
	for (int i = 0; i < NUM_TEST; i++)
	{
		printf("%lu ", map_deleting_item_time_NANO[i]);
		average += map_deleting_item_time_NANO[i];
	}
	printf(" AVARAGE: %lu\n", (average / NUM_TEST));

	average = 0;
	printf("DELETING ALL time in NANO seconds: ");
	for (int i = 0; i < NUM_TEST; i++)
	{
		printf("%lu ", map_deleting_all_time_NANO[i]);
		average += map_deleting_all_time_NANO[i];
	}
	printf(" AVARAGE: %lu\n", (average / NUM_TEST));
}

void test_Insert_VECTOR()
{
    std::cout << "****** TESTING vector::insert *******" << std::endl;
    
    unsigned long average = 0;
    
	for (int i = 0; i < NUM_TEST; i++)
	{
		// insert
        
		auto start = std::chrono::high_resolution_clock::now();
		for (int a = 0; a < NUM_OBJECTS; a++)
        {
            a1.insert(a1.begin(), TEST_S(1, a));
        }
		auto stop = std::chrono::high_resolution_clock::now();

		auto duration_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		auto duration_micro = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

		vector_insert_time_MICRO[i] = duration_micro.count();

		// search
		start = std::chrono::high_resolution_clock::now();
		TEST temp = a1.at(NUM_POSITION_SEARCHED_OBJECT);
		stop = std::chrono::high_resolution_clock::now();
		duration_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		vector_search_time_NANO[i] = duration_nano.count();


		// delete one item
		start = std::chrono::high_resolution_clock::now();
		a1.erase(a1.begin() + NUM_POSITION_DELETED_OBJECT);
		stop = std::chrono::high_resolution_clock::now();
		duration_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		vector_deleting_item_time_NANO[i] = duration_nano.count();


		// delete all
		start = std::chrono::high_resolution_clock::now();
		a1.clear();
		stop = std::chrono::high_resolution_clock::now();
		duration_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

		vector_deleting_all_time_NANO[i] = duration_nano.count();
	}
    
    printf("INSERTING time in MICRO seconds (all %d objects): ",NUM_OBJECTS);
	for (int i = 0; i < NUM_TEST; i++)
	{
		printf("%lu ", vector_insert_time_MICRO[i]);
		average += vector_insert_time_MICRO[i];
	}
	printf(" AVARAGE: %lu\n", (average / NUM_TEST));

	average = 0;
	printf("SEARCH time in NANO seconds (item position %d): ",NUM_POSITION_SEARCHED_OBJECT);
	for (int i = 0; i < NUM_TEST; i++)
	{
		printf("%lu ", vector_search_time_NANO[i]);
		average += vector_search_time_NANO[i];
	}
	printf(" AVARAGE: %lu\n", (average / NUM_TEST));

	average = 0;
	printf("DELETING ONE ITEM time in NANO seconds (item position %d): ",NUM_POSITION_DELETED_OBJECT);
	for (int i = 0; i < NUM_TEST; i++)
	{
		printf("%lu ", vector_deleting_item_time_NANO[i]);
		average += vector_deleting_item_time_NANO[i];
	}
	printf(" AVARAGE: %lu\n", (average / NUM_TEST));

	average = 0;
	printf("DELETING ALL time in NANO seconds: ");
	for (int i = 0; i < NUM_TEST; i++)
	{
		printf("%lu ", vector_deleting_all_time_NANO[i]);
		average += vector_deleting_all_time_NANO[i];
	}
	printf(" AVARAGE: %lu\n", (average / NUM_TEST));

	std::cout << std::endl;
}

void test_push_back_VECOR()
{
    std::cout << "****** TESTING vector::push_back *******" << std::endl;
    
    unsigned long average = 0;

	for (int i = 0; i < NUM_TEST; i++)
	{
		// push back
		auto start = std::chrono::high_resolution_clock::now();
		for (int a = 0; a < NUM_OBJECTS; a++)
			a1.push_back(TEST_S(1, a));
		auto stop = std::chrono::high_resolution_clock::now();

		auto duration_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		auto duration_micro = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

		vector_push_back_time_MICRO[i] = duration_micro.count();


		// search
		start = std::chrono::high_resolution_clock::now();
		TEST temp = a1.at(NUM_POSITION_SEARCHED_OBJECT);
		stop = std::chrono::high_resolution_clock::now();
		duration_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		vector_search_time_NANO[i] = duration_nano.count();


		// delete one item
		start = std::chrono::high_resolution_clock::now();
		a1.erase(a1.begin() + NUM_POSITION_DELETED_OBJECT);
		stop = std::chrono::high_resolution_clock::now();
		duration_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		vector_deleting_item_time_NANO[i] = duration_nano.count();


		// delete all
		start = std::chrono::high_resolution_clock::now();
		a1.clear();
		stop = std::chrono::high_resolution_clock::now();
		duration_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		vector_deleting_all_time_NANO[i] = duration_nano.count();
	}
    
    
	printf("PUSH BACK time in MICRO seconds (all %d objects): ", NUM_OBJECTS);
	for (int i = 0; i < NUM_TEST; i++)
	{
		printf("%lu ", vector_push_back_time_MICRO[i]);
		average += vector_push_back_time_MICRO[i];
	}
	printf(" AVARAGE: %lu\n", (average / NUM_TEST));

	average = 0;
	printf("SEARCH time in NANO seconds (item position %d): ",NUM_POSITION_SEARCHED_OBJECT);
	for (int i = 0; i < NUM_TEST; i++)
	{
		printf("%lu ", vector_search_time_NANO[i]);
		average += vector_search_time_NANO[i];
	}
	printf(" AVARAGE: %lu\n", (average / NUM_TEST));

	average = 0;
	printf("DELETING ONE ITEM time in NANO seconds (item position %d): ",NUM_POSITION_DELETED_OBJECT);
	for (int i = 0; i < NUM_TEST; i++)
	{
		printf("%lu ", vector_deleting_item_time_NANO[i]);
		average += vector_deleting_item_time_NANO[i];
	}
	printf(" AVARAGE: %lu\n", (average / NUM_TEST));

	average = 0;
	printf("DELETING ALL time in NANO seconds: ");
	for (int i = 0; i < NUM_TEST; i++)
	{
		printf("%lu ", vector_deleting_all_time_NANO[i]);
		average += vector_deleting_all_time_NANO[i];
	}
	printf(" AVARAGE: %lu\n", (average / NUM_TEST));
    
	std::cout << std::endl;
}