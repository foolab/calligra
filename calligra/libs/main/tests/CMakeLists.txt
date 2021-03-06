set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )
include_directories( ${KOMAIN_INCLUDES} )

add_definitions(-DFILES_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data/")

########### next target ###############

set(priorityqueue_test_SRCS priorityqueue_test.cpp )
kde4_add_unit_test(priorityqueue_test TESTNAME libs-komain-priorityQueueTest ${priorityqueue_test_SRCS})
target_link_libraries(priorityqueue_test ${QT_QTTEST_LIBRARY} ${KDE4_KDECORE_LIBS})

########### next target ###############

set(filterchain_test_SRCS filterchain_test.cpp )
kde4_add_unit_test(filterchain_test TESTNAME libs-komain-filterchainTest ${filterchain_test_SRCS})
target_link_libraries(filterchain_test ${KDE4_KDECORE_LIBS}  komain )

########### next target ###############

set(filter_graph_SRCS filter_graph.cpp )
kde4_add_unit_test(filter_graph TESTNAME libs-komain-filterGraphTest ${filter_graph_SRCS})
target_link_libraries(filter_graph ${KDE4_KDECORE_LIBS}  komain )

########### next target ###############


set(rtreetestapp_SRCS rtreetestapp.cpp Tool.cpp )
kde4_add_executable(rtreetestapp TEST ${rtreetestapp_SRCS})
target_link_libraries(rtreetestapp komain ${QT_QTTEST_LIBRARY} )

########### next target ###############

set(documentstructuretest_SRCS documentstructuretest.cpp )
kde4_add_unit_test(DocumentStructureTest TESTNAME libs-komain-DocumentStructureTest ${documentstructuretest_SRCS})
target_link_libraries(DocumentStructureTest komain  ${QT_QTTEST_LIBRARY})

########### next target ###############

set(findmatch_test_SRCS testfindmatch.cpp )
kde4_add_unit_test(testfindmatch TESTNAME libs-komain-testfindmatch ${findmatch_test_SRCS})
target_link_libraries(testfindmatch komain ${QT_QTTEST_LIBRARY})

