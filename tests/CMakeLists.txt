add_custom_target(twisted_tests)

set(TESTS
        test_SimplifiedHarrisSpectrum
        )

message(STATUS "Listing twisted_tests :")
foreach(test ${TESTS})

    message(STATUS "...add ${test}")

    add_executable(${test} "${test}.cpp")
    target_link_libraries(${test} twisted_engine)

    add_dependencies(twisted_tests ${test})

endforeach()
