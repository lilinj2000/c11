// Copyright (c) 2010
// All rights reserved.


#include <unordered_set>
#include "gtest/gtest.h"

class CMarketDataUpdateTimeField {
 public:
  char InstrumentID[31];
  char UpdateTime[9];
  int  UpdateMillisec;
  char ActionDay[9];
};

struct Hash_CMarketDataUpdateTimeField {
  size_t operator()(const CMarketDataUpdateTimeField &field) const {
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&field);
    std::size_t h = 2166136261;

    for (unsigned int i = 0; i < sizeof(CMarketDataUpdateTimeField); ++i)
      h = (h * 16777619) ^ p[i];

    return h;
  }
};

struct Equal_CMarketDataUpdateTimeField {
  bool operator()(const CMarketDataUpdateTimeField &left,
                  const CMarketDataUpdateTimeField &right) const {
    return 0 == memcmp(&left, &right, sizeof(CMarketDataUpdateTimeField));
  }
};

TEST(SetTest, UnorderedSetTest) {
  std::unordered_set<CMarketDataUpdateTimeField,
                     Hash_CMarketDataUpdateTimeField,
                     Equal_CMarketDataUpdateTimeField> md_set;

  CMarketDataUpdateTimeField md1 = {"cu1605", "10:10:20", 0, "20160714"};
  CMarketDataUpdateTimeField md2 = {"cu1606", "10:10:20", 0, "20160714"};
  md_set.insert(md1);

  ASSERT_EQ(md_set.count(md1), 1);
  ASSERT_EQ(md_set.count(md2), 0);
}
