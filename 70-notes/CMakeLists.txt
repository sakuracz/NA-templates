add_executable(71-var
    71-varTemp.cpp
)

add_custom_target(run-71-var
    DEPENDS 71-var
    COMMAND ./71-var
)

add_executable(72-tempSemant
    72-tempSemant.cpp
)

add_custom_target(run-72-tempSemant
    DEPENDS 72-tempSemant
    COMMAND ./72-tempSemant
)

add_custom_target(run-70-all)
add_dependencies(run-70-all
    run-71-var
    run-72-tempSemant
)

add_dependencies(run-all
    run-70-all
)
