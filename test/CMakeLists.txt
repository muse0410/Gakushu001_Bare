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
)

# 自分のコードのヘッダ場所を教える
target_include_directories(unit_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../interface
    ${CMAKE_CURRENT_SOURCE_DIR}/../driver
)

# GTestをリンク
target_link_libraries(unit_tests GTest::gtest_main)

# CTestを有効化（VS Codeのテストエクスプローラー用）
include(CTest)
add_test(NAME MySensorTest COMMAND unit_tests)