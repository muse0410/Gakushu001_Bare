cmake_minimum_required(VERSION 3.10)
project(Gakushu_Tests)

# GoogleTestを自動取得するためのFetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# テスト実行ファイルの定義
add_executable(unit_tests 
    test_main.cpp
    # テストしたいソースを追加（ただしハードウェア非依存なもの）
    ../driver/sht31/SHT31.cpp
)

# 自分のコードのヘッダ場所を教える
target_include_directories(unit_tests PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/../interface"
    "${CMAKE_CURRENT_SOURCE_DIR}/../driver/sht31"
)

# GTestをリンク
# ★ここが重要：gtest だけでなく gmock もリンクする
target_link_libraries(unit_tests PRIVATE 
    gtest_main 
    gmock       # これが必要！
)

# CTestを有効化（VS Codeのテストエクスプローラー用）
include(CTest)
add_test(NAME MySensorTest COMMAND unit_tests)