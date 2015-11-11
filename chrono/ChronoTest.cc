#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

#include "gtest/gtest.h"


class ChronoTest : public ::testing::Test
{
public:
  ChronoTest()
  {
  }

  void SetUp()
  {
  }

  void TearDown()
  {
  }

 protected:

};


TEST_F(ChronoTest, chronoTest)
{
  using std::chrono::system_clock;
  
  system_clock::time_point cur_time = system_clock::now();

  auto tt = system_clock::to_time_t( cur_time );

  std::cout <<std::ctime( &tt ) <<std::endl;

  
  // std::cout <<cur_time.toString() <<std::endl;
  
  // std::cout <<cur_time <<std::endl;

  // SOIL_DEBUG <<cur_time;

  // Chrono cur_time2("10:10:20");
  // std::cout <<cur_time2 <<std::endl;
  
  ASSERT_TRUE( true );
}

TEST_F(ChronoTest, durationTest)
{
  {  // duration constructor
    typedef std::chrono::duration<int> seconds_type;
    typedef std::chrono::duration<int,std::milli> milliseconds_type;
    typedef std::chrono::duration<int,std::ratio<60*60>> hours_type;

    hours_type h_oneday (24);                  // 24h
    seconds_type s_oneday (60*60*24);          // 86400s
    milliseconds_type ms_oneday (s_oneday);    // 86400000ms

    seconds_type s_onehour (60*60);            // 3600s
    // hours_type h_onehour (s_onehour);          // NOT VALID (type truncates), use:
    hours_type h_onehour (std::chrono::duration_cast<hours_type>(s_onehour));
    milliseconds_type ms_onehour (s_onehour);  // 3600000ms (ok, no type truncation)

    std::cout << ms_onehour.count() << "ms in 1h" << std::endl;

    ASSERT_EQ( ms_onehour.count(), 3600000 );
  }

  {
    // duration cast
    std::chrono::seconds s (1);             // 1 second
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds> (s);
    ms += std::chrono::milliseconds(2500);  // 2500 millisecond
  
    s = std::chrono::duration_cast<std::chrono::seconds> (ms);   // truncated

    std::cout << "ms: " << ms.count() << std::endl;
    std::cout << "s: " << s.count() << std::endl;

    ASSERT_EQ( ms.count(), 3500 );
    ASSERT_EQ( s.count(), 3 );
  }

  {
    // duration::count
    using namespace std::chrono;

    // std::chrono::milliseconds is an instatiation of std::chrono::duration:
    milliseconds foo (1000); // 1 second
    foo*=60;

    std::cout << "duration (in periods): ";
    std::cout << foo.count() << " milliseconds.\n";
    
    std::cout << "duration (in seconds): ";
    std::cout << foo.count() * milliseconds::period::num / milliseconds::period::den;
    std::cout << " seconds.\n";

    ASSERT_EQ( foo.count(), 60000 );
    
  }
}

// TEST_F(ChronoTest, operatorTest)
// {
//   Chrono cur_time;
  
//   std::cout <<cur_time <<std::endl;
  
//   cur_time = cur_time + milliseconds(100);

//   std::cout <<cur_time <<std::endl;

//   cur_time += seconds(20);
//   std::cout <<cur_time <<std::endl;

//   Chrono cur_time2;
//   time_duration d = cur_time - cur_time2;

//   std::cout <<d.total_seconds() <<" seconds." <<std::endl;

//   ASSERT_TRUE( true );
// }


