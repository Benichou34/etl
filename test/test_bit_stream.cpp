/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl
https://www.etlcpp.com

Copyright(c) 2018 jwellbelove

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#include "UnitTest++.h"

#include "etl/bit_stream.h"

#include <array>
#include <numeric>

namespace
{
  SUITE(test_bit_stream)
  {
    //*************************************************************************
    TEST(put_bool)
    {
      unsigned char storage = 0;
      unsigned char compare_data = 0x5A;
      
      etl::bit_stream bit_stream(&storage, 1);
      bit_stream.clear();

      CHECK(bit_stream.put(false));
      CHECK(bit_stream.put(true));
      CHECK(bit_stream.put(false));
      CHECK(bit_stream.put(true));
      CHECK(bit_stream.put(true));
      CHECK(bit_stream.put(false));
      CHECK(bit_stream.put(true));
      CHECK(bit_stream.put(false));

      // One too many.
      CHECK(!bit_stream.put(true));

      CHECK_EQUAL(int(compare_data), int(storage));
    }

    //*************************************************************************
    TEST(put_int8_t)
    {
      std::array<unsigned char, 256> storage;

      std::array<unsigned char, 256> compare_data;
      std::iota(compare_data.begin(), compare_data.end(), 0);

      etl::bit_stream bit_stream(storage.data(), storage.size());
      bit_stream.clear();

      for (size_t i = 0; i < 256; ++i)
      {
        CHECK(bit_stream.put(int8_t(i)));
      }

      // One too many.
      CHECK(!bit_stream.put(int8_t(0)));

      for (size_t i = 0; i < storage.size(); ++i)
      {
        CHECK_EQUAL(int(compare_data[i]), int(storage[i]));
      }
    }

    //*************************************************************************
    TEST(put_uint8_t)
    {
      std::array<unsigned char, 256> storage;

      std::array<unsigned char, 256> compare_data;
      std::iota(compare_data.begin(), compare_data.end(), 0);

      etl::bit_stream bit_stream(storage.data(), storage.size());
      bit_stream.clear();

      for (size_t i = 0; i < 256; ++i)
      {
        CHECK(bit_stream.put(uint8_t(i)));
      }

      // One too many.
      CHECK(!bit_stream.put(uint8_t(0)));

      for (size_t i = 0; i < storage.size(); ++i)
      {
        CHECK_EQUAL(int(compare_data[i]), int(storage[i]));
      }
    }

    //*************************************************************************
    TEST(put_int16_t)
    {
      // Tests assume big endian.
      std::array<unsigned char, sizeof(int16_t) * 4> storage;
      std::array<unsigned char, sizeof(int16_t) * 4> compare_data = { 0x00, 0x01, 0x5A, 0xA5, 0xA5, 0x5A, 0xFF, 0xFF };

      CHECK(compare_data.size() == storage.size());

      etl::bit_stream bit_stream(storage.data(), storage.size());
      bit_stream.clear();

      CHECK(bit_stream.put(int16_t(0x0001)));
      CHECK(bit_stream.put(int16_t(0x5AA5)));
      CHECK(bit_stream.put(int16_t(0xA55A)));
      CHECK(bit_stream.put(int16_t(0xFFFF)));

      // One too many.
      CHECK(!bit_stream.put(int16_t(0)));

      for (size_t i = 0; i < storage.size(); ++i)
      {
        CHECK_EQUAL(int(compare_data[i]), int(storage[i]));
      }
    }

    //*************************************************************************
    TEST(put_uint16_t)
    {
      // Tests assume big endian.
      std::array<unsigned char, sizeof(uint16_t) * 4> storage;
      std::array<unsigned char, sizeof(uint16_t) * 4> compare_data = { 0x00, 0x01, 0x5A, 0xA5, 0xA5, 0x5A, 0xFF, 0xFF };

      CHECK(compare_data.size() == storage.size());

      etl::bit_stream bit_stream(storage.data(), storage.size());
      bit_stream.clear();

      CHECK(bit_stream.put(uint16_t(0x0001)));
      CHECK(bit_stream.put(uint16_t(0x5AA5)));
      CHECK(bit_stream.put(uint16_t(0xA55A)));
      CHECK(bit_stream.put(uint16_t(0xFFFF)));

      // One too many.
      CHECK(!bit_stream.put(uint16_t(0)));

      for (size_t i = 0; i < storage.size(); ++i)
      {
        CHECK_EQUAL(int(compare_data[i]), int(storage[i]));
      }
    }

    //*************************************************************************
    TEST(put_int32_t)
    {
      // Tests assume big endian.
      std::array<unsigned char, sizeof(int32_t) * 4> storage;
      std::array<unsigned char, sizeof(int32_t) * 4> compare_data = { 0x00, 0x00, 0x00, 0x01, 
                                                                      0x5A, 0xA5, 0xA5, 0x5A,
                                                                      0xA5, 0x5A, 0x5A, 0xA5,
                                                                      0xFF, 0xFF, 0xFF, 0xFF };

      CHECK(compare_data.size() == storage.size());

      etl::bit_stream bit_stream(storage.data(), storage.size());
      bit_stream.clear();

      CHECK(bit_stream.put(int32_t(0x00000001)));
      CHECK(bit_stream.put(int32_t(0x5AA5A55A)));
      CHECK(bit_stream.put(int32_t(0xA55A5AA5)));
      CHECK(bit_stream.put(int32_t(0xFFFFFFFF)));

      // One too many.
      CHECK(!bit_stream.put(int32_t(0)));

      for (size_t i = 0; i < storage.size(); ++i)
      {
        CHECK_EQUAL(int(compare_data[i]), int(storage[i]));
      }
    }

    //*************************************************************************
    TEST(put_uint32_t)
    {
      // Tests assume big endian.
      std::array<unsigned char, sizeof(uint32_t) * 4> storage;
      std::array<unsigned char, sizeof(uint32_t) * 4> compare_data = { 0x00, 0x00, 0x00, 0x01, 
                                                                       0x5A, 0xA5, 0xA5, 0x5A,
                                                                       0xA5, 0x5A, 0x5A, 0xA5,
                                                                       0xFF, 0xFF, 0xFF, 0xFF };

      CHECK(compare_data.size() == storage.size());

      etl::bit_stream bit_stream(storage.data(), storage.size());
      bit_stream.clear();

      CHECK(bit_stream.put(uint32_t(0x00000001)));
      CHECK(bit_stream.put(uint32_t(0x5AA5A55A)));
      CHECK(bit_stream.put(uint32_t(0xA55A5AA5)));
      CHECK(bit_stream.put(uint32_t(0xFFFFFFFF)));

      // One too many.
      CHECK(!bit_stream.put(uint32_t(0)));

      for (size_t i = 0; i < storage.size(); ++i)
      {
        CHECK_EQUAL(int(compare_data[i]), int(storage[i]));
      }
    }

    //*************************************************************************
    TEST(put_float)
    {
      // Tests assume little endian.
      std::array<unsigned char, sizeof(float) * 4> storage;

      etl::bit_stream bit_stream(storage.data(), storage.size());
      bit_stream.clear();

      float fmax = std::numeric_limits<float>::max();
      unsigned char* cfmax = reinterpret_cast<unsigned char*>(&fmax);

      float fmin = std::numeric_limits<float>::min();
      unsigned char* cfmin = reinterpret_cast<unsigned char*>(&fmin);

      float flowest = std::numeric_limits<float>::lowest();
      unsigned char* cflowest = reinterpret_cast<unsigned char*>(&flowest);

      float fpi = 3.1415927f;
      unsigned char* cfpi = reinterpret_cast<unsigned char*>(&fpi);

      CHECK(bit_stream.put(fmax));
      CHECK(bit_stream.put(fmin));
      CHECK(bit_stream.put(flowest));
      CHECK(bit_stream.put(fpi));

      // One too many.
      CHECK(!bit_stream.put(0.0f));

      // Check max
      unsigned char* pdata = storage.data();

      for (int i = 0, j = (sizeof(float) - 1); i < sizeof(float); ++i, --j)
      {
        CHECK_EQUAL(int(cfmax[j]), int(pdata[i]));
      }

      // Check min
      pdata += sizeof(float);

      for (int i = 0, j = (sizeof(float) - 1); i < sizeof(float); ++i, --j)
      {
        CHECK_EQUAL(int(cfmin[j]), int(pdata[i]));
      }

      // Check lowest
      pdata += sizeof(float);

      for (int i = 0, j = (sizeof(float) - 1); i < sizeof(float); ++i, --j)
      {
        CHECK_EQUAL(int(cflowest[j]), int(pdata[i]));
      }

      // Check PI
      pdata += sizeof(float);

      for (int i = 0, j = (sizeof(float) - 1); i < sizeof(float); ++i, --j)
      {
        CHECK_EQUAL(int(cfpi[j]), int(pdata[i]));
      }
    }

    //*************************************************************************
    TEST(put_double)
    {
      // Tests assume little endian.
      std::array<unsigned char, sizeof(double) * 4> storage;

      etl::bit_stream bit_stream(storage.data(), storage.size());
      bit_stream.clear();

      double fmax = std::numeric_limits<double>::max();
      unsigned char* cfmax = reinterpret_cast<unsigned char*>(&fmax);

      double fmin = std::numeric_limits<double>::min();
      unsigned char* cfmin = reinterpret_cast<unsigned char*>(&fmin);

      double flowest = std::numeric_limits<double>::lowest();
      unsigned char* cflowest = reinterpret_cast<unsigned char*>(&flowest);

      double fpi = 3.1415927;
      unsigned char* cfpi = reinterpret_cast<unsigned char*>(&fpi);

      CHECK(bit_stream.put(fmax));
      CHECK(bit_stream.put(fmin));
      CHECK(bit_stream.put(flowest));
      CHECK(bit_stream.put(fpi));

      // One too many.
      CHECK(!bit_stream.put(0.0));

      // Check max
      unsigned char* pdata = storage.data();

      for (int i = 0, j = (sizeof(double) - 1); i < sizeof(double); ++i, --j)
      {
        CHECK_EQUAL(int(cfmax[j]), int(pdata[i]));
      }

      // Check min
      pdata += sizeof(double);

      for (int i = 0, j = (sizeof(double) - 1); i < sizeof(double); ++i, --j)
      {
        CHECK_EQUAL(int(cfmin[j]), int(pdata[i]));
      }

      // Check lowest
      pdata += sizeof(double);

      for (int i = 0, j = (sizeof(double) - 1); i < sizeof(double); ++i, --j)
      {
        CHECK_EQUAL(int(cflowest[j]), int(pdata[i]));
      }

      // Check PI
      pdata += sizeof(double);

      for (int i = 0, j = (sizeof(double) - 1); i < sizeof(double); ++i, --j)
      {
        CHECK_EQUAL(int(cfpi[j]), int(pdata[i]));
      }
    }

    //*************************************************************************
    TEST(put_long_double)
    {
      // Tests assume little endian.
      std::array<unsigned char, sizeof(long double) * 4> storage;

      etl::bit_stream bit_stream(storage.data(), storage.size());
      bit_stream.clear();

      long double fmax = std::numeric_limits<long double>::max();
      unsigned char* cfmax = reinterpret_cast<unsigned char*>(&fmax);

      long double fmin = std::numeric_limits<long double>::min();
      unsigned char* cfmin = reinterpret_cast<unsigned char*>(&fmin);

      long double flowest = std::numeric_limits<long double>::lowest();
      unsigned char* cflowest = reinterpret_cast<unsigned char*>(&flowest);

      long double fpi = 3.1415927L;
      unsigned char* cfpi = reinterpret_cast<unsigned char*>(&fpi);

      CHECK(bit_stream.put(fmax));
      CHECK(bit_stream.put(fmin));
      CHECK(bit_stream.put(flowest));
      CHECK(bit_stream.put(fpi));

      // One too many.
      CHECK(!bit_stream.put(0.0));

      // Check max
      unsigned char* pdata = storage.data();

      for (int i = 0, j = (sizeof(long double) - 1); i < sizeof(long double); ++i, --j)
      {
        CHECK_EQUAL(int(cfmax[j]), int(pdata[i]));
      }

      // Check min
      pdata += sizeof(long double);

      for (int i = 0, j = (sizeof(long double) - 1); i < sizeof(long double); ++i, --j)
      {
        CHECK_EQUAL(int(cfmin[j]), int(pdata[i]));
      }

      // Check lowest
      pdata += sizeof(long double);

      for (int i = 0, j = (sizeof(long double) - 1); i < sizeof(long double); ++i, --j)
      {
        CHECK_EQUAL(int(cflowest[j]), int(pdata[i]));
      }

      // Check PI
      pdata += sizeof(long double);

      for (int i = 0, j = (sizeof(long double) - 1); i < sizeof(long double); ++i, --j)
      {
        CHECK_EQUAL(int(cfpi[j]), int(pdata[i]));
      }
    }

    //*************************************************************************
    TEST(put_get_bool)
    {
      std::array<bool, 8> flags =
      {
        false, true, false, true, true, false, true, false
      };

      unsigned char storage = 0;
      etl::bit_stream bit_stream(&storage, 1);
      bit_stream.clear();

      for (size_t i = 0; i < flags.size(); ++i)
      {
        bit_stream.put(flags[i]);
      }

      bit_stream.restart();

      for (size_t i = 0; i < flags.size(); ++i)
      {
        bool flag;
        CHECK(bit_stream.get(flag));
        CHECK_EQUAL(flags[i], flag);
      }
    }

    //*************************************************************************
    TEST(put_get_int8_t)
    {
      std::array<unsigned char, 4> storage;
      std::array<int8_t, 4> put_data = { int8_t(0x01), int8_t(0x5A), int8_t(0xA5), int8_t(0xFF) };
      std::array<int8_t, 4> get_data = { int8_t(0x00), int8_t(0x00), int8_t(0x00), int8_t(0x00) };

      etl::bit_stream bit_stream(storage.data(), storage.size());
      bit_stream.clear();

      // Insert into the stream
      bit_stream.put(put_data[0]);
      bit_stream.put(put_data[1]);
      bit_stream.put(put_data[2]);
      bit_stream.put(put_data[3]);

      bit_stream.restart();

      CHECK(bit_stream.get(get_data[0]));
      CHECK(bit_stream.get(get_data[1]));
      CHECK(bit_stream.get(get_data[2]));
      CHECK(bit_stream.get(get_data[3]));
    }

    //*************************************************************************
    TEST(put_get_int8_t_5bits)
    {
      std::array<unsigned char, 4> storage;
      std::array<int8_t, 4> put_data    = { int8_t(0x01), int8_t(0x15), int8_t(0x0A), int8_t(0x1F) }; // 1, -11, 10, -1
      std::array<int8_t, 4> expect_data = { int8_t(0x01), int8_t(0xF5), int8_t(0x0A), int8_t(0xFF) }; // 1, -11, 10, -1
      std::array<int8_t, 4> get_data    = { int8_t(0x00), int8_t(0x00), int8_t(0x00), int8_t(0x00) };

      etl::bit_stream bit_stream(storage.data(), storage.size());
      bit_stream.clear();

      // Insert into the stream
      bit_stream.put(put_data[0], 5);
      bit_stream.put(put_data[1], 5);
      bit_stream.put(put_data[2], 5);
      bit_stream.put(put_data[3], 5);

      bit_stream.restart();

      CHECK(bit_stream.get(get_data[0], 5));
      CHECK_EQUAL((int)expect_data[0], (int)get_data[0]);

      CHECK(bit_stream.get(get_data[1], 5));
      CHECK_EQUAL((int)expect_data[1], (int)get_data[1]);

      CHECK(bit_stream.get(get_data[2], 5));
      CHECK_EQUAL((int)expect_data[2], (int)get_data[2]);

      CHECK(bit_stream.get(get_data[3], 5));
      CHECK_EQUAL((int)expect_data[3], (int)get_data[3]);
    }
  };
}
