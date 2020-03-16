# - Try to find the LIBIGL library
# Once done this will define
#
#  LIBIGL_FOUND - system has LIBIGL
#  LIBIGL_INCLUDE_DIR - **the** LIBIGL include directory
if(LIBIGL_FOUND)
    return()
endif()

find_path(LIBIGL_INCLUDE_DIR igl/readOBJ.h # igl/readOBJ.hを探す 見つかるとLIBIGL_INCLUDE_DIRの変数が定義される
    HINTS
        ${LIBIGL_DIR}
        ENV LIBIGL_DIR #環境変数から読み込む
    PATH_SUFFIXES include # サブディレクトリincludeにもigl/readOBJ.hがあるかチェックする
)

include(FindPackageHandleStandardArgs) # cmakeのモジュールinclude
find_package_handle_standard_args(LIBIGL
    "\nlibigl not found --- You can download it using:\n\tgit clone https://github.com/libigl/libigl.git ${CMAKE_SOURCE_DIR}/../libigl"
    LIBIGL_INCLUDE_DIR) # LIBIGL_INCLUDE_DIRの値が有効ならLIBIGL_FOUNDの変数が定義される
mark_as_advanced(LIBIGL_INCLUDE_DIR) # advancedの状態を追加(GUIでadvanceオプション有効にしないと見えない変数になる)

list(APPEND CMAKE_MODULE_PATH "${LIBIGL_INCLUDE_DIR}/../cmake") # libiglのcmakeフォルダをリストに追加
include(libigl) # libigl.cmakeをinclude
