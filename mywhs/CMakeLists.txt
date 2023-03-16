project(mywhs)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(HEADER_FILES
    list/node/node.h
    list/list/list.h
    whs/whs.h
    whs/utils/utils.h
    whs/whs_p/whc_p.h)

set(SOURCE_FILES
    list/node/node.c
    list/list/list.c
    whs/whs/whs_1t.c
    whs/utils/utils.c
    whs/whs_p/whc_p.c
    whs/whs/whs_mt.c)

add_library(mywhs STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(mywhs)

