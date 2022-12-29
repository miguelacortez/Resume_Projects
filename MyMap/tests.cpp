// tests.cpp
//
// Author: Miguel Cortez
//
// Contributors: hvu28, jbola6, ulnu3
// 
// Date: 11/2/2022
// 
// This file will contain all of the units associated with
// the mymap class created for Program 05, CS 251 Fall 2022
//

#include <gtest/gtest.h>
#include "mymap.h"
#include <string>
#include <time.h>
#include <map>
#include "myrandom.h"

// Test Purpose: ensure default constructor functions
TEST(mymap, constructorTest01) 
{
    for (int i = 0; i < 250; i++)
    {
        mymap <int, int> testMapName;

        EXPECT_EQ(testMapName.Size(), 0);
    }  
}

TEST(mymap, constructorTest02) 
{
    for (int i = 0; i < 250; i++)
    {
        mymap <string, int> testMapName;

        EXPECT_EQ(testMapName.Size(), 0);
    }  
}

TEST(mymap, constructorTest03) 
{
    for (int i = 0; i < 250; i++)
    {
        mymap <int, char> testMapName;

        EXPECT_EQ(testMapName.Size(), 0);
    }  
}

TEST(mymap, constructorTest04) 
{
    for (int i = 0; i < 250; i++)
    {
        mymap <double, double> testMapName;

        EXPECT_EQ(testMapName.Size(), 0);
    }  
}

// Test Purpose: ensure that put() function, functions
TEST(mymap, putTest01)
{
    srand(time(0));

    mymap <int, int> map;

    int testKey = -1;
    int testValue = -1;
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = rand();
        testValue = rand();

        map.put(testKey, testValue);

        EXPECT_EQ(map.Size(), i + 1);
    }
}

TEST(mymap, putTest02)
{
    mymap <int, char> map;

    int testKey = -1;
    char testValue = ' ';
    char letters[] = "abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = rand();
        testValue = letters[rand() % 26];

        map.put(testKey, testValue);

        EXPECT_EQ(map.Size(), i + 1);
    }
}

TEST(mymap, putTest03)
{
    mymap <string, int> map;

    string testKey = to_string(-1);
    int testValue = -1;
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = to_string(rand());
        testValue = rand();

        map.put(testKey, testValue);

        EXPECT_EQ(map.Size(), i + 1);
    }
}

// Test(s) sourced from: ulnu3
TEST(mymap, putAndSize) 
{
    mymap <int, int > map1;

    for (int i = 0 ; i < 100; i++)
    {
        map1.put(i, randomInteger(0, 10000));
        EXPECT_EQ(map1.Size(), i+1);
    }

    for (int i = 25 ; i < 75; i++)
    {
        map1.put(i, randomInteger(0, 10000));
        EXPECT_EQ(map1.Size(), 100);
    }
 
    mymap <float , int > map2;

    for (int i = 0 ; i < 100; i++)
    {
        float f = (float)i;
        map2.put(f, randomInteger(0, 10000));
        EXPECT_EQ(map2.Size(), i+1);
    }

    for (int i = 25 ; i < 75; i++)
    {
        map2.put((float)i, randomInteger(0, 10000));
        EXPECT_EQ(map2.Size(), 100);
    }
 
    mymap <double , int > map3 ;

    for (int i = 0 ; i < 100; i++)
    {
        double d = (double)i;
        map3.put(d, randomInteger(0, 10000));
        EXPECT_EQ(map3.Size(), i+1);
    }

    for (int i = 25 ; i < 75; i++)
    {
        map3.put((double)i, randomInteger(0, 10000));
        EXPECT_EQ(map1.Size(), 100);
    }

    mymap <char , int > map4 ;

    for (int i = 32 ; i < 127; i++)
    {
        map4.put (i,randomInteger(0,10000));
        EXPECT_EQ(map4.Size(), i+1-32);
    }

    for (int i = 0 ; i < 100 ; i++)
    {
        map4.put(randomInteger(32,126), randomInteger(0,190000));
        EXPECT_EQ(map4.Size(), 95);
    }
}

// Test Purpose: ensure that .Size() function, functions
TEST(mymap, testSize01)
{
    mymap <int, int> map;

    int testKey = -1;
    int testValue = -1;
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = rand();
        testValue = rand();

        map.put(testKey, testValue);

        EXPECT_EQ(map.Size(), i + 1);
    }
}

TEST(mymap, testSize02)
{
    mymap <int, char> map;

    int testKey = -1;
    char testValue = ' ';
    char letters[] = "abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = rand();
        testValue = letters[rand() % 26];

        map.put(testKey, testValue);

        EXPECT_EQ(map.Size(), i + 1);
    }
}

TEST(mymap, testSize03)
{
    mymap <string, int> map;

    string testKey = to_string(-1);
    int testValue = -1;
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = to_string(rand());
        testValue = rand();

        map.put(testKey, testValue);

        EXPECT_EQ(map.Size(), i + 1);
    }
}

// Test Purpose: ensure that .contains() function, functions
TEST(mymap, testContains01)
{
    mymap <int, char> testMapName;

    int testKey = -1;
    char testValue = ' ';
    char letters[] = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 250; i++)
    {
        testKey = rand();
        testValue = letters[rand() % 26];

        testMapName.put(testKey, testValue);

        EXPECT_EQ(testMapName.contains(testKey), true);
    }  
}

TEST(mymap, testContains02)
{
    for (int i = 0; i < 250; i++)
    {
        mymap <int, int> testMapName;

        testMapName.put(i, i);

        EXPECT_EQ(testMapName.contains(i), true);
    }
}

TEST(mymap, testContains03)
{
    mymap <string, int> map;

    string testKey = to_string(-1);
    int testValue = -1;
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = to_string(rand());
        testValue = rand();

        map.put(testKey, testValue);

        EXPECT_EQ(map.contains(testKey), true);
    }
}

// Test(s) sourced from: ulnu3
TEST(mymap, putAndContain )
{
    mymap <int , int > map1;

    for (int i = 0 ; i < 100; i++)
    {
        map1.put(i, randomInteger(0, 10000));
    }

    for (int i = 0; i < 100; i++) 
    {
        EXPECT_TRUE(map1.contains(i));
    }

    for (int i = 0 ; i < 100 ; i++)
    {
        EXPECT_FALSE(map1.contains(i+100));
    }
 
    mymap <float , int > map2;

    for (int i = 0 ; i < 100; i++)
    {
        map2.put((float)i, randomInteger(0, 10000));
    }

    for (int i = 0; i < 100; i++) 
    {
        EXPECT_TRUE(map2.contains((float)i));
    }

    for (int i = 0 ; i < 100 ; i++)
    {
        EXPECT_FALSE(map2.contains((float)i+100));
    }
 
    mymap <double , int > map3;

    for (int i = 0 ; i < 100; i++)
    {
        map3.put((double)i, randomInteger(0, 10000));
    }

    for (int i = 0; i < 100; i++) 
    {
        EXPECT_TRUE(map3.contains((double)i));
    }

    for (int i = 0 ; i < 100 ; i++)
    {
        EXPECT_FALSE(map3.contains((double)i+100));
    }
 
    mymap <char , int > map4;

    for (int i = 32 ; i < 65; i++)
    {
        map4.put((char)i, randomInteger(0, 10000));
    }

    for (int i = 32; i < 65; i++) 
    {
        EXPECT_TRUE(map4.contains((char)i));
    }

    for (int i = 65 ; i < 127 ; i++)
    {
        EXPECT_FALSE(map4.contains((char)i));
    }
}

// Test Purpose: ensure that .get() function, functions
TEST(mymap, testGet01)
{
    mymap <string, int> map;

    string testKey = to_string(-1);
    int testValue = -1;

    int getValue = -1;
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = to_string(rand());
        testValue = rand();

        map.put(testKey, testValue);

        getValue = map.get(testKey);

        EXPECT_EQ(testValue, getValue);
    }
}

TEST(mymap, testGet02)
{
    mymap <int, int> map;

    int testKey = -1;
    int testValue = -1;

    int getValue = -1;
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = rand();
        testValue = rand();

        map.put(testKey, testValue);

        getValue = map.get(testKey);

        EXPECT_EQ(testValue, getValue);
    }
}

TEST(mymap, testGet03)
{
    mymap <char, char> testMapName;

    char testKey = ' ';
    char testValue = ' ';
    char letters[] = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 250; i++)
    {
        testKey = letters[rand() % 26];
        testValue = letters[rand() % 26];

        testMapName.put(testKey, testValue);

        char getValue = testMapName.get(testKey);

        EXPECT_EQ(testMapName.get(testKey), getValue);
    }  
}

// Test(s) sourced from: ulnu3
TEST (mymap , putAndGet)
{
    mymap <int , int > map1 ;
    map <int , int > solution ;

    for (int i = 0 ; i < 100; i++)
    {
        int n =  randomInteger(0, 10000);
        map1.put(i,n);
        solution [i] = n ;  
    }

    for (int i = 0 ; i< 150 ;i++)
    {
        EXPECT_EQ(map1.get(i), solution[i]);
    }
 
    mymap <float , int > map2 ;
    map <float , int > solution2 ;

    for (int i = 0 ; i < 100; i++)
    {
        int n =  randomInteger(0, 10000);
        map2.put((float)i,n);
        solution2 [(float)i] = n ;  
    }

    for (int i = 0 ; i< 150 ;i++)
    {
        EXPECT_EQ(map2.get((float)i), solution2[(float)i]);
    }
 
    mymap <double, int> map3;
    map <double , int > solution3 ;

    for (int i = 0 ; i < 100; i++)
    {
        int n =  randomInteger(0, 10000);
        map3.put((double)i,n);
        solution3 [(double)i] = n ;  
    }

    for (int i = 0 ; i< 150 ;i++)
    {
        EXPECT_EQ(map3.get((double)i), solution3[(double)i]);
    }
 
    mymap <char , int > map4 ;
    map <char , int > solution4 ;
    for (int i = 32 ; i < 65; i++)
    {
        int n =  randomInteger(0, 10000);
        map4.put((char)i,n);
        solution4 [(char)i] = n ;  
    }

    for (int i = 32 ; i< 127 ;i++)
    {
        EXPECT_EQ(map4.get((char)i), solution4[(char)i]);
    }
}

// Test(s) sourced from: jbola6
TEST (testGetDouble, subTestThreeDouble) 
{
    mymap<double, int> map;

    double arr[] = {2.2, 1.4, 5.6};

    for (int i = 0; i < 3; i++) 
    {
        map.put(arr[i], i);
    }

    for (int i = 0; i < 3; i++) 
    {
        EXPECT_EQ(map.get(arr[i]), i);
        EXPECT_FALSE(map.get(arr[i]) == 5);
        EXPECT_EQ(map.Size(), 3);
    }
}

// Test Purpose: ensure that .toString function, functions
TEST(mymap, testToString01)
{
    mymap <int, int> mapOne;
    map <int, int> mapTwo;
    stringstream ss;

    int testKey = -1;
    int testValue = -1;
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = rand();
        testValue = rand();

        mapOne.put(testKey, testValue);
        mapTwo[testKey] = testValue;  
    }

    for (auto e: mapTwo)
    {
        ss << "key: " << e.first << " value: " << e.second << endl;
    }

    EXPECT_EQ(mapOne.toString(), ss.str());
}

TEST(mymap, testToString02)
{
    mymap <char, char> mapOne;
    map <char, char> mapTwo;
    char letters[] = "abcdefghijklmnopqrstuvwxyz";
    stringstream ss;

    char testKey = ' ';
    char testValue = ' ';
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = letters[rand() % 26];
        testValue = letters[rand() % 26];

        mapOne.put(testKey, testValue);
        mapTwo[testKey] = testValue;  
    }

    for (auto e: mapTwo)
    {
        ss << "key: " << e.first << " value: " << e.second << endl;
    }

    EXPECT_EQ(mapOne.toString(), ss.str());
}

TEST(mymap, testToString03)
{
    mymap <string, string> mapOne;
    map <string, string> mapTwo;
    stringstream ss;

    string testKey = to_string(-1);
    string testValue = to_string(-1);
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = to_string(rand());
        testValue = to_string(rand());

        mapOne.put(testKey, testValue);
        mapTwo[testKey] = testValue;  
    }

    for (auto e: mapTwo)
    {
        ss << "key: " << e.first << " value: " << e.second << endl;
    }

    EXPECT_EQ(mapOne.toString(), ss.str());
}

// Test(s) sourced from: ulnu3
TEST (mymap, tostring)
{
    mymap <int , int > map1 ;
    map <int , int > solution ;

    for (int i = 0 ; i < 100; i++)
    {
        int n =  randomInteger(0, 10000);
        map1.put(i,n);
        solution [i] = n ;  
    }
    string mystring = map1.toString () ;
    stringstream sol("") ;

    for (auto it : solution)
    {
        sol << "key: " << it.first << " value: " << it.second << "\n" ;      
    }

    EXPECT_EQ(mystring, sol.str());
 
    mymap <float , int > map2 ;
    map <float , int > solution2 ;

    for (int i = 0 ; i < 100; i++)
    {
        int n =  randomInteger(0, 10000);
        float j = (float)i;
        map2.put(j,n);
        solution2 [j] = n ;  
    }

    string mystring2 = map2.toString () ;
    stringstream sol2("") ;

    for (auto it : solution2)
    {
        sol2 << "key: " << it.first << " value: " << it.second << "\n" ;      
    }
    EXPECT_EQ(mystring2, sol2.str());
 
    mymap <double , int > map3 ;
    map <double , int > solution3 ;

    for (int i = 0 ; i < 100; i++)
    {
        int n =  randomInteger(0, 10000);
        double j = (double)i;
        map3.put(j,n);
        solution3 [j] = n ;  
    }
    string mystring3 = map3.toString () ;
    stringstream sol3("") ;

    for (auto it : solution3)
    {
        sol3 << "key: " << it.first << " value: " << it.second << "\n" ;      
    }
    EXPECT_EQ(mystring3, sol3.str());
 
    mymap <char , int > map4 ;
    map <char , int > solution4 ;

    for (int i = 32 ; i < 127; i++)
    {
        int n =  randomInteger(0, 10000);
        char j = (char)i;
        map4.put(j,n);
        solution4 [j] = n ;  
    }

    string mystring4 = map4.toString () ;
    stringstream sol4("") ;

    for (auto it : solution4)
    {
        sol4 << "key: " << it.first << " value: " << it.second << "\n" ;      
    }

    EXPECT_EQ(mystring4, sol4.str());
}

// Test Purpose: ensure that operator[] overload functions
TEST(mymap, testBracketOp01)
{
    mymap <int, int> mapOne;

    int testKey = -1;
    int testValue = -1;
    
    for (int i = 0; i < 25; i++) 
    {
        testKey = rand();
        testValue = rand();

        mapOne.put(testKey, testValue);

        // cout << mapOne[testKey] << endl;

        // use .put() to add into map 
        // then use [] to check values that it'll return
        // test default values? look them up for a couple data types

        EXPECT_EQ(mapOne[testKey], testValue);

        // cout << mapOne.Size() << endl;  
    }
}

TEST(mymap, testBracketOp02)
{
    mymap <string, int> mapOne;

    string testKey = to_string(-1);
    int testValue = -1;
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = to_string(rand());
        testValue = rand();

        mapOne.put(testKey, testValue);

        EXPECT_EQ(mapOne[testKey], testValue); 
    }
}

TEST(mymap, testBracketOp03)
{
    mymap <char, int> mapOne;

    char testKey = ' ';
    int testValue = -1;

    char letters[] = "abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0; i < 100; i++) 
    {
        testKey = letters[rand() % 26];
        testValue = rand();
        
        mapOne.put(testKey, testValue);

        EXPECT_EQ(mapOne[testKey], testValue); 
    }
}

// Test(s) sourced from: ulnu3
TEST (mymap , bracketsOperator)
{
    mymap <int , int > map1 ;
    map <int , int > solution ;
    int m = 0  ;  

    for (int i = 0 ; i < 1000; i++)
    {
        int n =  randomInteger(0, 500);
        m =  i + randomInteger(0, 10000);
        map1.put(n, m);
        solution [n] = m ;
    }

    for (int i = 0 ; i< 1000 ;i++)
    {
        EXPECT_EQ(map1[i], solution[i]);
    }
 
    mymap <float , int > map2 ;
    map <float , int > solution2 ;

    for (int i = 0 ; i < 1000; i++)
    {
        float n = (float) randomInteger(0, 500);
        m =  i + randomInteger(0, 10000);
        map2.put(n, m);
        solution2 [n] = m ;
    }

    for (int i = 0 ; i< 1000 ;i++)
    {
        EXPECT_EQ(map2[(float)i], solution2[(float)i]);
    }
 
    mymap <double , int > map3 ;
    map <double , int > solution3 ;

    for (int i = 0 ; i < 1000; i++)
    {
        double n = (double) randomInteger(0, 500);
        m =  i + randomInteger(0, 10000);
        map3.put(n, m);
        solution3 [n] = m ;
    }

    for (int i = 0 ; i< 1000 ;i++)
    {
        EXPECT_EQ(map3[(double)i], solution3[(double)i]);
    }
 
    mymap <char, int > map4;
    map <char, int > solution4;

    for (int i = 32 ; i < 127; i++)
    {
        char n = (char) randomInteger(32, 126);
        m =  i + randomInteger(0, 10000);
        map4.put(n, m);
        solution4 [n] = m ;
    }
    
    for (int i = 32 ; i< 127 ;i++)
    {
        EXPECT_EQ(map4[(char)i], solution4[(char)i]);
    }
}

// Test(s) sourced from: jbola6
TEST (testBracketOperator, subTestOneInt) 
{
    mymap<int, int> map;

    int arr[] = {2, 1, 3};

    for (int i = 0; i < 3; i++) 
    {
        map.put(arr[i], arr[i]);
    }

    for (int i = 0; i < 3; i++) 
    {
        EXPECT_EQ(map[arr[i]], arr[i]);
        EXPECT_FALSE(map[arr[i]] == 100);
        EXPECT_EQ(map.Size(), 3);
    }

    //so now lets look for something that does not exist
    EXPECT_FALSE(map.contains(77));

    //when using the [] we should get the default value
    EXPECT_EQ(map[77], int());

    //finally, now that we are checking if it exists, this should be true since the function above should have added it
    EXPECT_TRUE(map.contains(77));
}

// Test Purpose: ensure that ++ operator overload functions
TEST(mymap, testPlusPlusOp01)
{
    mymap<int, int> map;

    int arr[] = {2, 1, 3};

    int order[] = {1, 2, 3};

    for (int i = 0; i < 3; i++) 
    {
        map.put(arr[i], arr[i]);
    }

    int i = 0;

    for (auto key : map) 
    {
        EXPECT_EQ(order[i++], key);
    }
}

TEST(mymap, testPlusPlusOp02)
{
    mymap<int, string> map;

    int arr[] = {2, 1, 3};

    int order[] = {1, 2, 3};

    for (int i = 0; i < 3; i++) 
    {
        map.put(arr[i], to_string(arr[i]));
    }

    int i = 0;

    for (auto key : map) 
    {
        EXPECT_EQ(order[i++], key);
    }
}

// Test(s) sourced from: jbola6
TEST (testIteratorString, subTestFiveString) 
{
   mymap<string, int> map;
   //set up our map
   vector <string> hey = {"AAA", "BBB", "CCC"};

   for (int i = 0; i < 3; i++) 
   {
       map.put(hey[i], i);
   }
 
   //sort the vector
   sort(hey.begin(), hey.end());
 
   //loop and check if we are getting the same values as expected
   int i = 0;

   for (auto key : map) 
   {
       EXPECT_EQ(hey[i++], key);
   }
}

//Test(s) sourced from: ulnu3
TEST (mymap, iteratorForeachloop) 
{
    mymap<int, int> map;
    set <int > solution ;

    for (int i = 0; i < 10000; i++) 
    {
        int n = randomInteger(0, 10000);
        map.put(n, i+randomInteger(0, 10000));
        solution .insert(n );
    }

    for (auto key : map) 
    {
        EXPECT_TRUE(solution.find(key)!= solution.end() );
    }
 
    mymap<float, int> map2;
    set <float> solution2;

    for (int i = 0; i < 10000; i++) 
    {
        float n = (float)randomInteger(0, 10000);
        map2.put(n, i+randomInteger(0, 10000));
        solution2 .insert(n );
    }

    for (auto key : map2) 
    {
        EXPECT_TRUE(solution2.find(key)!= solution2.end() );
    }
 
    mymap<double, int> map3;
    set <double > solution3 ;

    for (int i = 0; i < 10000; i++) 
    {
        double n = (double)randomInteger(0, 10000);
        map3.put(n, i+randomInteger(0, 10000));
        solution3 .insert(n );
    }

    for (auto key : map3) 
    {
        EXPECT_TRUE(solution3.find(key)!= solution3.end() );
    }
 
    mymap<char, int> map4;
    set <char > solution4 ;

    for (int i = 0; i < 10000; i++) 
    {
        char n = randomInteger(32, 126);
        map4.put(n, i+randomInteger(0, 10000));
        solution4 .insert(n );
    }

    for (auto key : map4) 
    {
        EXPECT_TRUE(solution4.find(key)!= solution4.end() );
    }
}

// Test Purpose: ensure that the .clear() function, functions
TEST(mymap, testClear01)
{
    mymap <int, int> mapOne;

    int testKey = -1;
    int testValue = -1;
    
    for (int i = 0; i < 100; i++) 
    {
        testKey = rand();
        testValue = rand();

        mapOne.put(testKey, testValue);

        mapOne.clear();

        EXPECT_EQ(mapOne.Size(), 0);
    }
}

TEST(mymap, testClear02)
{
    mymap <int, char> map;

    int testKey = -1;
    char testValue = ' ';
    char letters[] = "abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = rand();
        testValue = letters[rand() % 26];

        map.put(testKey, testValue);

        map.clear();

        EXPECT_EQ(map.Size(), 0);
    }
}

TEST(mymap, testClear03)
{
    mymap <string, int> map;

    string testKey = to_string(-1);
    int testValue = -1;
    
    for (int i = 0; i < 250; i++) 
    {
        testKey = to_string(rand());
        testValue = rand();

        map.put(testKey, testValue);

        map.clear();

        EXPECT_EQ(map.Size(), 0);
    }
}

TEST(mymap, testClear04)
{
    mymap <double, double> mapOne;

    double testKey = -1.0;
    double testValue = -1.0;
    
    for (int i = 0; i < 100; i++) 
    {
        testKey = rand();
        testValue = rand();

        mapOne.put(testKey, testValue);

        mapOne.clear();

        EXPECT_EQ(mapOne.Size(), 0);
    }
}

// Test purpose: ensure that the equal operator overload, functions
TEST(mymap, testEqualOp01)
{
    mymap <int, int> mapOne;
    mymap <int, int> mapTwo;

    int testKey = -1;
    int testValue = -1;
    
    for (int i = 0; i < 100; i++) 
    {
        testKey = rand();
        testValue = rand();

        mapOne.put(testKey, testValue);

        mapOne = mapTwo;

        EXPECT_EQ(mapOne[testKey], mapTwo[testKey]);
    }
}

TEST(mymap, testEqualOp02)
{
    mymap <string, int> mapOne;
    mymap <string, int> mapTwo;

    string testKey = "";
    int testValue = -1;
    
    for (int i = 0; i < 100; i++) 
    {
        testKey = to_string(rand());
        testValue = rand();

        mapOne.put(testKey, testValue);

        mapOne = mapTwo;

        EXPECT_EQ(mapOne[testKey], mapTwo[testKey]);
    }
}

TEST(mymap, testEqualOp03)
{
    mymap <double, int> mapOne;
    mymap <double, int> mapTwo;

    double testKey = -1.0;
    int testValue = -1;
    
    for (int i = 0; i < 100; i++) 
    {
        testKey = rand();
        testValue = rand();

        mapOne.put(testKey, testValue);

        mapOne = mapTwo;

        EXPECT_EQ(mapOne[testKey], mapTwo[testKey]);
    }
}

TEST(mymap, testEqual04)
{
    mymap <char, int> mapOne;
    mymap <char, int> mapTwo;
    char letters[] = "abcdefghijklmnopqrstuvwxyz";

    char testKey = ' ';
    int testValue = -1;
    
    for (int i = 0; i < 100; i++) 
    {
        testKey = letters[rand() % 26];
        testValue = rand();

        mapOne.put(testKey, testValue);

        mapOne = mapTwo;

        EXPECT_EQ(mapOne[testKey], mapTwo[testKey]);
    }
}

// Test(s) sourced from: ulnu3
TEST (mymap, equalToOperator)
{
    mymap<int, int> map;

    for (int j = 0 ; j < 100; j++ )
    {
        for (int i = 0; i < 1000; i++) 
        {
            map.put(randomInteger(0, 10000) , randomInteger(0, 10000));
        }

        mymap<int , int > map2 ;

        for (int i = 0; i < 1000; i++) 
        {
            map2.put(randomInteger(0, 10000) , randomInteger(0, 10000));
        }
        map2 = map ;
        EXPECT_EQ(map2.toString(), map.toString()) ;
 
    }
    mymap<float, int> map3;

    for (int j = 0 ; j < 100 ; j++)
    {
        for (int i = 0; i < 1000; i++) 
        {
            map3.put((float)randomInteger(0, 10000) , randomInteger(0, 10000));
        }
        mymap<float , int > map4 ;
        for (int i = 0; i < 1000; i++) 
        {
            map4.put((float)randomInteger(0, 10000) , randomInteger(0, 10000));
        }
        map4  = map3;  
        EXPECT_EQ(map4.toString(), map3.toString()) ;
        EXPECT_EQ(map4.Size() , map3.Size() );
    }
 
    mymap<double, int> map5;

    for (int j = 0 ; j < 100 ; j++)
    {
        for (int i = 0; i < 1000; i++) 
        {
            map5.put((double)randomInteger(0, 10000) , randomInteger(0, 10000));
        }
        mymap<double , int > map6 ;

        for (int i = 0; i < 1000; i++) 
        {
            map6.put((double)randomInteger(0, 10000) , randomInteger(0, 10000));
        }

        map6 = map5 ;

        EXPECT_EQ(map6.toString(), map5.toString()) ;
        EXPECT_EQ(map6.Size() , map5.Size() );
    }
 
    mymap<char, int> map7;

    for (int j = 0 ; j < 100 ; j++)
    {
        for (int i = 0; i < 1000; i++) 
        {
            map7.put(randomInteger(32, 126) , randomInteger(0, 10000));
        }
        mymap<char , int > map8 ;

        for (int i = 0; i < 1000; i++) 
        {
            map8.put(randomInteger(32, 126) , randomInteger(0, 10000));
        }

        map8 = map7 ;  
        EXPECT_EQ(map8.toString(), map7.toString()) ;
        EXPECT_EQ(map8.Size() , map7.Size() );
    }
}

// Test(s) sourced from: ulnu3
TEST (mymap, toVector)
{
    for (int k = 0 ; k < 100 ; k++)
    {
 
        mymap <int, int > map1;

        map <int ,int > solution1;

        for (int i = 0 ; i < 1000; i++)
        {
            int n = randomInteger(0, 10000);
            int m = randomInteger(0, 10000);

            map1.put( n,m );

            solution1[n] = m ;
        }

        vector <pair<int, int> > vec1 = map1.toVector();
        vector <pair<int, int> > sol1;

        for (auto it : solution1)
        {
            pair <int , int> p(it.first, it.second);
            sol1.push_back(p);
        }
 
        EXPECT_EQ(vec1 ,sol1);
 
        mymap <float, int> map2;
        map <float, int> solution2;

        for (int i = 0 ; i < 1000; i++)
        {
            float n = (float)randomInteger(0, 10000);
            int m = randomInteger(0, 10000);

            map2.put( n,m );
            solution2[n] = m ;
        }
 
        vector<pair<float, int> > vec2 = map2.toVector();
        vector<pair<float, int> > sol2 ;

        for (auto it : solution2)
        {
            pair<int , int > p(it.first, it.second);
            sol2.push_back(p);
        }
 
        EXPECT_EQ(vec2, sol2);
 
        mymap <double, int> map3;
        map <double ,int> solution3;

        for (int i = 0 ; i < 1000; i++)
        {
            double n = (double)randomInteger(0, 10000);
            int m = randomInteger(0, 10000);
            map3.put( n,m );
            solution3[n] = m ;
        }

        vector<pair<double, int> > vec3 = map3.toVector();
        vector<pair<double, int> > sol3 ;

        for (auto it : solution3)
        {
            pair<int, int> p(it.first, it.second);
            sol3.push_back(p);
        }
 
        EXPECT_EQ(vec3, sol3);
 
        mymap <char, int> map4 ;
        map <char , int> solution4 ;

        for(int i = 0 ; i < 1000; i++)
        {
            char n = randomInteger(32, 126);
            int m = randomInteger(0, 10000);

            map4.put(n, m);
            solution4[n] = m ;
        }

        vector<pair<char, int> > vec4 = map4.toVector();
        vector<pair<char, int> > sol4;

        for (auto it : solution4)
        {
            pair<int , int > p(it.first, it.second);
            sol4.push_back(p);
        }
 
        EXPECT_EQ(vec4 ,sol4);
    }
}

// Test(s) sourced from: hvu28
TEST(stress, randomStressTest)
{
    mymap<int, string> m;
    mymap<int, string> m2;

    int randomSize = randomInteger(500, 3000);
    int randomKey;
    string randomValue;

    for (int i = 0; i < randomSize; i++)
    {
        randomKey = randomInteger(0, 10000);
        randomValue = randomInteger(1, 1000);

        m.put(randomKey, randomValue);
        m2.put(randomKey, randomValue);
    }

    ASSERT_EQ(m.Size(), m2.Size());
    ASSERT_EQ(m.toString(), m2.toString());
    ASSERT_EQ(m.toVector(), m2.toVector());

    for (auto k : m)
    {
        ASSERT_EQ(m2[k], m[k]);
    }

    mymap<int, string> m3 = m2;

    m2.clear();

    for (auto k : m3)
    {
        ASSERT_EQ(m3[k], m[k]);
    }

    EXPECT_EQ(m3.toString(), m.toString());
    ASSERT_EQ(m.toVector(), m3.toVector());
}

// TEST(mymap, testTemplate00)
// {

// }

// This main function will execute all tests
int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
