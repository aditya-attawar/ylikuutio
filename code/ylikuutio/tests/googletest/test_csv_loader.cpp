#include "gtest/gtest.h"
#include "code/ylikuutio/load/csv_loader.hpp"
#include "code/ylikuutio/linear_algebra/matrix.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <limits>  // std::numeric_limits
#include <memory>  // std::make_shared, std::shared_ptr
#include <string>  // std::string
#include <vector>  // std::vector

TEST(csv_file_must_be_loaded_appropriately, some_finnish_railway_stations_float)
{
    const std::string some_finnish_railway_stations_csv_filename = "some_finnish_railway_stations_float.csv";
    std::size_t data_width;
    std::size_t data_height;
    std::size_t data_size;
    std::shared_ptr<std::vector<float>> data_vector = yli::load::load_CSV_file<float>(some_finnish_railway_stations_csv_filename, data_width, data_height, data_size);
    ASSERT_NE(data_vector, nullptr);

    ASSERT_EQ(data_width, 17);
    ASSERT_EQ(data_height, 17);
    ASSERT_EQ(data_size, 17 * 17);

    yli::linear_algebra::Matrix railway_neighbors_from_csv_file(17, 17);
    ASSERT_TRUE(railway_neighbors_from_csv_file.get_is_square());
    ASSERT_EQ(railway_neighbors_from_csv_file.get_height(), 17);
    ASSERT_EQ(railway_neighbors_from_csv_file.get_height(), 17);

    railway_neighbors_from_csv_file << *data_vector;

#define INF std::numeric_limits<float>::infinity()

    yli::linear_algebra::Matrix railway_neighbors(17, 17);
    railway_neighbors << std::vector<float> {
//      Hpk,    Ilm,    Jns,     Jy,     Ke,     Kv,     Lh,     Ov,     Ol,     Ri,    Psl,     Pm,     Sk,    Tpe,     Tl,    Tku,     Yv
       0.0f,    INF,    INF,  78.0f,    INF,    INF,    INF,  72.0f,    INF,    INF,    INF,    INF, 118.0f,    INF,    INF,    INF,    INF,   // Hpk
        INF,   0.0f,    INF,    INF,    INF,    INF,    INF,    INF, 275.0f,    INF,    INF, 174.0f,    INF,    INF,    INF,    INF, 154.0f,   // Ilm
        INF,    INF,   0.0f,    INF,    INF, 316.0f,    INF,    INF,    INF,    INF,    INF, 183.0f,    INF,    INF,    INF,    INF,    INF,   // Jns
      78.0f,    INF,    INF,   0.0f,    INF,    INF,    INF, 113.0f,    INF,    INF,    INF,  80.0f,    INF,    INF,    INF,    INF,    INF,   // Jy
        INF,    INF,    INF,    INF,   0.0f,    INF,  75.0f,    INF,    INF,  42.0f,  26.0f,    INF,    INF,    INF,    INF,    INF,    INF,   // Ke
        INF,    INF, 316.0f,    INF,    INF,   0.0f,  62.0f,    INF,    INF,    INF,    INF, 184.0f,    INF,    INF,    INF,    INF,    INF,   // Kv
        INF,    INF,    INF,    INF,  75.0f,  62.0f,   0.0f,    INF,    INF,  59.0f,    INF,    INF,    INF,    INF,    INF,    INF,    INF,   // Lh
      72.0f,    INF,    INF, 113.0f,    INF,    INF,    INF,   0.0f,    INF,    INF,    INF,    INF,    INF,  42.0f,    INF,    INF,    INF,   // Ov
        INF, 275.0f,    INF,    INF,    INF,    INF,    INF,    INF,   0.0f,    INF,    INF,    INF,    INF,    INF,    INF,    INF, 122.0f,   // Ol
        INF,    INF,    INF,    INF,  42.0f,    INF,  59.0f,    INF,    INF,   0.0f,    INF,    INF,    INF,    INF,  76.0f,    INF,    INF,   // Ri
        INF,    INF,    INF,    INF,  26.0f,    INF,    INF,    INF,    INF,    INF,   0.0f,    INF,    INF,    INF,    INF, 191.0f,    INF,   // Psl
        INF, 174.0f, 183.0f,  80.0f,    INF, 184.0f,    INF,    INF,    INF,    INF,    INF,   0.0f,    INF,    INF,    INF,    INF,    INF,   // Pm
     118.0f,    INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,   0.0f, 160.0f,    INF,    INF, 211.0f,   // Sk
        INF,    INF,    INF,    INF,    INF,    INF,    INF,  42.0f,    INF,    INF,    INF,    INF, 160.0f,   0.0f,  40.0f,    INF,    INF,   // Tpe
        INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,  76.0f,    INF,    INF,    INF,  40.0f,   0.0f, 128.0f,    INF,   // Tl
        INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF, 191.0f,    INF,    INF,    INF, 128.0f,   0.0f,    INF,   // Tku
        INF, 154.0f,    INF,    INF,    INF,    INF,    INF,    INF, 122.0f,    INF,    INF,    INF, 211.0f,    INF,    INF,    INF,   0.0f }; // Yv

#undef INF

    ASSERT_EQ(railway_neighbors_from_csv_file, railway_neighbors);
}

TEST(csv_file_must_be_loaded_appropriately, some_finnish_railway_stations_int32_t)
{
    const std::string some_finnish_railway_stations_csv_filename = "some_finnish_railway_stations_integer.csv";
    std::size_t data_width;
    std::size_t data_height;
    std::size_t data_size;
    std::shared_ptr<std::vector<int32_t>> data_vector = yli::load::load_CSV_file<int32_t>(some_finnish_railway_stations_csv_filename, data_width, data_height, data_size);
    ASSERT_NE(data_vector, nullptr);

    ASSERT_EQ(data_width, 17);
    ASSERT_EQ(data_height, 17);
    ASSERT_EQ(data_size, 17 * 17);

    std::vector<int32_t> railway_neighbors  {
//   Hpk, Ilm, Jns,  Jy,  Ke,  Kv,  Lh,  Ov,  Ol,  Ri, Psl,  Pm,  Sk, Tpe,  Tl, Tku,  Yv
       0,  -1,  -1,  78,  -1,  -1,  -1,  72,  -1,  -1,  -1,  -1, 118,  -1,  -1,  -1,  -1,   // Hpk
      -1,   0,  -1,  -1,  -1,  -1,  -1,  -1, 275,  -1,  -1, 174,  -1,  -1,  -1,  -1, 154,   // Ilm
      -1,  -1,   0,  -1,  -1, 316,  -1,  -1,  -1,  -1,  -1, 183,  -1,  -1,  -1,  -1,  -1,   // Jns
      78,  -1,  -1,   0,  -1,  -1,  -1, 113,  -1,  -1,  -1,  80,  -1,  -1,  -1,  -1,  -1,   // Jy
      -1,  -1,  -1,  -1,   0,  -1,  75,  -1,  -1,  42,  26,  -1,  -1,  -1,  -1,  -1,  -1,   // Ke
      -1,  -1, 316,  -1,  -1,   0,  62,  -1,  -1,  -1,  -1, 184,  -1,  -1,  -1,  -1,  -1,   // Kv
      -1,  -1,  -1,  -1,  75,  62,   0,  -1,  -1,  59,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   // Lh
      72,  -1,  -1, 113,  -1,  -1,  -1,   0,  -1,  -1,  -1,  -1,  -1,  42,  -1,  -1,  -1,   // Ov
      -1, 275,  -1,  -1,  -1,  -1,  -1,  -1,   0,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 122,   // Ol
      -1,  -1,  -1,  -1,  42,  -1,  59,  -1,  -1,   0,  -1,  -1,  -1,  -1,  76,  -1,  -1,   // Ri
      -1,  -1,  -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,   0,  -1,  -1,  -1,  -1, 191,  -1,   // Psl
      -1, 174, 183,  80,  -1, 184,  -1,  -1,  -1,  -1,  -1,   0,  -1,  -1,  -1,  -1,  -1,   // Pm
     118,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0, 160,  -1,  -1, 211,   // Sk
      -1,  -1,  -1,  -1,  -1,  -1,  -1,  42,  -1,  -1,  -1,  -1, 160,   0,  40,  -1,  -1,   // Tpe
      -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  76,  -1,  -1,  -1,  40,   0, 128,  -1,   // Tl
      -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 191,  -1,  -1,  -1, 128,   0,  -1,   // Tku
      -1, 154,  -1,  -1,  -1,  -1,  -1,  -1, 122,  -1,  -1,  -1, 211,  -1,  -1,  -1,   0 }; // Yv

    ASSERT_EQ(*data_vector, railway_neighbors);
}

TEST(csv_file_must_be_loaded_appropriately, some_finnish_railway_stations_uint32_t)
{
    const std::string some_finnish_railway_stations_csv_filename = "some_finnish_railway_stations_unsigned_integer.csv";
    std::size_t data_width;
    std::size_t data_height;
    std::size_t data_size;
    std::shared_ptr<std::vector<uint32_t>> data_vector = yli::load::load_CSV_file<uint32_t>(some_finnish_railway_stations_csv_filename, data_width, data_height, data_size);
    ASSERT_NE(data_vector, nullptr);

    ASSERT_EQ(data_width, 17);
    ASSERT_EQ(data_height, 17);
    ASSERT_EQ(data_size, 17 * 17);

    std::vector<uint32_t> railway_neighbors  {
//   Hpk,  Ilm,  Jns,   Jy,   Ke,   Kv,   Lh,   Ov,   Ol,   Ri,  Psl,   Pm,   Sk,  Tpe,   Tl,  Tku,   Yv
       0, 9999, 9999,   78, 9999, 9999, 9999,   72, 9999, 9999, 9999, 9999,  118, 9999, 9999, 9999, 9999,    // Hpk
    9999,    0, 9999, 9999, 9999, 9999, 9999, 9999,  275, 9999, 9999,  174, 9999, 9999, 9999, 9999,  154,    // Ilm
    9999, 9999,    0, 9999, 9999,  316, 9999, 9999, 9999, 9999, 9999,  183, 9999, 9999, 9999, 9999, 9999,    // Jns
      78, 9999, 9999,    0, 9999, 9999, 9999,  113, 9999, 9999, 9999,   80, 9999, 9999, 9999, 9999, 9999,    // Jy
    9999, 9999, 9999, 9999,    0, 9999,   75, 9999, 9999,   42,   26, 9999, 9999, 9999, 9999, 9999, 9999,    // Ke
    9999, 9999,  316, 9999, 9999,    0,   62, 9999, 9999, 9999, 9999,  184, 9999, 9999, 9999, 9999, 9999,    // Kv
    9999, 9999, 9999, 9999,   75,   62,    0, 9999, 9999,   59, 9999, 9999, 9999, 9999, 9999, 9999, 9999,    // Lh
      72, 9999, 9999,  113, 9999, 9999, 9999,    0, 9999, 9999, 9999, 9999, 9999,   42, 9999, 9999, 9999,    // Ov
    9999,  275, 9999, 9999, 9999, 9999, 9999, 9999,    0, 9999, 9999, 9999, 9999, 9999, 9999, 9999,  122,    // Ol
    9999, 9999, 9999, 9999,   42, 9999,   59, 9999, 9999,    0, 9999, 9999, 9999, 9999,   76, 9999, 9999,    // Ri
    9999, 9999, 9999, 9999,   26, 9999, 9999, 9999, 9999, 9999,    0, 9999, 9999, 9999, 9999,  191, 9999,    // Psl
    9999,  174,  183,   80, 9999,  184, 9999, 9999, 9999, 9999, 9999,    0, 9999, 9999, 9999, 9999, 9999,    // Pm
     118, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999,    0,  160, 9999, 9999,  211,    // Sk
    9999, 9999, 9999, 9999, 9999, 9999, 9999,   42, 9999, 9999, 9999, 9999,  160,    0,   40, 9999, 9999,    // Tpe
    9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999,   76, 9999, 9999, 9999,   40,    0,  128, 9999,    // Tl
    9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999,  191, 9999, 9999, 9999,  128,    0, 9999,    // Tku
    9999,  154, 9999, 9999, 9999, 9999, 9999, 9999,  122, 9999, 9999, 9999,  211, 9999, 9999, 9999,    0 }; // Yv

    ASSERT_EQ(*data_vector, railway_neighbors);
}
